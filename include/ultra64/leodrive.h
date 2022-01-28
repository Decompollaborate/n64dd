#ifndef LEODRIVE_H
#define LEODRIVE_H

#include "types.h"

typedef union {
    /* 0x0 */ u8 u8_data[4];
    /* 0x0 */ u16 u16_data[2];
    /* 0x0 */ u32 u32_data;
} data_trans_form; // size = 0x4

typedef struct {
    /* 0x00 */ u8* pntr;
    /* 0x04 */ u8* c2buff_e;
    /* 0x08 */ u8 err_pos[4];
    /* 0x0C */ u8 err_num;
    /* 0x0D */ u8 bytes;
    /* 0x0E */ u16 blkbytes;
} block_param_form; // size = 0x10

typedef struct {
    /* 0x0 */ u16 lba;
    /* 0x2 */ u16 cylinder;
    /* 0x4 */ u16 blk_bytes;
    /* 0x6 */ u8 sec_bytes;
    /* 0x7 */ u8 head;
    /* 0x8 */ u8 zone;
    /* 0x9 */ u8 rdwr_blocks;
    /* 0xA */ u8 start_block;
} tgt_param_form; // size = 0xC

typedef union {
    /* 0x00 */ struct {
        /* 0x00 */ u32 country;
        /* 0x04 */ u8 fmt_type;
        /* 0x05 */ u8 disk_type;
        /* 0x06 */ u16 ipl_load_len;
        /* 0x08 */ u8 defect_num[20];
        /* 0x1C */ void* loadptr;
        /* 0x20 */ u8 defect_data[192];
        /* 0xE0 */ u16 rom_end_lba;
        /* 0xE2 */ u16 ram_start_lba;
        /* 0xE4 */ u16 ram_end_lba;
    } param;
    /* 0x00 */ u64 u64_data[29];
} leo_sys_form; // size = 0xE8

#endif
