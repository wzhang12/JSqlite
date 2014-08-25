/*
 * com_baidu_javalite_Database.c
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */
#include "com_baidu_javalite_Database.h"
#include "util.h"
#include <sqlite3.h>

jlong JNICALL Java_com_baidu_javalite_Database_sqlite3_1open_1v2(JNIEnv *env,
        jclass cls, jstring filename, jint flags, jstring zVfs) {
    if (filename == 0) {
        throwSqliteException(env, "Can't open database file!");
        return 0;
    }

    sqlite3* handle;
    const char* name = (*env)->GetStringUTFChars(env, filename, 0);

    char* cZvfs = 0;
    if (zVfs != 0) {
        cZvfs = (char*) (*env)->GetStringUTFChars(env, zVfs, 0);
    }

    int rc = sqlite3_open_v2(name, &handle, flags, cZvfs);

    if (rc) {
        throwSqliteException(env, "Can't open database file!");
        sqlite3_close(handle);
    }

    (*env)->ReleaseStringUTFChars(env, filename, name);
    if (cZvfs != 0) {
        (*env)->ReleaseStringUTFChars(env, zVfs, cZvfs);
    }
    return (jlong) handle;
}
