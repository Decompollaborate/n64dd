#include "n64dd.h"
#include "n64dd_functions.h"

#if 0
static void (*cmd_tbl)(/* ECOFF does not store param types */)[16];

void leomain(void* arg);
//{
//    u32 cur_status;
//    u32 sense_code;
//    u8 disktype_bak;
//    Label: invalid_disktype @ 1252;
//    Label: post_exe @ 1340;
//}

static const LEOCmdRead system_read_cmd;

static const u8 system_lba[8];

u8 leoRead_system_area();
//{
//    LEOCmdRead dummy_cmd;
//    void* backup_pointer;
//    u32 retry_cntr;
//    u32 read_mode;
//    Label: system_retry @ 1848;
//    Label: sys_read_end @ 1968;
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leocmdex/system_lba.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leocmdex/leomain.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leocmdex/leoRead_system_area.s")
