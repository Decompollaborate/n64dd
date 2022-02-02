#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

#if 0
s32 LeoReadWrite(LEOCmd* cmdBlock, s32 direction, u32 LBA, void* vAddr, u32 nLBAs, OSMesgQueue* mq);
//{
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/readwrite/LeoReadWrite.s")
