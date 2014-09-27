#include <jni.h>
#include "util.h"
#include <sqlite3.h>

static jlong Java_sqlite3_blob_open
(JNIEnv *env, jclass cls, jlong connHandle, jstring dbName, jstring tableName,
        jstring columnName, jlong rowId, jint flags)
{
    if (connHandle == 0) {
        throwSqliteException(env, "conn is NULL!");
        return 0;
    }

    sqlite3* conn = (sqlite3*) connHandle;
    sqlite3_blob* blob = 0;

    const char* zDb = (*env)->GetStringUTFChars(env, dbName, 0);
    const char* zTable = (*env)->GetStringUTFChars(env, tableName, 0);
    const char* zColumn = (*env)->GetStringUTFChars(env, columnName, 0);

    int rc = sqlite3_blob_open(conn, zDb, zTable, zColumn, rowId, flags, &blob);

    (*env)->ReleaseStringUTFChars(env, dbName, zDb);
    (*env)->ReleaseStringUTFChars(env, tableName, zTable);
    (*env)->ReleaseStringUTFChars(env, columnName, zColumn);

    if (rc != SQLITE_OK) {
        throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
    }

    return (jlong) blob;
}

static void Java_sqlite3_blob_reopen
(JNIEnv *env, jclass cls, jlong handle, jlong newRowId)
{
    if (handle == 0) {
        throwSqliteException(env, "Handle is NULL!");
        return;
    }

    sqlite3_blob* blob = (sqlite3_blob*) handle;

    int rc = sqlite3_blob_reopen(blob, newRowId);

    if (rc != SQLITE_OK) {
        throwSqliteException2(env, rc, sqlite3_errstr(rc));
    }
}

static void Java_sqlite3_blob_close
(JNIEnv *env,
        jclass cls, jlong handle)
{
    if (handle == 0) {
        throwSqliteException(env, "Handle is NULL!");
        return;
    }

    sqlite3_blob* blob = (sqlite3_blob*) handle;

    int rc = sqlite3_blob_close(blob);

    if (rc != SQLITE_OK) {
        throwSqliteException2(env, rc, sqlite3_errstr(rc));
    }
}

static jint Java_sqlite3_blob_bytes
(JNIEnv *env,
        jclass cls, jlong handle)
{
    if (handle == 0) {
        throwSqliteException(env, "Handle is NULL!");
        return 0;
    }

    sqlite3_blob* blob = (sqlite3_blob*) handle;

    return sqlite3_blob_bytes(blob);
}

static void Java_sqlite3_blob_read
(JNIEnv *env,
        jclass cls, jlong handle, jbyteArray buf, jint offset, jint len,
        jint nOffset)
{
    if (handle == 0) {
        throwSqliteException(env, "Handle is NULL!");
        return;
    }

    sqlite3_blob* blob = (sqlite3_blob*) handle;
    void* cBuf = (*env)->GetByteArrayElements(env, buf, 0);

    int rc = sqlite3_blob_read(blob, cBuf + offset, len, nOffset);

    if (rc == SQLITE_OK) {
        (*env)->ReleaseByteArrayElements(env, buf, (jbyte*) cBuf, JNI_COMMIT); // 同步到 Java 数组中
    }
    else {
        (*env)->ReleaseByteArrayElements(env, buf, (jbyte*) cBuf, JNI_ABORT); // 没有修改 Java 数组
        throwSqliteException2(env, rc, sqlite3_errstr(rc));
    }
}

static void Java_sqlite3_blob_write
(JNIEnv *env,
        jclass cls, jlong handle, jbyteArray buf, jint offset, jint len,
        jint nOffset)
{
    if (handle == 0) {
        throwSqliteException(env, "Handle is NULL!");
        return;
    }

    sqlite3_blob* blob = (sqlite3_blob*) handle;
    void* cBuf = (*env)->GetByteArrayElements(env, buf, 0);

    int rc = sqlite3_blob_write(blob, cBuf + offset, len, nOffset);

    (*env)->ReleaseByteArrayElements(env, buf, (jbyte*) cBuf, JNI_ABORT); // 没有修改 Java 数组
    if (rc != SQLITE_OK) {
        throwSqliteException2(env, rc, sqlite3_errstr(rc));
    }
}

void com_baidu_javalite_Blob_RegisterNatives(JNIEnv* env)
{
    jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Blob");
    JNINativeMethod methods[6];
    int index = 0;

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_blob_open";
        method->signature = "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;JI)J";
        method->fnPtr = Java_sqlite3_blob_open;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_blob_reopen";
        method->signature = "(JJ)V";
        method->fnPtr = Java_sqlite3_blob_reopen;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_blob_close";
        method->signature = "(J)V";
        method->fnPtr = Java_sqlite3_blob_close;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_blob_bytes";
        method->signature = "(J)I";
        method->fnPtr = Java_sqlite3_blob_bytes;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_blob_read";
        method->signature = "(J[BIII)V";
        method->fnPtr = Java_sqlite3_blob_read;
    }

    {
        JNINativeMethod* method = methods + (index++);
        method->name = "sqlite3_blob_write";
        method->signature = "(J[BIII)V";
        method->fnPtr = Java_sqlite3_blob_write;
    }

    (*env)->RegisterNatives(env, cls, methods, index);
    (*env)->DeleteLocalRef(env, cls);
}