#include <jni.h>
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static jobject g_exec_callback;
static jobject g_busy_handler;
static jobject g_commit_hook;
static jobject g_rollback_hook;
static jobject g_trace_listener;
static jobject g_profile_listener;
static jobject g_update_hook;
static jobject g_authorizer;
static jobject g_collation;

static void _internal_free_all(JNIEnv *env)
{
  // 删除 conn 的 exec 的回调函数的全局引用
  if (g_exec_callback != 0)
  {
    (*env)->DeleteGlobalRef(env, g_exec_callback);
    g_exec_callback = 0;
  }

  // 删除 conn 的 Busyhandler 全局引用
  if (g_busy_handler != 0)
  {
    (*env)->DeleteGlobalRef(env, g_busy_handler);
    g_busy_handler = 0;
  }

  // 删除 conn 的 CommitHook 全局引用
  if (g_commit_hook != 0)
  {
    (*env)->DeleteGlobalRef(env, g_commit_hook);
    g_commit_hook = 0;
  }

  // 删除 conn 的 RollbackHook 全局引用
  if (g_rollback_hook != 0)
  {
    (*env)->DeleteGlobalRef(env, g_rollback_hook);
    g_rollback_hook = 0;
  }

  // 删除 conn 的 TraceListener 全局引用
  if (g_trace_listener != 0)
  {
    (*env)->DeleteGlobalRef(env, g_trace_listener);
    g_trace_listener = 0;
  }

  // 删除 conn 的 ProfileListener 全局引用
  if (g_profile_listener != 0)
  {
    (*env)->DeleteGlobalRef(env, g_profile_listener);
    g_profile_listener = 0;
  }

  // 删除 conn 的 UpdateHook 全局引用
  if (g_update_hook != 0)
  {
    (*env)->DeleteGlobalRef(env, g_update_hook);
    g_update_hook = 0;
  }

  // 删除 conn 的 Authorizer 全局引用
  if (g_authorizer != 0)
  {
    (*env)->DeleteGlobalRef(env, g_authorizer);
    g_authorizer = 0;
  }

  // 删除 conn 的 collation 全局引用
  if (g_collation != 0)
  {
    (*env)->DeleteGlobalRef(env, g_collation);
    g_collation = 0;
  }
}

static int exec_callback(void* data, int ncols, char** values, char** headers)
{
  if (g_exec_callback == 0)
  {
    return 0;
  }

  JNIEnv* env = getEnv();
  jobjectArray vs = createStringArray(env, values, ncols);
  jobjectArray hs = createStringArray(env, headers, ncols);
  jmethodID callbackMid = getSqlExecCallback(env);

  int rc = (*env)->CallIntMethod(env, g_exec_callback, callbackMid, ncols, vs,
                                 hs);

  (*env)->DeleteLocalRef(env, vs);
  (*env)->DeleteLocalRef(env, hs);
  return rc;
}

static int jni_busy_handler(void* data, int times)
{
  if (g_busy_handler == 0)
  {
    return 0;
  } else
  {
    return callBusyHandlerCallback(getEnv(), g_busy_handler, times);
  }
}

static int jni_commit_hook(void* conn)
{
  if (g_commit_hook == 0)
  {
    return 0;
  }

  JNIEnv* env = getEnv();
  int rs;
  jobject jConn = newDBConnection(env, (jlong) conn);

  rs = callCommitHookCallback(env, g_commit_hook, jConn);

  (*env)->DeleteGlobalRef(env, jConn);
  return rs;
}

static void jni_rollback_hook(void* conn)
{
  if (g_rollback_hook == 0)
  {
    return;
  }

  JNIEnv* env = getEnv();
  jobject jConn = newDBConnection(env, (jlong) conn);

  callRollbackHookCallback(env, g_rollback_hook, jConn);

  (*env)->DeleteGlobalRef(env, jConn);
}

static void _function_destroy_callback(void* data)
{
  if (data == 0)
  {
    return;
  }

  func_data* gData = (func_data*) data;
  JNIEnv* env = getEnv();

  (*env)->DeleteGlobalRef(env, gData->callback);

  if (gData->app)
  {
    (*env)->DeleteGlobalRef(env, gData->app);
  }

  free(gData); // 在堆上清除内存
}

static void _xFunc_callback(sqlite3_context* ctx, int n, sqlite3_value** values)
{
  JNIEnv* env = getEnv();
  func_data* data = (func_data*) sqlite3_user_data(ctx);
  jobjectArray array = newJavaliteValueArray(env, n, values);
  callScalarFunctionFuncMethod(env, data->callback,
                               newJavaliteContext(env, (jlong) ctx), array);
}

static void _xStep_callback(sqlite3_context* ctx, int n, sqlite3_value** values)
{
  JNIEnv* env = getEnv();
  func_data* data = (func_data*) sqlite3_user_data(ctx);
  jobjectArray array = newJavaliteValueArray(env, n, values);
  callAggregateFunctionStepMethod(env, data->callback,
                                  newJavaliteContext(env, (jlong) ctx), array);
}

static void _xFinal_callback(sqlite3_context* ctx)
{
  JNIEnv* env = getEnv();
  func_data* data = (func_data*) sqlite3_user_data(ctx);
  callAggregateFunctionFinalMethod(env, data->callback,
                                   newJavaliteContext(env, (jlong) ctx));
}

static void _internal_trace_callback(void* conn, const char* msg)
{
  if (g_trace_listener == 0)
  {
    return;
  }

  jlong connHandle = (jlong) conn;
  JNIEnv* env = getEnv();
  jobject jconn = newDBConnection(env, connHandle);
  jstring jmsg = (*env)->NewStringUTF(env, msg == 0 ? "" : msg);

  callTraceListenerCallback(env, g_trace_listener, jconn, jmsg);

  (*env)->DeleteLocalRef(env, jconn);
  (*env)->DeleteLocalRef(env, jmsg);
}

static void _internal_profile_callback(void* conn, const char* msg,
                                       sqlite3_uint64 nanoseconds)
{
  if (g_profile_listener == 0)
  {
    return;
  }

  jlong connHandle = (jlong) conn;
  JNIEnv* env = getEnv();
  jobject jconn = newDBConnection(env, connHandle);
  jstring jmsg = (*env)->NewStringUTF(env, msg == 0 ? "" : msg);

  callProfileListenerCallback(env, g_profile_listener, jconn, jmsg,
                              (jlong) nanoseconds);

  (*env)->DeleteLocalRef(env, jconn);
  (*env)->DeleteLocalRef(env, jmsg);
}

static void _internal_update_hook(void* data, int action, char const *db,
                                  char const *tb, sqlite3_int64 rowid)
{
  if (g_update_hook == 0)
  {
    return;
  }

  sqlite3* conn = (sqlite3*) data;
  JNIEnv* env = getEnv();

  jobject jconn = newDBConnection(env, (jlong) conn);
  jstring jdb = (*env)->NewStringUTF(env, db);
  jstring jtb = (*env)->NewStringUTF(env, tb);

  callUpdateHookCallback(env, g_update_hook, jconn, action, jdb, jtb, rowid);

  (*env)->DeleteLocalRef(env, jconn);
  (*env)->DeleteLocalRef(env, jdb);
  (*env)->DeleteLocalRef(env, jtb);
}

static int _internal_authorizer_callback(void* data, int action, const char* s1,
                                         const char* s2, const char* s3, const char* s4)
{
  if (g_authorizer == 0)
  {
    return SQLITE_OK;
  }

  sqlite3* conn = (sqlite3*) data;
  JNIEnv* env = getEnv();

  jobject jconn = newDBConnection(env, (jlong) conn);
  jstring js1 = s1 == 0 ? 0 : (*env)->NewStringUTF(env, s1);
  jstring js2 = s2 == 0 ? 0 : (*env)->NewStringUTF(env, s2);
  jstring js3 = s3 == 0 ? 0 : (*env)->NewStringUTF(env, s3);
  jstring js4 = s4 == 0 ? 0 : (*env)->NewStringUTF(env, s4);

  int rc = callAuthorizerCallback(env, g_authorizer, jconn, action, js1, js2, js3, js4);

  (*env)->DeleteLocalRef(env, jconn);
  if (js1 != 0)
  {
    (*env)->DeleteLocalRef(env, js1);
  }
  if (js2 != 0)
  {
    (*env)->DeleteLocalRef(env, js2);
  }
  if (js3 != 0)
  {
    (*env)->DeleteLocalRef(env, js3);
  }
  if (js4 != 0)
  {
    (*env)->DeleteLocalRef(env, js4);
  }

  return rc;
}

static int _internal_collation_compare(void* data, int countA, const void* bufA,
                                       int countB, const void* bufB)
{
  if (g_collation == 0)
  {
    return 0;
  }

  sqlite3* conn = (sqlite3*) data;
  JNIEnv* env = getEnv();

  jobject jconn = newDBConnection(env, (jlong) conn);
  jbyteArray arrayA = (*env)->NewByteArray(env, countA >= 0 ? countA : 0);
  jbyteArray arrayB = (*env)->NewByteArray(env, countB >= 0 ? countB : 0);

  if (countA > 0)
  {
    (*env)->SetByteArrayRegion(env, arrayA, 0, countA, (jbyte*) bufA);
  }

  if (countB > 0)
  {
    (*env)->SetByteArrayRegion(env, arrayB, 0, countB, (jbyte*) bufB);
  }

  int rc = callCollationCompareCallback(env, g_collation, jconn, arrayA, arrayB);

  (*env)->DeleteLocalRef(env, jconn);
  (*env)->DeleteLocalRef(env, arrayA);
  (*env)->DeleteLocalRef(env, arrayB);

  return rc;
}

static void _internal_collation_destroy(void* data)
{
  if (g_collation == 0)
  {
    return;
  }

  sqlite3* conn = (sqlite3*) data;
  JNIEnv* env = getEnv();
  jobject jconn = newDBConnection(env, (jlong) conn);

  callCollationDestroyCallback(env, g_collation, jconn);

  (*env)->DeleteLocalRef(env, jconn);
}

///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////

static jlong Java_sqlite3_prepare_v2
(JNIEnv *env, jclass cls, jlong handle, jstring sql)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  if (sql == 0)
  {
    throwSqliteException(env, "sql is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;
  const char* csql = (*env)->GetStringUTFChars(env, sql, 0);
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v2(conn, csql, -1, &stmt, NULL);

  (*env)->ReleaseStringUTFChars(env, sql, csql);

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
    return 0;
  }

  return (jlong) stmt;
}

static jobject Java_sqlite3_get_table
(JNIEnv *env, jclass cls, jlong handle, jstring sql)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  if (sql == 0)
  {
    throwSqliteException(env, "sql is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;
  const char* csql = (*env)->GetStringUTFChars(env, sql, 0);
  char** azResult;
  int row;
  int column;
  char* errmsg;

  int rc = sqlite3_get_table(conn, csql, &azResult, &row, &column, &errmsg);

  (*env)->ReleaseStringUTFChars(env, sql, csql);

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
    sqlite3_free_table(azResult);
    return 0;
  }

  jobject rs = newTableResult(env, azResult, row + 1, column);
  sqlite3_free_table(azResult);

  return rs;
}

static jlong Java_sqlite3_last_insert_rowid
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }
  sqlite3* conn = (sqlite3*) handle;
  return sqlite3_last_insert_rowid(conn);
}

static jint Java_sqlite3_changes
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;
  return sqlite3_changes(conn);
}

static jint Java_sqlite3_total_changes
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;
  return sqlite3_total_changes(conn);
}

static void Java_sqlite3_exec
(JNIEnv *env, jclass cls, jlong handle, jstring sql, jobject callback)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  if (sql == 0)
  {
    throwSqliteException(env, "sql is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;
  const char* csql = (*env)->GetStringUTFChars(env, sql, 0);
  int rc;

  if (g_exec_callback != 0)
  {
    (*env)->DeleteGlobalRef(env, g_exec_callback);
    g_exec_callback = 0;
  }

  if (callback != 0)
  {
    g_exec_callback = (*env)->NewGlobalRef(env, callback);
    rc = sqlite3_exec(conn, csql, exec_callback, 0, 0);
  } else
  {
    rc = sqlite3_exec(conn, csql, 0, 0, 0);
  }

  (*env)->ReleaseStringUTFChars(env, sql, csql);

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_close
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;

  int rc = sqlite3_close_v2(conn);

  if (rc == SQLITE_OK)
  {
    // 清理所有的全局引用
    _internal_free_all(env);
  } else
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_busy_handler
(JNIEnv *env, jclass cls, jlong handle, jobject jHandler)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;
  int rc;

  if (g_busy_handler != 0)
  {
    (*env)->DeleteGlobalRef(env, g_busy_handler);
    g_busy_handler = 0;
  }

  if (jHandler == 0)
  {
    rc = sqlite3_busy_handler(conn, 0, 0);
  } else
  {
    g_busy_handler = (*env)->NewGlobalRef(env, jHandler);
    rc = sqlite3_busy_handler(conn, jni_busy_handler, 0);
  }

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_busy_timeout
(JNIEnv *env, jclass clss, jlong handle, jint ms)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;
  int rc = sqlite3_busy_timeout(conn, ms);

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_commit_hook
(JNIEnv *env, jclass clss, jlong handle, jobject hook)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;

  if (g_commit_hook != 0)
  {
    (*env)->DeleteGlobalRef(env, g_commit_hook);
    g_commit_hook = 0;
  }

  if (hook == 0)
  {
    sqlite3_commit_hook(conn, 0, 0);
  } else
  {
    g_commit_hook = (*env)->NewGlobalRef(env, hook);
    sqlite3_commit_hook(conn, jni_commit_hook, conn);
  }
}

static void Java_sqlite3_rollback_hook
(JNIEnv *env, jclass clss, jlong handle, jobject hook)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;

  if (g_rollback_hook != 0)
  {
    (*env)->DeleteGlobalRef(env, g_rollback_hook);
    g_rollback_hook = 0;
  }

  if (hook == 0)
  {
    sqlite3_rollback_hook(conn, 0, 0);
  } else
  {
    g_rollback_hook = (*env)->NewGlobalRef(env, hook);
    sqlite3_rollback_hook(conn, jni_rollback_hook, conn);
  }
}

static void Java_sqlite3_create_function_v2
(JNIEnv *env, jclass clss, jlong handle, jstring funcName, jint nArgs, jobject app, jobject callbacks)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  if (funcName == 0)
  {
    throwSqliteException(env, "funcName is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;
  const char* name = (*env)->GetStringUTFChars(env, funcName, 0);
  int rc;

  if (callbacks == 0)
  { // 删除某个函数
    rc = sqlite3_create_function_v2(conn, name, nArgs, SQLITE_UTF8, 0, 0, 0,
                                    0, 0);
  } else
  {
    func_data* data = (func_data*) malloc(sizeof (func_data)); // 在堆上分配内存
    data->callback = (*env)->NewGlobalRef(env, callbacks);
    data->app = app == 0 ? 0 : (*env)->NewGlobalRef(env, app);

    jclass aggregateFunctionClass = (*env)->FindClass(env,
                                                      "com/baidu/javalite/AggregateFunction");

    if ((*env)->IsInstanceOf(env, callbacks, aggregateFunctionClass))
    {
      // 是 AggregateFunction
      rc = sqlite3_create_function_v2(conn, name, nArgs, SQLITE_UTF8,
                                      data, _xFunc_callback, _xStep_callback, _xFinal_callback,
                                      _function_destroy_callback);
    } else
    {
      // 是 ScalarFunction
      rc = sqlite3_create_function_v2(conn, name, nArgs, SQLITE_UTF8,
                                      data, _xFunc_callback, 0, 0, _function_destroy_callback);
    }

    (*env)->DeleteLocalRef(env, aggregateFunctionClass);
  }

  (*env)->ReleaseStringUTFChars(env, funcName, name);

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static jint Java_sqlite3_db_release_memory
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;

  return sqlite3_db_release_memory(conn);
}

static jint Java_sqlite3_limit
(JNIEnv *env, jclass clss, jlong handle, jint id, jint newVal)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;

  return sqlite3_limit(conn, id, newVal);
}

static jlong Java_sqlite3_next_stmt
(JNIEnv *env, jclass clss, jlong handle, jlong stmtHandle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;

  if (stmtHandle == 0)
  {
    return (jlong) sqlite3_next_stmt(conn, 0);
  } else
  {
    sqlite3_stmt* stmt = (sqlite3_stmt*) stmtHandle;
    return (jlong) sqlite3_next_stmt(conn, stmt);
  }
}

static void Java_sqlite3_trace
(JNIEnv *env, jclass clss, jlong handle, jobject listener)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;

  if (g_trace_listener != 0)
  {
    (*env)->DeleteGlobalRef(env, g_trace_listener);
    g_trace_listener = 0;
  }

  if (listener == 0)
  {
    sqlite3_trace(conn, 0, 0);
  } else
  {
    g_trace_listener = (*env)->NewGlobalRef(env, listener);
    sqlite3_trace(conn, _internal_trace_callback, conn);
  }
}

static void Java_sqlite3_profile
(JNIEnv *env, jclass clss, jlong handle, jobject listener)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;

  if (g_profile_listener != 0)
  {
    (*env)->DeleteGlobalRef(env, g_profile_listener);
    g_profile_listener = 0;
  }

  if (listener == 0)
  {
    sqlite3_profile(conn, 0, 0);
  } else
  {
    g_profile_listener = (*env)->NewGlobalRef(env, listener);
    sqlite3_profile(conn, _internal_profile_callback, conn);
  }
}

static void Java_sqlite3_update_hook
(JNIEnv *env, jclass clss, jlong handle, jobject hook)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;

  if (g_update_hook != 0)
  {
    (*env)->DeleteGlobalRef(env, g_update_hook);
    g_update_hook = 0;
  }

  if (hook == 0)
  {
    sqlite3_update_hook(conn, 0, 0);
  } else
  {
    g_update_hook = (*env)->NewGlobalRef(env, hook);
    sqlite3_update_hook(conn, _internal_update_hook, conn);
  }
}

static void Java_sqlite3_set_authorizer
(JNIEnv *env, jclass clss, jlong handle, jobject authorizer)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;

  if (g_authorizer != 0)
  {
    (*env)->DeleteGlobalRef(env, g_authorizer);
    g_authorizer = 0;
  }

  int rc;
  if (authorizer == 0)
  {
    rc = sqlite3_set_authorizer(conn, 0, 0);
  } else
  {
    g_authorizer = (*env)->NewGlobalRef(env, authorizer);
    rc = sqlite3_set_authorizer(conn, _internal_authorizer_callback, conn);
  }

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_create_collation_v2
(JNIEnv *env, jclass clss, jlong handle, jstring name, jobject collation)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  if (name == 0)
  {
    throwSqliteException(env, "name is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;

  if (g_collation != 0)
  {
    (*env)->DeleteGlobalRef(env, g_collation);
    g_collation = 0;
  }

  const char* cname = (*env)->GetStringUTFChars(env, name, 0);
  int rc;

  if (collation == 0)
  {
    rc = sqlite3_create_collation_v2(conn, cname, SQLITE_UTF8, 0, 0, 0);
  } else
  {
    g_collation = (*env)->NewGlobalRef(env, collation);
    rc = sqlite3_create_collation_v2(conn, cname, SQLITE_UTF8,
                                     conn, _internal_collation_compare,
                                     _internal_collation_destroy);
  }

  (*env)->ReleaseStringUTFChars(env, name, cname);

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

void com_baidu_javalite_DBConnection_RegisterNatives(JNIEnv* env)
{
  jclass cls = (*env)->FindClass(env, "com/baidu/javalite/DBConnection");
  JNINativeMethod methods[20];
  int index = 0;

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_prepare_v2";
    method->signature = "(JLjava/lang/String;)J";
    method->fnPtr = Java_sqlite3_prepare_v2;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_get_table";
    method->signature = "(JLjava/lang/String;)Lcom/baidu/javalite/TableResult;";
    method->fnPtr = Java_sqlite3_get_table;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_last_insert_rowid";
    method->signature = "(J)J";
    method->fnPtr = Java_sqlite3_last_insert_rowid;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_changes";
    method->signature = "(J)I";
    method->fnPtr = Java_sqlite3_changes;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_total_changes";
    method->signature = "(J)I";
    method->fnPtr = Java_sqlite3_total_changes;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_exec";
    method->signature = "(JLjava/lang/String;Lcom/baidu/javalite/SqlExecCallback;)V";
    method->fnPtr = Java_sqlite3_exec;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_close";
    method->signature = "(J)V";
    method->fnPtr = Java_sqlite3_close;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_busy_handler";
    method->signature = "(JLcom/baidu/javalite/BusyHandler;)V";
    method->fnPtr = Java_sqlite3_busy_handler;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_busy_timeout";
    method->signature = "(JI)V";
    method->fnPtr = Java_sqlite3_busy_timeout;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_commit_hook";
    method->signature = "(JLcom/baidu/javalite/CommitHook;)V";
    method->fnPtr = Java_sqlite3_commit_hook;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_rollback_hook";
    method->signature = "(JLcom/baidu/javalite/RollbackHook;)V";
    method->fnPtr = Java_sqlite3_rollback_hook;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_create_function_v2";
    method->signature = "(JLjava/lang/String;ILjava/lang/Object;Lcom/baidu/javalite/ScalarFunction;)V";
    method->fnPtr = Java_sqlite3_create_function_v2;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_db_release_memory";
    method->signature = "(J)I";
    method->fnPtr = Java_sqlite3_db_release_memory;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_limit";
    method->signature = "(JII)I";
    method->fnPtr = Java_sqlite3_limit;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_next_stmt";
    method->signature = "(JJ)J";
    method->fnPtr = Java_sqlite3_next_stmt;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_trace";
    method->signature = "(JLcom/baidu/javalite/TraceListener;)V";
    method->fnPtr = Java_sqlite3_trace;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_profile";
    method->signature = "(JLcom/baidu/javalite/ProfileListener;)V";
    method->fnPtr = Java_sqlite3_profile;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_update_hook";
    method->signature = "(JLcom/baidu/javalite/UpdateHook;)V";
    method->fnPtr = Java_sqlite3_update_hook;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_set_authorizer";
    method->signature = "(JLcom/baidu/javalite/Authorizer;)V";
    method->fnPtr = Java_sqlite3_set_authorizer;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_create_collation_v2";
    method->signature = "(JLjava/lang/String;Lcom/baidu/javalite/Collation;)V";
    method->fnPtr = Java_sqlite3_create_collation_v2;
  }

  (*env)->RegisterNatives(env, cls, methods, index);
  (*env)->DeleteLocalRef(env, cls);
}