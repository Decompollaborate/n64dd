#ifndef N64DD_H
#define N64DD_H

#include "ultra64.h"
#include "macros.h"
#include "libultra_functions.h"
#include "code_functions.h"

#define THREAD_ID_N64DD 8
#define THREAD_ID_DDMSG 9

#define THREAD_PRI_N64DD 13
#define THREAD_PRI_DDMSG 13

typedef struct struct_801E0D18 {
    /* 0x00 */ LEOCmd unk_00;
    /* 0x1C */ OSMesgQueue unk_1C;
    /* 0x38 */ LEODiskID diskId;
    /* 0x58 */ UNK_TYPE unk_58;
    /* 0x5C */ UNK_TYPE unk_5C;
    /* 0x60 */ u32 unk_60;
    /* 0x64 */ u8 unk_64;
    /* 0x65 */ u8 unk_65;
    /* 0x66 */ u8 unk_66;
    /* 0x68 */ s32 unk_68;
    /* 0x6C */ s32 unk_6C;
} struct_801E0D18; // size = 0x70

typedef struct struct_801D9D50 {
    /* 0x00 */ u8 unk_00; // command enum
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08;
    /* 0x0C */ void (*unk_0C)(void*, void*, void*);
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ void (*unk_14)(void*, uintptr_t, size_t);
    /* 0x18 */ void* unk_18;
    /* 0x1C */ void* unk_1C; // either OSMesgQueue* (command 0) or integer LBA (commands 2 and 3)
    /* 0x20 */ void* unk_20; // either OSMesgQueue* (command 0) or integer byte size (commands 3 and 4)
    /* 0x24 */ OSId unk_24;
    /* 0x28 */ void* unk_28;
    /* 0x2C */ OSPri unk_2C;
} struct_801D9D50; // size = 0x30

#define LANGUAGE_JP 0
#define LANGUAGE_EN 1

// Segment-external
extern s32 gCurrentRegion;
extern IrqMgr gIrqMgr;

extern u8 D_80121212;
extern vu8 D_80121213;
extern vu8 D_80121214;

extern u32 osTvType;
extern u32 osRomBase;
extern u32 osResetType;
extern u32 osMemSize;
extern u8 osAppNmiBuffer[0x40];

// n64dd
extern s32 (*D_801D2E54)(struct_801E0D18*);

extern u8 B_801DC000[];

extern s32 D_801D2E90;
extern OSMesgQueue* B_801E0D10[2];

extern s32 D_801D2EA0;
extern s32 D_801D2EA8;
extern s32 B_801E0F60;
extern s32 B_801E0F64;
extern void (*D_801D2EB4)(void*, void*, void*);

extern const char* D_801D2ED0[];        // "Error Number    " array
extern const char* D_801D2EE0[2][8][4]; // Array of error message strings

extern u8 D_801D2FE0[2][192 * 16 / 2]; // i4 textures, 192*16. Error 41
extern u8 D_801D3BE0[2][0x2800];       // Texture array

// libleo
extern leo_sys_form LEO_sys_data;
extern OSThread LEOcommandThread;
extern OSThread LEOinterruptThread;
extern STACK(LEOcommandThreadStack, 0x400);
extern STACK(LEOinterruptThreadStack, 0x400);
extern OSMesgQueue LEOcommand_que;
extern OSMesgQueue LEOevent_que;
extern OSMesgQueue LEOcontrol_que;
extern OSMesgQueue LEOdma_que;
extern OSMesgQueue LEOblock_que;
extern OSMesg LEOevent_que_buf[1];
extern OSMesg LEOcontrol_que_buf[1];
extern OSMesg LEOdma_que_buf[2];
extern OSMesg LEOblock_que_buf[1];
extern u8* LEOwrite_pointer;
extern LEOCmd* LEOcur_command;
extern u32 LEOasic_bm_ctl_shadow;
extern u32 LEOasic_seq_ctl_shadow;
extern u8 LEOdrive_flag;
extern vu8 LEOclr_que_flag;
// needs to not be volatile in some files
// extern vu16 LEOrw_flags;
extern u8 LEOdisk_type;
extern tgt_param_form LEOtgt_param;
extern u32 LEO_country_code;

extern const char LEOfirmware_rev[];
extern const u8 LEOBYTE_TBL1[];
extern const u16 LEOBYTE_TBL2[];
extern const u16 LEOVZONE_TBL[][0x10];
extern const u16 LEOZONE_SCYL_TBL[];
extern const u8 LEOVZONE_PZONEHD_TBL[][0x10];
extern const u16 LEOZONE_OUTERCYL_TBL[];
extern const u16 LEORAM_START_LBA[];
extern const s32 LEORAM_BYTE[];

extern s32 __leoActive;
extern LEOVersion __leoVersion;
extern STACK(leoDiskStack, 0x1000);

extern OSPiHandle* LEOPiInfo;

#endif
