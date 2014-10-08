#include "util.h"
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

static jstring Java_sqlite3_sql
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const char* csql = sqlite3_sql(stmt);

  if (csql == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    return (*env)->NewStringUTF(env, csql);
  }
}

static jboolean Java_sqlite3_stmt_readonly
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  return sqlite3_stmt_readonly(stmt) != 0;
}

static jboolean Java_sqlite3_stmt_busy
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  return sqlite3_stmt_busy(stmt) != 0;
}

static jint Java_sqlite3_bind_parameter_count
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  return sqlite3_bind_parameter_count(stmt);
}

static jstring Java_sqlite3_bind_parameter_name
(JNIEnv *env, jclass clss, jlong handle, jint index)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const char* name = sqlite3_bind_parameter_name(stmt, index);

  if (name == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    return (*env)->NewStringUTF(env, name);
  }
}

static jint Java_sqlite3_bind_parameter_index
(JNIEnv *env, jclass clss, jlong handle, jstring zName)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  if (zName == 0)
  {
    throwSqliteException(env, "zName is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const char* cn = (*env)->GetStringUTFChars(env, zName, 0);

  int rc = sqlite3_bind_parameter_index(stmt, cn);

  (*env)->ReleaseStringUTFChars(env, zName, cn);

  return rc;
}

static void Java_sqlite3_clear_bindings
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  int rc = sqlite3_clear_bindings(stmt);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_bind_text
(JNIEnv *env, jclass clss, jlong handle, jint column, jstring value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  if (value == 0)
  {
    throwSqliteException(env, "value is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const char* cstr = (*env)->GetStringUTFChars(env, value, 0);
  const size_t len = strlen(cstr);

  int rc = sqlite3_bind_text(stmt, column, cstr, len, SQLITE_TRANSIENT);

  (*env)->ReleaseStringUTFChars(env, value, cstr);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_bind_null
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  int rc = sqlite3_bind_null(stmt, column);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_bind_int64
(JNIEnv *env, jclass clss, jlong handle, jint column, jlong value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  int rc = sqlite3_bind_int64(stmt, column, value);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_bind_int
(JNIEnv *env, jclass clss, jlong handle, jint column, jint value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  int rc = sqlite3_bind_int(stmt, column, value);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_bind_double
(JNIEnv *env, jclass clss, jlong handle, jint column, jdouble value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  int rc = sqlite3_bind_double(stmt, column, value);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_bind_blob
(JNIEnv *env, jclass clss, jlong handle, jint column, jbyteArray value)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  if (value == 0)
  {
    throwSqliteException(env, "value is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const int len = (*env)->GetArrayLength(env, value);
  char buf[len];
  (*env)->GetByteArrayRegion(env, value, 0, len, (jbyte*) buf);

  int rc = sqlite3_bind_blob(stmt, column, (void*) buf, len,
          SQLITE_TRANSIENT);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static jint Java_sqlite3_column_type
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  return sqlite3_column_type(stmt, column);
}

static jstring Java_sqlite3_column_text
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const unsigned char* cn = sqlite3_column_text(stmt, column);
  int bytes = sqlite3_column_bytes(stmt, column);

  if (bytes == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    char* text = (char*) malloc(bytes + 1); // bytes 的大小无法在编译时确定
    memset(text, 0, bytes + 1);
    strncpy(text, (const char*) cn, bytes);
    jstring rs = (*env)->NewStringUTF(env, text);
    free(text);
    return rs;
  }
}

static jlong Java_sqlite3_column_int64
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  return sqlite3_column_int64(stmt, column);
}

static jint Java_sqlite3_column_int
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  return sqlite3_column_int(stmt, column);
}

static jdouble Java_sqlite3_column_double
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  return sqlite3_column_double(stmt, column);
}

static jbyteArray Java_sqlite3_column_blob
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const void* data = sqlite3_column_blob(stmt, column);
  int bytes = sqlite3_column_bytes(stmt, column);

  jbyteArray array;
  if (bytes != 0)
  {
    array = (*env)->NewByteArray(env, bytes);
    jbyte* bin = (jbyte*) data;
    (*env)->SetByteArrayRegion(env, array, 0, bytes, bin);
  } else
  {
    array = (*env)->NewByteArray(env, 0);
  }
  return array;
}

static jint Java_sqlite3_data_count
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  return sqlite3_data_count(stmt);
}

static jstring Java_sqlite3_column_decltype
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const char* cn = sqlite3_column_decltype(stmt, column);

  if (cn == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    return (*env)->NewStringUTF(env, cn);
  }
}

static jstring Java_sqlite3_column_origin_name
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const char* cn = sqlite3_column_origin_name(stmt, column);

  if (cn == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    return (*env)->NewStringUTF(env, cn);
  }
}

static jstring Java_sqlite3_column_table_name
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const char* cn = sqlite3_column_table_name(stmt, column);

  if (cn == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    return (*env)->NewStringUTF(env, cn);
  }
}

static jstring Java_sqlite3_column_database_name
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const char* cn = sqlite3_column_database_name(stmt, column);

  if (cn == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    return (*env)->NewStringUTF(env, cn);
  }
}

static jstring Java_sqlite3_column_name
(JNIEnv *env, jclass clss, jlong handle, jint column)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  const char* cn = sqlite3_column_name(stmt, column);

  if (cn == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    return (*env)->NewStringUTF(env, cn);
  }
}

static jint Java_sqlite3_column_count
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  return sqlite3_column_count(stmt);
}

static jboolean Java_sqlite3_step
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return JNI_FALSE;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  int rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW)
  {
    return JNI_TRUE;
  } else if (rc == SQLITE_DONE)
  {
    return JNI_FALSE;
  } else
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
    return JNI_FALSE;
  }
}

static void Java_sqlite3_finalize
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  int rc = sqlite3_finalize(stmt);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_reset
(JNIEnv *env, jclass clss, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  int rc = sqlite3_reset(stmt);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

static void Java_sqlite3_bind_zeroblob
(JNIEnv *env, jclass clss, jlong handle, jint column, jint bytes)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return;
  }

  sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

  int rc = sqlite3_bind_zeroblob(stmt, column, bytes);

  if (rc != SQLITE_OK)
  {
    sqlite3* conn = sqlite3_db_handle(stmt);
    throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
  }
}

void com_baidu_javalite_PrepareStmt_RegisterNatives(JNIEnv* env)
{
  jclass cls = (*env)->FindClass(env, "com/baidu/javalite/PrepareStmt");
  JNINativeMethod methods[30];
  int index = 0;

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_sql";
    method->signature = "(J)Ljava/lang/String;";
    method->fnPtr = Java_sqlite3_sql;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_stmt_readonly";
    method->signature = "(J)Z";
    method->fnPtr = Java_sqlite3_stmt_readonly;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_stmt_busy";
    method->signature = "(J)Z";
    method->fnPtr = Java_sqlite3_stmt_busy;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_parameter_count";
    method->signature = "(J)I";
    method->fnPtr = Java_sqlite3_bind_parameter_count;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_parameter_name";
    method->signature = "(JI)Ljava/lang/String;";
    method->fnPtr = Java_sqlite3_bind_parameter_name;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_parameter_index";
    method->signature = "(JLjava/lang/String;)I";
    method->fnPtr = Java_sqlite3_bind_parameter_index;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_clear_bindings";
    method->signature = "(J)V";
    method->fnPtr = Java_sqlite3_clear_bindings;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_text";
    method->signature = "(JILjava/lang/String;)V";
    method->fnPtr = Java_sqlite3_bind_text;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_null";
    method->signature = "(JI)V";
    method->fnPtr = Java_sqlite3_bind_null;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_int64";
    method->signature = "(JIJ)V";
    method->fnPtr = Java_sqlite3_bind_int64;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_int";
    method->signature = "(JII)V";
    method->fnPtr = Java_sqlite3_bind_int;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_double";
    method->signature = "(JID)V";
    method->fnPtr = Java_sqlite3_bind_double;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_blob";
    method->signature = "(JI[B)V";
    method->fnPtr = Java_sqlite3_bind_blob;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_type";
    method->signature = "(JI)I";
    method->fnPtr = Java_sqlite3_column_type;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_text";
    method->signature = "(JI)Ljava/lang/String;";
    method->fnPtr = Java_sqlite3_column_text;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_int64";
    method->signature = "(JI)J";
    method->fnPtr = Java_sqlite3_column_int64;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_int";
    method->signature = "(JI)I";
    method->fnPtr = Java_sqlite3_column_int;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_double";
    method->signature = "(JI)D";
    method->fnPtr = Java_sqlite3_column_double;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_blob";
    method->signature = "(JI)[B";
    method->fnPtr = Java_sqlite3_column_blob;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_data_count";
    method->signature = "(J)I";
    method->fnPtr = Java_sqlite3_data_count;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_decltype";
    method->signature = "(JI)Ljava/lang/String;";
    method->fnPtr = Java_sqlite3_column_decltype;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_origin_name";
    method->signature = "(JI)Ljava/lang/String;";
    method->fnPtr = Java_sqlite3_column_origin_name;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_table_name";
    method->signature = "(JI)Ljava/lang/String;";
    method->fnPtr = Java_sqlite3_column_table_name;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_database_name";
    method->signature = "(JI)Ljava/lang/String;";
    method->fnPtr = Java_sqlite3_column_database_name;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_name";
    method->signature = "(JI)Ljava/lang/String;";
    method->fnPtr = Java_sqlite3_column_name;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_column_count";
    method->signature = "(J)I";
    method->fnPtr = Java_sqlite3_column_count;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_step";
    method->signature = "(J)Z";
    method->fnPtr = Java_sqlite3_step;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_finalize";
    method->signature = "(J)V";
    method->fnPtr = Java_sqlite3_finalize;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_reset";
    method->signature = "(J)V";
    method->fnPtr = Java_sqlite3_reset;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_bind_zeroblob";
    method->signature = "(JII)V";
    method->fnPtr = Java_sqlite3_bind_zeroblob;
  }

  (*env)->RegisterNatives(env, cls, methods, index);
  (*env)->DeleteLocalRef(env, cls);
}