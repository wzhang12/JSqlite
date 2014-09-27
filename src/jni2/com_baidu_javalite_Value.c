#include <jni.h>
#include <sqlite3.h>
#include "util.h"
#include <string.h>
#include <stdlib.h>

static jbyteArray Java_sqlite3_value_blob
(JNIEnv *env, jclass clss, jlong handle)
{
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    sqlite3_value* value = (sqlite3_value*) handle;
    int len = sqlite3_value_bytes(value);

    if (len == 0) {
        return (*env)->NewByteArray(env, 0);
    }

    jbyteArray rs = (*env)->NewByteArray(env, len);
    const void* buf = sqlite3_value_blob(value);
    (*env)->SetByteArrayRegion(env, rs, 0, len, (jbyte*) buf);

    return rs;
}

static jdouble Java_sqlite3_value_double
(JNIEnv *env, jclass clss, jlong handle)
{
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    sqlite3_value* value = (sqlite3_value*) handle;
    return sqlite3_value_double(value);
}

static jint Java_sqlite3_value_int
(JNIEnv *env, jclass clss, jlong handle)
{
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    sqlite3_value* value = (sqlite3_value*) handle;
    return sqlite3_value_int(value);
}

static jlong Java_sqlite3_value_int64
(JNIEnv *env, jclass clss, jlong handle)
{
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    sqlite3_value* value = (sqlite3_value*) handle;
    return sqlite3_value_int64(value);
}

static jstring Java_sqlite3_value_text
(JNIEnv *env, jclass clss, jlong handle)
{
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    sqlite3_value* value = (sqlite3_value*) handle;
    int len = sqlite3_value_bytes(value);

    if (len == 0) {
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

static jint Java_sqlite3_value_type
(JNIEnv *env, jclass clss, jlong handle)
{
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    sqlite3_value* value = (sqlite3_value*) handle;
    return sqlite3_value_type(value);
}

static jint Java_sqlite3_value_numeric_type
(JNIEnv *env, jclass clss, jlong handle)
{
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    sqlite3_value* value = (sqlite3_value*) handle;
    return sqlite3_value_numeric_type(value);
}

void com_baidu_javalite_Value_RegisterNatives(JNIEnv* env)
{
    jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Value");
    JNINativeMethod methods[7];
    int index = 0;

    {
        JNINativeMethod method = methods[index++];
        method.name = "sqlite3_value_blob";
        method.signature = "(J)[B";
        method.fnPtr = Java_sqlite3_value_blob;
    }

    {
        JNINativeMethod method = methods[index++];
        method.name = "sqlite3_value_double";
        method.signature = "(J)D";
        method.fnPtr = Java_sqlite3_value_double;
    }

    {
        JNINativeMethod method = methods[index++];
        method.name = "sqlite3_value_int";
        method.signature = "(J)I";
        method.fnPtr = Java_sqlite3_value_int;
    }

    {
        JNINativeMethod method = methods[index++];
        method.name = "sqlite3_value_int64";
        method.signature = "(J)J";
        method.fnPtr = Java_sqlite3_value_int64;
    }

    {
        JNINativeMethod method = methods[index++];
        method.name = "sqlite3_value_text";
        method.signature = "(J)Ljava/lang/String;";
        method.fnPtr = Java_sqlite3_value_text;
    }

    {
        JNINativeMethod method = methods[index++];
        method.name = "sqlite3_value_type";
        method.signature = "(J)I";
        method.fnPtr = Java_sqlite3_value_type;
    }

    {
        JNINativeMethod method = methods[index++];
        method.name = "sqlite3_value_numeric_type";
        method.signature = "(J)I";
        method.fnPtr = Java_sqlite3_value_numeric_type;
    }

    (*env)->RegisterNatives(env, cls, methods, index);
    (*env)->DeleteLocalRef(env, cls);
}