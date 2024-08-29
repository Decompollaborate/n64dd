#ifndef N64DD_FUNCTIONS_H
#define N64DD_FUNCTIONS_H

#include "ultra64.h"
#include "n64dd.h"

// Used in code
u32 func_801C6E80(void);
s32 func_801C70FC(void);
void func_801C7268(void);
s32 func_801C7658(void);
s32 func_801C7818(void);
void func_801C7C1C(void* arg0, s32 arg1, s32 arg2);
void n64dd_SetDiskVersion(s32 arg0);

s32 func_801C8000(struct_801D9D50* arg0);
s32 func_801C81C4(void);
void func_801C81EC(struct_801E0D18* arg0);
void func_801C8298(struct_801E0D18* arg0);
void func_801C82E0(struct_801E0D18* arg0);
void func_801C832C(struct_801E0D18* arg0);
void func_801C83A0(struct_801E0D18* arg0);
void func_801C8414(struct_801E0D18* arg0);
s32 func_801C873C(struct_801E0D18* arg0);

void func_801C8AA8(void);
s32 func_801C91E0(struct_801E0D18*);
s32 func_801C9260(struct_801E0D18*);
s32 func_801C9334(struct_801E0D18*);
s32 func_801C93C4(struct_801E0D18*);

void func_801C94F8(u8* bytes, u16 arg1);
void func_801C9A10(u8* arg0, s32 arg1, u8* str);
void func_801C9B50(s32 arg0, void (*arg1)(void*, uintptr_t, size_t));

u8* func_801C9E28(s32 errorNum);
u8* func_801C9EC0(void);
u8* func_801C9F90(s32 errorNum);
u8* func_801C9FFC(void);
u8* func_801CA030(s32 errorNum);
u8* func_801CA070(void);

void func_801CA1F0(void* charTexBuf, s32 posX, s32 posY, s32 dx, s32 dy, s32 cy, void* frameBuf, s32 screenWidth);

#endif
