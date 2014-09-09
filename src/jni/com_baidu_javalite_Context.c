/*
 * com_baidu_javalite_Context.c
 *
 *  Created on: 2014年9月4日
 *      Author: clark
 */

#include "com_baidu_javalite_Context.h"
#include "util.h"
#include <sqlite3.h>

jobject JNICALL Java_com_baidu_javalite_Context_sqlite3_1user_1data(JNIEnv *env,
		jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return 0;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;

	func_data* data = (func_data*) sqlite3_user_data(ctx);
	if (data) {
		return data->app;
	}

	return 0;
}

jlong JNICALL Java_com_baidu_javalite_Context_sqlite3_1context_1db_1handle(
		JNIEnv *env, jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return 0;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;

	sqlite3* conn = sqlite3_context_db_handle(ctx);

	return (jlong) conn;
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1aggregate_1context__JLjava_lang_Object_2(
		JNIEnv *env, jclass cls, jlong handle, jobject value) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;

	void* rs = sqlite3_aggregate_context(ctx, 0);

	if (rs != 0) {
		throwSqliteException(env,
				"Function sqlite3_aggregate_context() already called!");
		return;
	}

	if (value == 0) {
		return;
	}

	rs = sqlite3_aggregate_context(ctx, sizeof(size_t));

	if (rs == 0) {
		throwSqliteException(env,
				"Fail to get buffer from sqlite3_aggregate_context()!");
		return;
	}

	*((jobject*) rs) = (*env)->NewGlobalRef(env, value); // 将 buffer 的值设置为 Java 对象引用的地址
}

jobject JNICALL Java_com_baidu_javalite_Context_sqlite3_1aggregate_1context__J(
		JNIEnv *env, jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return 0;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;

	void* rs = (jobject) sqlite3_aggregate_context(ctx, 0); // 返回的是指向 buffer 的指针

	if (rs == 0) {
		return 0;
	} else {
		return *((jobject*) rs); // 返回 buffer 上存储的 Java 对象的引用地址
	}
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1aggregate_1context_1free(
		JNIEnv *env, jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;

	void* rs = (jobject) sqlite3_aggregate_context(ctx, 0); // 返回的是指向 buffer 的指针

	if (rs != 0) {
		jobject gctx = *((jobject*) rs);
		(*env)->DeleteGlobalRef(env, gctx); // 释放全局引用
		*((jobject*) rs) = 0;
	}
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1result_1double(
		JNIEnv *env, jclass cls, jlong handle, jdouble value) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;
	sqlite3_result_double(ctx, value);
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1result_1int(JNIEnv *env,
		jclass cls, jlong handle, jint value) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;
	sqlite3_result_int(ctx, value);
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1result_1int64(JNIEnv *env,
		jclass cls, jlong handle, jlong value) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;
	sqlite3_result_int64(ctx, value);
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1result_1null(JNIEnv *env,
		jclass cls, jlong handle) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;
	sqlite3_result_null(ctx);
}

static jstring _internal_result_txt;

static void _internal_free_result_text(void* txt) {
	if (_internal_result_txt != 0) {
		JNIEnv* env = getEnv();
		(*env)->ReleaseStringUTFChars(env, _internal_result_txt,
				(const char*) txt);
		(*env)->DeleteGlobalRef(env, _internal_result_txt);
		_internal_result_txt = 0;
	}
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1result_1text(JNIEnv *env,
		jclass cls, jlong handle, jstring value) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;

	if (value == 0) {
		sqlite3_result_null(ctx);
	} else {
		if (_internal_result_txt != 0) {
			(*env)->DeleteGlobalRef(env, _internal_result_txt);
			_internal_result_txt = 0;
		}

		_internal_result_txt = (*env)->NewGlobalRef(env, value);
		const char* txt = (*env)->GetStringUTFChars(env, _internal_result_txt, 0);
		sqlite3_result_text(ctx, txt, -1, _internal_free_result_text);
	}
}

static jbyteArray _internal_result_blob;

static void _internal_free_result_blob(void* blob) {
	if (_internal_result_blob != 0) {
		JNIEnv* env = getEnv();
		(*env)->ReleaseByteArrayElements(env, _internal_result_blob,
				(jbyte*) blob, JNI_ABORT);
		(*env)->DeleteGlobalRef(env, _internal_result_blob);
		_internal_result_blob = 0;
	}
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1result_1blob(JNIEnv *env,
		jclass cls, jlong handle, jbyteArray value) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;

	if (value == 0) {
		sqlite3_result_null(ctx);
	} else {
		if (_internal_result_blob != 0) {
			(*env)->DeleteGlobalRef(env, _internal_result_blob);
			_internal_result_blob = 0;
		}

		_internal_result_blob = (*env)->NewGlobalRef(env, value);
		jbyte* elems = (*env)->GetByteArrayElements(env, _internal_result_blob,
				0);
		int len = (*env)->GetArrayLength(env, _internal_result_blob);
		sqlite3_result_blob(ctx, (const void*) elems, len,
				_internal_free_result_blob);
	}
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1result_1zeroblob(
		JNIEnv *env, jclass cls, jlong handle, jint size) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;
	sqlite3_result_zeroblob(ctx, size);
}

void JNICALL Java_com_baidu_javalite_Context_sqlite3_1result_1value(JNIEnv *env,
		jclass cls, jlong handle, jlong valueHandle) {
	if (handle == 0) {
		throwSqliteException(env, "Native handle is NULL!");
		return;
	}

	if (valueHandle == 0) {
		throwSqliteException(env, "Native sqlite3_value handle is NULL!");
		return;
	}

	sqlite3_context* ctx = (sqlite3_context*) handle;
	sqlite3_value* vl = (sqlite3_value*) valueHandle;
	sqlite3_result_value(ctx, vl);
}
