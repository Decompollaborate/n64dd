#ifndef N64DD_H
#define N64DD_H

#include "ultra64.h"
#include "libultra_functions.h"
#include "n64dd_functions.h"

typedef struct {
    /* 0x000 */ char unk_000[0x118];
} struct_801D9C30; // size = 0x118

typedef struct {
    /* 0x00 */ struct_801D9C30* unk_00;
    /* 0x00 */ char unk_004[0x10];
} struct_801D9D48; // size = 0x14? maybe 0x38

typedef struct {
    /* 0x0000 */ char unk_0000[0x4D10];
} struct_801DC000; // size = 0x4D10?

#endif
