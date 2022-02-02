#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA0B0.s")

const u16 D_801D9390[0x10] = {
    1,
    0x1085,
    0x2109,
    0x318D,
    0x4211,
    0x5295,
    0x6319,
    0x739D,
    0x8C63,
    0x9CE7,
    0xAD6B,
    0xBDEF,
    0xCE73,
    0xDEF7,
    0xEF7B,
    0xFFFF,
};

u16 func_801CA1D4(u32 arg0) {
    return D_801D9390[arg0 % ARRAY_COUNT(D_801D9390)];
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA1F0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA2F8.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA314.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA334.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA350.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA3B4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA3CC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA4F4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA5BC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA618.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA670.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA6A0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA6D8.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA6E4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CA0B0/func_801CA704.s")
