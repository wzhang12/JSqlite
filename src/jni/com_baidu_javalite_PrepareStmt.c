/*
 * com_baidu_javalite_PrepareStmt.c
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */

#include "com_baidu_javalite_PrepareStmt.h"
#include "util.h"
#include <sqlite3.h>

jboolean JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1step(JNIEnv *env,
		jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return JNI_FALSE;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	int rc = sqlite3_step(stmt);

	if (rc == SQLITE_ROW) {
		return JNI_TRUE;
	} else if (rc == SQLITE_DONE) {
		return JNI_FALSE;
	} else {
		sqlite3* conn = sqlite3_db_handle(stmt);
		throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
		return JNI_FALSE;
	}
}

void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1finalize(JNIEnv *env,
		jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	int rc = sqlite3_finalize(stmt);

	if (rc != SQLITE_OK) {
		sqlite3* conn = sqlite3_db_handle(stmt);
		throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
	}
}

void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1reset(JNIEnv *env,
		jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	int rc = sqlite3_reset(stmt);

	if (rc != SQLITE_OK) {
		sqlite3* conn = sqlite3_db_handle(stmt);
		throwSqliteException2(env, sqlite3_errcode(conn), sqlite3_errmsg(conn));
	}
}
