#include "util.h"

static jmethodID mid_SqliteExceptionInit;

static jmethodID getMidSqliteExceptionInit(JNIEnv* env)
{
    if (mid_SqliteExceptionInit == 0) {
        jclass excls = (*env)->FindClass(env,
                                         "com/baidu/javalite/SqliteException");
        mid_SqliteExceptionInit = (*env)->GetMethodID(env, excls, "<init>",
                                                      "(Ljava/lang/String;I)V");
        (*env)->DeleteLocalRef(env, excls);
    }
    return mid_SqliteExceptionInit;
}

jint throwSqliteException(JNIEnv* env, const char* msg)
{
    jclass excls = (*env)->FindClass(env, "com/baidu/javalite/SqliteException");
    jint rc;
    if (msg != 0) {
        rc = (*env)->ThrowNew(env, excls, msg);
    }
    else {
        rc = (*env)->ThrowNew(env, excls, "");
    }
    (*env)->DeleteLocalRef(env, excls);
    return rc;
}

jint throwSqliteException2(JNIEnv* env, int errorCode, const char* errorMsg)
{
    jclass excls = (*env)->FindClass(env, "com/baidu/javalite/SqliteException");
    jmethodID mid = getMidSqliteExceptionInit(env);
    jstring jErrorMsg;
    if (errorMsg != 0) {
        jErrorMsg = (*env)->NewStringUTF(env, errorMsg);
    }
    else {
        jErrorMsg = (*env)->NewStringUTF(env, "");
    }
    jthrowable thr = (*env)->NewObject(env, excls, mid, jErrorMsg, errorCode);
    jint rc = (*env)->Throw(env, thr);

    (*env)->DeleteLocalRef(env, excls);
    (*env)->DeleteLocalRef(env, jErrorMsg);
    (*env)->DeleteLocalRef(env, thr);
    return rc;
}

jint throwSqliteException3(JNIEnv* env, int errorCode)
{
    return throwSqliteException2(env, errorCode, 0);
}

static jmethodID mid_getSqlExecCallback;

jmethodID getSqlExecCallback(JNIEnv* env)
{
    if (mid_getSqlExecCallback == 0) {
        jclass cls = (*env)->FindClass(env,
                                       "com/baidu/javalite/SqlExecCallback");
        mid_getSqlExecCallback = (*env)->GetMethodID(env, cls, "callback",
                                                     "(I[Ljava/lang/String;[Ljava/lang/String;)I");
        (*env)->DeleteLocalRef(env, cls);
    }
    return mid_getSqlExecCallback;
}

jobjectArray createStringArray(JNIEnv* env, char** array, int len)
{
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

void setJavaVM(JavaVM* vm)
{
    g_vm = vm;
}

JNIEnv* getEnv(void)
{
    JNIEnv* rs;
    (*g_vm)->GetEnv(g_vm, (void**) &rs, JNI_VERSION_1_6);
    return rs;
}

static jmethodID mid_TableResultInit;

jmethodID getTableResultInit(JNIEnv* env)
{
    if (mid_TableResultInit == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/TableResult");
        mid_TableResultInit = (*env)->GetMethodID(env, cls, "<init>",
                                                  "([Ljava/lang/String;II)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_TableResultInit;
}

jobject newTableResult(JNIEnv* env, char** result, int row, int col)
{
    jobjectArray jresult = createStringArray(env, result, row * col);
    jclass cls = (*env)->FindClass(env, "com/baidu/javalite/TableResult");
    jobject rs = (*env)->NewObject(env, cls, getTableResultInit(env), jresult,
                                   row, col);

    (*env)->DeleteLocalRef(env, jresult);
    (*env)->DeleteLocalRef(env, cls);
    return rs;
}

static jmethodID mid_BusyHandlerCallback;

jmethodID getBusyHandlerCallback(JNIEnv* env)
{
    if (mid_BusyHandlerCallback == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/BusyHandler");
        mid_BusyHandlerCallback = (*env)->GetMethodID(env, cls, "handle",
                                                      "(I)I");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_BusyHandlerCallback;
}

jint callBusyHandlerCallback(JNIEnv* env, jobject obj, int times)
{
    return (*env)->CallIntMethod(env, obj, getBusyHandlerCallback(env), times);
}

static jmethodID mid_CommitHookCallback;

jmethodID getCommitHookCallback(JNIEnv* env)
{
    if (mid_CommitHookCallback == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/CommitHook");
        mid_CommitHookCallback = (*env)->GetMethodID(env, cls, "callback",
                                                     "(Lcom/baidu/javalite/DBConnection;)I");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_CommitHookCallback;
}

jint callCommitHookCallback(JNIEnv* env, jobject obj, jobject conn)
{
    return (*env)->CallIntMethod(env, obj, getCommitHookCallback(env), conn);
}

static jmethodID mid_RollbackHookCallback;

jmethodID getRollbackHookCallback(JNIEnv* env)
{
    if (mid_RollbackHookCallback == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/RollbackHook");
        mid_RollbackHookCallback = (*env)->GetMethodID(env, cls, "callback",
                                                       "(Lcom/baidu/javalite/DBConnection;)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_RollbackHookCallback;
}

void callRollbackHookCallback(JNIEnv* env, jobject obj, jobject conn)
{
    (*env)->CallVoidMethod(env, obj, getRollbackHookCallback(env), conn);
}

static jmethodID mid_javalite_init;

static jmethodID getJavaliteInit(JNIEnv* env)
{
    if (mid_javalite_init == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Value");
        mid_javalite_init = (*env)->GetMethodID(env, cls, "<init>", "(J)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_javalite_init;
}

jobject newJavaliteValue(JNIEnv* env, jlong handle)
{
    jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Value");
    jobject rs = (*env)->NewObject(env, cls, getJavaliteInit(env), handle);
    (*env)->DeleteLocalRef(env, cls);
    return rs;
}

jobjectArray newJavaliteValueArray(JNIEnv* env, int n, sqlite3_value** values)
{
    jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Value");
    jobjectArray rs = (*env)->NewObjectArray(env, n, cls, 0);

    if (rs == 0) {
        (*env)->DeleteLocalRef(env, cls);
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        (*env)->SetObjectArrayElement(env, rs, i,
                                      newJavaliteValue(env, (jlong) values[i]));
    }
    (*env)->DeleteLocalRef(env, cls);
    return rs;
}

static jmethodID mid_ScalarFunction_func;

static jmethodID getScalarFunctionFuncMid(JNIEnv* env)
{
    if (mid_ScalarFunction_func == 0) {
        jclass cls = (*env)->FindClass(env,
                                       "com/baidu/javalite/ScalarFunction");
        mid_ScalarFunction_func = (*env)->GetMethodID(env, cls, "xFunc",
                                                      "(Lcom/baidu/javalite/Context;[Lcom/baidu/javalite/Value;)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_ScalarFunction_func;
}

void callScalarFunctionFuncMethod(JNIEnv* env, jobject target, jobject ctx,
        jobjectArray values)
{
    (*env)->CallVoidMethod(env, target, getScalarFunctionFuncMid(env), ctx,
                           values);
}

static jmethodID mid_AggregateFunction_step;

static jmethodID getAggregateFunctionStepId(JNIEnv* env)
{
    if (mid_ScalarFunction_func == 0) {
        jclass cls = (*env)->FindClass(env,
                                       "com/baidu/javalite/AggregateFunction");
        mid_AggregateFunction_step = (*env)->GetMethodID(env, cls, "xStep",
                                                         "(Lcom/baidu/javalite/Context;[Lcom/baidu/javalite/Value;)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_AggregateFunction_step;
}

void callAggregateFunctionStepMethod(JNIEnv* env, jobject target, jobject ctx,
        jobjectArray values)
{
    (*env)->CallVoidMethod(env, target, getAggregateFunctionStepId(env), ctx,
                           values);
}

static jmethodID mid_AggregateFunction_final;

static jmethodID getAggregateFunctionFinalId(JNIEnv* env)
{
    if (mid_ScalarFunction_func == 0) {
        jclass cls = (*env)->FindClass(env,
                                       "com/baidu/javalite/AggregateFunction");
        mid_AggregateFunction_final = (*env)->GetMethodID(env, cls, "xFinal",
                                                          "(Lcom/baidu/javalite/Context;)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_AggregateFunction_final;
}

void callAggregateFunctionFinalMethod(JNIEnv* env, jobject target, jobject ctx)
{
    (*env)->CallVoidMethod(env, target, getAggregateFunctionFinalId(env), ctx);
}

static jmethodID mid_context_init;

static jmethodID getContextInitId(JNIEnv* env)
{
    if (mid_context_init == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Context");
        mid_context_init = (*env)->GetMethodID(env, cls, "<init>", "(J)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_context_init;
}

jobject newJavaliteContext(JNIEnv* env, jlong handle)
{
    jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Context");
    jobject rs = (*env)->NewObject(env, cls, getContextInitId(env), handle);
    (*env)->DeleteLocalRef(env, cls);
    return rs;
}

static jmethodID mid_DBConnection_init;

static jmethodID getDBConnectionInitId(JNIEnv* env)
{
    if (mid_DBConnection_init == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/DBConnection");
        mid_DBConnection_init = (*env)->GetMethodID(env, cls, "<init>", "(J)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_DBConnection_init;
}

jobject newDBConnection(JNIEnv* env, jlong handle)
{
    jclass cls = (*env)->FindClass(env, "com/baidu/javalite/DBConnection");
    jobject rs = (*env)->NewObject(env, cls, getDBConnectionInitId(env),
                                   handle);
    (*env)->DeleteLocalRef(env, cls);
    return rs;
}

static jmethodID mid_TraceListener_callback;

static jmethodID getTraceListenerCallbackId(JNIEnv* env)
{
    if (mid_TraceListener_callback == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/TraceListener");
        mid_TraceListener_callback = (*env)->GetMethodID(env, cls, "trace",
                                                         "(Lcom/baidu/javalite/DBConnection;Ljava/lang/String;)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_TraceListener_callback;
}

void callTraceListenerCallback(JNIEnv* env, jobject listener, jobject conn,
        jstring msg)
{
    (*env)->CallVoidMethod(env, listener, getTraceListenerCallbackId(env), conn,
                           msg);
}

static jmethodID mid_ProfileListener_callback;

static jmethodID getProfileListenerCallbackId(JNIEnv* env)
{
    if (mid_ProfileListener_callback == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/ProfileListener");
        mid_ProfileListener_callback = (*env)->GetMethodID(env, cls, "profile",
                                                           "(Lcom/baidu/javalite/DBConnection;Ljava/lang/String;J)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_ProfileListener_callback;
}

void callProfileListenerCallback(JNIEnv* env, jobject listener, jobject conn,
        jstring msg, jlong nano)
{
    (*env)->CallVoidMethod(env, listener, getProfileListenerCallbackId(env),
                           conn, msg, nano);
}

static jmethodID mid_UpdateHook_callback;

static jmethodID getUpdateHookCallbackId(JNIEnv* env)
{
    if (mid_UpdateHook_callback == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/UpdateHook");
        mid_UpdateHook_callback = (*env)->GetMethodID(env, cls, "hook", "(Lcom/baidu/javalite/DBConnection;ILjava/lang/String;Ljava/lang/String;J)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_UpdateHook_callback;
}

void callUpdateHookCallback(JNIEnv* env, jobject hook, jobject conn, int action, jstring db, jstring tb, jlong rowid)
{
    (*env)->CallVoidMethod(env, hook, getUpdateHookCallbackId(env), conn, action, db, tb, rowid);
}

static jmethodID mid_authorizer_callback;

static jmethodID getAuthorizerCallbackId(JNIEnv* env)
{
    if (mid_authorizer_callback == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Authorizer");
        mid_authorizer_callback = (*env)->GetMethodID(env, cls, "xAuth", "(Lcom/baidu/javalite/DBConnection;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_authorizer_callback;
}

int callAuthorizerCallback(JNIEnv* env, jobject authorizer, jobject conn, int action, jstring s1, jstring s2, jstring s3, jstring s4)
{
    return (*env)->CallIntMethod(env, authorizer, getAuthorizerCallbackId(env), conn, action, s1, s2, s3, s4);
}

static jmethodID mid_collation_compare;

static jmethodID getCollationCompareId(JNIEnv* env)
{
    if (mid_collation_compare == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Collation");
        mid_collation_compare = (*env)->GetMethodID(env,
                                                    cls,
                                                    "xCompare",
                                                    "(Lcom/baidu/javalite/DBConnection;[B[B)I");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_collation_compare;
}

int callCollationCompareCallback(JNIEnv* env, jobject collation, jobject conn,
        jbyteArray a, jbyteArray b)
{
    return (*env)->CallIntMethod(env, collation, getCollationCompareId(env), conn, a, b);
}

static jmethodID mid_collation_destroy;

static jmethodID getCollationDestroyId(JNIEnv* env)
{
    if (mid_collation_destroy == 0) {
        jclass cls = (*env)->FindClass(env, "com/baidu/javalite/Collation");
        mid_collation_destroy = (*env)->GetMethodID(env,
                                                    cls,
                                                    "xDestroy",
                                                    "(Lcom/baidu/javalite/DBConnection;)V");
        (*env)->DeleteLocalRef(env, cls);
    }

    return mid_collation_destroy;
}

void callCollationDestroyCallback(JNIEnv* env, jobject collation, jobject conn)
{
    (*env)->CallVoidMethod(env, collation, getCollationDestroyId(env), conn);
}
