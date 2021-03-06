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


#ifdef CLI_SUPPORT

#ifdef __cplusplus
extern "C"
{
#endif

#include "u_cli.h"

#ifdef __cplusplus
}
#endif

#include "u_playback_uri.h"

#include "playback_uri.h"
#include "playback_uri_cli.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _playback_uri_msg(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _playback_uri_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _playback_uri_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _playback_uri_url(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _playback_uri_time(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _playback_uri_seek(INT32 i4_argc, const CHAR** pps_argv);
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
extern PlaybackUri *UriPlay;
/* command table */
static CLI_EXEC_T at_pb_uri_cmd_tbl[] =
{
    {
        CLI_GET_DBG_LVL_STR,
        NULL,
        _playback_uri_cli_get_dbg_level,
        NULL,
        CLI_GET_DBG_LVL_HELP_STR,
        CLI_GUEST
    },
    {
        CLI_SET_DBG_LVL_STR,
        NULL,
        _playback_uri_cli_set_dbg_level,
        NULL,
        CLI_SET_DBG_LVL_HELP_STR,
        CLI_GUEST
    },
    {
        "uri_msg",
        "msg",
        _playback_uri_msg,
        NULL,
        "[uri]uri_play_start",
        CLI_GUEST
    },
    {
        "play_url",
        "url",
        _playback_uri_url,
        NULL,
        "[uri]uri_play_url",
        CLI_GUEST
    },
    {
        "get_time_info",
        "time",
        _playback_uri_time,
        NULL,
        "[uri]uri_get_time",
        CLI_GUEST
    },
    {
        "seek",
        NULL,
        _playback_uri_seek,
        NULL,
        "[uri]uri_seek",
        CLI_GUEST
    },
    END_OF_CLI_CMD_TBL
};

/* SVL Builder root command table */
static CLI_EXEC_T at_playback_uri_root_cmd_tbl[] =
{
    {   "playback_uri",
        "uri",
        NULL,
        at_pb_uri_cmd_tbl,
        "playback_uri commands",
        CLI_GUEST
    },
    END_OF_CLI_CMD_TBL
};

INT32 playback_uri_cli_attach_cmd_tbl(VOID)
{
    return (u_cli_attach_cmd_tbl(at_playback_uri_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI));
}

static INT32 _playback_uri_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret;

    i4_ret = u_cli_show_dbg_level(playback_uri_get_dbg_level());

    return i4_ret;
}

static INT32 _playback_uri_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level;
    INT32  i4_ret;

    i4_ret = u_cli_parse_dbg_level(i4_argc, pps_argv, &ui2_dbg_level);

    if (i4_ret == CLIR_OK){
        playback_uri_set_dbg_level(ui2_dbg_level);
    }

    return i4_ret;
}

static INT32 _playback_uri_msg(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret=0;

    PB_URI_MSG_T t_msg;

    t_msg.ui4_msg_id = atoi(pps_argv[1]);
    t_msg.ui4_data1  = 0;
    t_msg.ui4_data2  = 0;
    t_msg.ui4_data3  = 0;

    UriPlay->send_msg_to_self(&t_msg);

    return i4_ret;
}

static INT32 _playback_uri_url(INT32 i4_argc, const CHAR** pps_argv)
{
    ASSISTANT_STUB_PLAY_T t_play = {0};
    memcpy(t_play.uri, pps_argv[1], ASSISTANT_STUB_URI_MAX_LENGTH);
    UriPlay->set_current_play((INT8*)&t_play, 0);
    return PB_URI_OK;
}

static INT32 _playback_uri_time(INT32 i4_argc, const CHAR** pps_argv)
{
    int i4_progress = 0;
    int i4_duration = 0;
    UriPlay->get_current_progress(&i4_progress);
    UriPlay->get_current_duration(&i4_duration);
    URI_MSG("progress:[%d]ms duration:[%d]ms!\n", i4_progress, i4_duration);
    return PB_URI_OK;
}

static INT32 _playback_uri_seek(INT32 i4_argc, const CHAR** pps_argv)
{
    int i4_seek_time = atoi(pps_argv[1]);
    UriPlay->set_seek(i4_seek_time);
    return PB_URI_OK;
}

#endif
