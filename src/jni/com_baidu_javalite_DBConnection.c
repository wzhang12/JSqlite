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
    int rc = sqlite3_close_v2(conn);
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
    const char* csql = (*env)->GetStringUTFChars(env, sql, 0);
    int rc;

    if (g_exec_callback != 0) {
        (*env)->DeleteGlobalRef(env, g_exec_callback);
        g_exec_callback = 0;
    }

    if (callback != 0) {
        g_exec_callback = (*env)->NewGlobalRef(env, callback);
        rc = sqlite3_exec(conn, csql, exec_callback, 0, 0);
    } else {
        rc = sqlite3_exec(conn, csql, 0, 0, 0);
    }

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

jint JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1total_1changes(
        JNIEnv *env, jclass cls, jlong handle) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return 0;
    }

    sqlite3* conn = (sqlite3*) handle;
    return sqlite3_total_changes(conn);
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

jlong JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1prepare_1v2(
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
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(conn, csql, -1, &stmt, NULL);

    (*env)->ReleaseStringUTFChars(env, sql, csql);

    if (rc != SQLITE_OK) {
        throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
        return 0;
    }

    return (jlong) stmt;
}

static jobject g_busy_handler;

static int my_busy_handler(void* data, int times) {
    if (g_busy_handler == 0) {
        return 0;
    } else {
        return callBusyHandlerCallback(getEnv(), g_busy_handler, times);
    }
}

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1busy_1handler(
        JNIEnv *env, jclass cls, jlong handle, jobject jHandler) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return;
    }

    sqlite3* conn = (sqlite3*) handle;
    int rc;

    if (g_busy_handler != 0) {
        (*env)->DeleteGlobalRef(env, g_busy_handler);
        g_busy_handler = 0;
    }

    if (jHandler == 0) {
        rc = sqlite3_busy_handler(conn, 0, 0);
    } else {
        g_busy_handler = (*env)->NewGlobalRef(env, jHandler);
        rc = sqlite3_busy_handler(conn, my_busy_handler, 0);
    }

    if (rc != SQLITE_OK) {
        throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
    }
}

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1busy_1timeout(
        JNIEnv *env, jclass cls, jlong handle, jint ms) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return;
    }

    sqlite3* conn = (sqlite3*) handle;
    int rc = sqlite3_busy_timeout(conn, ms);

    if (rc != SQLITE_OK) {
        throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
    }
}

static jobject g_commit_hook;

static int jni_commit_hook(void* arg) {
    if (g_commit_hook == 0) {
        return 0;
    }

    jobject jArg;
    JNIEnv* env = getEnv();
    int rs;

    if (arg != 0) {
        jArg = (jobject) arg;
    } else {
        jArg = 0;
    }

    rs = callCommitHookCallback(env, g_commit_hook, jArg);

    (*env)->DeleteGlobalRef(env, jArg);
    return rs;
}

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1commit_1hook(
        JNIEnv *env, jclass cls, jlong handle, jobject hook, jobject arg) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return;
    }

    sqlite3* conn = (sqlite3*) handle;

    if (g_commit_hook != 0) {
        (*env)->DeleteGlobalRef(env, g_commit_hook);
        g_commit_hook = 0;
    }

    if (hook == 0) {
        sqlite3_commit_hook(conn, 0, 0);
    } else {
        jobject jArg = 0;
        if (arg != 0) {
            jArg = (*env)->NewGlobalRef(env, arg);
        }

        sqlite3_commit_hook(conn, jni_commit_hook, (void*) jArg);
    }
}

static jobject g_rollback_hook;

static void rollback_hook(void* arg) {
    if (g_rollback_hook == 0) {
        return;
    }

    jobject jArg;
    JNIEnv* env = getEnv();

    if (arg != 0) {
        jArg = (jobject) arg;
    } else {
        jArg = 0;
    }

    callRollbackHookCallback(env, g_rollback_hook, jArg);

    (*env)->DeleteGlobalRef(env, jArg);
}

void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1rollback_1hook(
        JNIEnv *env, jclass cls, jlong handle, jobject hook, jobject arg) {
    if (handle == 0) {
        throwSqliteException(env, "handle is NULL");
        return;
    }

    sqlite3* conn = (sqlite3*) handle;

    if (g_rollback_hook != 0) {
        (*env)->DeleteGlobalRef(env, g_rollback_hook);
        g_rollback_hook = 0;
    }

    if (hook == 0) {
        sqlite3_rollback_hook(conn, 0, 0);
    } else {
        jobject jArg = 0;
        if (arg != 0) {
            jArg = (*env)->NewGlobalRef(env, arg);
        }

        sqlite3_rollback_hook(conn, rollback_hook, jArg);
    }
}
