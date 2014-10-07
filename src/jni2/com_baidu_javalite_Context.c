#include "util.h"
#include <sqlite3.h>

static jobject Java_sqlite3_user_data
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return 0;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  func_data* data = (func_data*) sqlite3_user_data(ctx);
  if (data)
  {
    return data->app;
  }

  return 0;
}

static jlong Java_sqlite3_context_db_handle
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return 0;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  sqlite3* conn = sqlite3_context_db_handle(ctx);

  return (jlong) conn;
}

static void Java_sqlite3_aggregate_context
(JNIEnv *env, jclass cls, jlong handle, jobject value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  void* rs = sqlite3_aggregate_context(ctx, 0);

  if (rs != 0)
  {
    throwSqliteException(env,
                         "Function sqlite3_aggregate_context() already called!");
    return;
  }

  if (value == 0)
  {
    return;
  }

  rs = sqlite3_aggregate_context(ctx, sizeof (size_t));

  if (rs == 0)
  {
    throwSqliteException(env,
                         "Fail to get buffer from sqlite3_aggregate_context()!");
    return;
  }

  *((jobject*) rs) = (*env)->NewGlobalRef(env, value); // 将 buffer 的值设置为 Java 对象引用的地址
}

static jobject Java_sqlite3_aggregate_context_v2
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return 0;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  void* rs = (jobject) sqlite3_aggregate_context(ctx, 0); // 返回的是指向 buffer 的指针

  if (rs == 0)
  {
    return 0;
  } else
  {
    return *((jobject*) rs); // 返回 buffer 上存储的 Java 对象的引用地址
  }
}

static void Java_sqlite3_aggregate_context_free
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  void* rs = (jobject) sqlite3_aggregate_context(ctx, 0); // 返回的是指向 buffer 的指针

  if (rs != 0)
  {
    jobject gctx = *((jobject*) rs);
    (*env)->DeleteGlobalRef(env, gctx); // 释放全局引用
    *((jobject*) rs) = 0;
  }
}

static void Java_sqlite3_result_double
(JNIEnv *env, jclass cls, jlong handle, jdouble value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;
  sqlite3_result_double(ctx, value);
}

static void Java_sqlite3_result_int
(JNIEnv *env, jclass cls, jlong handle, jint value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;
  sqlite3_result_int(ctx, value);
}

static void Java_sqlite3_result_int64
(JNIEnv *env, jclass cls, jlong handle, jlong value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;
  sqlite3_result_int64(ctx, value);
}

static void Java_sqlite3_result_null
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;
  sqlite3_result_null(ctx);
}

static void Java_sqlite3_result_text
(JNIEnv *env, jclass cls, jlong handle, jstring value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  if (value == 0)
  {
    sqlite3_result_null(ctx);
  } else
  {
    const char* txt = (*env)->GetStringUTFChars(env, value, 0);
    sqlite3_result_text(ctx, txt, -1, SQLITE_TRANSIENT);
    (*env)->ReleaseStringUTFChars(env, value, txt);
  }
}

static void Java_sqlite3_result_blob
(JNIEnv *env, jclass cls, jlong handle, jbyteArray value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  if (value == 0)
  {
    sqlite3_result_null(ctx);
  } else
  {
    jbyte* elems = (*env)->GetByteArrayElements(env, value, 0);
    int len = (*env)->GetArrayLength(env, value);
    sqlite3_result_blob(ctx, (const void*) elems, len, SQLITE_TRANSIENT);
    (*env)->ReleaseByteArrayElements(env, value, elems, JNI_ABORT);
  }
}

static void Java_sqlite3_result_zeroblob
(JNIEnv *env, jclass cls, jlong handle, jint size)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;
  sqlite3_result_zeroblob(ctx, size);
}

static void Java_sqlite3_result_value
(JNIEnv *env, jclass cls, jlong handle, jlong valueHandle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  if (valueHandle == 0)
  {
    throwSqliteException(env, "Native sqlite3_value handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;
  sqlite3_value* vl = (sqlite3_value*) valueHandle;
  sqlite3_result_value(ctx, vl);
}

static void Java_sqlite3_result_error
(JNIEnv *env, jclass cls, jlong handle, jstring msg, jint code)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  if (msg == 0)
  {
    sqlite3_result_error_code(ctx, code);
  } else
  {
    const char* cmsg = (*env)->GetStringUTFChars(env, msg, 0);
    sqlite3_result_error(ctx, cmsg, code);
    (*env)->ReleaseStringUTFChars(env, msg, cmsg);
  }
}

static void Java_sqlite3_result_error_toobig
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  sqlite3_result_error_toobig(ctx);
}

static void Java_sqlite3_result_error_nomem
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  sqlite3_result_error_nomem(ctx);
}

static void Java_sqlite3_result_error_code
(JNIEnv *env, jclass cls, jlong handle, jint code)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_context* ctx = (sqlite3_context*) handle;

  sqlite3_result_error_code(ctx, code);
}

void com_baidu_javalite_Context_RegisterNatives(JNIEnv* env)
{
  jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Context");
  JNINativeMethod methods[17];
  int index = 0;

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_user_data";
    method->signature = "(J)Ljava/lang/Object;";
    method->fnPtr = Java_sqlite3_user_data;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_context_db_handle";
    method->signature = "(J)J";
    method->fnPtr = Java_sqlite3_context_db_handle;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_aggregate_context";
    method->signature = "(JLjava/lang/Object;)V";
    method->fnPtr = Java_sqlite3_aggregate_context;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_aggregate_context";
    method->signature = "(J)Ljava/lang/Object;";
    method->fnPtr = Java_sqlite3_aggregate_context_v2;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_aggregate_context_free";
    method->signature = "(J)V";
    method->fnPtr = Java_sqlite3_aggregate_context_free;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_double";
    method->signature = "(JD)V";
    method->fnPtr = Java_sqlite3_result_double;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_int";
    method->signature = "(JI)V";
    method->fnPtr = Java_sqlite3_result_int;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_int64";
    method->signature = "(JJ)V";
    method->fnPtr = Java_sqlite3_result_int64;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_null";
    method->signature = "(J)V";
    method->fnPtr = Java_sqlite3_result_null;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_text";
    method->signature = "(JLjava/lang/String;)V";
    method->fnPtr = Java_sqlite3_result_text;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_blob";
    method->signature = "(J[B)V";
    method->fnPtr = Java_sqlite3_result_blob;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_zeroblob";
    method->signature = "(JI)V";
    method->fnPtr = Java_sqlite3_result_zeroblob;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_value";
    method->signature = "(JJ)V";
    method->fnPtr = Java_sqlite3_result_value;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_error";
    method->signature = "(JLjava/lang/String;I)V";
    method->fnPtr = Java_sqlite3_result_error;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_error_toobig";
    method->signature = "(J)V";
    method->fnPtr = Java_sqlite3_result_error_toobig;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_error_nomem";
    method->signature = "(J)V";
    method->fnPtr = Java_sqlite3_result_error_nomem;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_result_error_code";
    method->signature = "(JI)V";
    method->fnPtr = Java_sqlite3_result_error_code;
  }

  (*env)->RegisterNatives(env, cls, methods, index);
  (*env)->DeleteLocalRef(env, cls);
}