#include <jni.h>
#include "util.h"
#include <sqlite3.h>
#include <stdio.h>

static jlong Java_sqlite3_backup_init
(JNIEnv *env, jclass cls, jlong dstHandle, jstring dstName, jlong srcHandle,
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

static jboolean Java_sqlite3_backup_step
(JNIEnv *env, jclass cls, jlong handle, jint nPage)
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

static void Java_sqlite3_backup_finish
(JNIEnv *env, jclass cls, jlong handle)
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

static jint Java_sqlite3_backup_remaining
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return 0;
  }

  sqlite3_backup* bu = (sqlite3_backup*) handle;

  return sqlite3_backup_remaining(bu);
}

static jint Java_sqlite3_backup_pagecount
(JNIEnv *env, jclass cls, jlong handle)
{
  if (handle == 0)
  {
    throwSqliteException(env, "Native handle is NULL!");
    return 0;
  }

  sqlite3_backup* bu = (sqlite3_backup*) handle;

  return sqlite3_backup_pagecount(bu);
}

void com_baidu_javalite_Backup_RegisterNatives(JNIEnv* env)
{
  jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Backup");
  JNINativeMethod methods[5];
  int index = 0;

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_backup_init";
    method->signature = "(JLjava/lang/String;JLjava/lang/String;)J";
    method->fnPtr = Java_sqlite3_backup_init;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_backup_step";
    method->signature = "(JI)Z";
    method->fnPtr = Java_sqlite3_backup_step;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_backup_finish";
    method->signature = "(J)V";
    method->fnPtr = Java_sqlite3_backup_finish;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_backup_remaining";
    method->signature = "(J)I";
    method->fnPtr = Java_sqlite3_backup_remaining;
  }

  {
    JNINativeMethod* method = methods + (index++);
    method->name = "sqlite3_backup_pagecount";
    method->signature = "(J)I";
    method->fnPtr = Java_sqlite3_backup_pagecount;
  }

  (*env)->RegisterNatives(env, cls, methods, index);
  (*env)->DeleteLocalRef(env, cls);
}