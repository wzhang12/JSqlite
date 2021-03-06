/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_baidu_javalite_Backup */

#ifndef _Included_com_baidu_javalite_Backup
#define _Included_com_baidu_javalite_Backup
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_baidu_javalite_Backup
 * Method:    sqlite3_backup_init
 * Signature: (JLjava/lang/String;JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1init
  (JNIEnv *, jclass, jlong, jstring, jlong, jstring);

/*
 * Class:     com_baidu_javalite_Backup
 * Method:    sqlite3_backup_step
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1step
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_Backup
 * Method:    sqlite3_backup_finish
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1finish
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_Backup
 * Method:    sqlite3_backup_remaining
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1remaining
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_Backup
 * Method:    sqlite3_backup_pagecount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_baidu_javalite_Backup_sqlite3_1backup_1pagecount
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
