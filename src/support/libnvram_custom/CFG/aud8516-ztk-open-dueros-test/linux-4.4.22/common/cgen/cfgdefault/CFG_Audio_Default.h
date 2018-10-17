/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2014. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/
#ifndef _CFG_AUDIO_H
#define _CFG_AUDIO_H
/* include rule :
   1st : find path/files relative current position (Common)
   2nd : find path/files from other projects
*/
#include "CFG_AUDIO_File.h"

//audio related default value
#include "cfgdefault/sph_coeff_record_mode_default.h"
#include "cfgdefault/sph_coeff_dmnr_default.h"
#include "cfgdefault/sph_coeff_dmnr_handsfree_default.h"
#include "cfgdefault/audio_hd_record_custom.h"
#include "cfgdefault/audio_acf_default.h"
#include "cfgdefault/audio_hcf_default.h"
#include "cfgdefault/audio_effect_default.h"
#include "cfgdefault/audio_gain_table_default.h"
#include "cfgdefault/audio_ver1_volume_custom_default.h"
#include "cfgdefault/voice_recognition_custom.h"
#include "cfgdefault/audio_audenh_control_option.h"
#include "cfgdefault/audio_voip_custom.h"
//#include "cfgdefault/audio_acfsub_default.h"
#include "cfgdefault/audio_music_drc_default.h"
#include "cfgdefault/audio_ringtone_drc_default.h"
#include "cfgdefault/sph_coeff_anc_default.h"
#include "cfgdefault/audio_speaker_monitor_custom.h"
#include "cfgdefault/sph_coeff_lpbk_default.h"

//speech related default value
#include "cfgdefault/sph_coeff_default.h"
#include "cfgdefault/audio_custom.h"
#include "cfgdefault/med_audio_default.h"
#include "cfgdefault/audio_volume_custom_default.h"
#include "cfgdefault/audio_ver1_volume_custom_default.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __ALLOCATE_CFG_AUDIO_DEFAULT_H
// Allocate data by \vendor\mediatek\proprietary\external\nvram\libcustom_nvram\CFG_file_info.c

AUDIO_CUSTOM_PARAM_STRUCT speech_custom_default = {
    /* INT8 volume[MAX_VOL_CATE][MAX_VOL_TYPE] */
    /* Normal volume: TON, SPK, MIC, FMR, SPH, SID, MED */
    GAIN_NOR_TON_VOL, GAIN_NOR_KEY_VOL, GAIN_NOR_MIC_VOL, GAIN_NOR_FMR_VOL, GAIN_NOR_SPH_VOL, GAIN_NOR_SID_VOL, GAIN_NOR_MED_VOL
    ,
    /* Headset volume: TON, SPK, MIC, FMR, SPH, SID, MED */
    GAIN_HED_TON_VOL, GAIN_HED_KEY_VOL, GAIN_HED_MIC_VOL, GAIN_HED_FMR_VOL, GAIN_HED_SPH_VOL, GAIN_HED_SID_VOL, GAIN_HED_MED_VOL
    ,
    /* Handfree volume: TON, SPK, MIC, FMR, SPH, SID, MED */
    GAIN_HND_TON_VOL, GAIN_HND_KEY_VOL, GAIN_HND_MIC_VOL, GAIN_HND_FMR_VOL, GAIN_HND_SPH_VOL, GAIN_HND_SID_VOL, GAIN_HND_MED_VOL
    ,
    /* UINT16 speech_common_para[12] */
    DEFAULT_SPEECH_COMMON_PARA
    ,
    /* UINT16 speech_mode_para[8][16] */
    DEFAULT_SPEECH_NORMAL_MODE_PARA,
    DEFAULT_SPEECH_EARPHONE_MODE_PARA,
    DEFAULT_SPEECH_LOUDSPK_MODE_PARA,
    DEFAULT_SPEECH_BT_EARPHONE_MODE_PARA,
    DEFAULT_SPEECH_BT_CORDLESS_MODE_PARA,
    DEFAULT_SPEECH_CARKIT_MODE_PARA,
    DEFAULT_SPEECH_AUX1_MODE_PARA,
    DEFAULT_SPEECH_AUX2_MODE_PARA
    ,
    /* UINT16 speech_volume_para[4] */
    DEFAULT_SPEECH_VOL_PARA
    ,
    /* UINT16 debug_info[16] */
    DEFAULT_AUDIO_DEBUG_INFO
    ,
    /* INT16 sph_in_fir[6][45], sph_out_fir */
    SPEECH_INPUT_FIR_COEFF,
    SPEECH_OUTPUT_FIR_COEFF
    ,
    /* UINT16 DG_DL_Speech */
    DG_DL_Speech
    ,
    /* UINT16 DG_Microphone */
    DG_Microphone
    ,
    /* UINT16 FM record volume*/
    FM_Record_Vol
    ,
    /* UINT16 BT sync type and length*/
    DEFAULT_BLUETOOTH_SYNC_TYPE,
    DEFAULT_BLUETOOTH_SYNC_LENGTH
    ,
    /* UINT16 BT PCM in/out digital gain*/
    DEFAULT_BT_PCM_IN_VOL,
    DEFAULT_BT_PCM_OUT_VOL
    ,
    /* user mode : normal mode, earphone mode, loud speaker mode */
    /* UCHAR  user_mode             */
    VOL_NORMAL
    ,
    /* auto VM record setting */
    DEFAULT_VM_SUPPORT,
    DEFAULT_AUTO_VM,
    /* Micbais voltage 1900 --> 2200 */
    MICBAIS,
};

AUDIO_VER1_CUSTOM_VOLUME_STRUCT audio_ver1_custom_default = {
    VER1_AUD_VOLUME_RING,
    VER1_AUD_VOLUME_SIP,
    VER1_AUD_VOLUME_MIC,
    VER1_AUD_VOLUME_FM,
    VER1_AUD_VOLUME_SPH,
    VER1_AUD_VOLUME_SPH, // sph2 now use the same
    VER1_AUD_VOLUME_SID,
    VER1_AUD_VOLUME_MEDIA,
    VER1_AUD_VOLUME_MATV,
    VER1_AUD_NORMAL_VOLUME_DEFAULT,
    VER1_AUD_HEADSER_VOLUME_DEFAULT,
    VER1_AUD_SPEAKER_VOLUME_DEFAULT,
    VER1_AUD_HEADSETSPEAKER_VOLUME_DEFAULT,
    VER1_AUD_EXTAMP_VOLUME_DEFAULT,
    VER1_AUD_VOLUME_LEVEL_DEFAULT
};


AUDIO_CUSTOM_WB_PARAM_STRUCT wb_speech_custom_default = {
    /* unsigned short speech_mode_wb_para[8][16] */
    DEFAULT_WB_SPEECH_NORMAL_MODE_PARA,
    DEFAULT_WB_SPEECH_EARPHONE_MODE_PARA,
    DEFAULT_WB_SPEECH_LOUDSPK_MODE_PARA,
    DEFAULT_WB_SPEECH_BT_EARPHONE_MODE_PARA,
    DEFAULT_WB_SPEECH_BT_CORDLESS_MODE_PARA,
    DEFAULT_WB_SPEECH_CARKIT_MODE_PARA,
    DEFAULT_WB_SPEECH_AUX1_MODE_PARA,
    DEFAULT_WB_SPEECH_AUX2_MODE_PARA,
    /* short sph_wb_in_fir[6][90] */
    WB_Speech_Input_FIR_Coeff,
    /* short sph_wb_out_fir[6][90] */
    WB_Speech_Output_FIR_Coeff,
};
#if defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V5)
/*
unsigned int bes_loudness_Sep_LR_Filter;
    unsigned int bes_loudness_WS_Gain_Max;
    unsigned int bes_loudness_WS_Gain_Min;
    unsigned int bes_loudness_Filter_First;
    unsigned int bes_loudness_Num_Bands;
    unsigned int bes_loudness_Flt_Bank_Order;
    unsigned int bes_loudness_Cross_Freq[7];
    int DRC_Th[8][5];
    int DRC_Gn[8][5];
    int SB_Gn[8];
    unsigned int SB_Mode[8];
    unsigned int DRC_Delay;
    unsigned int Att_Time[8][6];
    unsigned int Rel_Time[8][6];
    int Hyst_Th[8][6];
    int Lim_Th;
    int Lim_Gn;
    unsigned int Lim_Const;
    unsigned int Lim_Delay;
    int SWIPRev;

*/
AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_custom_default = {
#if 1
    BES_LOUDNESS_ACF_L_HPF_FC,
    BES_LOUDNESS_ACF_L_HPF_ORDER,
    BES_LOUDNESS_ACF_L_LPF_FC,
    BES_LOUDNESS_ACF_L_LPF_ORDER,
    BES_LOUDNESS_ACF_L_BPF_FC,
    BES_LOUDNESS_ACF_L_BPF_BW,
    BES_LOUDNESS_ACF_L_BPF_GAIN,

    BES_LOUDNESS_ACF_R_HPF_FC,
    BES_LOUDNESS_ACF_R_HPF_ORDER,
    BES_LOUDNESS_ACF_R_LPF_FC,
    BES_LOUDNESS_ACF_R_LPF_ORDER,
    BES_LOUDNESS_ACF_R_BPF_FC,
    BES_LOUDNESS_ACF_R_BPF_BW,
    BES_LOUDNESS_ACF_R_BPF_GAIN,

    BES_LOUDNESS_ACF_SEP_LR_FILTER,
    BES_LOUDNESS_ACF_WS_GAIN_MAX,
    BES_LOUDNESS_ACF_WS_GAIN_MIN,
    BES_LOUDNESS_ACF_FILTER_FIRST,
    BES_LOUDNESS_ACF_NUM_BANDS,
    BES_LOUDNESS_ACF_FLT_BANK_ORDER,
    BES_LOUDNESS_ACF_CROSSOVER_FREQ,
    BES_LOUDNESS_ACF_GAIN_MAP_IN,
    BES_LOUDNESS_ACF_GAIN_MAP_OUT,
    BES_LOUDNESS_ACF_SB_GAIN,
    BES_LOUDNESS_ACF_SB_MODE,
    BES_LOUDNESS_ACF_DRC_DELAY,
    BES_LOUDNESS_ACF_ATT_TIME,
    BES_LOUDNESS_ACF_REL_TIME,
    BES_LOUDNESS_ACF_HYST_TH,
    BES_LOUDNESS_ACF_LIM_TH,
    BES_LOUDNESS_ACF_LIM_GN,
    BES_LOUDNESS_ACF_LIM_CONST,
    BES_LOUDNESS_ACF_LIM_DELAY,
    0x0520,
#else
    BES_LOUDNESS_HSF_COEFF_L,
    BES_LOUDNESS_BPF_COEFF_L,
    BES_LOUDNESS_LPF_COEFF_L,
    BES_LOUDNESS_HSF_COEFF_R,
    BES_LOUDNESS_BPF_COEFF_R,
    BES_LOUDNESS_LPF_COEFF_R,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,

    BES_LOUDNESS_SEP_LR_FILTER,
    BES_LOUDNESS_NUM_BANDS,
    BES_LOUDNESS_FLT_BANK_ORDER,
    BES_LOUDNESS_CROSSOVER_FREQ,

    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
    BES_LOUDNESS_SB_GAIN,
    BES_LOUDNESS_SB_MODE,
    BES_LOUDNESS_DRC_DELAY,
    BES_LOUDNESS_ATT_TIME,
    BES_LOUDNESS_REL_TIME,
    BES_LOUDNESS_HYST_TH,
    BES_LOUDNESS_LIM_TH,
    BES_LOUDNESS_LIM_GN,
    BES_LOUDNESS_LIM_CONST,
    BES_LOUDNESS_LIM_DELAY,
#endif

};
#if 0
AUDIO_ACF_CUSTOM_PARAM_STRUCT audiosub_custom_default = {
    BES_LOUDNESS_HSF_COEFF_SUB_L,
    BES_LOUDNESS_BPF_COEFF_SUB_L,
    BES_LOUDNESS_LPF_COEFF_SUB_L,
    BES_LOUDNESS_HSF_COEFF_SUB_R,
    BES_LOUDNESS_BPF_COEFF_SUB_R,
    BES_LOUDNESS_LPF_COEFF_SUB_R,
    BES_LOUDNESS_WS_GAIN_MAX_SUB,
    BES_LOUDNESS_WS_GAIN_MIN_SUB,
    BES_LOUDNESS_FILTER_FIRST_SUB,

    BES_LOUDNESS_SEP_LR_FILTER_SUB,
    BES_LOUDNESS_NUM_BANDS_SUB,
    BES_LOUDNESS_FLT_BANK_ORDER_SUB,
    BES_LOUDNESS_CROSSOVER_FREQ_SUB,

    BES_LOUDNESS_GAIN_MAP_IN_SUB,
    BES_LOUDNESS_GAIN_MAP_OUT_SUB,
    BES_LOUDNESS_SB_GAIN_SUB,
    BES_LOUDNESS_SB_MODE_SUB,
    BES_LOUDNESS_DRC_DELAY_SUB,
    BES_LOUDNESS_ATT_TIME_SUB,
    BES_LOUDNESS_REL_TIME_SUB,
    BES_LOUDNESS_HYST_TH_SUB,
    BES_LOUDNESS_LIM_TH_SUB,
    BES_LOUDNESS_LIM_GN,
    BES_LOUDNESS_LIM_CONST,
    BES_LOUDNESS_LIM_DELAY,


};
#endif

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_hcf_custom_default = {
    BES_LOUDNESS_HCF_L_HPF_FC,
    BES_LOUDNESS_HCF_L_HPF_ORDER,
    BES_LOUDNESS_HCF_L_LPF_FC,
    BES_LOUDNESS_HCF_L_LPF_ORDER,
    BES_LOUDNESS_HCF_L_BPF_FC,
    BES_LOUDNESS_HCF_L_BPF_BW,
    BES_LOUDNESS_HCF_L_BPF_GAIN,

    BES_LOUDNESS_HCF_R_HPF_FC,
    BES_LOUDNESS_HCF_R_HPF_ORDER,
    BES_LOUDNESS_HCF_R_LPF_FC,
    BES_LOUDNESS_HCF_R_LPF_ORDER,
    BES_LOUDNESS_HCF_R_BPF_FC,
    BES_LOUDNESS_HCF_R_BPF_BW,
    BES_LOUDNESS_HCF_R_BPF_GAIN,

    BES_LOUDNESS_HCF_SEP_LR_FILTER,
    BES_LOUDNESS_HCF_WS_GAIN_MAX,
    BES_LOUDNESS_HCF_WS_GAIN_MIN,
    BES_LOUDNESS_HCF_FILTER_FIRST,
    BES_LOUDNESS_HCF_NUM_BANDS,
    BES_LOUDNESS_HCF_FLT_BANK_ORDER,
    BES_LOUDNESS_HCF_CROSSOVER_FREQ,
    BES_LOUDNESS_HCF_GAIN_MAP_IN,
    BES_LOUDNESS_HCF_GAIN_MAP_OUT,
    BES_LOUDNESS_HCF_SB_GAIN,
    BES_LOUDNESS_HCF_SB_MODE,
    BES_LOUDNESS_HCF_DRC_DELAY,
    BES_LOUDNESS_HCF_ATT_TIME,
    BES_LOUDNESS_HCF_REL_TIME,
    BES_LOUDNESS_HCF_HYST_TH,
    BES_LOUDNESS_HCF_LIM_TH,
    BES_LOUDNESS_HCF_LIM_GN,
    BES_LOUDNESS_HCF_LIM_CONST,
    BES_LOUDNESS_HCF_LIM_DELAY,
    0x0520,

};
AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_vibspk_custom_default = {
    BES_LOUDNESS_ACF_L_HPF_FC,
    BES_LOUDNESS_ACF_L_HPF_ORDER,
    BES_LOUDNESS_ACF_L_LPF_FC,
    BES_LOUDNESS_ACF_L_LPF_ORDER,
    BES_LOUDNESS_ACF_L_BPF_FC,
    BES_LOUDNESS_ACF_L_BPF_BW,
    BES_LOUDNESS_ACF_L_BPF_GAIN,

    BES_LOUDNESS_ACF_R_HPF_FC,
    BES_LOUDNESS_ACF_R_HPF_ORDER,
    BES_LOUDNESS_ACF_R_LPF_FC,
    BES_LOUDNESS_ACF_R_LPF_ORDER,
    BES_LOUDNESS_ACF_R_BPF_FC,
    BES_LOUDNESS_ACF_R_BPF_BW,
    BES_LOUDNESS_ACF_R_BPF_GAIN,

    0,
    BES_LOUDNESS_ACF_WS_GAIN_MAX,
    BES_LOUDNESS_ACF_WS_GAIN_MIN,
    BES_LOUDNESS_ACF_FILTER_FIRST,
    BES_LOUDNESS_ACF_NUM_BANDS,
    BES_LOUDNESS_ACF_FLT_BANK_ORDER,
    BES_LOUDNESS_ACF_CROSSOVER_FREQ,
    BES_LOUDNESS_ACF_GAIN_MAP_IN,
    BES_LOUDNESS_ACF_GAIN_MAP_OUT,
    BES_LOUDNESS_ACF_SB_GAIN,
    BES_LOUDNESS_ACF_SB_MODE,
    BES_LOUDNESS_ACF_DRC_DELAY,
    BES_LOUDNESS_ACF_ATT_TIME,
    BES_LOUDNESS_ACF_REL_TIME,
    BES_LOUDNESS_ACF_HYST_TH,
    BES_LOUDNESS_ACF_LIM_TH,
    BES_LOUDNESS_ACF_LIM_GN,
    BES_LOUDNESS_ACF_LIM_CONST,
    BES_LOUDNESS_ACF_LIM_DELAY,
    0x0520,


};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_musicdrc_custom_default = {
    BES_LOUDNESS_MUSICDRC_L_HPF_FC,
    BES_LOUDNESS_MUSICDRC_L_HPF_ORDER,
    BES_LOUDNESS_MUSICDRC_L_LPF_FC,
    BES_LOUDNESS_MUSICDRC_L_LPF_ORDER,
    BES_LOUDNESS_MUSICDRC_L_BPF_FC,
    BES_LOUDNESS_MUSICDRC_L_BPF_BW,
    BES_LOUDNESS_MUSICDRC_L_BPF_GAIN,

    BES_LOUDNESS_MUSICDRC_R_HPF_FC,
    BES_LOUDNESS_MUSICDRC_R_HPF_ORDER,
    BES_LOUDNESS_MUSICDRC_R_LPF_FC,
    BES_LOUDNESS_MUSICDRC_R_LPF_ORDER,
    BES_LOUDNESS_MUSICDRC_R_BPF_FC,
    BES_LOUDNESS_MUSICDRC_R_BPF_BW,
    BES_LOUDNESS_MUSICDRC_R_BPF_GAIN,

    BES_LOUDNESS_MUSICDRC_SEP_LR_FILTER,
    BES_LOUDNESS_MUSICDRC_WS_GAIN_MAX,
    BES_LOUDNESS_MUSICDRC_WS_GAIN_MIN,
    BES_LOUDNESS_MUSICDRC_FILTER_FIRST,
    BES_LOUDNESS_MUSICDRC_NUM_BANDS,
    BES_LOUDNESS_MUSICDRC_FLT_BANK_ORDER,
    BES_LOUDNESS_MUSICDRC_CROSSOVER_FREQ,
    BES_LOUDNESS_MUSICDRC_GAIN_MAP_IN,
    BES_LOUDNESS_MUSICDRC_GAIN_MAP_OUT,
    BES_LOUDNESS_MUSICDRC_SB_GAIN,
    BES_LOUDNESS_MUSICDRC_SB_MODE,
    BES_LOUDNESS_MUSICDRC_DRC_DELAY,
    BES_LOUDNESS_MUSICDRC_ATT_TIME,
    BES_LOUDNESS_MUSICDRC_REL_TIME,
    BES_LOUDNESS_MUSICDRC_HYST_TH,
    BES_LOUDNESS_MUSICDRC_LIM_TH,
    BES_LOUDNESS_MUSICDRC_LIM_GN,
    BES_LOUDNESS_MUSICDRC_LIM_CONST,
    BES_LOUDNESS_MUSICDRC_LIM_DELAY,
    0x0520,


};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_ringtonedrc_custom_default = {
    BES_LOUDNESS_RINGTONEDRC_L_HPF_FC,
    BES_LOUDNESS_RINGTONEDRC_L_HPF_ORDER,
    BES_LOUDNESS_RINGTONEDRC_L_LPF_FC,
    BES_LOUDNESS_RINGTONEDRC_L_LPF_ORDER,
    BES_LOUDNESS_RINGTONEDRC_L_BPF_FC,
    BES_LOUDNESS_RINGTONEDRC_L_BPF_BW,
    BES_LOUDNESS_RINGTONEDRC_L_BPF_GAIN,

    BES_LOUDNESS_RINGTONEDRC_R_HPF_FC,
    BES_LOUDNESS_RINGTONEDRC_R_HPF_ORDER,
    BES_LOUDNESS_RINGTONEDRC_R_LPF_FC,
    BES_LOUDNESS_RINGTONEDRC_R_LPF_ORDER,
    BES_LOUDNESS_RINGTONEDRC_R_BPF_FC,
    BES_LOUDNESS_RINGTONEDRC_R_BPF_BW,
    BES_LOUDNESS_RINGTONEDRC_R_BPF_GAIN,

    BES_LOUDNESS_RINGTONEDRC_SEP_LR_FILTER,
    BES_LOUDNESS_RINGTONEDRC_WS_GAIN_MAX,
    BES_LOUDNESS_RINGTONEDRC_WS_GAIN_MIN,
    BES_LOUDNESS_RINGTONEDRC_FILTER_FIRST,
    BES_LOUDNESS_RINGTONEDRC_NUM_BANDS,
    BES_LOUDNESS_RINGTONEDRC_FLT_BANK_ORDER,
    BES_LOUDNESS_RINGTONEDRC_CROSSOVER_FREQ,
    BES_LOUDNESS_RINGTONEDRC_GAIN_MAP_IN,
    BES_LOUDNESS_RINGTONEDRC_GAIN_MAP_OUT,
    BES_LOUDNESS_RINGTONEDRC_SB_GAIN,
    BES_LOUDNESS_RINGTONEDRC_SB_MODE,
    BES_LOUDNESS_RINGTONEDRC_DRC_DELAY,
    BES_LOUDNESS_RINGTONEDRC_ATT_TIME,
    BES_LOUDNESS_RINGTONEDRC_REL_TIME,
    BES_LOUDNESS_RINGTONEDRC_HYST_TH,
    BES_LOUDNESS_RINGTONEDRC_LIM_TH,
    BES_LOUDNESS_RINGTONEDRC_LIM_GN,
    BES_LOUDNESS_RINGTONEDRC_LIM_CONST,
    BES_LOUDNESS_RINGTONEDRC_LIM_DELAY,
    0x0520,


};


#elif defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V4)
AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_custom_default = {
    BES_LOUDNESS_HSF_COEFF,
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_LPF_COEFF,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_ATT_TIME,
    BES_LOUDNESS_REL_TIME,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};
#if 0
AUDIO_ACF_CUSTOM_PARAM_STRUCT audiosub_custom_default = {
    BES_LOUDNESS_HSF_COEFF_SUB,
    BES_LOUDNESS_BPF_COEFF_SUB,
    BES_LOUDNESS_LPF_COEFF_SUB,
    BES_LOUDNESS_WS_GAIN_MAX_SUB,
    BES_LOUDNESS_WS_GAIN_MIN_SUB,
    BES_LOUDNESS_FILTER_FIRST_SUB,
    BES_LOUDNESS_ATT_TIME_SUB,
    BES_LOUDNESS_REL_TIME_SUB,
    BES_LOUDNESS_GAIN_MAP_IN_SUB,
    BES_LOUDNESS_GAIN_MAP_OUT_SUB,
};
#endif

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_hcf_custom_default = {
    BES_LOUDNESS_HCF_HSF_COEFF,
    BES_LOUDNESS_HCF_BPF_COEFF,
    BES_LOUDNESS_HCF_LPF_COEFF,
    BES_LOUDNESS_HCF_WS_GAIN_MAX,
    BES_LOUDNESS_HCF_WS_GAIN_MIN,
    BES_LOUDNESS_HCF_FILTER_FIRST,
    BES_LOUDNESS_HCF_ATT_TIME,
    BES_LOUDNESS_HCF_REL_TIME,
    BES_LOUDNESS_HCF_GAIN_MAP_IN,
    BES_LOUDNESS_HCF_GAIN_MAP_OUT,
};
AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_vibspk_custom_default = {
    BES_LOUDNESS_HSF_COEFF,
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_LPF_COEFF,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_ATT_TIME,
    BES_LOUDNESS_REL_TIME,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_musicdrc_custom_default = {
    BES_LOUDNESS_HSF_COEFF,
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_LPF_COEFF,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_ATT_TIME,
    BES_LOUDNESS_REL_TIME,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_ringtonedrc_custom_default = {
    BES_LOUDNESS_HSF_COEFF,
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_LPF_COEFF,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_ATT_TIME,
    BES_LOUDNESS_REL_TIME,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};


#else
AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_custom_default = {
    /* Compensation Filter HSF coeffs: default all pass filter       */
    /* BesLoudness also uses this coeffs    */
    BES_LOUDNESS_HSF_COEFF,
    /* Compensation Filter BPF coeffs: default all pass filter      */
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_DRC_FORGET_TABLE,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_hcf_custom_default = {
    /* Compensation Filter HSF coeffs: default all pass filter       */
    /* BesLoudness also uses this coeffs    */
    BES_LOUDNESS_HCF_HSF_COEFF,
    /* Compensation Filter BPF coeffs: default all pass filter      */
    BES_LOUDNESS_HCF_BPF_COEFF,
    BES_LOUDNESS_HCF_DRC_FORGET_TABLE,
    BES_LOUDNESS_HCF_WS_GAIN_MAX,
    BES_LOUDNESS_HCF_WS_GAIN_MIN,
    BES_LOUDNESS_HCF_FILTER_FIRST,
    BES_LOUDNESS_HCF_GAIN_MAP_IN,
    BES_LOUDNESS_HCF_GAIN_MAP_OUT,
};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_vibspk_custom_default = {
    /* Compensation Filter HSF coeffs: default all pass filter       */
    /* BesLoudness also uses this coeffs    */
    BES_LOUDNESS_HSF_COEFF,
    /* Compensation Filter BPF coeffs: default all pass filter      */
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_DRC_FORGET_TABLE,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_musicdrc_custom_default = {
    /* Compensation Filter HSF coeffs: default all pass filter       */
    /* BesLoudness also uses this coeffs    */
    BES_LOUDNESS_HSF_COEFF,
    /* Compensation Filter BPF coeffs: default all pass filter      */
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_DRC_FORGET_TABLE,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_ringtonedrc_custom_default = {
    /* Compensation Filter HSF coeffs: default all pass filter       */
    /* BesLoudness also uses this coeffs    */
    BES_LOUDNESS_HSF_COEFF,
    /* Compensation Filter BPF coeffs: default all pass filter      */
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_DRC_FORGET_TABLE,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};

#endif

AUDIO_EFFECT_CUSTOM_PARAM_STRUCT audio_effect_custom_default = {
    // DSRD parameters
    BSRD_LEVEL,
    BSRD_DISTANCE1,
    BSRD_DISTANCE2,
    BSRD_BAND_SELECT,

    // BASS
    BASS_CUTOFF_FREQ,
    BASS_ISVB,

    //EQ effect
    NORMAL_GAIN_LEVEL,
    DANCE_GAIN_LEVEL,
    BASS_GAIN_LEVEL,
    CLASSICAL_GAIN_LEVEL,
    TREBLE_GAIN_LEVEL,
    PARTY_GAIN_LEVEL,
    POP_GAIN_LEVEL,
    ROCK_GAIN_LEVEL,

    //loudness mode
    LOUDENHANCEMODE,

    //TS
    TIME_TD_TF,
    TIME_TS_RATIO
};

AUDIO_PARAM_MED_STRUCT audio_param_med_default = {
    SPEECH_INPUT_MED_FIR_COEFF,
    SPEECH_OUTPUT_MED_FIR_COEFF,
    FIR_output_index,
    FIR_input_index,
    MED_SPEECH_NORMAL_MODE_PARA,
    MED_SPEECH_EARPHONE_MODE_PARA,
    MED_SPEECH_BT_EARPHONE_MODE_PARA,
    MED_SPEECH_LOUDSPK_MODE_PARA,
    MED_SPEECH_CARKIT_MODE_PARA,
    MED_SPEECH_BT_CORDLESS_MODE_PARA,
    MED_SPEECH_AUX1_MODE_PARA,
    MED_SPEECH_AUX2_MODE_PARA
};


AUDIO_VOLUME_CUSTOM_STRUCT audio_volume_custom_default = {
    AUD_VOLUME_RING,
    AUD_VOLUME_KEY,
    AUD_VOLUME_MIC,
    AUD_VOLUME_FMR,
    AUD_VOLUME_SPH,
    AUD_VOLUME_SID,
    AUD_VOLUME_MEDIA,
    AUD_VOLUME_MATV
};

AUDIO_CUSTOM_EXTRA_PARAM_STRUCT dual_mic_custom_default = {
    DEFAULT_SPEECH_DUAL_MIC_ABF_PARA,
    DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA,
    DEFAULT_SPEECH_DUAL_MIC_ABF_PARA_LoudSPK,
    DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA_LoudSPK,
    DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA_VR,
    DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA_VOIP,
    DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA_VOIP_LoudSPK
};

AUDIO_GAIN_TABLE_STRUCT Gain_control_table_default = {
    DEFAULT_VOICE_GAIN_TABLE_PARA,
    DEFAULT_SYSTEM_GAIN_TABLE_PARA,
    DEFAULT_RINGTONE_GAIN_TABLE_PARA,
    DEFAULT_MUSIC_GAIN_TABLE_PARA,
    DEFAULT_ALARM_GAIN_TABLE_PARA,
    DEFAULT_NOTIFICATION_GAIN_TABLE_PARA,
    DEFAULT_BLUETOOTH_SCO_GAIN_TABLE_PARA,
    DEFAULT_ENFORCEAUDIBLE_GAIN_TABLE_PARA,
    DEFAULT_DTMF_GAIN_TABLE_PARA,
    DEFAULT_TTS_GAIN_TABLE_PARA,
    DEFAULT_FM_GAIN_TABLE_PARA,
    DEFAULT_MATV_GAIN_TABLE_PARA,
    DEFAULT_SPEECH_NB_GAIN_TABLE_PARA,
    DEFAULT_SPEECH_WB_GAIN_TABLE_PARA,
    DEFAULT_SIDETONE_NB_GAIN_TABLE_PARA,
    DEFAULT_SIDETONE_WB_GAIN_TABLE_PARA,
    DEFAULT_MICROPHONE_GAIN_TABLE_PARA
};

AUDIO_BT_GAIN_STRUCT bt_gain_control_default = {
    DEFAULT_BLUETOOTH_NREC_GAIN_TABLE_PARA
};

AUDIO_HD_RECORD_PARAM_STRUCT Hd_Recrod_Par_default = {
    //hd_rec mode num & fir num
    HD_REC_MODE_INDEX_NUM,
    HD_REC_FIR_INDEX_NUM,
    //hd_rec_speech_mode_para
    DEFAULT_HD_RECORD_SPH_MODE_PAR,
    //hd_rec_fir
    DEFAULT_HD_RECORD_FIR_Coeff,
    //hd_rec fir mapping - ch1
    DEFAULT_HD_RECORD_MODE_FIR_MAPPING_CH1,
    //hd_rec fir mapping - ch2
    DEFAULT_HD_RECORD_MODE_FIR_MAPPING_CH2,
    //hd_rec device mode mapping
    DEFAULT_HD_RECORD_MODE_DEV_MAPPING,
    //hd_rec_map_to_input_src
    DEFAULT_HD_RECORD_MODE_INPUT_SRC_MAPPING,
    //hd_rec_map_to_stereo_flag
    DEFAULT_HD_RECORD_MODE_STEREO_FLAGS
};

AUDIO_HD_RECORD_SCENE_TABLE_STRUCT Hd_Recrod_Scene_Table_default = {
    DEFAULT_HD_RECORD_NUM_VOICE_RECOGNITION_SCENES,
    DEFAULT_HD_RECORD_NUM_VOICE_SCENES,
    DEFAULT_HD_RECORD_NUM_VIDEO_SCENES,
    DEFAULT_HD_RECORD_NUM_VOICE_UNLOCK_SCENES,
    DEFAULT_HD_RECORD_NUM_CUSTOMIZATION_SCENES,
    DEFAULT_HD_RECORD_SCENE_TABLE,
    DEFAULT_HD_RECORD_SCENE_NAME
};

VOICE_RECOGNITION_PARAM_STRUCT Voice_Recognize_Par_default = {
    //for framework, voice ui related
    DEFAULT_AP_NUM,
    DEFAULT_LANGUAGE_NUM,
    DEFAULT_LANGUAGE_FOLDER_NAME,
    DEFAULT_COMMAND_NUM_PER_LAN,
    DEFAULT_AP_SUPPORT_INFO,
    DEFAULT_ALGORITHM_PARAM // for CTO
};

AUDIO_AUDENH_CONTROL_OPTION_STRUCT AUDENH_Control_Option_Par_default = {
    DEFAULT_AUDIO_AUDENH_CONTROL_OPTION_Coeff
};

AUDIO_BUFFER_DC_CALIBRATION_STRUCT Audio_Buffer_DC_Calibration_Par_default = {
    0xFFFF,
    0,
    0,
    0
};

AUDIO_VOIP_PARAM_STRUCT Audio_VOIP_Par_default = {
    DEFAULT_VOIP_SPEECH_COMMON_PARAM,
    DEFAULT_VOIP_SPEECH_MODE_PARAM,
    DEFAULT_VOIP_IN_FIR_PARAM,
    DEFAULT_VOIP_OUT_FIR_PARAM
};

AUDIO_ANC_CUSTOM_PARAM_STRUCT speech_ANC_custom_default = {
    DEFAULT_SPEECH_ANC_PARA,
    DEFAULT_SPEECH_ANC_APPLY,
    DEFAULT_SPEECH_ANC_LOG_ENABLE,
    DEFAULT_SPEECH_ANC_LOG_DOWNSAMPLE,
    DEFAULT_SPEECH_ANC_DL_PGA
};

AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT speech_magi_conference_custom_default = {
    DEFAULT_SPEECH_VOICE_TRACKING_MODE_PARA,
    DEFAULT_WB_SPEECH_VOICE_TRACKING_MODE_PARA
};

AUDIO_CUSTOM_HAC_PARAM_STRUCT speech_hac_param_custom_default = {
    DEFAULT_SPEECH_HAC_MODE_PARA,
    DEFAULT_WB_SPEECH_HAC_MODE_PARA,
    DEFAULT_SPEECH_HAC_INPUT_FIR_COEFF,
    DEFAULT_SPEECH_HAC_OUTPUT_FIR_COEFF,
    DEFAULT_WB_SPEECH_HAC_INPUT_FIR_COEFF,
    DEFAULT_WB_SPEECH_HAC_OUTPUT_FIR_COEFF,
    DEFAULT_VER1_AUD_VOLUME_MIC_HAC,
    DEFAULT_VER1_AUD_VOLUME_SPH_HAC,
    DEFAULT_VER1_AUD_VOLUME_SID_HAC
};

AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT speech_lpbk_param_custom_default = {
    DEFAULT_SPEECH_LPBK_NORMAL_MODE_PARA,
    DEFAULT_SPEECH_LPBK_EARPHONE_MODE_PARA,
    DEFAULT_SPEECH_LPBK_LOUDSPK_MODE_PARA,
};

AUDIO_SPEAKER_MONITOR_PARAM_STRUCT speaker_monitor_par_default = {
    DEFAULT_SPEAKER_MONITOR_PARAM,
    DEFAULT_SPEAKER_TEMP_INITIAL,
    /* hardware setting */
    DEFAULT_SPEAKER_CURRENT_SENSE_RESISTOR,
    /* resonant frqquency*/
    DEFAULT_SPEAKER_RESONANT_FC,
    DEFAULT_SPEAKER_RESONANT_BW,
    DEFAULT_SPEAKER_RESONANT_TH,
    /* temperature estimation */
    DEFAULT_SPEAKER_PREFER_HIGH_BAND,
    DEFAULT_SPEAKER_PREFER_LOW_BAND,
    /* temperature estimation control*/
    DEFAULT_SPEAKER_TEMP_CONTROL_LOW,   // low limit
    DEFAULT_SPEAKER_TEMP_CONTROL_HIGH,  // high limit
    DEFAULT_SPEAKER_TEMP_CONTROL_LOG,   // max log time
    /* monitor interval */
    DEFAULT_SPEAKER_MONITOR_INTERVAL //unit: ms
};

#else
extern AUDIO_CUSTOM_PARAM_STRUCT speech_custom_default;

extern AUDIO_VER1_CUSTOM_VOLUME_STRUCT audio_ver1_custom_default;


extern AUDIO_CUSTOM_WB_PARAM_STRUCT wb_speech_custom_default;

extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_custom_default;

extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_hcf_custom_default;
extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_vibspk_custom_default;
extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_musicdrc_custom_default;
extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_ringtonedrc_custom_default;

extern AUDIO_EFFECT_CUSTOM_PARAM_STRUCT audio_effect_custom_default;

extern AUDIO_PARAM_MED_STRUCT audio_param_med_default;

extern AUDIO_VOLUME_CUSTOM_STRUCT audio_volume_custom_default;

extern AUDIO_CUSTOM_EXTRA_PARAM_STRUCT dual_mic_custom_default;

extern AUDIO_GAIN_TABLE_STRUCT Gain_control_table_default;

extern AUDIO_HD_RECORD_PARAM_STRUCT Hd_Recrod_Par_default;

extern AUDIO_HD_RECORD_SCENE_TABLE_STRUCT Hd_Recrod_Scene_Table_default;


extern VOICE_RECOGNITION_PARAM_STRUCT Voice_Recognize_Par_default;

extern AUDIO_AUDENH_CONTROL_OPTION_STRUCT AUDENH_Control_Option_Par_default;

extern AUDIO_BUFFER_DC_CALIBRATION_STRUCT Audio_Buffer_DC_Calibration_Par_default;

extern AUDIO_VOIP_PARAM_STRUCT Audio_VOIP_Par_default;
extern AUDIO_ANC_CUSTOM_PARAM_STRUCT speech_ANC_custom_default;
extern AUDIO_SPEAKER_MONITOR_PARAM_STRUCT speaker_monitor_par_default;
extern AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT speech_magi_conference_custom_default;
extern AUDIO_CUSTOM_HAC_PARAM_STRUCT speech_hac_param_custom_default;
extern AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT speech_lpbk_param_custom_default;
extern AUDIO_BT_GAIN_STRUCT bt_gain_control_default;

#endif
#ifdef __cplusplus
}
#endif

#endif
