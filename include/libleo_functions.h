#ifndef LIBLEO_FUNCTIONS_H
#define LIBLEO_FUNCTIONS_H

#include "ultra64.h"
#include "n64dd.h"

s32 LeoReadWrite(LEOCmd* cmdBlock, s32 direction, u32 LBA, void* vAddr, u32 nLBAs, OSMesgQueue* mq);

void leoInitialize(OSPri compri, OSPri intpri, OSMesg* command_que_buf, u32 cmd_buff_size);
void leoCommand(void* cmd_blk_addr);
void LeoReset(void);
s32 __leoSetReset(void);
s32 LeoResetClear(void);

void leointerrupt(void* arg);

void leomain(void* arg);
u8 leoRead_system_area(void);

int LeoGetAAdr2(u32 ccode, int* dx, int* dy, int* cy);

void leoRead(void);
void leoRead_common(unsigned int offset);

s32 LeoLBAToByte(s32 startlba, u32 nlbas, s32* bytes);

void leoInquiry(void);

OSPiHandle* osLeoDiskInit(void);

s32 LeoSeek(LEOCmd* cmdBlock, u32 lba, OSMesgQueue* mq);

void leoReadDiskId(void);

u8 leoAnalize_asic_status(void);
u8 leoChk_asic_ready(u32 asic_cmd);
u8 leoChk_done_status(u32 asic_cmd);
u8 leoSend_asic_cmd_i(u32 asic_cmd, u32 asic_data);
u8 leoWait_mecha_cmd_done(u32 asic_cmd);
u8 leoSend_asic_cmd_w(u32 asic_cmd, u32 asic_data);
u8 leoSend_asic_cmd_w_nochkDiskChange(u32 asic_cmd, u32 asic_data);
u8 leoDetect_index_w(void);
u8 leoRecal_i(void);
u8 leoRecal_w(void);
u8 leoSeek_i(u16 rwmode);
u8 leoSeek_w(void);
u8 leoRecv_event_mesg(s32 control);
u32 leoChk_err_retry(u32 sense);
u8 leoChk_cur_drvmode(void);
void leoDrive_reset(void);
u32 leoChkUnit_atten(void);
u32 leoRetUnit_atten(void);
void leoClrUA_RESET(void);
void leoClrUA_MEDIUM_CHANGED(void);
void leoSetUA_MEDIUM_CHANGED(void);
void leoInitUnit_atten(void);

s32 LeoSpdlMotor(LEOCmd* cmdBlock, LEOSpdlMode mode, OSMesgQueue* mq);

int leoC2_Correction(void);

void leoSet_mseq(u16 rwmode);

void leoStart_stop(void);

u32 LeoDriveExist(void);

void leoMode_sel(void);

void leoRd_capacity(void);

u16 leoLba_to_phys(u32 lba);
u16 leoLba_to_vzone(u32 lba);

void leoRezero(void);

s32 LeoClearQueue(void);

s32 LeoByteToLBA(s32 startlba, u32 nbytes, s32* lba);

void leoClr_queue(void);
void leoClr_reset(void);

void leoTranslate();

void leoReadTimer(void);
void leoSetTimer(void);

// Handwritten function, looks up offset in `kanji` or similar of Shift-JIS codepoint using a table.
int LeoGetKAdr(int sjis);

// Handwritten function, looks up glyphs in a table.
int LeoGetAAdr(int code, int* dx, int* dy, int* cy);

void leoWrite(void);

s32 LeoCJCreateLeoManager(OSPri comPri, OSPri intPri, OSMesg* cmdBuf, s32 cmdMsgCnt);

s32 __osLeoInterrupt(void);

s32 LeoCACreateLeoManager(OSPri comPri, OSPri intPri, OSMesg* cmdBuf, s32 cmdMsgCnt);

s32 LeoTestUnitReady(LEOStatus* status);

void leoTest_unit_rdy(void);

void leoSeek(void);

#endif
