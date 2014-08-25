/*
 * com_baidu_javalite_DBConnection.c
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */

#include "com_baidu_javalite_DBConnection.h"
#include "util.h"
#include <stdio.h>
#include <sqlite3.h>

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1close(JNIEnv *env,
        jclass cls, jlong handle) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return;
    }

    sqlite3* conn = (sqlite3*) handle;
    int rc = sqlite3_close(conn);
    if (rc != SQLITE_OK) {
        throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
    }
}

static jobject g_exec_callback;

static int exec_callback(void* data, int ncols, char** values, char** headers) {
    if (g_exec_callback == 0) {
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
        jclass cls, jlong handle, jstring sql, jobject callback) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return;
    }

    if (sql == 0) {
        throwSqliteException(env, "sql is NULL");
        return;
    }

    sqlite3* conn = (sqlite3*) handle;
    char* errMsg;
    const char* csql = (*env)->GetStringUTFChars(env, sql, 0);

    if (g_exec_callback != 0) {
        (*env)->DeleteGlobalRef(env, g_exec_callback);
        g_exec_callback = 0;
    }

    if (callback != 0) {
        g_exec_callback = (*env)->NewGlobalRef(env, callback);
    }

    int rc = sqlite3_exec(conn, csql, exec_callback, 0, &errMsg);

    (*env)->ReleaseStringUTFChars(env, sql, csql);

    if (rc != SQLITE_OK) {
    	throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
    }
}

jint JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1changes(JNIEnv *env,
        jclass cls, jlong handle) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    sqlite3* conn = (sqlite3*) handle;
    return sqlite3_changes(conn);
}

jlong JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1last_1insert_1rowid(
        JNIEnv *env, jclass cls, jlong handle) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }
    sqlite3* conn = (sqlite3*) handle;
    return sqlite3_last_insert_rowid(conn);
}

jobject JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1get_1table(
        JNIEnv *env, jclass cls, jlong handle, jstring sql) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    if (sql == 0) {
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

    if (rc != SQLITE_OK) {
    	throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
//        throwSqliteException(env, errmsg);
    	sqlite3_free_table(azResult);
        return 0;
    }

    jobject rs = newTableResult(env, azResult, row + 1, column);
    sqlite3_free_table(azResult);

    return rs;
}
