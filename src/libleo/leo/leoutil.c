#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

#if 0
u16 leoLba_to_phys(u32 lba) {
    //s32 temp_t6;
    u16 temp_v0_2;
    //s32 temp_a0;
    int new_var;
    u16 phi_v1;
    u16 phi_a1;
    u16 phi_t1;
    u16 phi_v1_2;
    u16 phi_t2;
    s16 temp_t7;
    u16 aux;

    LEOtgt_param.rdwr_blocks = 2 - (lba & 1);

    if (((lba & 3) != 0) && ((lba & 3) != 3)) {
        LEOtgt_param.start_block = 1;
    } else {
        LEOtgt_param.start_block = 0;
    }

    temp_v0_2 = leoLba_to_vzone(lba);

    phi_t2 = LEOVZONE_PZONEHD_TBL[LEOdisk_type][temp_v0_2];

    LEOtgt_param.head =  0;
    LEOtgt_param.zone = LEOVZONE_PZONEHD_TBL[LEOdisk_type][temp_v0_2];

    if (((u8)phi_t2 > 7) ) 
    {
        temp_t7 = LEOVZONE_PZONEHD_TBL[LEOdisk_type][temp_v0_2] - 7;

        //phi_t2 = LEOtgt_param.zone = phi_t2 - 7;
        LEOtgt_param.zone = temp_t7 & 0xFF;
        LEOtgt_param.head = 1;


        //if (1) {}
        //if (phi_t2 && phi_t2) {}
        phi_t2 = (u8)temp_t7;
    }

    phi_t1 = LEOZONE_SCYL_TBL[phi_t2];
    //if (temp_v0_2 != 0) {
    //    //phi_v1 = *(D_801D9516 + ((LEOdisk_type << 5) + (temp_v0_2 * 2)));
    //    //phi_v1 = LEOVZONE_TBL[((LEOdisk_type << 5) + (temp_v0_2 * 2))-1];
    //    phi_v1 = LEOVZONE_TBL[LEOdisk_type][temp_v0_2-1];
    //} else {
    //    phi_v1 = 0;
    //}
    phi_v1 = (temp_v0_2 != 0) ? LEOVZONE_TBL[LEOdisk_type][temp_v0_2-1] : 0;

    new_var = 1;
    if (LEOtgt_param.head != 0) {
        LEOtgt_param.cylinder = phi_t1 - ((lba - phi_v1) >> new_var);
        //phi_t1 = *(LEOVZONE_PZONEHD_TBL + 0x6E + (phi_t2 * 2));
        phi_t1 = LEOZONE_OUTERCYL_TBL[phi_t2-new_var];
        if (1) {}
    } else {
        //*(s16* )0x801E0000 = phi_t1 + ((u32) (lba - phi_v1) >> 1);
        LEOtgt_param.cylinder = phi_t1 + ((lba - phi_v1) >> new_var);
        if (phi_t2) {}
    }

    //if (phi_t2 != 0) {
    //    phi_a1 = LEO_sys_data.param.defect_num[phi_t2-1];
    //} else {
    //    phi_a1 = 0;
    //}

    phi_a1 = (phi_t2 != 0) ? LEO_sys_data.param.defect_num[phi_t2-1] : 0;

    //temp_t6 = ((&LEO_sys_data + phi_t2)->unk_8 - phi_a1) & 0xFFFF;
    phi_v1_2 = (LEO_sys_data.param.defect_num[phi_t2] - phi_a1);
    //phi_v1_2 = LEO_sys_data.param.defect_num[phi_t2];
    //phi_v1_2 -= phi_a1;

    while (phi_v1_2 != 0) {
        aux = LEO_sys_data.param.defect_data[phi_a1] + phi_t1;

        //if (LEOtgt_param.cylinder < aux) 
        if (((((LEOtgt_param.cylinder & 0xFFFF) & 0xFFFF) & 0xFFFF) & 0xFFFF) < aux)
        {
            break;
        }

        LEOtgt_param.cylinder++;
        phi_a1++;
        phi_v1_2--;
    }

    LEOtgt_param.sec_bytes = LEOBYTE_TBL1[phi_t2];
    //LEOtgt_param.blk_bytes = LEOBYTE_TBL2[phi_t2];
    phi_t1 = LEOBYTE_TBL2[phi_t2 & 0xFFFFFFFF];
    LEOtgt_param.blk_bytes = phi_t1;

    if ((LEO_country_code == 0) && (lba < 0xC)) {
        LEOtgt_param.sec_bytes = 0xC0;
        LEOtgt_param.blk_bytes = 0x3FC0;
    }

    return 0;
}
#else
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoutil/leoLba_to_phys.s")
#endif

u16 leoLba_to_vzone(u32 lba) {
    u16 i;
    const u16* ptr = LEOVZONE_TBL[LEOdisk_type];

    for (i = 0; i < ARRAY_COUNT(LEOVZONE_TBL[LEOdisk_type]); i++, ptr++) {
        if (lba < *ptr) {
            return i;
        }
    }

    return 0xFF;
}
