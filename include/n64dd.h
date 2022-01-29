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

//extern u16 D_801D9516[];
//extern u16 D_801D9686[];
extern u8 LEOBYTE_TBL1[];
extern u16 LEOBYTE_TBL2[];
extern u8 LEOVZONE_PZONEHD_TBL[][0x10];
extern u16 LEOZONE_SCYL_TBL[];
extern s32 LEO_country_code;
extern u8 LEOdisk_type;
extern u16 LEOZONE_OUTERCYL_TBL[];
extern u16 LEOVZONE_TBL[][0x10];

extern leo_sys_form LEO_sys_data;
extern tgt_param_form LEOtgt_param;

extern s32 __leoActive;

// bss
extern LEOCmd *LEOcur_command;

#endif
