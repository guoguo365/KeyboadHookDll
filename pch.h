// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#define _CRT_SECURE_NO_WARNINGS

#ifndef PCH_H
#define PCH_H
#include <stdio.h>

// add headers that you want to pre-compile here
#include "framework.h"

#define MY_API __declspec(dllexport)
extern "C" MY_API VOID SetHookOn();
extern "C" MY_API VOID SetHookOff();

// 狗子句柄
static HHOOK g_Hook = NULL;

// dll模塊句柄
static HINSTANCE g_Inst = NULL;

#endif //PCH_H

