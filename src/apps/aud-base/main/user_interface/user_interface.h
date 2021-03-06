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


#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_dbg.h"
#include "u_timerd.h"
#include "u_sm.h"
#include "u_acfg.h"               
#include "u_appman.h"
#include "u_app_thread.h"

#undef   DBG_LEVEL_MODULE
#define  DBG_LEVEL_MODULE       user_interface_get_dbg_level()

#define UI_TAG "<user_interface>"
#define MAX_USR_MSG_LEN     20

#define UI_OK                    ((INT32)0)
#define UI_FAIL                  ((INT32)-1) /* abnormal return must < 0 */
#define UI_INV_ARG               ((INT32)-2)


typedef struct _USER_INTERFACE_T
{
    UINT32          ui4_msg_id;    
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    UINT32          ui4_data3;
} USER_INTERFACE_MSG_T;


/* application structure */
typedef struct _USER_INTERFACE_OBJ_T
{
    HANDLE_T        h_app;    
    BOOL            b_app_init_ok;
    BOOL            b_recv_iom_msg;
}USER_INTERFACE_OBJ_T;


/*app private  msg*/
enum
{
    USERCMDMNGR_PRI_KEY_MSG,
    USERCMDMNGR_PRI_DM_MSG,
    USERCMDMNGR_PRI_MAX_MSG
};

/*------------------------------------------------------------------------------
                                            funcitons declarations
------------------------------------------------------------------------------*/
extern SOURCE_INFO_T g_t_source_list[];

extern UINT16 user_interface_get_dbg_level(VOID);
extern VOID user_interface_set_dbg_level(UINT16 ui2_db_level);
extern VOID *user_interface_key_event_monitor_thread(VOID *arg);
                                                                                                 
#endif /* _USER_INTERFACE_H_ */
