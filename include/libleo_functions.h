#ifndef LIBLEO_FUNCTIONS_H
#define LIBLEO_FUNCTIONS_H

#include "ultra64.h"
#include "n64dd.h"

s32 LeoReadWrite(LEOCmd* cmdBlock, s32 direction, u32 LBA, void* vAddr, u32 nLBAs, OSMesgQueue* mq);

// void func_801CA7D0();
// void func_801CA9A4();
// void func_801CAB04();
// void func_801CAB94();
// void func_801CABB8();

// void func_801CAC40();
// void func_801CADD0();
// void func_801CB3CC();
// void func_801CB434();
// void func_801CB51C();

// void func_801CB640();
// void func_801CBABC();

// void func_801CBCD0();

void leoRead(void);
void leoRead_common(unsigned int offset);

s32 LeoByteToLBA(s32 startLBA, u32 nbytes, s32 *lbas);

void leoInquiry(void);
OSPiHandle* osLeoDiskInit(void);

// void func_801CC190();
void func_801CC1F0(void);

u8 leoAnalize_asic_status(void);
// void func_801CC48C();
// void func_801CC574();
// void func_801CC728();
// void func_801CC7D0();
u8 leoSend_asic_cmd_w(u32 asic_cmd, u32 asic_data);
u8 leoSend_asic_cmd_w_nochkDiskChange(u32 asic_cmd, u32 asic_data);
// void func_801CC944();
// void func_801CC96C();
u8 leoRecal_w(void);
// void func_801CC9BC();
u8 leoSeek_w(void);
// void func_801CCA5C();
u32 leoChk_err_retry(u32 sense);
s8 leoChk_cur_drvmode(void);

// void func_801CCC00();
// void func_801CCC30();
// void func_801CCC3C();
// void func_801CCC70();
// void func_801CCC8C();
// void func_801CCCA8();
// void func_801CCCC0();
// void func_801CCCD0();

int leoC2_Correction(void);
// void func_801CCE1C();
// void func_801CCEF0();
// void func_801CD170();
// void func_801CD558();
// void func_801CDDF4();
// void func_801CDE38();
// void leoSet_mseq();
void leoStart_stop(void);

// void LeoDriveExist();

void leoMode_sel(void);

void leoRd_capacity(void);

u16 leoLba_to_phys(u32 lba);
u16 leoLba_to_vzone(u32 lba);

void leoRezero(void);

// void LeoClearQueue();

// void LeoByteToLBA();

void func_801CE7E0(void);
void leoClr_reset(void);

void func_801CE900(void);

void func_801CEBA0(void);
void func_801CEC5C(void);
// void func_801CEE94();
// void func_801CF004();

// void LeoGetKAdr();

void leoWrite(void);

// void func_801D2170();

// void func_801D23B0();
// void func_801D2910();
// void func_801D29C4();
// void func_801D2A80();

// void func_801D2CB0();

void leoTest_unit_rdy(void);
void leoSeek(void);

#endif
