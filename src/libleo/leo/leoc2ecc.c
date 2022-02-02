#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

#if 0
static const unsigned char ganlog[512];

static const unsigned char glog[512];

int leoC2_Correction();
//{
//}

// static
void leoC2_single_ecc();
//{
//    u8* pointer;
//    unsigned int byte;
//    u8* p_s;
//}

// static
void leoC2_double_ecc();
//{
//    register unsigned int s0;
//    register unsigned int error_k;
//    u8* pointer1;
//    u8* pointer2;
//    unsigned int k;
//    unsigned int m;
//    unsigned int a;
//    unsigned int d;
//    unsigned int byte;
//    u8* p_s;
//    Label: c2_2_2 @ 580;
//    Label: c2_2_1 @ 624;
//}

// static
void leoC2_3_ecc();
//{
//    register unsigned int s0;
//    register unsigned int error_i;
//    register unsigned int error_j;
//    register unsigned int error_k;
//    u8* pointer1;
//    u8* pointer2;
//    u8* pointer3;
//    unsigned int byte;
//    unsigned int ii;
//    unsigned int jj;
//    unsigned int kk;
//    unsigned int c;
//    unsigned int f;
//    unsigned int o;
//    unsigned int b;
//    unsigned int d;
//    unsigned int h;
//    unsigned int a;
//    unsigned int e;
//    unsigned int g;
//    unsigned int p;
//    u8* p_s;
//    Label: c2_3_3 @ 1756;
//    Label: c2_3_2 @ 1800;
//    Label: c2_3_1 @ 1844;
//}

// static
void leoC2_4_ecc();
//{
//    register unsigned int s0;
//    register unsigned int R0;
//    register unsigned int R1;
//    register unsigned int R2;
//    register unsigned int R3;
//    u8* pointer1;
//    u8* pointer2;
//    u8* pointer3;
//    u8* pointer4;
//    unsigned int aa;
//    unsigned int bb;
//    unsigned int dd;
//    unsigned int ee;
//    unsigned int gg;
//    unsigned int hh;
//    unsigned int pp;
//    unsigned int qq;
//    unsigned int ll;
//    unsigned int ii;
//    unsigned int jj;
//    unsigned int kk;
//    unsigned int byte;
//    unsigned int s;
//    unsigned int a;
//    unsigned int e;
//    unsigned int g;
//    unsigned int p;
//    unsigned int c;
//    unsigned int f;
//    unsigned int o;
//    unsigned int r;
//    unsigned int t;
//    unsigned int u;
//    unsigned int v;
//    unsigned int b;
//    unsigned int d;
//    unsigned int h;
//    unsigned int q;
//    u8* p_s;
//    Label: c2_4_4 @ 4276;
//    Label: c2_4_3 @ 4320;
//    Label: c2_4_2 @ 4364;
//    Label: c2_4_1 @ 4408;
//}

// static
int leoAlpha_mult(int i, int k);
//{
//}

// static
int leoAlpha_div(int i, int k);
//{
//}
#endif

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoc2ecc/R_801D96D0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoc2ecc/R_801D98D0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoc2ecc/leoC2_Correction.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoc2ecc/leoC2_single_ecc.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoc2ecc/leoC2_double_ecc.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoc2ecc/leoC2_3_ecc.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoc2ecc/leoC2_4_ecc.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoc2ecc/leoAlpha_mult.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/leoc2ecc/leoAlpha_div.s")
