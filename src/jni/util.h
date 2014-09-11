/*
 * util.h
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <jni.h>
#include <sqlite3.h>

jint throwSqliteException(JNIEnv* env, const char* msg);

jint throwSqliteException2(JNIEnv* env, int errorCode, const char* errorMsg);

jint throwSqliteException3(JNIEnv* env, int errorCode);

jmethodID getSqlExecCallback(JNIEnv* env);

jobjectArray createStringArray(JNIEnv* env, char** array, int len);

void setJavaVM(JavaVM* vm);

JNIEnv* getEnv(void);

jmethodID getTableResultInit(JNIEnv* env);

jobject newTableResult(JNIEnv* env, char** result, int row, int col);

jmethodID getBusyHandlerCallback(JNIEnv* env);

jint callBusyHandlerCallback(JNIEnv* env, jobject obj, int times);

jmethodID getCommitHookCallback(JNIEnv* env);

jint callCommitHookCallback(JNIEnv* env, jobject obj, jobject arg);

jmethodID getRollbackHookCallback(JNIEnv* env);

void callRollbackHookCallback(JNIEnv* env, jobject obj, jobject arg);

typedef struct {
	// 回调对象
	jobject callback;

	// app 对象
	jobject app;
} func_data;

jobject newJavaliteValue(JNIEnv* env, jlong handle);

jobjectArray newJavaliteValueArray(JNIEnv* env, int n, sqlite3_value** values);

void callScalarFunctionFuncMethod(JNIEnv* env, jobject target, jobject ctx, jobjectArray values);

void callAggregateFunctionStepMethod(JNIEnv* env, jobject target, jobject ctx, jobjectArray values);

void callAggregateFunctionFinalMethod(JNIEnv* env, jobject target, jobject ctx);

jobject newJavaliteContext(JNIEnv* env, jlong handle);

jobject newDBConnection(JNIEnv* env, jlong handle);

void callTraceListenerCallback(JNIEnv* env, jobject listener, jobject conn, jstring msg);

void callProfileListenerCallback(JNIEnv* env, jobject listener, jobject conn, jstring msg, jlong nano);

#endif /* UTIL_H_ */
