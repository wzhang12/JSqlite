/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_baidu_javalite_PrepareStmt */

#ifndef _Included_com_baidu_javalite_PrepareStmt
#define _Included_com_baidu_javalite_PrepareStmt
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_step
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1step
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_finalize
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1finalize
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_reset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1reset
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
