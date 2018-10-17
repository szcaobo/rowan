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
 * MediaTek Inc. (C) 2016-2017. All rights reserved.
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


#ifndef _BT_DBG_CONFIG_H_
#define _BT_DBG_CONFIG_H_

#if defined(BT_RPC_DBG_SERVER) || defined(BT_RPC_DBG_CLIENT)
#include "bt_dbg_def.h"
#include "bt_dbg_config_gap.h"
#include "bt_dbg_config_l2cap.h"
#include "bt_dbg_config_gatt.h"
#include "bt_dbg_config_a2dp.h"
#include "bt_dbg_config_hid.h"
#include "bt_dbg_config_avrcp.h"
#include "bt_dbg_config_hfp.h"
#include "bt_dbg_config_spp.h"

#define VERSION "1.0"

static MAIN_CMD m_cmd[DBG_END - DBG_START] =
{
    {"GAP",     DBG_GAP,    gap_cmd,    GAP_CMD_NUM,    "GAP rpc debug"},
    {"L2CAP",   DBG_L2CAP,  l2cap_cmd,  L2CAP_CMD_NUM,  "L2CAP rpc debug"},
    {"GATT",    DBG_GATT,   gatt_cmd,   GATT_CMD_NUM,   "GATT rpc debug"},
    {"A2DP",    DBG_A2DP,   a2dp_cmd,   A2DP_CMD_NUM,   "A2DP rpc debug"},
    {"HID",     DBG_HID,    hid_cmd,    HID_CMD_NUM,    "HID rpc debug"},
    {"AVRCP",   DBG_AVRCP,  avrcp_cmd,  AVRCP_CMD_NUM,  "AVRCP rpc debug"},
    {"HFP",     DBG_HFP,    hfp_cmd,    HFP_CMD_NUM,    "HFP rpc debug"},
    {"SPP",     DBG_SPP,    spp_cmd,    SPP_CMD_NUM,    "SPP rpc debug"},

    {NULL,      0,          NULL,       0,              NULL }
};
#endif

#endif

