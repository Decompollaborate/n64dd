#include "n64dd.h"
#include "n64dd_functions.h"

extern struct_801E5E78* LEOcur_command;
extern OSPiHandle* B_801E5EC0;

void func_801CC040(void) {
    u32 sp1C;

    osEPiReadIo(B_801E5EC0, 0x05000540U, &sp1C);
    if (func_801CC820(0x1B0000, 0) == 0) {
        u32 sp18;

        osEPiReadIo(B_801E5EC0, 0x05000500U, &sp18);
        if (sp18 & 0x10000) {
            sp1C |= 0x100000;
        }
    }

    LEOcur_command->unk_0C = 0;
    LEOcur_command->unk_0D = (s8) (sp1C >> 0x10);
    LEOcur_command->unk_0E = 1;
    LEOcur_command->unk_0F = 0;
    LEOcur_command->unk_04 = 0;
}

extern struct_801E5EF0 B_801E5EF0;
extern struct_801E5F04 B_801E5F04;
extern struct_801E5EF0* B_801E5F64;
extern struct_801E5EF0* D_8000638C;

struct_801E5EF0* func_801CC0F0(void) {
    struct_801E5EF0 *temp_t9;
    u32 prevInt;

    B_801E5EF0.unk_4 = 2;
    B_801E5EF0.unk_C = 0xA5000000;
    B_801E5EF0.unk_5 = 3;
    B_801E5EF0.unk_8 = 6;
    B_801E5EF0.unk_6 = 6;
    B_801E5EF0.unk_7 = 2;
    B_801E5EF0.unk_9 = 1;
    B_801E5EF0.unk_10 = 0;

    bzero(&B_801E5F04, sizeof(struct_801E5F04));
    prevInt = __osDisableInt();

    temp_t9 = &B_801E5EF0;
    B_801E5EF0.unk_0 = D_8000638C;
    D_8000638C = temp_t9;
    B_801E5F64 = temp_t9;

    __osRestoreInt(prevInt);

    return &B_801E5EF0;
}
