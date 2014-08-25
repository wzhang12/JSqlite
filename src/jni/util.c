#include "util.h"

//static jmethodID SqliteException_init;
//
//static jmethodID getMethodId_SqliteException_init(JNIEnv* env) {
//    jclass excls = (*env)->FindClass(env,
//            "Lcom/baidu/javalite/SqliteException;");
//    if (SqliteException_init == 0) {
//        SqliteException_init = (*env)->GetMethodID(env, excls, "<init>",
//                "(Ljava/lang/String;)V");
//    }
//    return SqliteException_init;
//}

jint throwSqliteException(JNIEnv* env, const char* msg) {
    jclass excls = (*env)->FindClass(env,
            "Lcom/baidu/javalite/SqliteException;");
    jint rc = (*env)->ThrowNew(env, excls, msg);
    (*env)->DeleteLocalRef(env, excls);
    return rc;
}

static jmethodID mid_getSqlExecCallback;

jmethodID getSqlExecCallback(JNIEnv* env) {
    if (mid_getSqlExecCallback == 0) {
        jclass cls = (*env)->FindClass(env,
                "Lcom/baidu/javalite/SqlExecCallback;");
        mid_getSqlExecCallback = (*env)->GetMethodID(env, cls, "callback",
                "(I[Ljava/lang/String;[Ljava/lang/String;)I");
        (*env)->DeleteLocalRef(env, cls);
    }
    return mid_getSqlExecCallback;
}

jobjectArray createStringArray(JNIEnv* env, char** array, int len) {
    jclass cls = (*env)->FindClass(env, "Ljava/lang/String;");
    jobjectArray rs = (*env)->NewObjectArray(env, len, cls, 0);
    jstring s;
    for (int i = 0; i < len; ++i) {
        s = (*env)->NewStringUTF(env, array[i]);
        (*env)->SetObjectArrayElement(env, rs, i, s);
        (*env)->DeleteLocalRef(env, s);
    }

    (*env)->DeleteLocalRef(env, cls);
    return rs;
}

static JavaVM* g_vm;

void setJavaVM(JavaVM* vm) {
    g_vm = vm;
}

JNIEnv* getEnv() {
    JNIEnv* rs;
    (*g_vm)->GetEnv(g_vm, &rs, JNI_VERSION_1_6);
    return rs;
}

static jmethodID mid_TableResultInit;

jmethodID getTableResultInit(JNIEnv* env) {
    if (mid_TableResultInit == 0) {
        jclass cls = (*env)->FindClass(env, "Lcom/baidu/javalite/TableResult;");
        mid_TableResultInit = (*env)->GetMethodID(env, cls, "<init>",
                "([Ljava/lang/String;II)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_TableResultInit;
}

jobject newTableResult(JNIEnv* env, char** result, int row, int col) {
    jobjectArray jresult = createStringArray(env, result, row * col);
    jclass cls = (*env)->FindClass(env, "Lcom/baidu/javalite/TableResult;");
    jobject rs = (*env)->NewObject(env, cls, getTableResultInit(env), jresult,
            row, col);

    (*env)->DeleteLocalRef(env, jresult);
    (*env)->DeleteLocalRef(env, cls);
    return rs;
}

