#ifndef CODE_FUNCTIONS_H
#define CODE_FUNCTIONS_H

#include "ultra64.h"

s32 PrintUtils_VPrintf(PrintCallback* pfn, const char* fmt, va_list args);

void Fault_AddHungupAndCrash(const char* filename, u32 line);

void func_800AD51C(void);

#endif
