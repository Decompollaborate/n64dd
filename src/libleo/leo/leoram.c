#include "n64dd.h"
#include "n64dd_functions.h"
#include "libleo_functions.h"

leo_sys_form LEO_sys_data;

OSThread LEOcommandThread;

OSThread LEOinterruptThread;

u8 LEOcommandThreadStack[0x400];

u8 LEOinterruptThreadStack[0x400];

OSMesgQueue LEOcommand_que;

OSMesgQueue LEOevent_que;

OSMesgQueue LEOcontrol_que;

OSMesgQueue LEOdma_que;

OSMesgQueue LEOblock_que;

OSMesg LEOevent_que_buf[1];

OSMesg LEOcontrol_que_buf[1];

OSMesg LEOdma_que_buf[2];

OSMesg LEOblock_que_buf[1];

u8* LEOwrite_pointer;

LEOCmd* LEOcur_command;

u32 LEOasic_bm_ctl_shadow;

u32 LEOasic_seq_ctl_shadow;

u8 LEOdrive_flag;

vu8 LEOclr_que_flag;

// volatile?
vu16 LEOrw_flags;

u8 LEOdisk_type;

tgt_param_form LEOtgt_param;

UNK_TYPE4 LEO_country_code;
