#include <jni.h>
#include "util.h"
#include <sqlite3.h>

static jlong Java_sqlite3_open_v2
(JNIEnv *env, jclass clss, jstring filename, jint flags, jstring zVfs)
{
    if (filename == 0) {
        throwSqliteException(env, "Can't open database file!");
        return 0;
    }

    sqlite3* handle;
    const char* name = (*env)->GetStringUTFChars(env, filename, 0);

    char* cZvfs = 0;
    if (zVfs != 0) {
        cZvfs = (char*) (*env)->GetStringUTFChars(env, zVfs, 0);
    }

    int rc = sqlite3_open_v2(name, &handle, flags, cZvfs);

    if (rc != SQLITE_OK) {
        throwSqliteException2(env, sqlite3_errcode(handle),
                              sqlite3_errmsg(handle));
        sqlite3_close(handle);
        handle = 0;
    }

    (*env)->ReleaseStringUTFChars(env, filename, name);
    if (cZvfs != 0) {
        (*env)->ReleaseStringUTFChars(env, zVfs, cZvfs);
    }
    return (jlong) handle;
}

static jboolean Java_sqlite3_threadsafe
(JNIEnv *env, jclass clss)
{
    return sqlite3_threadsafe() != 0;
}

static void Java_sqlite3_threadmode_config
(JNIEnv *env, jclass clss, jint option)
{
    int rc = sqlite3_config(option);
    if (rc != SQLITE_OK) {
        throwSqliteException2(env, rc, sqlite3_errstr(rc));
    }
}

static void Java_sqlite3_initialize
(JNIEnv *env, jclass clss)
{
    int rc = sqlite3_initialize();
    if (rc != SQLITE_OK) {
        throwSqliteException2(env, rc, sqlite3_errstr(rc));
    }
}

static void Java_sqlite3_shutdown
(JNIEnv *env, jclass clss)
{
    int rc = sqlite3_shutdown();
    if (rc != SQLITE_OK) {
        throwSqliteException2(env, rc, sqlite3_errstr(rc));
    }
}

static jstring Java_sqlite3_libversion
(JNIEnv *env, jclass clss)
{
    const char* ver = sqlite3_libversion();

    if (ver == 0) {
        return (*env)->NewStringUTF(env, "");
    }
    else {
        return (*env)->NewStringUTF(env, ver);
    }
}

static jstring Java_sqlite3_sourceid
(JNIEnv *env, jclass clss)
{
    const char* ver = sqlite3_sourceid();

    if (ver == 0) {
        return (*env)->NewStringUTF(env, "");
    }
    else {
        return (*env)->NewStringUTF(env, ver);
    }
}

static jint Java_sqlite3_libversion_number
(JNIEnv *env, jclass clss)
{
    return sqlite3_libversion_number();
}

static jboolean Java_sqlite3_complete
(JNIEnv *env, jclass clss, jstring sql)
{
    if (sql == 0) {
        return JNI_FALSE;
    }

    const char* csql = (*env)->GetStringUTFChars(env, sql, 0);
    int rc = sqlite3_complete(csql);
    if (rc == 1) {
        return JNI_TRUE;
    }
    else if (rc == 0) {
        return JNI_FALSE;
    }
    else {
        throwSqliteException2(env, rc, sqlite3_errstr(rc));
        return JNI_FALSE;
    }
}

void com_baidu_javalite_Database_RegisterNatives(JNIEnv* env)
{
    jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Database");
    JNINativeMethod methods[9];
    int index = 0;

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_open_v2";
        method->signature = "(Ljava/lang/String;ILjava/lang/String;)J";
        method->fnPtr = Java_sqlite3_open_v2;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_threadsafe";
        method->signature = "()Z";
        method->fnPtr = Java_sqlite3_threadsafe;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_threadmode_config";
        method->signature = "(I)V";
        method->fnPtr = Java_sqlite3_threadmode_config;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_initialize";
        method->signature = "()V";
        method->fnPtr = Java_sqlite3_initialize;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_shutdown";
        method->signature = "()V";
        method->fnPtr = Java_sqlite3_shutdown;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_libversion";
        method->signature = "()Ljava/lang/String;";
        method->fnPtr = Java_sqlite3_libversion;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_sourceid";
        method->signature = "()Ljava/lang/String;";
        method->fnPtr = Java_sqlite3_sourceid;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_libversion_number";
        method->signature = "()I";
        method->fnPtr = Java_sqlite3_libversion_number;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_complete";
        method->signature = "(Ljava/lang/String;)Z";
        method->fnPtr = Java_sqlite3_complete;
    }

    (*env)->RegisterNatives(env, cls, methods, index);
    (*env)->DeleteLocalRef(env, cls);
}