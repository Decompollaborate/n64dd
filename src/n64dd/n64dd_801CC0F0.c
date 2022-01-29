#include "n64dd.h"
#include "n64dd_functions.h"

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
