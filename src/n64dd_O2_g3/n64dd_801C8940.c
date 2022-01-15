#include "n64dd.h"

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8940.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8974.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C89B8.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C89EC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8A30.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8A64.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8AA8.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8B58.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8B90.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8BC0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8C1C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8CEC.s")

s32 func_801C8DC0(UNK_PTR arg0);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8DC0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8E70.s")

extern s32 (*D_801D2E54)(s32);

s32 func_801C8F1C(UNK_TYPE arg0) {
    if (D_801D2E54 != 0) {
        return D_801D2E54(arg0);
    }
    return 1;
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C8F58.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C9000.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C90C4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C90FC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C912C.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C91E0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C9260.s")

s32 func_801C9334(UNK_PTR arg0) {
    while (true) {
        u32 temp_v0 = func_801C8DC0(arg0);

        if ((temp_v0 == 3) || (temp_v0 == 4) || (temp_v0 == 5)) {
            return temp_v0;
        }
        // Fake match
        if ((temp_v0  & 0xFFFFFFFFu) == 0) {
            if (func_801C8F1C(arg0) != 0) {
                return 0;
            }
            return 7;
        }
        if (1) {}
    }
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C8940/func_801C93C4.s")
