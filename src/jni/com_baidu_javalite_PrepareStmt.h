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
 * Method:    sqlite3_sql
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1sql
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_stmt_readonly
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1stmt_1readonly
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_stmt_busy
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1stmt_1busy
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_parameter_count
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1parameter_1count
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_parameter_name
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1parameter_1name
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_parameter_index
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1parameter_1index
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_clear_bindings
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1clear_1bindings
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_text
 * Signature: (JILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1text
  (JNIEnv *, jclass, jlong, jint, jstring);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_null
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1null
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_int64
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1int64
  (JNIEnv *, jclass, jlong, jint, jlong);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_int
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1int
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_double
 * Signature: (JID)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1double
  (JNIEnv *, jclass, jlong, jint, jdouble);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_blob
 * Signature: (JI[B)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1blob
  (JNIEnv *, jclass, jlong, jint, jbyteArray);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_type
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1type
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_text
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1text
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_int64
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1int64
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_int
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1int
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_double
 * Signature: (JI)D
 */
JNIEXPORT jdouble JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1double
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_blob
 * Signature: (JI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1blob
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_data_count
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1data_1count
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_decltype
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1decltype
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_origin_name
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1origin_1name
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_table_name
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1table_1name
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_database_name
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1database_1name
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_name
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1name
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_column_count
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1column_1count
  (JNIEnv *, jclass, jlong);

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

/*
 * Class:     com_baidu_javalite_PrepareStmt
 * Method:    sqlite3_bind_zeroblob
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_com_baidu_javalite_PrepareStmt_sqlite3_1bind_1zeroblob
  (JNIEnv *, jclass, jlong, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
