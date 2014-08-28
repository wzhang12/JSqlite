/*
 * util.h
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <jni.h>

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

#endif /* UTIL_H_ */
