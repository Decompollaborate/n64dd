#include "n64dd.h"

#define LANGUAGE_JP 0
#define LANGUAGE_EN 1

// i4 texture, 192*16. Error 41
extern u8 D_801D2FE0[2][192*16/2];

// I'm not completely sure about the indices
//extern const char* D_801D2EE0[2][8][4];

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9B70.s")

extern s32 gCurrentRegion;

s32 func_801C9C48(void) {
    return gCurrentRegion == 1 ? LANGUAGE_JP : LANGUAGE_EN;
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9C74.s")

// "Error Number    " array
extern const char* D_801D2ED0[];

const char* func_801C9CA4(void) {
    return D_801D2ED0[func_801C9C48()];
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9CD4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9D54.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9DB8.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9E28.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9EC0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9EF4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9F90.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9FFC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801CA030.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801CA070.s")
