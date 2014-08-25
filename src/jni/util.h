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

jmethodID getSqlExecCallback(JNIEnv* env);

jobjectArray createStringArray(JNIEnv* env, char** array, int len);

void setJavaVM(JavaVM* vm);

JNIEnv* getEnv();

jmethodID getTableResultInit(JNIEnv* env);

jobject newTableResult(JNIEnv* env, char** result, int row, int col);

#endif /* UTIL_H_ */
