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


#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/prctl.h>
#include <sys/statfs.h>

#include "u_appman.h"
#include "u_app_thread.h"
#include "upg_download.h"
#include "curl/curl.h"

#define BUF_SIZE_ENTRIE 256
#define BUF_SIZE_HALF 128
#define BUF_SIZE_QUT 64
#define URL_LENGTH 255


CHAR g_url[BUF_SIZE_ENTRIE] = {NETWORK_UPGRADE_BASE_URL};
DOWNLOAD_TREAD_PARAM g_dl_param;

INT32 _upgrade_parse_id_file_info(UPGRADE_FILE_INFO *info, CHAR *file_path)
{
    CHAR read_buffer[BUF_SIZE_HALF] = {0};
    CHAR value_buffer[BUF_SIZE_QUT] = {0};
    FILE* fp = NULL;

    fp = fopen(file_path, "rb");
    if (NULL == fp)
    {
        DBG_UPG_TRIGGER_DEFAULT(("fail to open id file %s\n", file_path));
        return UPG_TRIGGER_FAIL;
    }

    while (fgets(read_buffer, sizeof(read_buffer), fp))
    {
        /* read Force_Update value */
        memset(value_buffer, 0, sizeof(value_buffer));
        if (sscanf(read_buffer, "Force_Update=%s", value_buffer))
        {
            if(!strncmp(value_buffer, "true", strlen("true")))
            {
                info->is_force_update = TRUE;
            }
            else
            {
                info->is_force_update = FALSE;
            }
            memset(read_buffer, 0, sizeof(read_buffer));
            continue;
        }

        /* read Version value */
        if (sscanf(read_buffer, "Version=%d", &info->upgrade_file_version))
        {
            memset(read_buffer, 0, sizeof(read_buffer));
            continue;
        }

        /* read File_Size value */
        if (sscanf(read_buffer, "File_Size=%d", &info->upgrade_file_size))
        {
            memset(read_buffer, 0, sizeof(read_buffer));
            continue;
        }

        /* read Low_Memory value */
        memset(value_buffer, 0, sizeof(value_buffer));
        if (sscanf(read_buffer, "Low_Memory=%s",value_buffer))
        {
            if (!strncmp(value_buffer, "true", strlen("true")))
            {
                info->is_low_mem_upg= TRUE;
            }
            else
            {
                info->is_low_mem_upg = FALSE;
            }
            memset(read_buffer, 0, sizeof(read_buffer));
            continue;
        }

    }

    DBG_UPG_TRIGGER_INFO(("is_force_update: %d\n", info->is_force_update));
    DBG_UPG_TRIGGER_INFO(("upgrade_file_version:%d\n", info->upgrade_file_version));
    DBG_UPG_TRIGGER_INFO(("upgrade_file_size:%d\n", info->upgrade_file_size));
    DBG_UPG_TRIGGER_INFO(("is_low_mem_upg: %d\n", info->is_low_mem_upg));
    DBG_UPG_TRIGGER_INFO(("_upgrade_parse_id_file_info done\n"));

    fclose(fp);
    return UPG_TRIGGER_OK;
}

VOID _upgrade_download_id_file_info_init(UPGRADE_FILE_INFO *info)
{
    memset(info->url,0,BUF_SIZE_ENTRIE);
    memset(info->save_path,0,BUF_SIZE_ENTRIE);

    strncpy(info->url,g_url,strlen(g_url));
    strncat(info->url,UPGRADE_ID_FILE_NAME,strlen(UPGRADE_ID_FILE_NAME));
    strncpy(info->save_path,UPGRADE_ID_FILE_TMP_PATH,strlen(UPGRADE_ID_FILE_TMP_PATH));
    strncat(info->save_path,UPGRADE_ID_FILE_NAME,strlen(UPGRADE_ID_FILE_NAME));

    DBG_UPG_TRIGGER_INFO(("NETWORK_UPGRADE_BASE_URL =%s\r\n", g_url));
    DBG_UPG_TRIGGER_INFO(("NETWORK_UPGRADE_ID_FILE_NAME =%s\r\n", UPGRADE_ID_FILE_NAME));
    DBG_UPG_TRIGGER_INFO(("NETWORK_UPGRADE_SAVE_PATH =%s\r\n", UPGRADE_ID_FILE_TMP_PATH));

}

INT32 _upgrade_get_id_file_info(UPGRADE_FILE_INFO *info, UINT32 t_delivery_type)
{
    INT32 i4_ret = 0;

    switch (t_delivery_type)
    {
    case UPDATE_FROM_CARD:
    case UPDATE_GET_OTA_INFO:
        {
            strncpy(info->save_path,UPGRADE_ID_FILE_SAVE_PATH, strlen(UPGRADE_ID_FILE_SAVE_PATH));
            strncat(info->save_path,UPGRADE_ID_FILE_NAME, strlen(UPGRADE_ID_FILE_NAME));
            if (!(access(info->save_path, F_OK)))
            {
                DBG_UPG_TRIGGER_INFO(("ID file exist in %s\r\n", info->save_path));
            }
            else
            {
                DBG_UPG_TRIGGER_DEFAULT(("No ID file found in %s\r\n", info->save_path));
            }
            break;
        }
    case UPDATE_FROM_NET:
        {
            /* id file from server will be storaged in tmpfs temporarily */
            i4_ret = _upgrade_download_make_dest_dir(UPGRADE_ID_FILE_TMP_PATH);
            if (i4_ret)
            {
                DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_make_dest_dir failed\n"));
                return i4_ret;
            }

            _upgrade_download_id_file_info_init(info);

            i4_ret = _upgrade_download_id_file(info->url, info->save_path);
            if (i4_ret)
            {
                DBG_UPG_TRIGGER_DEFAULT(("download id file failed\n"));
                return i4_ret;
            }
            break;
        }
    case UPDATE_FROM_TEMP:
        {
            strncpy(info->save_path,UPGRADE_ID_FILE_TMP_PATH, strlen(UPGRADE_ID_FILE_TMP_PATH));
            strncat(info->save_path,UPGRADE_ID_FILE_NAME, strlen(UPGRADE_ID_FILE_NAME));
            if (!(access(info->save_path, F_OK)))
            {
                DBG_UPG_TRIGGER_INFO(("ID file exist in %s\r\n",info->save_path));
            }
            else
            {
                DBG_UPG_TRIGGER_DEFAULT(("No ID file found in %s\r\n",info->save_path));
            }
            break;
        }
    default:
            DBG_UPG_TRIGGER_DEFAULT(("Err: wrong parameter! @Line %d\n", __LINE__));
            return UPG_TRIGGER_FAIL;

    }

    i4_ret = _upgrade_parse_id_file_info(info, info->save_path);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_parse_id_file_info failed\n"));
    }
    return i4_ret;

}

INT32 _upgrade_download_resume(DOWNLOAD_TREAD_PARAM *dl_param, INT32 offset,INT32 file_size)
{
    INT32 i4_ret = 0;
    INT32 downloaded_size = 0;
    INT32 requested_size = 0;
    DOUBLE dl_percent = 0;
    INT32 try_times = UPGRADE_DOWNLOAD_RESUME_TIMES;

    DBG_UPG_TRIGGER_DEFAULT(("Trying to resume download from brocken\n"));

    while (try_times--)
    {
        /* for head info, use offset directly */
        if (dl_param->is_head_info)
        {
            downloaded_size = 0;
        }
        else
        {
            downloaded_size = dl_param->downloaded_size;
        }
        requested_size = dl_param->requested_size;
        dl_percent = (double)downloaded_size/(double)requested_size;
        DBG_UPG_TRIGGER_DEFAULT(("Download from offset:%d, progress: %0.2f%%\n",downloaded_size + offset, dl_percent*100));

        if (downloaded_size < requested_size)
        {
            curl_easy_setopt(dl_param->curl,CURLOPT_RESUME_FROM, downloaded_size + offset);
            dl_param->errcode = curl_easy_perform(dl_param->curl);

            if (CURLE_OK == dl_param->errcode)
            {
                DBG_UPG_TRIGGER_DEFAULT(("--------complete download! size:%d-----------\n", dl_param->downloaded_size));
                return 0;
            }
            else
            {
                i4_ret = _upgrade_download_check_upg_status();
                if (i4_ret)
                {
                    DBG_UPG_TRIGGER_DEFAULT(("check upg status failed, download may be cancelled\n"));
                    return -1;
                }

                if (dl_param->is_request_done)
                {
                    DBG_UPG_TRIGGER_DEFAULT(("--------complete download! size:%d-----------\n", dl_param->downloaded_size));
                    return 0;
                }
                else
                {
                    DBG_UPG_TRIGGER_DEFAULT(("Resume download failed, err:%d %s %s, times:%d\n",
                        dl_param->errcode,curl_easy_strerror(dl_param->errcode),dl_param->curl_error_buf, try_times));
                    /* met connection issue, wait 1s and try again */
                    if (CURLE_COULDNT_CONNECT == dl_param->errcode)
                        sleep(1);
                }
            }
        }
    }
    DBG_UPG_TRIGGER_DEFAULT(("Resume download failed\n"));
    return -1;
}

SIZE_T _upgrade_download_id_file_cb(VOID *ptr, SIZE_T size, SIZE_T nmemb, VOID *stream)
{

    FILE *fp = (FILE *)stream;

    unsigned char *buffer=(unsigned char *)malloc(size * nmemb);
    if (buffer == NULL){
        printf("memory is not enough \n");
        return 0;
    }

    memcpy(buffer, ptr, size * nmemb);
    fwrite(buffer, 1, size * nmemb, fp);
    free(buffer);

    return size * nmemb;
}

INT32 _upgrade_download_id_file(CHAR *url,CHAR *save_path)
{
    INT32 i4_ret = 0;
    FILE *fp = NULL;
    CURLcode errcode = 0;
    CHAR curl_error_buf[CURL_ERROR_SIZE] = {0};
    CURL *curl = NULL;

    if (0 == access(save_path, F_OK))
    {
        if (0 != remove(save_path))
            DBG_UPG_TRIGGER_DEFAULT(("remove %s failed\n", save_path));
    }

    fp = fopen(save_path,"wb");
    if (fp == NULL)
    {
        DBG_UPG_TRIGGER_DEFAULT(("fail to open save file:%s\n",save_path));
        return -1;
    }
    DBG_UPG_TRIGGER_DEFAULT(("----------start download id file-----\n"));

    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _upgrade_download_id_file_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA , fp);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL , 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 500);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_error_buf);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    errcode=curl_easy_perform(curl);
    if (CURLE_OK!=errcode)
    {
        DBG_UPG_TRIGGER_DEFAULT(("download fail , err:%d %s %s\n ",
                                 errcode,curl_easy_strerror(errcode),curl_error_buf));
        i4_ret = -1;
    }
    else
    {
        DBG_UPG_TRIGGER_DEFAULT(("----------finish download id file-----\n"));
        i4_ret = 0;
    }
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    fclose(fp);

    return i4_ret;
}

INT32 _upgrade_download_send_msg(UPGRADE_DL_MSG *dl_msg,const CHAR *ps_name)
{
    INT32 i4_ret = 0;
    HANDLE_T h_app = NULL_HANDLE;

    i4_ret = u_am_get_app_handle_from_name(&h_app, ps_name);
    UPG_CONTROL_ASSERT(i4_ret);

    i4_ret = u_app_send_msg(h_app,
                            E_APP_MSG_TYPE_UPG_CTRL,
                            dl_msg,
                            sizeof(UPGRADE_DL_MSG),
                            NULL,
                            NULL);
    UPG_CONTROL_ASSERT(i4_ret);
    return i4_ret;
}

INT32 _upgrade_download_request_to_flash_data(DOWNLOAD_TREAD_PARAM *dl_param)
{
    INT32 i4_ret = 0;
    UPGRADE_DL_MSG dl_msg;
    dl_msg.pt_msg.ui4_sender_id = MSG_FROM_UPG_CONTROL;
    dl_msg.pt_msg.ui4_msg_type = E_UPG_CONTROL_FLASH_IMG_DATA;
    dl_msg.dl_param = dl_param;
    i4_ret = _upgrade_download_send_msg(&dl_msg, UPG_CONTROL_THREAD_NAME);
    if (i4_ret)
        DBG_UPG_TRIGGER_DEFAULT(("_upg_control_send_msg failed:%d\n", i4_ret));

    return i4_ret;
}

INT32 _upgrade_download_check_upg_status(VOID)
{
    INT32 i4_ret = 0;
    E_UPG_CONTROL_UPGRADE_STATUS status = 0;

    status = _upg_control_get_upgrade_status();
    if (status == E_UPG_CONTROL_UPGRADE_STATUS_CANCELLED)
    {
        i4_ret = -1;
    }
    return i4_ret;
}


SIZE_T _upgrade_download_full_ota_package_cb(VOID *ptr, SIZE_T size, SIZE_T nmemb, VOID *stream)
{
    INT32 i4_ret = 0;
    DOWNLOAD_TREAD_PARAM *dl_param = (DOWNLOAD_TREAD_PARAM*)stream;
    UCHAR* buffer = NULL;
    DOUBLE percent = 0.0;
    INT32 file_size = 0;
    if (NULL == dl_param->fp)
    {
        DBG_UPG_TRIGGER_DEFAULT(("please init download parameter first\n"));
        return -1;
    }

    i4_ret = _upgrade_download_check_upg_status();
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("check upg status failed, download may be cancelled\n"));
        return -1;
    }

    buffer=(unsigned char *)malloc(size * nmemb);
    if (NULL == buffer)
    {
        DBG_UPG_TRIGGER_DEFAULT(("malloc buffer failed\n"));
        return -1;
    }

    file_size = ftell(dl_param->fp);
    DBG_UPG_TRIGGER_INFO(("full cb: current dl size:%d, file size:%d\n", dl_param->downloaded_size, file_size));

    memcpy(buffer, ptr, size * nmemb);
    i4_ret = fwrite(buffer, 1, size * nmemb, dl_param->fp);
    if (i4_ret != (size * nmemb))
    {
        DBG_UPG_TRIGGER_DEFAULT(("ERROR: write size:%d, but return:%d, something may wrong\n", size * nmemb, i4_ret));
    //    _upg_control_set_upgrade_status(E_UPG_CONTROL_UPGRADE_STATUS_CANCELLED);
        free(buffer);
        return -1;
    }

    fflush(dl_param->fp);
    fsync(fileno(dl_param->fp));
    free(buffer);
    dl_param->downloaded_size += (size * nmemb);

    percent = (DOUBLE)dl_param->downloaded_size / dl_param->requested_size * 100;
    DBG_UPG_TRIGGER_INFO(("full pkg download: download data/requested size: %d/%d --- %0.2f%%\n",
            dl_param->downloaded_size, dl_param->requested_size, percent));

    if(dl_param->downloaded_size >= dl_param->requested_size)
    {
        DBG_UPG_TRIGGER_DEFAULT(("full pkg download done,download_size/requested_size: %d/%d\n",
            dl_param->downloaded_size,dl_param->requested_size));
        dl_param->is_request_done = FALSE;
        i4_ret = _upgrade_download_request_to_flash_data(dl_param);
        if(i4_ret)
            DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_request_to_flash_data failed, ignore \n"));
    }
    return (size * nmemb);

}

SIZE_T _upgrade_download_ota_package_cb(VOID *ptr, SIZE_T size, SIZE_T nmemb, VOID *stream)
{
    INT32 i4_ret = 0;
    DOWNLOAD_TREAD_PARAM *dl_param = (DOWNLOAD_TREAD_PARAM *)stream;
    UCHAR *buffer = NULL;
    INT32 usful_size = 0;
    UPGRADE_IMAGE_INFO *img_info = NULL;

    i4_ret = _upgrade_download_check_upg_status();
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("check upg status failed, download may be cancelled\n"));
        return -1;
    }

    if (dl_param->is_head_info)
    {
        if (dl_param->conntent_buf)
        {
            if ((dl_param->downloaded_size + (size * nmemb)) >= (dl_param->requested_size))
            {
                memcpy(dl_param->conntent_buf, ptr,(dl_param->requested_size - dl_param->downloaded_size));
                dl_param->is_request_done = TRUE;
                DBG_UPG_TRIGGER_DEFAULT(("ota package cb:head info downloaded_size:%d, requested_size:%d\n",
                    dl_param->downloaded_size + (size * nmemb), dl_param->requested_size));
                return -1;
            }
            else
            {
                memcpy(dl_param->conntent_buf, ptr, size * nmemb);
                dl_param->downloaded_size += (size * nmemb);
                return (size * nmemb);
            }
        }
    }
    else
    {
        if (NULL == dl_param->fp)
        {
            DBG_UPG_TRIGGER_DEFAULT(("please init download parameter first\n"));
            return -1;
        }

        buffer=(unsigned char *)malloc(size*nmemb);
        if (buffer == NULL)
            return 0;
        img_info = &(dl_param->image[dl_param->processing_img_idx]);

        if ((dl_param->downloaded_size + (size * nmemb)) >= (dl_param->requested_size))
        {
            usful_size = dl_param->requested_size - dl_param->downloaded_size;
            memcpy(buffer, ptr, usful_size);
            fwrite(buffer, 1, usful_size, dl_param->fp);
            fflush(dl_param->fp);
            fsync(fileno(dl_param->fp)); /* is it neccesary to sync this file which has no backing device? it is just memory */
            free(buffer);

            dl_param->is_request_done = TRUE;
            dl_param->downloaded_size += (size * nmemb);
            img_info->img_downloaded_size += usful_size;
            if (img_info->img_downloaded_size >= img_info->img_header.comp_size)
                img_info->is_img_download_done = TRUE;

            DBG_UPG_TRIGGER_INFO(("ota package cb: downloaded_size:%d, requested_size:%d, img_downloade_size:%d \n",
                dl_param->downloaded_size, dl_param->requested_size,
                img_info->img_downloaded_size));

            DBG_UPG_TRIGGER_INFO(("ota package cb: download data/comp_size: %d/%d --- %0.2f%%\n",img_info->img_downloaded_size,
                img_info->img_header.comp_size, (double)img_info->img_downloaded_size/img_info->img_header.comp_size*100));

            img_info->is_flash_unit_done = FALSE;
            i4_ret = _upgrade_download_request_to_flash_data(dl_param);
            if (i4_ret)
                DBG_UPG_TRIGGER_DEFAULT(("ota package cb: _upgrade_download_request_to_flash_data failed, ignore \n"));

            _upgrade_download_wait_data_flash_done(dl_param, &img_info->is_flash_unit_done);
            return -1;
        }
        else
        {
            memcpy(buffer, ptr, size * nmemb);
            fwrite(buffer, 1, size * nmemb, dl_param->fp);
            fflush(dl_param->fp);
            fsync(fileno(dl_param->fp));
            free(buffer);
            dl_param->downloaded_size += (size * nmemb);
            img_info->img_downloaded_size += (size * nmemb);
            if ((img_info->img_downloaded_size - img_info->img_flashed_size) >= img_info->img_flash_unit_size)
            {
                DBG_UPG_TRIGGER_INFO(("ota package cb: download data: %d/%d --- %0.2f%%\n",
                    img_info->img_downloaded_size, img_info->img_header.comp_size, (double)img_info->img_downloaded_size/img_info->img_header.comp_size*100));

                img_info->is_flash_unit_done = FALSE;
                i4_ret = _upgrade_download_request_to_flash_data(dl_param);
                if (i4_ret)
                {
                    DBG_UPG_TRIGGER_DEFAULT(("ota package cb: _upgrade_download_request_to_flash_data failed, ignore \n"));
                }
                _upgrade_download_wait_data_flash_done(dl_param, &img_info->is_flash_unit_done);
            }
            return (size * nmemb);
        }
    }
}

DOUBLE _upgrade_get_download_file_lenth(CURL *handle, const CHAR *url)
{
    DOUBLE downloadFileLenth = 0.0;
    CURL *curl = NULL;

    curl= curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
    if (curl_easy_perform(curl) == CURLE_OK)
    {
        curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &downloadFileLenth);
    }
    else
    {
        downloadFileLenth = -1;
    }
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return downloadFileLenth;
}

INT32 _upgrade_download_make_dest_dir(CHAR *DEST_DIR)
{
    if ((access(DEST_DIR, F_OK)))
    {
        if (mkdir(DEST_DIR, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH))
        {
            DBG_UPG_TRIGGER_DEFAULT(("Can not mkdir %s\n",DEST_DIR));
            return -1;
        }
    }

    return 0;
}

INT32 _upgrade_download_param_basic_init(DOWNLOAD_TREAD_PARAM *dl_param, 
                                                 CHAR *url, 
                                                 CHAR *save_path,
                                                 INT32 file_size,
                                                 BOOL is_full_pkg)
{
    INT32 i4_ret = 0;
    DOUBLE dl_lenth = 0;
    CHAR* file_name = NULL;

    if (is_full_pkg)
    {
        file_name = UPGRADE_FULL_PKG_NAME;
    }
    else
    {
        file_name = UPGRADE_OTA_FILE_NAME;
    }
    memset(dl_param, 0, sizeof(DOWNLOAD_TREAD_PARAM));

    pthread_mutex_init(&dl_param->flash_mutex, NULL);
    pthread_cond_init(&dl_param->flash_cond, NULL);

    dl_param->is_full_pkg_update = is_full_pkg;
    dl_param->upg_file_size = file_size;

    strncpy(dl_param->url, url, strlen(url));
    strncat(dl_param->url, file_name, strlen(file_name));

    strncpy(dl_param->save_path, save_path, strlen(save_path));
    strncat(dl_param->save_path, file_name, strlen(file_name));

    dl_lenth = _upgrade_get_download_file_lenth(NULL, dl_param->url);
    if ((dl_lenth > 0) && 
        ((INT32)dl_lenth != file_size))
    {
        dl_param->upg_file_size = (INT32)dl_lenth;
        DBG_UPG_TRIGGER_DEFAULT(("file size from id:%d, size not match, use server size:%d.\n",file_size,dl_param->upg_file_size));
    }

    dl_param->fp = fopen(dl_param->save_path,"wb");
    if (dl_param->fp == NULL)
    {
        DBG_UPG_TRIGGER_DEFAULT(("fail to open save file:%s, reopen later\n",dl_param->save_path));
    }

    return i4_ret;
}

INT32 _upgrade_download_param_reset(DOWNLOAD_TREAD_PARAM *dl_param)
{
    dl_param->errcode = 0;
    dl_param->is_head_info = FALSE;
    dl_param->requested_size = 0;
    dl_param->downloaded_size = 0;
    dl_param->conntent_buf = NULL;
    dl_param->is_request_done = FALSE;
}

INT32 _upgrade_download_curl_init(DOWNLOAD_TREAD_PARAM *dl_param, CURL *curl, CURL_CB_FCT curl_callback_fct)
{
    INT32 i4_ret = 0;
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,       curl_callback_fct);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,           dl_param);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL,            1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS,   1000);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,             CURL_DOWNLOAD_TIMEOUT);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER,         dl_param->curl_error_buf);

    /* To prevent blocking when connection issue occured */
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME,      5);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT,     50);
    curl_easy_setopt(curl, CURLOPT_URL,                 dl_param->url);

    DBG_UPG_TRIGGER_DEFAULT(("initial URl:%s\n",dl_param->url));

    dl_param->curl = curl;
    dl_param->is_curl_inited = TRUE;
    return i4_ret;
}

VOID _upgrade_download_clean_basic_info(DOWNLOAD_TREAD_PARAM *dl_param)
{
    pthread_cond_destroy(&dl_param->flash_cond);
    pthread_mutex_destroy(&dl_param->flash_mutex);

    if (dl_param->curl)
    {
        curl_easy_cleanup(dl_param->curl);
        curl_global_cleanup();
        dl_param->curl = NULL;
    }

    if (dl_param->fp)
    {
        fclose(dl_param->fp);
        dl_param->fp = NULL;
    }

    if (0 == access(dl_param->save_path, F_OK))
    {
        if (0 == remove(dl_param->save_path))
        {
            DBG_UPG_TRIGGER_DEFAULT(("remove existing %s \n", dl_param->save_path));
        }
        else
        {
            DBG_UPG_TRIGGER_DEFAULT(("remove existing %s failed\n", dl_param->save_path));
        }
    }
}

INT32 _upgrade_download_from_offset(DOWNLOAD_TREAD_PARAM *dl_param, INT32 offset, INT32 size)
{
    INT32 i4_ret = 0;
    if (!dl_param->is_curl_inited)
    {
        DBG_UPG_TRIGGER_DEFAULT(("please init curl first\n"));
        i4_ret = -1;
    }

    if (offset)
    {
        curl_easy_setopt(dl_param->curl,CURLOPT_RESUME_FROM, offset);
    }
    if (size)
    {
        dl_param->requested_size = size;
    }
    DBG_UPG_TRIGGER_DEFAULT(("--------start to download!-----------\n"));
    DBG_UPG_TRIGGER_DEFAULT(("from:%s, offset:%d, size:%d\n", dl_param->url, offset, dl_param->requested_size));
    dl_param->errcode = curl_easy_perform(dl_param->curl);

    if (CURLE_OK != dl_param->errcode)
    {
        i4_ret = _upgrade_download_check_upg_status();
        if (i4_ret)
        {
            DBG_UPG_TRIGGER_DEFAULT(("check upg status failed, download may be cancelled\n"));
            return -1;
        }

        if (dl_param->is_request_done)
        {
            DBG_UPG_TRIGGER_DEFAULT(("--------complete unit download! downloaded size:%d-----------\n", dl_param->downloaded_size));
            i4_ret = 0;
        }
        else
        {
            DBG_UPG_TRIGGER_DEFAULT(("download fail , err:%d %s %s\n ",
                dl_param->errcode, curl_easy_strerror(dl_param->errcode), dl_param->curl_error_buf));

            /* use absolute offset for full pkg download resuming */
            if (dl_param->is_full_pkg_update)
            {
                offset = 0;
            }
            i4_ret = _upgrade_download_resume(dl_param, offset, dl_param->requested_size);
        }
    }
    else
    {
        DBG_UPG_TRIGGER_DEFAULT(("--------complete download! downloaded size:%d-----------\n", dl_param->downloaded_size));
        i4_ret = 0;
    }

    return i4_ret;
}

INT32 _upgrade_parse_zip_head_info(const struct zip_header_raw *raw_data, struct zip_header *data)
{
    INT32 i4_ret = 0;

    parse_zip_head_info(raw_data, data);
    if (ZIP_HEAD_SIGN != data->sign_head)
    {
        DBG_UPG_TRIGGER_DEFAULT(("parse_zip_head_info failed, header signature not match\n"));
        i4_ret = -1;
    }

    return i4_ret;
}

INT32 _upgrade_download_get_img_headinfo(DOWNLOAD_TREAD_PARAM *dl_param)
{
    INT32 i4_ret = 0;
    CURL* curl = NULL;
    INT32 head_offset = 0;
    INT32 img_index = 0;
    CHAR  img_header[ZIP_HEAD_PRE_SIZE] = {0};
    UPGRADE_IMAGE_INFO *image = NULL;

    i4_ret = _upgrade_download_curl_init(dl_param, curl, _upgrade_download_ota_package_cb);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_curl_init failed\n"));
        return i4_ret;
    }

    while (1)
    {
        _upgrade_download_param_reset(dl_param);
        memset(img_header, 0, ZIP_HEAD_PRE_SIZE);

        dl_param->requested_size= ZIP_HEAD_PRE_SIZE;
        dl_param->is_head_info = TRUE;
        dl_param->conntent_buf = &img_header;

        i4_ret = _upgrade_download_from_offset(dl_param, head_offset, ZIP_HEAD_PRE_SIZE);
        if (i4_ret)
        {
            DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_from_offset failed\n"));
            break;
        }

        if (ZIP_HEAD_SIGN != *(INT32*)(&img_header))
        {
            dl_param->img_num = img_index;
            DBG_UPG_TRIGGER_DEFAULT(("get img headinfo done! img num:%d\n",img_index));
            break;
        }

        if (UPGRADE_IMG_NUM <= img_index)
        {
            DBG_UPG_TRIGGER_DEFAULT(("request imgs num: %d, we now only support %d images to update\n",img_index + 1, UPGRADE_IMG_NUM));
            break;
        }

        image = &(dl_param->image[img_index]);
        i4_ret = _upgrade_parse_zip_head_info((struct zip_header_raw*)(&img_header), &(image->img_header));
        if (i4_ret)
        {
            DBG_UPG_TRIGGER_DEFAULT(("_upgrade_parse_zip_head_info failed\n"));
            break;
        }

        image->img_data_offset = head_offset + ZIP_HEAD_SIZE_ROW + image->img_header.name_length + image->img_header.ext_field_length;
        head_offset = image->img_data_offset + image->img_header.comp_size;
        img_index++;
    }

    if (!dl_param->img_num)
    {
        DBG_UPG_TRIGGER_DEFAULT(("No image need to be updated\n"));
        i4_ret = -1;
    }

    if (dl_param->curl)
    {
        curl_easy_cleanup(dl_param->curl);
        curl_global_cleanup();
        dl_param->curl = NULL;
    }

    return i4_ret;
}

INT32 _upgrade_download_reopen_save_file(DOWNLOAD_TREAD_PARAM *dl_param)
{
    INT32 i4_ret = 0;
    INT32 file_size = 0;
    CHAR* file_path = NULL;

    if (dl_param->is_full_pkg_update)
    {
        file_path = UPGRADE_FULL_PKG_SAVE_PATH;
    }
    else
    {
        file_path = UPGRADE_OTA_FILE_SAVE_PATH;
    }
    if (dl_param->fp)
    {
        file_size = ftell(dl_param->fp);
        DBG_UPG_TRIGGER_INFO(("close update file size: %d\n", file_size));
        fclose(dl_param->fp);
        dl_param->fp = NULL;
    }

    i4_ret = _upgrade_download_make_dest_dir(file_path);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_make_dest_dir failed\n"));
        return i4_ret;
    }

    if (0 == access(dl_param->save_path, F_OK))
    {
        if (0 == remove(dl_param->save_path))
        {
            DBG_UPG_TRIGGER_DEFAULT(("remove existing %s \n", dl_param->save_path));
        }
        else
        {
            DBG_UPG_TRIGGER_DEFAULT(("remove existing %s failed\n", dl_param->save_path));
            return -1;
        }
    }

    dl_param->fp = fopen(dl_param->save_path, "wb");
    if (dl_param->fp == NULL)
    {
        DBG_UPG_TRIGGER_DEFAULT(("fail to open save file:%s\n", dl_param->save_path));
        return -1;
    }
    return 0;
}

VOID _upgrade_download_map_partition_name(const CHAR *img_name, CHAR **part_name)
{
    if (!strncmp(img_name, BOOT_IMAGE_NAME, strlen(BOOT_IMAGE_NAME)))
    {
        strncpy(*part_name, A_BOOT_PARTITION_NAME, sizeof(A_BOOT_PARTITION_NAME));
    }
    else if(!strncmp(img_name, TZ_IMAGE_NAME, strlen(TZ_IMAGE_NAME)))
    {
        strncpy(*part_name, A_TZ_PARTITION_NAME, sizeof(A_TZ_PARTITION_NAME));
    }
    else if(!strncmp(img_name, ROOTFS_IMAGE_NAME, strlen(ROOTFS_IMAGE_NAME)))
    {
        strncpy(*part_name, A_ROOTFS_PARTITION_NAME, sizeof(A_ROOTFS_PARTITION_NAME));
    }
    else if(!strncmp(img_name, LK_IMAGE_NAME, strlen(LK_IMAGE_NAME)))
    {
        strncpy(*part_name, LK_PARTITION_NAME, sizeof(LK_PARTITION_NAME));
    }
    DBG_UPG_TRIGGER_INFO(("image name:%s, map to partition name:%s \n", img_name, *part_name));
}

INT32 _upgrade_get_img_blk_size_by_name(DOWNLOAD_TREAD_PARAM *dl_param)
{
    INT32 i4_ret = 0;
    INT32 img_idx = 0;
    INT32 img_blk_size = 0;
    CHAR partition_name[BUF_SIZE_QUT] = {0};
    CHAR *p_part_name = NULL;;
    UPGRADE_IMAGE_INFO *image_info = NULL;

    while (img_idx != dl_param->img_num)
    {
        memset(partition_name, 0, 64);
        p_part_name = &partition_name;
        image_info = &(dl_param->image[img_idx]);

        _upgrade_download_map_partition_name(image_info->img_header.file_name, &p_part_name);
        i4_ret = get_partition_blk_size_by_name(partition_name, &image_info->img_blk_size);
        if (i4_ret)
        {
            DBG_UPG_TRIGGER_DEFAULT(("get_partition_blk_size_by_name failed\n"));
            return i4_ret;
        }

        img_blk_size = image_info->img_blk_size;
        image_info->img_flash_unit_size = (UPGRADE_TRANSFER_FLASH_SIZE + img_blk_size - 1) / img_blk_size * img_blk_size;
        img_idx++;
    }
    return i4_ret;
}

INT32 _upgrade_download_wait_data_flash_done(DOWNLOAD_TREAD_PARAM *dl_param, BOOL *is_done)
{
    INT32 i4_ret = 0;

    pthread_mutex_lock(&dl_param->flash_mutex);
    while (!(*is_done))
    {
        DBG_UPG_TRIGGER_INFO(("_upgrad_download_wait_data_flash_done\n"));
        pthread_cond_wait(&dl_param->flash_cond, &dl_param->flash_mutex);
    }
    pthread_mutex_unlock(&dl_param->flash_mutex);

    return i4_ret;
}

INT32 _upgrade_download_wakeup_data_flash_done(DOWNLOAD_TREAD_PARAM *dl_param, BOOL *is_done)
{
    INT32 i4_ret = 0;

    pthread_mutex_lock(&dl_param->flash_mutex);
    DBG_UPG_TRIGGER_INFO(("_upgrade_download_wakeup_data_flash_done\n"));
    *is_done = TRUE;
    pthread_cond_signal(&dl_param->flash_cond);
    pthread_mutex_unlock(&dl_param->flash_mutex);

    return i4_ret;
}

INT32 _upgrade_download_get_full_pkg_data(DOWNLOAD_TREAD_PARAM *dl_param)
{
    INT32 i4_ret = 0;
    CURL *curl = NULL;

    _upgrade_download_curl_init(dl_param, curl, _upgrade_download_full_ota_package_cb);

    _upgrade_download_param_reset(dl_param);

    while (dl_param->downloaded_size < dl_param->upg_file_size)
    {
        i4_ret = _upgrade_download_from_offset(dl_param, dl_param->downloaded_size, dl_param->upg_file_size);
        if (i4_ret)
        {
            /* sometimes the connection will be closed by server, we will try to request data untill all data downloaded,
                         but if resume download failed, we'll return failure. */
            DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_from_offset failed\n"));
            goto out;
        }
    }
    _upgrade_download_wait_data_flash_done(dl_param, &dl_param->is_request_done);

out:
    if (dl_param->curl)
    {
        curl_easy_cleanup(dl_param->curl);
        curl_global_cleanup();
        dl_param->curl = NULL;
    }
    return i4_ret;

}

INT32 _upgrade_download_get_img_data(DOWNLOAD_TREAD_PARAM *dl_param)
{
    INT32 i4_ret = 0;
    INT32 img_idx = 0;
    CURL* curl = NULL;
    INT32 img_dl_offset = 0;
    INT32 rest_dl_size = 0;
    UPGRADE_IMAGE_INFO *image_info = NULL;

    i4_ret = _upgrade_get_img_blk_size_by_name(dl_param);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_get_img_blk_size_by_name failed\n"));
        return i4_ret;
    }

    i4_ret = _upgrade_download_reopen_save_file(dl_param);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_reopen_save_file failed\n"));
        return i4_ret;
    }

    _upgrade_download_curl_init(dl_param, curl, _upgrade_download_ota_package_cb);

    while (img_idx != dl_param->img_num)
    {
        image_info = &(dl_param->image[img_idx]);
        img_dl_offset = image_info->img_data_offset;
        dl_param->processing_img_idx = img_idx;

        while (!image_info->is_img_download_done)
        {
            _upgrade_download_param_reset(dl_param);

            /* adjust to align flash unit size since update.bin has been removed */
            img_dl_offset = image_info->img_data_offset + image_info->img_flashed_size;
            image_info->img_downloaded_size = image_info->img_flashed_size;

            rest_dl_size = image_info->img_header.comp_size - image_info->img_downloaded_size;
            dl_param->requested_size = (rest_dl_size > image_info->img_flash_unit_size)?
                                       image_info->img_flash_unit_size:rest_dl_size;
            dl_param->is_head_info = FALSE;

            i4_ret = _upgrade_download_from_offset(dl_param, img_dl_offset, dl_param->requested_size);
            if (i4_ret)
            {
                DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_from_offset failed\n"));
                goto out;
            }

            i4_ret = _upgrade_download_reopen_save_file(dl_param);
            if (i4_ret)
            {
                DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_reopen_save_file failed\n"));
                goto out;
            }
        }

        img_idx++;
    }

out:
    if (dl_param->curl)
    {
        curl_easy_cleanup(dl_param->curl);
        curl_global_cleanup();
        dl_param->curl = NULL;
    }

    return i4_ret;
}

INT32 _upgrade_download_get_free_storage_size(CHAR *path)
{
    INT32 i4_ret = 0;
    struct statfs fs_info = {0};
    INT32 avail_size = 0;

    i4_ret = statfs(path, &fs_info);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_get_free_storage_size failed\n"));
        return -1;
    }
    avail_size = fs_info.f_bsize * fs_info.f_bavail;

    DBG_UPG_TRIGGER_INFO(("%s block size:%d, total block:%d, free block:%d, available block:%d \n",
        path, fs_info.f_bsize, fs_info.f_blocks, fs_info.f_bfree, fs_info.f_bavail));

    return avail_size;
}

INT32 _upgrade_download_check_storage_size(DOWNLOAD_TREAD_PARAM *dl_param)
{
    INT32 i4_ret = 0;
    INT32 avail_size = 0;
    INT32 ota_size = 0;

    ota_size = dl_param->upg_file_size;
    avail_size = _upgrade_download_get_free_storage_size(UPGRADE_FULL_PKG_SAVE_PATH);
    if (avail_size < ota_size)
    {
        DBG_UPG_TRIGGER_DEFAULT(("check free size failed, available size:%d, ota size:%d\n",
            avail_size, ota_size));
        i4_ret = -1;
    }

    return i4_ret;
}

INT32 _upgrade_download_full_ota_package(CHAR *url, CHAR *save_path, INT32 upg_file_size)
{
    INT32 i4_ret = 0;
    CURL* curl = NULL;
    DOWNLOAD_TREAD_PARAM* dl_param = &g_dl_param;

    i4_ret = _upgrade_download_param_basic_init(dl_param, url, save_path, upg_file_size, TRUE);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_param_basic_init failed\n"));
        goto out;
    }

    i4_ret = _upgrade_download_check_storage_size(dl_param);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_check_storage_size failed\n"));
        goto out;
    }

    i4_ret = _upgrade_download_reopen_save_file(dl_param);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_reopen_save_file failed\n"));
        goto out;
    }

    i4_ret = _upgrade_download_get_full_pkg_data(dl_param);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_get_img_data failed\n"));
        goto out;
    }

out:
    _upgrade_download_clean_basic_info(dl_param);

    return i4_ret;
}

INT32 _upgrade_download_ota_package(CHAR *url, CHAR *save_path, INT32 upg_file_size)
{
    INT32 i4_ret = 0;
    CURL *curl = NULL;
    DOWNLOAD_TREAD_PARAM *dl_param = &g_dl_param;

    i4_ret = _upgrade_download_param_basic_init(dl_param, url, save_path, upg_file_size, FALSE);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_param_basic_init failed\n"));
        goto out;
    }

    i4_ret = _upgrade_download_get_img_headinfo(dl_param);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_get_img_headinfo failed\n"));
        goto out;
    }

    i4_ret = _upgrade_download_get_img_data(dl_param);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_get_img_data failed\n"));
        goto out;
    }

out:
    _upgrade_download_clean_basic_info(dl_param);

    return i4_ret;
}

INT32 _upgrade_set_server_url(const CHAR *url)
{
    if (strlen(url) > URL_LENGTH)
    {
        DBG_UPG_TRIGGER_INFO(("url length is too long\n"));
        return -1;
    }
    if (url != NULL){
        memset(g_url, 0, sizeof(g_url));
        strncpy(g_url,url,strlen(url));
    }

    DBG_UPG_TRIGGER_INFO(("app set server url = %s\n",g_url));
    return 0;
}

INT32 _upgrade_download_notify_flash_done(VOID)
{
    INT32 i4_ret = 0;
    UPGRADE_DL_MSG dl_msg;
    dl_msg.pt_msg.ui4_sender_id = MSG_FROM_UPG_CONTROL;
    dl_msg.pt_msg.ui4_msg_type = E_UPG_CONTROL_FLASH_IMG_DONE;
    dl_msg.dl_param = NULL;
    i4_ret = _upgrade_download_send_msg(&dl_msg, UPG_CONTROL_THREAD_NAME);
    if (i4_ret)
    {
        DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_notify_flash_done failed:%d\n", i4_ret));
    }
    
    return i4_ret;
}

INT32 _upgrade_start_download_firmware(UINT32 t_delivery_type, const CHAR *ps_url, const CHAR *ps_fwPath)
{
    INT32 i4_ret = UPG_TRIGGER_OK;
    UINT32 ui4_update_type =UPDATE_FROM_CARD;
    CHAR ps_cmd[UPG_CMD_LEN]={0};
    UPGRADE_FILE_INFO info;

    memset(&info, 0, sizeof(UPGRADE_FILE_INFO));

    switch (t_delivery_type)
    {
    case UPDATE_FROM_NET:
        {
            memset(&info, 0, sizeof(UPGRADE_FILE_INFO));
            i4_ret = _upgrade_get_id_file_info(&info,UPDATE_FROM_TEMP);
            if (i4_ret)
            {
                DBG_UPG_TRIGGER_DEFAULT(("_upgrade_get_id_file_info from temp failed\n"));
                return i4_ret;
            }
            if (info.is_low_mem_upg)
            {
                i4_ret = _upgrade_download_ota_package(g_url,UPGRADE_OTA_FILE_SAVE_PATH,info.upgrade_file_size);
                if (i4_ret)
                {
                    DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_ota_package failed\n"));
                    return i4_ret;
                }
            }
            else
            {
                i4_ret = _upgrade_download_full_ota_package(g_url,UPGRADE_FULL_PKG_SAVE_PATH,info.upgrade_file_size);
                if (i4_ret)
                {
                    DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_full_ota_package failed\n"));
                    return i4_ret;
                }
            }
            i4_ret = _upgrade_download_notify_flash_done();
            if (i4_ret)
            {
                DBG_UPG_TRIGGER_DEFAULT(("_upgrade_download_notify_flash_done failed\n"));
            }
            break;
        }
    default:
            DBG_UPG_TRIGGER_DEFAULT(("Err: wrong parameter! @Line %d\n", __LINE__));
            return UPG_TRIGGER_FAIL;
    }

    return UPG_TRIGGER_OK;
}

CHAR *_upgrade_get_server_url(const CHAR *url)
{
    return g_url;
}

