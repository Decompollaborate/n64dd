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
    /* 0x00 */ char unk_00[0x64];
    /* 0x64 */ u8 unk_64;
    /* 0x65 */ u8 unk_65;
    /* 0x66 */ u8 unk_66;
    /* 0x67 */ char unk_67[1];
    /* 0x68 */ s32 unk_68;
    /* 0x6C */ s32 unk_6C;
} struct_801E0D18; // size >= 0x70

extern struct_801E0D18 B_801E0D18;

extern UNK_TYPE4 LEO_country_code;
extern u8 LEOdisk_type;

// leo_tbl
extern const char LEOfirmware_rev[];
extern const u8 LEOBYTE_TBL1[];
extern const u16 LEOBYTE_TBL2[];
extern const u16 LEOVZONE_TBL[][0x10];
extern const u16 LEOZONE_SCYL_TBL[];
extern const u8 LEOVZONE_PZONEHD_TBL[][0x10];
extern const u16 LEOZONE_OUTERCYL_TBL[];
extern const u16 LEORAM_START_LBA[];
extern const s32 LEORAM_BYTE[];

extern leo_sys_form LEO_sys_data;
extern tgt_param_form LEOtgt_param;

extern s32 __leoActive;

extern LEOVersion __leoVersion;
extern u8 leoDiskStack[];

extern OSPiHandle* LEOPiInfo;

// bss
extern LEOCmd *LEOcur_command;

extern OSMesgQueue LEOcommand_que;

// other
extern u32 osResetType;

#endif
