/* 
 * File:   import.h
 * Author: clark
 *
 * Created on 2014年10月7日, 下午9:38
 */

#ifndef IMPORT_H
#define	IMPORT_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include <jni.h>

#ifndef BAIDU_API
#define BAIDU_API __attribute__ ((visibility("hidden")))
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* IMPORT_H */

