/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_baidu_javalite_DBConnection */

#ifndef _Included_com_baidu_javalite_DBConnection
#define _Included_com_baidu_javalite_DBConnection
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_baidu_javalite_DBConnection
 * Method:    sqlite3_prepare_v2
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1prepare_1v2
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_baidu_javalite_DBConnection
 * Method:    sqlite3_get_table
 * Signature: (JLjava/lang/String;)Lcom/baidu/javalite/TableResult;
 */
JNIEXPORT jobject JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1get_1table
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_baidu_javalite_DBConnection
 * Method:    sqlite3_last_insert_rowid
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1last_1insert_1rowid
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_DBConnection
 * Method:    sqlite3_changes
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1changes
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_DBConnection
 * Method:    sqlite3_exec
 * Signature: (JLjava/lang/String;Lcom/baidu/javalite/SqlExecCallback;)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1exec
  (JNIEnv *, jclass, jlong, jstring, jobject);

/*
 * Class:     com_baidu_javalite_DBConnection
 * Method:    sqlite3_close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_DBConnection_sqlite3_1close
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
