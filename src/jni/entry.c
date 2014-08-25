/*
 * entry.c
 *
 *  Created on: 2014年8月25日
 *      Author: clark
 */

#include "util.h"

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    setJavaVM(vm);
    return JNI_VERSION_1_6;
}
