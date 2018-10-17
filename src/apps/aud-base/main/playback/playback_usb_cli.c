/* Copyright Statement:                                                        
 *                                                                             
 * This software/firmware and related documentation ("MediaTek Software") are  
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without 
 * the prior written permission of MediaTek inc. and/or its licensors, any     
 * reproduction, modification, use or disclosure of MediaTek Software, and     
 * information contained herein, in whole or in part, shall be strictly        
 * prohibited.                                                                 
 *                                                                             
 * MediaTek Inc. (C) 2014. All rights reserved.                                
 *                                                                             
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES 
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")     
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER  
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL          
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED    
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR          
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH 
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,            
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.   
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK       
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE  
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR     
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S 
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE       
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE  
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE  
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.    
 *                                                                             
 * The following software/firmware and/or related documentation ("MediaTek     
 * Software") have been modified by MediaTek Inc. All revisions are subject to 
 * any receiver's applicable license agreements with MediaTek Inc.             
 */


#include "playback_usb_cli.h"

#ifdef CLI_SUPPORT
#include "u_cli.h"
#include "playback_usb.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32  _playback_usb_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _playback_usb_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _playback_usb_cli_set_auto_play(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _playback_usb_cli_get_auto_play(INT32 i4_argc, const CHAR** pps_argv);
static INT32  _playback_usb_cli_alsa_test(INT32 i4_argc, const CHAR** pps_argv);

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/

/* command table */
static CLI_EXEC_T at_pb_usb_cmd_tbl[] =
{
    {
        CLI_GET_DBG_LVL_STR,
        NULL,
        _playback_usb_cli_get_dbg_level,
        NULL,
        CLI_GET_DBG_LVL_HELP_STR,
        CLI_GUEST
    },
    {
        CLI_SET_DBG_LVL_STR,
        NULL,
        _playback_usb_cli_set_dbg_level,
        NULL,
        CLI_SET_DBG_LVL_HELP_STR,
        CLI_GUEST
    },
    {
        "set_auto_play",
        NULL,
        _playback_usb_cli_set_auto_play,
        NULL,
        "[playback]set usb auto play",
        CLI_GUEST
    },
    {
        "get_auto_play",
        NULL,
        _playback_usb_cli_get_auto_play,
        NULL,
        "[playback]get usb auto play",
        CLI_GUEST
    },
    {
        "alsa_test",
        "alsa",
        _playback_usb_cli_alsa_test,
        NULL,
        "[playback_usb]alsa_playback_test",
        CLI_GUEST
    },
    END_OF_CLI_CMD_TBL
};
/* SVL Builder root command table */
static CLI_EXEC_T at_playback_usb_root_cmd_tbl[] =
{
    {   "playback_usb",
        "pbusb",
        NULL,
        at_pb_usb_cmd_tbl,
        "playback_usb commands",
        CLI_GUEST
    },
    END_OF_CLI_CMD_TBL
};
/*-----------------------------------------------------------------------------
 * export methods implementations
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:    playback_usb_cli_attach_cmd_tbl
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
INT32 playback_usb_cli_attach_cmd_tbl(VOID)
{
    return (u_cli_attach_cmd_tbl(at_playback_usb_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI));
}


static INT32 _playback_usb_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret;

    i4_ret = u_cli_show_dbg_level(playback_usb_get_dbg_level());

    return i4_ret;
}

static INT32 _playback_usb_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level;
    INT32  i4_ret;

    i4_ret = u_cli_parse_dbg_level(i4_argc, pps_argv, &ui2_dbg_level);

    if (i4_ret == CLIR_OK){
        playback_usb_set_dbg_level(ui2_dbg_level);
    }

    return i4_ret;
}

static INT32 _playback_usb_cli_set_auto_play(INT32 i4_argc, const CHAR** pps_argv)
{
    BOOL b_auto_mnt = atoi(pps_argv[1]);

    playback_usb_set_auto_play(b_auto_mnt);

    return CLIR_OK;
}

static INT32 _playback_usb_cli_get_auto_play(INT32 i4_argc, const CHAR** pps_argv)
{
    BOOL b_auto_mnt;

    b_auto_mnt = playback_usb_get_auto_play();

    dbg_print("usb mount, playback is %s\n", b_auto_mnt ? "auto play" : "not auto play");

    return CLIR_OK;
}

static INT32 _playback_usb_cli_alsa_test(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret=0;

    if (1)
    {
        PB_USB_MSG_T t_msg;

        t_msg.ui4_msg_id = atoi(pps_argv[1]);
        t_msg.ui4_data1  = 0;
        t_msg.ui4_data2  = 0;
        t_msg.ui4_data3  = 0;

        u_playback_usb_send_msg(&t_msg);
    }
    else
    {
        i4_ret = CLIR_INV_ARG;
    }

    return i4_ret;
}

#endif
