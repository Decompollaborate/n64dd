#include "n64dd.h"
#include "n64dd_functions.h"

// #pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801CE630/func_801CE630.s")
extern s32 D_801D8DF0; // boolean?

typedef struct {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s8 unk4[8];
} struct_801CE630;
void func_801CA9A4(struct_801CE630*);                               /* extern */

s32 func_801CE630(void) {
    // s32 pad[2];
    struct_801CE630 temp;

    if (D_801D8DF0 == 0) {
        return -1;
    }
    temp.unk0 = 1;
    temp.unk1 = 0;
    temp.unk2 = 0;
    temp.unk3 = 0;

    func_801CA9A4(&temp);
    return 0;
}