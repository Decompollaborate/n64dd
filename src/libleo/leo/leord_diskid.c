#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

#if 0
static const LEOCmdRead read_id_cmd;

static const u8 leo_disk_id_lba[2];

void leoReadDiskId();
//{
//    LEOCmdRead dummy_cmd;
//    u8* temp_pointer;
//    u32 cntr;
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leord_diskid/leo_disk_id_lba.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leord_diskid/leoReadDiskId.s")
