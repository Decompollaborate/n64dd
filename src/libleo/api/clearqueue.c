#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

typedef struct {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s8 unk4[8];
} struct_801CE630;

s32 LeoClearQueue(void) {
    struct_801CE630 temp;

    if (__leoActive == 0) {
        return -1;
    }
    temp.unk0 = 1;
    temp.unk1 = 0;
    temp.unk2 = 0;
    temp.unk3 = 0;

    leoCommand(&temp);
    return 0;
}
