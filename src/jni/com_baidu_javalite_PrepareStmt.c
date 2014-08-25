/*
 * com_baidu_javalite_PrepareStmt.c
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */

#include "com_baidu_javalite_PrepareStmt.h"
#include "util.h"
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

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

jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1count(
		JNIEnv *env, jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	return sqlite3_column_count(stmt);
}

jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1name(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	const char* cn = sqlite3_column_name(stmt, column);

	if (cn == 0) {
		return (*env)->NewStringUTF(env, "");
	} else {
		return (*env)->NewStringUTF(env, cn);
	}
}

jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1database_1name(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	const char* cn = sqlite3_column_database_name(stmt, column);

	if (cn == 0) {
		return (*env)->NewStringUTF(env, "");
	} else {
		return (*env)->NewStringUTF(env, cn);
	}
}

jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1table_1name(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	const char* cn = sqlite3_column_table_name(stmt, column);

	if (cn == 0) {
		return (*env)->NewStringUTF(env, "");
	} else {
		return (*env)->NewStringUTF(env, cn);
	}
}

jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1origin_1name(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	const char* cn = sqlite3_column_origin_name(stmt, column);

	if (cn == 0) {
		return (*env)->NewStringUTF(env, "");
	} else {
		return (*env)->NewStringUTF(env, cn);
	}
}

jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1decltype(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	const char* cn = sqlite3_column_decltype(stmt, column);

	if (cn == 0) {
		return (*env)->NewStringUTF(env, "");
	} else {
		return (*env)->NewStringUTF(env, cn);
	}
}

jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1data_1count(
		JNIEnv *env, jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	return sqlite3_data_count(stmt);
}

jbyteArray JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1blob(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	const void* data = sqlite3_column_blob(stmt, column);
	int bytes = sqlite3_column_bytes(stmt, column);

	jbyteArray array;
	if (bytes != 0) {
		array = (*env)->NewByteArray(env, bytes);
		jbyte* bin = (jbyte*) data;
		(*env)->SetByteArrayRegion(env, array, 0, bytes, bin);
	} else {
		array = (*env)->NewByteArray(env, 0);
	}
	return array;
}

jdouble JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1double(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	return sqlite3_column_double(stmt, column);
}

jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1int(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	return sqlite3_column_int(stmt, column);
}

jlong JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1int64(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	return sqlite3_column_int64(stmt, column);
}

jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1text(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	const unsigned char* cn = sqlite3_column_text(stmt, column);
	int bytes = sqlite3_column_bytes(stmt, column);

	if (bytes == 0) {
		return (*env)->NewStringUTF(env, "");
	} else {
		char* text = (char*) malloc(bytes + 1);
		memset(text, 0, bytes + 1);
		strncpy(text, (const char*) cn, bytes);
		jstring rs = (*env)->NewStringUTF(env, text);
		free(text);
		return rs;
	}
}

jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1type(
		JNIEnv *env, jclass cls, jlong handle, jint column) {
	if (handle == 0) {
		throwSqliteException(env, "handle is NULL");
		return 0;
	}

	sqlite3_stmt* stmt = (sqlite3_stmt*) handle;

	return sqlite3_column_type(stmt, column);
}
