/*
 * com_baidu_javalite_Backup.c
 *
 *  Created on: 2014年8月27日
 *      Author: clark
 */

#include "com_baidu_javalite_Backup.h"
#include "util.h"
#include <sqlite3.h>

jlong JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1init(JNIEnv *env,
        jclass cls, jlong dstHandle, jstring dstName, jlong srcHandle,
        jstring srcName)
{
  if (dstHandle == 0)
  {
    throwSqliteException(env, "Destination database handle is NULL!");
    return 0;
  }

  if (dstName == 0)
  {
    throwSqliteException(env, "Destination database name is NULL!");
    return 0;
  }

  if (srcHandle == 0)
  {
    throwSqliteException(env, "Source database handle is NULL!");
    return 0;
  }

  if (srcName == 0)
  {
    throwSqliteException(env, "Source database name is NULL!");
    return 0;
  }

  sqlite3* dst = (sqlite3*) dstHandle;
  sqlite3* src = (sqlite3*) srcHandle;

  const char* cDstName = (*env)->GetStringUTFChars(env, dstName, 0);
  const char* cSrcName = (*env)->GetStringUTFChars(env, srcName, 0);

  sqlite3_backup* bu = sqlite3_backup_init(dst, cDstName, src,
                                           cSrcName);

  if (bu == 0)
  {
    throwSqliteException2(env, sqlite3_errcode(dst), sqlite3_errmsg(dst));
  }

  (*env)->ReleaseStringUTFChars(env, dstName, cDstName);
  (*env)->ReleaseStringUTFChars(env, srcName, cSrcName);

  return (jlong) bu;
}

jboolean JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1step(
        JNIEnv *env, jclass cls, jlong handle, jint nPage)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return JNI_FALSE;
  }

  sqlite3_backup* bu = (sqlite3_backup*) handle;

  int rc = sqlite3_backup_step(bu, nPage);

  if (rc == SQLITE_OK)
  {
    return JNI_TRUE;
  } else if (rc == SQLITE_DONE)
  {
    return JNI_FALSE;
  } else
  {
    throwSqliteException2(env, rc, sqlite3_errstr(rc));
    return JNI_FALSE;
  }
}

void JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1finish(JNIEnv *env,
        jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return;
  }

  sqlite3_backup* bu = (sqlite3_backup*) handle;

  int rc = sqlite3_backup_finish(bu);

  if (rc != SQLITE_OK)
  {
    throwSqliteException2(env, rc, sqlite3_errstr(rc));
  }
}

jint JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1remaining(
        JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return 0;
  }

  sqlite3_backup* bu = (sqlite3_backup*) handle;

  return sqlite3_backup_remaining(bu);
}

jint JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1pagecount(
        JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return 0;
  }

  sqlite3_backup* bu = (sqlite3_backup*) handle;

  return sqlite3_backup_pagecount(bu);
}
