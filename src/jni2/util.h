/*
 * util.h
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "import.h"
#include <sqlite3.h>

BAIDU_API jint throwSqliteException(JNIEnv* env, const char* msg);

BAIDU_API jint throwSqliteException2(JNIEnv* env, int errorCode, const char* errorMsg);

BAIDU_API jint throwSqliteException3(JNIEnv* env, int errorCode);

BAIDU_API jmethodID getSqlExecCallback(JNIEnv* env);

BAIDU_API jobjectArray createStringArray(JNIEnv* env, char** array, int len);

BAIDU_API void setJavaVM(JavaVM* vm);

BAIDU_API JNIEnv* getEnv(void);

BAIDU_API jmethodID getTableResultInit(JNIEnv* env);

BAIDU_API jobject newTableResult(JNIEnv* env, char** result, int row, int col);

BAIDU_API jmethodID getBusyHandlerCallback(JNIEnv* env);

BAIDU_API jint callBusyHandlerCallback(JNIEnv* env, jobject obj, int times);

BAIDU_API jmethodID getCommitHookCallback(JNIEnv* env);

BAIDU_API jint callCommitHookCallback(JNIEnv* env, jobject obj, jobject conn);

BAIDU_API jmethodID getRollbackHookCallback(JNIEnv* env);

BAIDU_API void callRollbackHookCallback(JNIEnv* env, jobject obj, jobject conn);

typedef struct
{
  // 回调对象
  jobject callback;

  // app 对象
  jobject app;
} func_data;

BAIDU_API jobject newJavaliteValue(JNIEnv* env, jlong handle);

BAIDU_API jobjectArray newJavaliteValueArray(JNIEnv* env, int n, sqlite3_value** values);

BAIDU_API void callScalarFunctionFuncMethod(JNIEnv* env, jobject target, jobject ctx, jobjectArray values);

BAIDU_API void callAggregateFunctionStepMethod(JNIEnv* env, jobject target, jobject ctx, jobjectArray values);

BAIDU_API void callAggregateFunctionFinalMethod(JNIEnv* env, jobject target, jobject ctx);

BAIDU_API jobject newJavaliteContext(JNIEnv* env, jlong handle);

BAIDU_API jobject newDBConnection(JNIEnv* env, jlong handle);

BAIDU_API void callTraceListenerCallback(JNIEnv* env, jobject listener, jobject conn, jstring msg);

BAIDU_API void callProfileListenerCallback(JNIEnv* env, jobject listener, jobject conn,
        jstring msg, jlong nano);

BAIDU_API void callUpdateHookCallback(JNIEnv* env, jobject hook, jobject conn, int action,
        jstring db, jstring tb, jlong rowid);

BAIDU_API int callAuthorizerCallback(JNIEnv* env, jobject authorizer, jobject conn,
        int action, jstring s1, jstring s2, jstring s3, jstring s4);

BAIDU_API int callCollationCompareCallback(JNIEnv* env, jobject collation, jobject conn,
        jbyteArray a, jbyteArray b);

BAIDU_API void callCollationDestroyCallback(JNIEnv* env, jobject collation, jobject conn);

#endif /* UTIL_H_ */
