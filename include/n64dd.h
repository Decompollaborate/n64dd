#ifndef N64DD_H
#define N64DD_H

#include "ultra64.h"
#include "macros.h"
#include "libultra_functions.h"
#include "code_functions.h"

typedef struct {
    /* 0x000 */ UNK_TYPE unk_000;
    /* 0x004 */ UNK_TYPE unk_004;
    /* 0x008 */ UNK_TYPE unk_008; // maybe uintptr_t?
    /* 0x00C */ UNK_TYPE unk_00C; // maybe uintptr_t?
    /* 0x010 */ UNK_PTR unk_010; // function ptr
    /* 0x014 */ char unk_014[0x104];
} struct_801D9C30; // size = 0x118

typedef struct {
    /* 0x00 */ struct_801D9C30* unk_00;
    /* 0x00 */ char unk_004[0x10];
} struct_801D9D48; // size = 0x14? maybe 0x38

typedef struct {
    /* 0x0000 */ char unk_0000[0x4D10];
} struct_801DC000; // size = 0x4D10?

typedef struct {
    /* 0x00 */ UNK_TYPE4 unk_0;
    /* 0x04 */ UNK_TYPE1 unk_4;
    /* 0x05 */ UNK_TYPE1 unk_5;
    /* 0x06 */ UNK_TYPE1 unk_6;
    /* 0x07 */ UNK_TYPE1 unk_7;
    /* 0x08 */ UNK_TYPE1 unk_8;
    /* 0x09 */ UNK_TYPE1 unk_9;
    /* 0x0A */ char unk_A[0x2]; // padding?
    /* 0x0C */ UNK_TYPE4 unk_C;
    /* 0x10 */ UNK_TYPE4 unk_10;
} struct_801E5EF0; // size = 0x14

typedef struct {
    /* 0x00 */ char unk_00[0x60];
} struct_801E5F04; // size = 0x60


typedef struct {
    /* 0x00 */ char unk_00[0x4];
    /* 0x04 */ UNK_TYPE1 unk_04;
    /* 0x05 */ char unk_05[0x3];
    /* 0x08 */ char unk_08[0x4];
    /* 0x0C */ UNK_TYPE1 unk_0C;
    /* 0x0D */ UNK_TYPE1 unk_0D;
    /* 0x0E */ UNK_TYPE1 unk_0E;
    /* 0x0F */ UNK_TYPE1 unk_0F;
} struct_801E5E78; // size >= 0x10


#endif
