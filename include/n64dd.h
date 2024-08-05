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
    /* 0x00 */ LEOCmd unk_00;
    /* 0x1C */ OSMesgQueue unk_1C; // mq
    /* 0x34 */ char unk_34[0x4];
    /* 0x38 */ u32 unk_38; // lba
    /* 0x3C */ char unk_3C[0x1C];
    /* 0x58 */ UNK_TYPE unk_58;
    /* 0x5C */ UNK_TYPE unk_5C;
    /* 0x60 */ u32 unk_60;
    /* 0x64 */ u8 unk_64;
    /* 0x65 */ u8 unk_65;
    /* 0x66 */ u8 unk_66;
    /* 0x67 */ char unk_67[1];
    /* 0x68 */ s32 unk_68; // OSMesg?
    /* 0x6C */ s32 unk_6C;
} struct_801E0D18; // size >= 0x70

typedef struct {
    /* 0x00 */ char unk00[0x38];
    /* 0x38 */ LEODiskID diskId;
} struct_801C7A1C; // size >= 0x58

extern struct_801E0D18 B_801E0D18;


#define LANGUAGE_JP 0
#define LANGUAGE_EN 1



// Segment-external
extern s32 gCurrentRegion;

// bss
extern OSMesgQueue* B_801E0D10[2];


// leoram
extern leo_sys_form LEO_sys_data;
extern OSThread LEOcommandThread;
extern OSThread LEOinterruptThread;
extern u8 LEOcommandThreadStack[0x400];
extern u8 LEOinterruptThreadStack[0x400];
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

extern s32 __leoActive;

extern LEOVersion __leoVersion;
extern STACK(leoDiskStack, 0xFF0);

extern OSPiHandle* LEOPiInfo;

// bss

// other
extern u32 osTvType;
extern u32 osRomBase;
extern u32 osResetType;
extern u32 osMemSize;
extern u8 osAppNmiBuffer[0x40];

#endif
