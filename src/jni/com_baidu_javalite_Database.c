/*
 * com_baidu_javalite_Database.c
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */
#include "com_baidu_javalite_Database.h"
#include "util.h"
#include <sqlite3.h>

jlong JNICALL Java_com_baidu_javalite_Database_sqlite3_1open_1v2(JNIEnv *env,
        jclass cls, jstring filename, jint flags, jstring zVfs)
{
  if (filename == 0)
  {
    throwSqliteException(env, "Can't open database file!");
    return 0;
  }

  sqlite3* handle;
  const char* name = (*env)->GetStringUTFChars(env, filename, 0);

  char* cZvfs = 0;
  if (zVfs != 0)
  {
    cZvfs = (char*) (*env)->GetStringUTFChars(env, zVfs, 0);
  }

  int rc = sqlite3_open_v2(name, &handle, flags, cZvfs);

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, sqlite3_errcode(handle),
                          sqlite3_errmsg(handle));
    sqlite3_close(handle);
    handle = 0;
  }

  (*env)->ReleaseStringUTFChars(env, filename, name);
  if (cZvfs != 0)
  {
    (*env)->ReleaseStringUTFChars(env, zVfs, cZvfs);
  }
  return (jlong) handle;
}

jboolean JNICALL Java_com_baidu_javalite_Database_sqlite3_1threadsafe(
        JNIEnv *env, jclass cls)
{
  return sqlite3_threadsafe() != 0;
}

void JNICALL Java_com_baidu_javalite_Database_sqlite3_1threadmode_1config(
        JNIEnv *env, jclass cls, jint option)
{
  int rc = sqlite3_config(option);
  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, rc, sqlite3_errstr(rc));
  }
}

void JNICALL Java_com_baidu_javalite_Database_sqlite3_1initialize(JNIEnv *env,
        jclass cls)
{
  int rc = sqlite3_initialize();
  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, rc, sqlite3_errstr(rc));
  }
}

void JNICALL Java_com_baidu_javalite_Database_sqlite3_1shutdown(JNIEnv *env,
        jclass cls)
{
  int rc = sqlite3_shutdown();
  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, rc, sqlite3_errstr(rc));
  }
}

jstring JNICALL Java_com_baidu_javalite_Database_sqlite3_1libversion(
        JNIEnv *env, jclass cls)
{
  const char* ver = sqlite3_libversion();

  if (ver == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    return (*env)->NewStringUTF(env, ver);
  }
}

jstring JNICALL Java_com_baidu_javalite_Database_sqlite3_1sourceid(JNIEnv *env,
        jclass cls)
{
  const char* ver = sqlite3_sourceid();

  if (ver == 0)
  {
    return (*env)->NewStringUTF(env, "");
  } else
  {
    return (*env)->NewStringUTF(env, ver);
  }
}

jint JNICALL Java_com_baidu_javalite_Database_sqlite3_1libversion_1number(
        JNIEnv *env, jclass cls)
{
  return sqlite3_libversion_number();
}

jboolean JNICALL Java_com_baidu_javalite_Database_sqlite3_1complete(JNIEnv *env,
        jclass cls, jstring sql)
{
  if (sql == 0)
  {
    return JNI_FALSE;
  }

  const char* csql = (*env)->GetStringUTFChars(env, sql, 0);
  int rc = sqlite3_complete(csql);
  if (rc == 1)
  {
    return JNI_TRUE;
  } else if (rc == 0)
  {
    return JNI_FALSE;
  } else
  {
    throwSqliteException2(env, rc, sqlite3_errstr(rc));
    return JNI_FALSE;
  }
}
