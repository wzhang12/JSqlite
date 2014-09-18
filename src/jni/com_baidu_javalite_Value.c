/*
 * com_baidu_javalite_Value.c
 *
 *  Created on: 2014年9月9日
 *      Author: clark
 */

#include "com_baidu_javalite_Value.h"
#include "sqlite3.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>

jbyteArray JNICALL Java_com_baidu_javalite_Value_sqlite3_1value_1blob(
                                                                      JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_value* value = (sqlite3_value*) handle;
  int len = sqlite3_value_bytes(value);

  if (len == 0)
  {
    return (*env)->NewByteArray(env, 0);
  }

  jbyteArray rs = (*env)->NewByteArray(env, len);
  const void* buf = sqlite3_value_blob(value);
  (*env)->SetByteArrayRegion(env, rs, 0, len, (jbyte*) buf);

  return rs;
}

jdouble JNICALL Java_com_baidu_javalite_Value_sqlite3_1value_1double(
                                                                     JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_value* value = (sqlite3_value*) handle;
  return sqlite3_value_double(value);
}

jint JNICALL Java_com_baidu_javalite_Value_sqlite3_1value_1int(JNIEnv *env,
                                                               jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_value* value = (sqlite3_value*) handle;
  return sqlite3_value_int(value);
}

jlong JNICALL Java_com_baidu_javalite_Value_sqlite3_1value_1int64(JNIEnv *env,
                                                                  jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_value* value = (sqlite3_value*) handle;
  return sqlite3_value_int64(value);
}

jstring JNICALL Java_com_baidu_javalite_Value_sqlite3_1value_1text(JNIEnv *env,
                                                                   jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_value* value = (sqlite3_value*) handle;
  int len = sqlite3_value_bytes(value);

  if (len == 0)
  {
    return (*env)->NewStringUTF(env, "");
  }

  const void* buf = sqlite3_value_text(value);
  char* txt = (char*) malloc(len + 1);
  memset(txt, 0, len + 1);
  strncpy(txt, buf, len);

  jstring rs = (*env)->NewStringUTF(env, (const char*) txt);
  free(txt);

  return rs;
}

jint JNICALL Java_com_baidu_javalite_Value_sqlite3_1value_1type(JNIEnv *env,
                                                                jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_value* value = (sqlite3_value*) handle;
  return sqlite3_value_type(value);
}

jint JNICALL Java_com_baidu_javalite_Value_sqlite3_1value_1numeric_1type(
                                                                         JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "handle is NULL");
    return 0;
  }

  sqlite3_value* value = (sqlite3_value*) handle;
  return sqlite3_value_numeric_type(value);
}
