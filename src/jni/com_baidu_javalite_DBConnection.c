/*
 * com_baidu_javalite_DBConnection.c
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */

#include "com_baidu_javalite_DBConnection.h"
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
}

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1close(JNIEnv *env,
                                                                 jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3* conn = (sqlite3*) handle;

  // 清理所有的全局引用
  _internal_free_all(env);

  int rc = sqlite3_close_v2(conn);
  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
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

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1exec(JNIEnv *env,
                                                                jclass cls, jlong handle, jstring sql, jobject callback)
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
  }
  else
  {
    rc = sqlite3_exec(conn, csql, 0, 0, 0);
  }

  (*env)->ReleaseStringUTFChars(env, sql, csql);

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

jint JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1changes(JNIEnv *env,
                                                                   jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;
  return sqlite3_changes(conn);
}

jint JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1total_1changes(
                                                                          JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;
  return sqlite3_total_changes(conn);
}

jlong JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1last_1insert_1rowid(
                                                                                JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }
  sqlite3* conn = (sqlite3*) handle;
  return sqlite3_last_insert_rowid(conn);
}

jobject JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1get_1table(
                                                                         JNIEnv *env, jclass cls, jlong handle, jstring sql)
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

jlong JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1prepare_1v2(
                                                                        JNIEnv *env, jclass cls, jlong handle, jstring sql)
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

static int jni_busy_handler(void* data, int times)
{
  if (g_busy_handler == 0)
  {
    return 0;
  }
  else
  {
    return callBusyHandlerCallback(getEnv(), g_busy_handler, times);
  }
}

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1busy_1handler(
                                                                         JNIEnv *env, jclass cls, jlong handle, jobject jHandler)
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
  }
  else
  {
    g_busy_handler = (*env)->NewGlobalRef(env, jHandler);
    rc = sqlite3_busy_handler(conn, jni_busy_handler, 0);
  }

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1busy_1timeout(
                                                                         JNIEnv *env, jclass cls, jlong handle, jint ms)
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

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1commit_1hook(
                                                                        JNIEnv *env, jclass cls, jlong handle, jobject hook)
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
  }
  else
  {
    g_commit_hook = (*env)->NewGlobalRef(env, hook);
    sqlite3_commit_hook(conn, jni_commit_hook, conn);
  }
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

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1rollback_1hook(
                                                                          JNIEnv *env, jclass cls, jlong handle, jobject hook)
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
  }
  else
  {
    g_rollback_hook = (*env)->NewGlobalRef(env, hook);
    sqlite3_rollback_hook(conn, jni_rollback_hook, conn);
  }
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

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1create_1function_1v2(
                                                                                JNIEnv *env, jclass cls, jlong handle, jstring funcName, jint nArgs,
                                                                                jobject app, jobject callbacks)
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
  }
  else
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
    }
    else
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

jint JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1db_1release_1memory(
                                                                               JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;

  return sqlite3_db_release_memory(conn);
}

jint JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1limit(JNIEnv *env,
                                                                 jclass cls, jlong handle, jint id, jint newVal)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3* conn = (sqlite3*) handle;

  return sqlite3_limit(conn, id, newVal);
}

jlong JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1next_1stmt(
                                                                       JNIEnv *env, jclass cls, jlong handle, jlong stmtHandle)
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
  }
  else
  {
    sqlite3_stmt* stmt = (sqlite3_stmt*) stmtHandle;
    return (jlong) sqlite3_next_stmt(conn, stmt);
  }
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

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1trace(JNIEnv *env,
                                                                 jclass cls, jlong handle, jobject listener)
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
  }
  else
  {
    g_trace_listener = (*env)->NewGlobalRef(env, listener);
    sqlite3_trace(conn, _internal_trace_callback, conn);
  }
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

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1profile(JNIEnv *env,
                                                                   jclass cls, jlong handle, jobject listener)
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
  }
  else
  {
    g_profile_listener = (*env)->NewGlobalRef(env, listener);
    sqlite3_profile(conn, _internal_profile_callback, conn);
  }
}

static void _internal_update_hook(void* data, int action, char const *db, char const *tb, sqlite3_int64 rowid)
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

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1update_1hook(JNIEnv *env,
                                                                        jclass cls, jlong handle, jobject hook)
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
  }
  else
  {
    g_update_hook = (*env)->NewGlobalRef(env, hook);
    sqlite3_update_hook(conn, _internal_update_hook, conn);
  }
}
