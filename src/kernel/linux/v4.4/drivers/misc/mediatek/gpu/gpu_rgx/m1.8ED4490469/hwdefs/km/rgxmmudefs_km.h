/*************************************************************************/ /*!
@Title          Hardware definition file rgxmmudefs_km.h
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@License        Dual MIT/GPLv2

The contents of this file are subject to the MIT license as set out below.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

Alternatively, the contents of this file may be used under the terms of
the GNU General Public License Version 2 ("GPL") in which case the provisions
of GPL are applicable instead of those above.

If you wish to allow use of your version of this file only under the terms of
GPL, and not to allow others to use your version of this file under the terms
of the MIT license, indicate your decision by deleting the provisions above
and replace them with the notice and other provisions required by GPL as set
out in the file called "GPL-COPYING" included in this distribution. If you do
not delete the provisions above, a recipient may use your version of this file
under the terms of either the MIT license or GPL.

This License is also included in this distribution in the file called
"MIT-COPYING".

EXCEPT AS OTHERWISE STATED IN A NEGOTIATED AGREEMENT: (A) THE SOFTWARE IS
PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT; AND (B) IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/ /**************************************************************************/

/*               ****   Autogenerated C -- do not edit    ****               */

/*
 * Generated by regconv version MAIN@3328745
 *   from files:
 *      rogue_bif.def
 *      rogue_bif.def
 */


#ifndef _RGXMMUDEFS_KM_H_
#define _RGXMMUDEFS_KM_H_

#include "img_types.h"

/*

		Encoding of DM (note value 0x6 not used)

*/
#define RGX_BIF_DM_ENCODING_VERTEX                        (0x00000000U)
#define RGX_BIF_DM_ENCODING_PIXEL                         (0x00000001U)
#define RGX_BIF_DM_ENCODING_COMPUTE                       (0x00000002U)
#define RGX_BIF_DM_ENCODING_TLA                           (0x00000003U)
#define RGX_BIF_DM_ENCODING_PB_VCE                        (0x00000004U)
#define RGX_BIF_DM_ENCODING_PB_TE                         (0x00000005U)
#define RGX_BIF_DM_ENCODING_META                          (0x00000007U)
#define RGX_BIF_DM_ENCODING_HOST                          (0x00000008U)
#define RGX_BIF_DM_ENCODING_PM_ALIST                      (0x00000009U)


/*

		Labelling of fields within virtual address

*/
/*
Page Catalogue entry #
*/
#define RGX_MMUCTRL_VADDR_PC_INDEX_SHIFT                  (30U)
#define RGX_MMUCTRL_VADDR_PC_INDEX_CLRMSK                 (IMG_UINT64_C(0XFFFFFF003FFFFFFF))
/*
Page Directory entry #
*/
#define RGX_MMUCTRL_VADDR_PD_INDEX_SHIFT                  (21U)
#define RGX_MMUCTRL_VADDR_PD_INDEX_CLRMSK                 (IMG_UINT64_C(0XFFFFFFFFC01FFFFF))
/*
Page Table entry #
*/
#define RGX_MMUCTRL_VADDR_PT_INDEX_SHIFT                  (12U)
#define RGX_MMUCTRL_VADDR_PT_INDEX_CLRMSK                 (IMG_UINT64_C(0XFFFFFFFFFFE00FFF))


/*

		Number of entries in a PC

*/
#define RGX_MMUCTRL_ENTRIES_PC_VALUE                      (0x00000400U)


/*

		Number of entries in a PD

*/
#define RGX_MMUCTRL_ENTRIES_PD_VALUE                      (0x00000200U)


/*

		Number of entries in a PT

*/
#define RGX_MMUCTRL_ENTRIES_PT_VALUE                      (0x00000200U)


/*

		Size in bits of the PC entries in memory

*/
#define RGX_MMUCTRL_ENTRY_SIZE_PC_VALUE                   (0x00000020U)


/*

		Size in bits of the PD entries in memory

*/
#define RGX_MMUCTRL_ENTRY_SIZE_PD_VALUE                   (0x00000040U)


/*

		Size in bits of the PT entries in memory

*/
#define RGX_MMUCTRL_ENTRY_SIZE_PT_VALUE                   (0x00000040U)


/*

		Encoding of page size field

*/
#define RGX_MMUCTRL_PAGE_SIZE_MASK                        (0x00000007U)
#define RGX_MMUCTRL_PAGE_SIZE_4KB                         (0x00000000U)
#define RGX_MMUCTRL_PAGE_SIZE_16KB                        (0x00000001U)
#define RGX_MMUCTRL_PAGE_SIZE_64KB                        (0x00000002U)
#define RGX_MMUCTRL_PAGE_SIZE_256KB                       (0x00000003U)
#define RGX_MMUCTRL_PAGE_SIZE_1MB                         (0x00000004U)
#define RGX_MMUCTRL_PAGE_SIZE_2MB                         (0x00000005U)


/*

		Range of bits used for 4KB Physical Page

*/
#define RGX_MMUCTRL_PAGE_4KB_RANGE_SHIFT                  (12U)
#define RGX_MMUCTRL_PAGE_4KB_RANGE_CLRMSK                 (IMG_UINT64_C(0XFFFFFF0000000FFF))


/*

		Range of bits used for 16KB Physical Page

*/
#define RGX_MMUCTRL_PAGE_16KB_RANGE_SHIFT                 (14U)
#define RGX_MMUCTRL_PAGE_16KB_RANGE_CLRMSK                (IMG_UINT64_C(0XFFFFFF0000003FFF))


/*

		Range of bits used for 64KB Physical Page

*/
#define RGX_MMUCTRL_PAGE_64KB_RANGE_SHIFT                 (16U)
#define RGX_MMUCTRL_PAGE_64KB_RANGE_CLRMSK                (IMG_UINT64_C(0XFFFFFF000000FFFF))


/*

		Range of bits used for 256KB Physical Page

*/
#define RGX_MMUCTRL_PAGE_256KB_RANGE_SHIFT                (18U)
#define RGX_MMUCTRL_PAGE_256KB_RANGE_CLRMSK               (IMG_UINT64_C(0XFFFFFF000003FFFF))


/*

		Range of bits used for 1MB Physical Page

*/
#define RGX_MMUCTRL_PAGE_1MB_RANGE_SHIFT                  (20U)
#define RGX_MMUCTRL_PAGE_1MB_RANGE_CLRMSK                 (IMG_UINT64_C(0XFFFFFF00000FFFFF))


/*

		Range of bits used for 2MB Physical Page

*/
#define RGX_MMUCTRL_PAGE_2MB_RANGE_SHIFT                  (21U)
#define RGX_MMUCTRL_PAGE_2MB_RANGE_CLRMSK                 (IMG_UINT64_C(0XFFFFFF00001FFFFF))


/*

		Range of bits used for PT Base Address for 4KB Physical Page

*/
#define RGX_MMUCTRL_PT_BASE_4KB_RANGE_SHIFT               (12U)
#define RGX_MMUCTRL_PT_BASE_4KB_RANGE_CLRMSK              (IMG_UINT64_C(0XFFFFFF0000000FFF))


/*

		Range of bits used for PT Base Address for 16KB Physical Page

*/
#define RGX_MMUCTRL_PT_BASE_16KB_RANGE_SHIFT              (10U)
#define RGX_MMUCTRL_PT_BASE_16KB_RANGE_CLRMSK             (IMG_UINT64_C(0XFFFFFF00000003FF))


/*

		Range of bits used for PT Base Address for 64KB Physical Page

*/
#define RGX_MMUCTRL_PT_BASE_64KB_RANGE_SHIFT              (8U)
#define RGX_MMUCTRL_PT_BASE_64KB_RANGE_CLRMSK             (IMG_UINT64_C(0XFFFFFF00000000FF))


/*

		Range of bits used for PT Base Address for 256KB Physical Page

*/
#define RGX_MMUCTRL_PT_BASE_256KB_RANGE_SHIFT             (6U)
#define RGX_MMUCTRL_PT_BASE_256KB_RANGE_CLRMSK            (IMG_UINT64_C(0XFFFFFF000000003F))


/*

		Range of bits used for PT Base Address for 1MB Physical Page

*/
#define RGX_MMUCTRL_PT_BASE_1MB_RANGE_SHIFT               (5U)
#define RGX_MMUCTRL_PT_BASE_1MB_RANGE_CLRMSK              (IMG_UINT64_C(0XFFFFFF000000001F))


/*

		Range of bits used for PT Base Address for 2MB Physical Page

*/
#define RGX_MMUCTRL_PT_BASE_2MB_RANGE_SHIFT               (5U)
#define RGX_MMUCTRL_PT_BASE_2MB_RANGE_CLRMSK              (IMG_UINT64_C(0XFFFFFF000000001F))


/*

		Format of Page Table data

*/
/*
PM/Meta protect bit
*/
#define RGX_MMUCTRL_PT_DATA_PM_META_PROTECT_SHIFT         (62U)
#define RGX_MMUCTRL_PT_DATA_PM_META_PROTECT_CLRMSK        (IMG_UINT64_C(0XBFFFFFFFFFFFFFFF))
#define RGX_MMUCTRL_PT_DATA_PM_META_PROTECT_EN            (IMG_UINT64_C(0X4000000000000000))
/*
Upper part of vp page field
*/
#define RGX_MMUCTRL_PT_DATA_VP_PAGE_HI_SHIFT              (40U)
#define RGX_MMUCTRL_PT_DATA_VP_PAGE_HI_CLRMSK             (IMG_UINT64_C(0XC00000FFFFFFFFFF))
/*
Physical page address
*/
#define RGX_MMUCTRL_PT_DATA_PAGE_SHIFT                    (12U)
#define RGX_MMUCTRL_PT_DATA_PAGE_CLRMSK                   (IMG_UINT64_C(0XFFFFFF0000000FFF))
/*
Lower part of vp page field
*/
#define RGX_MMUCTRL_PT_DATA_VP_PAGE_LO_SHIFT              (6U)
#define RGX_MMUCTRL_PT_DATA_VP_PAGE_LO_CLRMSK             (IMG_UINT64_C(0XFFFFFFFFFFFFF03F))
/*
Entry pending
*/
#define RGX_MMUCTRL_PT_DATA_ENTRY_PENDING_SHIFT           (5U)
#define RGX_MMUCTRL_PT_DATA_ENTRY_PENDING_CLRMSK          (IMG_UINT64_C(0XFFFFFFFFFFFFFFDF))
#define RGX_MMUCTRL_PT_DATA_ENTRY_PENDING_EN              (IMG_UINT64_C(0X0000000000000020))
/*
PM Src
*/
#define RGX_MMUCTRL_PT_DATA_PM_SRC_SHIFT                  (4U)
#define RGX_MMUCTRL_PT_DATA_PM_SRC_CLRMSK                 (IMG_UINT64_C(0XFFFFFFFFFFFFFFEF))
#define RGX_MMUCTRL_PT_DATA_PM_SRC_EN                     (IMG_UINT64_C(0X0000000000000010))
/*
SLC Bypass Ctrl
*/
#define RGX_MMUCTRL_PT_DATA_SLC_BYPASS_CTRL_SHIFT         (3U)
#define RGX_MMUCTRL_PT_DATA_SLC_BYPASS_CTRL_CLRMSK        (IMG_UINT64_C(0XFFFFFFFFFFFFFFF7))
#define RGX_MMUCTRL_PT_DATA_SLC_BYPASS_CTRL_EN            (IMG_UINT64_C(0X0000000000000008))
/*
Cache Coherency bit
*/
#define RGX_MMUCTRL_PT_DATA_CC_SHIFT                      (2U)
#define RGX_MMUCTRL_PT_DATA_CC_CLRMSK                     (IMG_UINT64_C(0XFFFFFFFFFFFFFFFB))
#define RGX_MMUCTRL_PT_DATA_CC_EN                         (IMG_UINT64_C(0X0000000000000004))
/*
Read only
*/
#define RGX_MMUCTRL_PT_DATA_READ_ONLY_SHIFT               (1U)
#define RGX_MMUCTRL_PT_DATA_READ_ONLY_CLRMSK              (IMG_UINT64_C(0XFFFFFFFFFFFFFFFD))
#define RGX_MMUCTRL_PT_DATA_READ_ONLY_EN                  (IMG_UINT64_C(0X0000000000000002))
/*
Entry valid
*/
#define RGX_MMUCTRL_PT_DATA_VALID_SHIFT                   (0U)
#define RGX_MMUCTRL_PT_DATA_VALID_CLRMSK                  (IMG_UINT64_C(0XFFFFFFFFFFFFFFFE))
#define RGX_MMUCTRL_PT_DATA_VALID_EN                      (IMG_UINT64_C(0X0000000000000001))


/*

		Format of Page Directory data

*/
/*
Entry pending
*/
#define RGX_MMUCTRL_PD_DATA_ENTRY_PENDING_SHIFT           (40U)
#define RGX_MMUCTRL_PD_DATA_ENTRY_PENDING_CLRMSK          (IMG_UINT64_C(0XFFFFFEFFFFFFFFFF))
#define RGX_MMUCTRL_PD_DATA_ENTRY_PENDING_EN              (IMG_UINT64_C(0X0000010000000000))
/*
Page Table base address
*/
#define RGX_MMUCTRL_PD_DATA_PT_BASE_SHIFT                 (5U)
#define RGX_MMUCTRL_PD_DATA_PT_BASE_CLRMSK                (IMG_UINT64_C(0XFFFFFF000000001F))
/*
Page Size
*/
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_SHIFT               (1U)
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_CLRMSK              (IMG_UINT64_C(0XFFFFFFFFFFFFFFF1))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_4KB                 (IMG_UINT64_C(0000000000000000))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_16KB                (IMG_UINT64_C(0x0000000000000002))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_64KB                (IMG_UINT64_C(0x0000000000000004))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_256KB               (IMG_UINT64_C(0x0000000000000006))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_1MB                 (IMG_UINT64_C(0x0000000000000008))
#define RGX_MMUCTRL_PD_DATA_PAGE_SIZE_2MB                 (IMG_UINT64_C(0x000000000000000a))
/*
Entry valid
*/
#define RGX_MMUCTRL_PD_DATA_VALID_SHIFT                   (0U)
#define RGX_MMUCTRL_PD_DATA_VALID_CLRMSK                  (IMG_UINT64_C(0XFFFFFFFFFFFFFFFE))
#define RGX_MMUCTRL_PD_DATA_VALID_EN                      (IMG_UINT64_C(0X0000000000000001))


/*

		Format of Page Catalogue data

*/
/*
Page Catalogue base address
*/
#define RGX_MMUCTRL_PC_DATA_PD_BASE_SHIFT                 (4U)
#define RGX_MMUCTRL_PC_DATA_PD_BASE_CLRMSK                (0X0000000FU)
#define RGX_MMUCTRL_PC_DATA_PD_BASE_ALIGNSHIFT            (12U)
#define RGX_MMUCTRL_PC_DATA_PD_BASE_ALIGNSIZE             (4096U)
/*
Entry pending
*/
#define RGX_MMUCTRL_PC_DATA_ENTRY_PENDING_SHIFT           (1U)
#define RGX_MMUCTRL_PC_DATA_ENTRY_PENDING_CLRMSK          (0XFFFFFFFDU)
#define RGX_MMUCTRL_PC_DATA_ENTRY_PENDING_EN              (0X00000002U)
/*
Entry valid
*/
#define RGX_MMUCTRL_PC_DATA_VALID_SHIFT                   (0U)
#define RGX_MMUCTRL_PC_DATA_VALID_CLRMSK                  (0XFFFFFFFEU)
#define RGX_MMUCTRL_PC_DATA_VALID_EN                      (0X00000001U)


#endif /* _RGXMMUDEFS_KM_H_ */

/*****************************************************************************
 End of file (rgxmmudefs_km.h)
*****************************************************************************/

