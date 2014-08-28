#include "util.h"

static jmethodID mid_SqliteExceptionInit;

static jmethodID getMidSqliteExceptionInit(JNIEnv* env) {
    if (mid_SqliteExceptionInit == 0) {
        jclass excls = (*env)->FindClass(env,
                "com/baidu/javalite/SqliteException");
        mid_SqliteExceptionInit = (*env)->GetMethodID(env, excls, "<init>",
                "(Ljava/lang/String;I)V");
        (*env)->DeleteLocalRef(env, excls);
    }
    return mid_SqliteExceptionInit;
}

jint throwSqliteException(JNIEnv* env, const char* msg) {
    jclass excls = (*env)->FindClass(env,
            "com/baidu/javalite/SqliteException");
    jint rc;
    if (msg != 0) {
        rc = (*env)->ThrowNew(env, excls, msg);
    } else {
        rc = (*env)->ThrowNew(env, excls, "");
    }
    (*env)->DeleteLocalRef(env, excls);
    return rc;
}

jint throwSqliteException2(JNIEnv* env, int errorCode, const char* errorMsg) {
    jclass excls = (*env)->FindClass(env,
            "com/baidu/javalite/SqliteException");
    jmethodID mid = getMidSqliteExceptionInit(env);
    jstring jErrorMsg;
    if (errorMsg != 0) {
        jErrorMsg = (*env)->NewStringUTF(env, errorMsg);
    } else {
        jErrorMsg = (*env)->NewStringUTF(env, "");
    }
    jthrowable thr = (*env)->NewObject(env, excls, mid, jErrorMsg, errorCode);
    jint rc = (*env)->Throw(env, thr);

    (*env)->DeleteLocalRef(env, excls);
    (*env)->DeleteLocalRef(env, jErrorMsg);
    (*env)->DeleteLocalRef(env, thr);
    return rc;
}

jint throwSqliteException3(JNIEnv* env, int errorCode) {
    return throwSqliteException2(env, errorCode, 0);
}

static jmethodID mid_getSqlExecCallback;

jmethodID getSqlExecCallback(JNIEnv* env) {
    if (mid_getSqlExecCallback == 0) {
        jclass cls = (*env)->FindClass(env,
                "com/baidu/javalite/SqlExecCallback");
        mid_getSqlExecCallback = (*env)->GetMethodID(env, cls, "callback",
                "(I[Ljava/lang/String;[Ljava/lang/String;)I");
        (*env)->DeleteLocalRef(env, cls);
    }
    return mid_getSqlExecCallback;
}

jobjectArray createStringArray(JNIEnv* env, char** array, int len) {
    jclass cls = (*env)->FindClass(env, "java/lang/String");
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
    (*g_vm)->GetEnv(g_vm, (void**) &rs, JNI_VERSION_1_6);
    return rs;
}

static jmethodID mid_TableResultInit;

jmethodID getTableResultInit(JNIEnv* env) {
    if (mid_TableResultInit == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/TableResult");
        mid_TableResultInit = (*env)->GetMethodID(env, cls, "<init>",
                "([Ljava/lang/String;II)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_TableResultInit;
}

jobject newTableResult(JNIEnv* env, char** result, int row, int col) {
    jobjectArray jresult = createStringArray(env, result, row * col);
    jclass cls = (*env)->FindClass(env, "com/baidu/javalite/TableResult");
    jobject rs = (*env)->NewObject(env, cls, getTableResultInit(env), jresult,
            row, col);

    (*env)->DeleteLocalRef(env, jresult);
    (*env)->DeleteLocalRef(env, cls);
    return rs;
}

static jmethodID mid_BusyHandlerCallback;

jmethodID getBusyHandlerCallback(JNIEnv* env) {
    if (mid_BusyHandlerCallback == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/BusyHandler");
        mid_BusyHandlerCallback = (*env)->GetMethodID(env, cls, "handle", "(I)I");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_BusyHandlerCallback;
}

jint callBusyHandlerCallback(JNIEnv* env, jobject obj, int times) {
    return (*env)->CallIntMethod(env, obj, getBusyHandlerCallback(env), times);
}

