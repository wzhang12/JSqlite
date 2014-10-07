#include "util.h"

BAIDU_API void com_baidu_javalite_Backup_RegisterNatives(JNIEnv* env);
BAIDU_API void com_baidu_javalite_Blob_RegisterNatives(JNIEnv* env);
BAIDU_API void com_baidu_javalite_Context_RegisterNatives(JNIEnv* env);
BAIDU_API void com_baidu_javalite_DBConnection_RegisterNatives(JNIEnv* env);
BAIDU_API void com_baidu_javalite_Database_RegisterNatives(JNIEnv* env);
BAIDU_API void com_baidu_javalite_PrepareStmt_RegisterNatives(JNIEnv* env);
BAIDU_API void com_baidu_javalite_Value_RegisterNatives(JNIEnv* env);

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
  setJavaVM(vm);

  JNIEnv* rs;
  (*vm)->GetEnv(vm, (void**) &rs, JNI_VERSION_1_6);

  com_baidu_javalite_Backup_RegisterNatives(rs);
  com_baidu_javalite_Blob_RegisterNatives(rs);
  com_baidu_javalite_Context_RegisterNatives(rs);
  com_baidu_javalite_DBConnection_RegisterNatives(rs);
  com_baidu_javalite_Database_RegisterNatives(rs);
  com_baidu_javalite_PrepareStmt_RegisterNatives(rs);
  com_baidu_javalite_Value_RegisterNatives(rs);

  return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM *vm, void *reserved)
{
  setJavaVM(0); // clear
}