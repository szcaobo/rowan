#include <arch_helpers.h>
#include <assert.h>
#include <bl_common.h>
#include <debug.h>
#include <interrupt_mgmt.h>
#include <platform.h>
#include <plat_config.h>
#include <stdint.h>
#include <xlat_tables.h>
#include "plat_def.h"
#include "plat_private.h"
#include <platform_def.h>
#include <stdio.h>  /* for printf */
#include "rpmb_hmac.h"
#include <sip_error.h>
#include <mmio.h>
#include <console.h>
#include <string.h>
#include "sha2_export.h"
#include "lk_shared_mem.h"


/* #define MTK_RPMB_DEBUG */
/* #define MTK_HMAC_TEST_VECTOR */
#define RPMB_KEY_SIZE                (32)        /* fixed 32 bytes in rpmb case */


/* sync with preloader tz_mem.h, platform-dependent code */
#define ATF_BOOT_ARG_ADDR       (0x00100000)
#define TEE_BOOT_ARG_ADDR       (ATF_BOOT_ARG_ADDR + 0x100)
#define TEE_PARAMETER_ADDR      (TEE_BOOT_ARG_ADDR + 0x100)


/* copied from preloader tz_mem.h */
typedef struct {
	unsigned int magic;             /* Magic number */
	unsigned int version;           /* version */
	unsigned int svp_mem_start;     /* MM sec mem pool start addr. */
	unsigned int svp_mem_end;       /* MM sec mem pool end addr. */
	unsigned int tplay_table_start; /* tplay handle-to-physical table start */
	unsigned int tplay_table_size;  /* tplay handle-to-physical table size */
	unsigned int tplay_mem_start;   /* tplay physcial memory start address for crypto operation */
	unsigned int tplay_mem_size;    /* tplay phsycial memory size for crypto operation */
	unsigned int secmem_obfuscation;/* MM sec mem obfuscation or not */
	unsigned int msg_auth_key[8];   /* size of message auth key is 32bytes(256bits) */
	unsigned int rpmb_size;         /* size of rpmb partition */
	unsigned int shared_secmem;     /* indicate if the memory is shared between REE and TEE */
	unsigned int m4u_mem_start;     /* reserved start address of secure memory for m4u */
	unsigned int m4u_mem_size;      /* reserved size of secure memory for m4u */
	unsigned int cmdq_mem_start;    /* reserved start address of secure memory for cmdq */
	unsigned int cmdq_mem_size;     /* reserved size of secure memory for cmdq */
} sec_mem_arg_t, *sec_mem_arg_t_ptr;

static int rpmb_is_in_lk = MTK_RPMB_IN_LK;
static u8 rpmbk[HMAC_BLOCK_SIZE] = {0};   /* it has to be block_size(2*key_size) */


#ifdef MTK_RPMB_DEBUG
/* dump buffer content  */
static void dump_buf(u8 *buf, uint32_t size)
{
	int i;

	for (i = 0; i < size/8; i++) {
		printf("%02x %02x %02x %02x %02x %02x %02x %02x\n",
		       buf[0+i*8], buf[1+i*8], buf[2+i*8], buf[3+i*8],
		       buf[4+i*8], buf[5+i*8], buf[6+i*8], buf[7+i*8]);
	}
	for (i = 0; i < size%8; i++) {
		printf("%02x\n", buf[((size/8)*8) + i]);
	}
	return;
}
#endif

static int byte_reverse(unsigned char *id_ptr)
{
	int i = 0;
	int tmp = 0;

	for (i=0 ; i<=2; i+=2) {
		tmp = *(id_ptr+i);
		*(id_ptr+i) = *(id_ptr+i+1);
		*(id_ptr+i+1) = tmp;
	}
	return 0;
}

static int cross_id_switch(unsigned char *id_1_ptr, unsigned char *id_2_ptr)
{
	unsigned char tmp = 0;

	tmp = *(id_1_ptr+1);
	*(id_1_ptr+1) = *(id_2_ptr);
	*(id_2_ptr) = tmp;

	tmp = *(id_1_ptr+2);
	*(id_1_ptr+2) = *(id_2_ptr+3);
	*(id_2_ptr+3) = tmp;

	return 0;
}

static int dump_id_data(unsigned int id_1, unsigned int id_2)
{

	/* -----------------------------------  */
	/* Dump for debug                       */
	/* -----------------------------------  */
#ifdef MTK_RPMB_DEBUG
	printf("id_1:0x%x\n", id_1);
	printf("id_2:0x%x\n", id_2);
#endif //MTK_RPMB_DEBUG

	return 0;
}


static int compute_random_pattern(unsigned int *magic_pattern)
{
	int ret = SIP_SVC_E_SUCCESS;

	unsigned int id_1 = 0;
	unsigned int id_2 = 0;
	unsigned char* id_1_ptr = (unsigned char *)&id_1;
	unsigned char* id_2_ptr = (unsigned char *)&id_2;
	atf_arg_t_ptr teearg = &gteearg;


	id_1 =  teearg->HRID[0];
	id_2 =  teearg->HRID[1];
	*magic_pattern = 0;

	if ((id_1 == 0) || (id_2 == 0)) {
		printf("hrid is 0, [1]:%d, [2]:%d\n", id_1, id_2);
		ret = SIP_SVC_E_INVALID_PARAMS;
		goto _end;
	}

	dump_id_data(id_1, id_2);

	/* -----------------------------------  */
	/* Byte reverse                         */
	/* -----------------------------------  */
	byte_reverse(id_1_ptr);
	byte_reverse(id_2_ptr);
	dump_id_data(id_1, id_2);

	/* -----------------------------------  */
	/* Cross ID Switch                      */
	/* -----------------------------------  */
	cross_id_switch(id_1_ptr, id_2_ptr);
	dump_id_data(id_1, id_2);

	/* -----------------------------------  */
	/* xor ids                              */
	/* -----------------------------------  */
	id_1 = id_1 ^ id_2;
#ifdef MTK_RPMB_DEBUG
	printf("random pattern:0x%x\n", id_1);
#endif //MTK_RPMB_DEBUG
	*magic_pattern = id_1;

_end:
	return ret;

}



/* must be called after  */
static int32_t read_rpmbk(void)
{

	uint32_t key_size = RPMB_KEY_SIZE;

	/* rpmb key generated in preloader are of length 32 bytes, < block_size (64bytes) */
	sec_mem_arg_t_ptr sec_mem_ptr = (sec_mem_arg_t_ptr) (TEE_PARAMETER_ADDR);

#ifdef MTK_RPMB_DEBUG
	printf("dump original rpmb key in tee para:\n");
	dump_buf((u8 *)(sec_mem_ptr->msg_auth_key), 32);
#endif //MTK_RPMB_DEBUG

	memcpy(rpmbk, sec_mem_ptr->msg_auth_key, RPMB_KEY_SIZE);

	/* keys shorter than blocksize are zero-padded */
	if (key_size < HMAC_BLOCK_SIZE) {
		memset(rpmbk+key_size, 0x0, (HMAC_BLOCK_SIZE-key_size));
	}

#ifdef MTK_RPMB_DEBUG
	printf("rpmb key:\n");
	dump_buf(rpmbk, HMAC_BLOCK_SIZE);
#endif //MTK_RPMB_DEBUG

	return SIP_SVC_E_SUCCESS;
}

/* clear rpmb key after HMAC is calculated */
static int32_t clear_rpmbk(void)
{

	memset(rpmbk, 0x0 , HMAC_BLOCK_SIZE);
	return SIP_SVC_E_SUCCESS;
}

static int32_t reinit_key_pad(u8* i_key_pad, u8* o_key_pad)
{

	/* reinit o_key_pad */
	memset(o_key_pad, 0x5C, HMAC_BLOCK_SIZE);

	/* reinit i_key_pad */
	memset(i_key_pad, 0x36, HMAC_BLOCK_SIZE);

	return SIP_SVC_E_SUCCESS;

}

/*
 * rpmb_init: set shared memory region with lk.
 * return 0 for success, otherwise negative status code.
 */
int32_t rpmb_init(void)
{

	uint32_t phy_addr = LK_SHARED_MEM_ADDR;

#ifdef MTK_RPMB_DEBUG
	uint64_t *shared_mem_ptr;
	uint64_t offset = 0;

	set_uart_flag();
	printf("[%s] in rpmb shared mem smc, phy_addr:0x%x rpmb_is_in_lk:0x%x!!\n",
	       __func__, phy_addr, rpmb_is_in_lk);
#endif //MTK_RPMB_DEBUG

	/* return err if it's already invoked in lk */
	if (MTK_RPMB_LEAVING_LK == rpmb_is_in_lk) {
		printf("[%s] no longer in lk, return immediately\n", __func__);
		return SIP_SVC_E_NOT_SUPPORTED;
	} else if (MTK_RPMB_IN_LK == rpmb_is_in_lk) {
		printf("[%s] invoked from lk\n", __func__);
	}

	/* map physcial memory for 4KB size.
	 * assert inside mmap_add_region if error occurs. no need to check return
	 * value in this case
	 */
	mmap_add_region((uint64_t)(phy_addr & ~(PAGE_SIZE_MASK)),
	                (uint64_t)(phy_addr & ~(PAGE_SIZE_MASK)),
	                PAGE_SIZE,
	                MT_DEVICE | MT_RW | MT_NS);

	/* re-fill translation table */
	init_xlat_tables();

	/* flush phy_addr content  */
	flush_dcache_range((uint64_t)(phy_addr & ~(PAGE_SIZE_MASK)), (uint64_t)PAGE_SIZE);


#ifdef MTK_RPMB_DEBUG

	shared_mem_ptr = (uint64_t *)(uintptr_t)(phy_addr);
	offset = phy_addr - (phy_addr & ~(PAGE_SIZE_MASK));
	printf("[%s] in rpmb shared mem smc, aligned phy_addr:0x%x offset:0x%x!!\n",
	       __func__, (phy_addr & ~(PAGE_SIZE_MASK)), offset);
	printf("[%s] dump content 0x%x set in lk nwd:\n", __func__, shared_mem_ptr);
	unsigned int i = 0;

	for (i = 0; i < 2; i++, shared_mem_ptr++) {
		printf("0x%16lx:0x%16lx\n", (shared_mem_ptr), *(shared_mem_ptr));
	}

	clear_uart_flag();
#endif //MTK_RPMB_DEBUG

	return SIP_SVC_E_SUCCESS;
}

/*
 * rpmb_uninit: mark as leaving lk, avoid request from kernel. ToDo:release the shared memory region with lk
 * return 0 for success, otherwise negative status code.
 */
int32_t rpmb_uninit(void)
{

	/* ToDo: ummap the shared memory with LK for RPMB
	 * once unmap API is available in ATF
	 */

#ifdef MTK_RPMB_DEBUG
	set_uart_flag();
	printf("[%s] mark leaving lk\n", __func__);
#endif //MTK_RPMB_DEBUG
	/* mark leaving lk, kernel can't making smc call for HMAC computation */
	rpmb_is_in_lk = MTK_RPMB_LEAVING_LK;

#ifdef MTK_RPMB_DEBUG
	clear_uart_flag();
#endif //MTK_RPMB_DEBUG

	return SIP_SVC_E_SUCCESS;
}

/*
 * hmac_sha256: calculate HMAC with sepcified key and msg.
 * @key: specified key
 * @key_size: the size of key for hmac, here we don't consider key_size >  block_size
 * @msg: specified msg
 * @msg_len: the size of msg.
 * @mac: mac result, here the size is 32 bytes for sha256.
 * return 0 for success, otherwise negative status code.
 */
static int32_t hmac_sha256(u8 *key, uint32_t key_size, u8 *msg,
                           uint32_t msg_len, u8 *mac)
{

	int i = 0;
	u8 *i_key_pad_ptr = (u8 *)(LK_SHARED_MEM_ADDR + I_KEY_PAD_OFFSET);
	u8 *o_key_pad_ptr = (u8 *)(LK_SHARED_MEM_ADDR + O_KEY_PAD_OFFSET);
	u8 *hash1_ptr = (u8 *)(LK_SHARED_MEM_ADDR + HASH1_OFFSET);
	u8 *hash2_ptr = (u8 *)(LK_SHARED_MEM_ADDR + HASH2_OFFSET);

#ifdef MTK_RPMB_DEBUG
	set_uart_flag();
	printf("[%s] entering...\n", __func__);

	printf("key:\n");
	dump_buf(key, key_size);

	printf("msg addr:0x%x msg:\n", msg);
	dump_buf(msg, msg_len);
#endif //MTK_RPMB_DEBUG

	/* check valide range */
	if (msg_len > MSG_MAX_SIZE) {
		printf("[%s] size over maximum allowed size\n", __func__);
		return SIP_SVC_E_INVALID_Range;
	}

	if ((msg_len == 0) || (key_size == 0)) {
		printf("[%s] key or msg size is zero\n", __func__);
	}

	/* the key is always of fixed length in our use case.(HMAC-SHA256)
	*  so no need to check key length
	*/
	reinit_key_pad(i_key_pad_ptr, o_key_pad_ptr);

#ifdef MTK_RPMB_DEBUG
	printf("i_key_pad:\n");
	dump_buf(i_key_pad_ptr, HMAC_BLOCK_SIZE);

	printf("o_key_pad:\n");
	dump_buf(o_key_pad_ptr, HMAC_BLOCK_SIZE);
#endif //MTK_RPMB_DEBUG


	if (key_size > HMAC_BLOCK_SIZE) {
		/* do not consider this case in this implementation, key is always <
		HMAC_BLOCK_SIZE */
	}

	/* key xorred with o_key_pad & i_key_pad, rest is filled with 0x36(inner) or
	0x5C(outter) */
	for (i = 0; i < key_size; i++) {
		o_key_pad_ptr[i] = o_key_pad_ptr[i] ^ key[i];
		i_key_pad_ptr[i] = i_key_pad_ptr[i] ^ key[i];
	}

#ifdef MTK_RPMB_DEBUG
	printf("key_size:%d\n", key_size);
	printf("i_key_pad[with key]:\n");
	dump_buf(i_key_pad_ptr, HMAC_BLOCK_SIZE);

	printf("o_key_pad[with key]:\n");
	dump_buf(o_key_pad_ptr, HMAC_BLOCK_SIZE);
#endif //MTK_RPMB_DEBUG

	/*
	*  shared memory layout
	*  |           |           |     |            |       |         |       |         |    |                 |
	*  | i_key_pad |  message  | ... | o_key_pad  | hash1 | padding | hash2 | padding | iv |sha256 operation |
	*  |           |           |     |            |       |         |       |         |    |                 |
	*    i_key_size   msg_size         o_key_size   sha256   128B     sha256   128B     iv  sha256 mass data |
	*
	*/

#ifdef MTK_RPMB_DEBUG
	printf("compute first hash ==> hash(i_key_pad �� message)\n");
#endif //MTK_RPMB_DEBUG

	/* compute first hash ==> hash(i_key_pad �� message) */
	sha256(i_key_pad_ptr, (msg_len + HMAC_BLOCK_SIZE), hash1_ptr);

#ifdef MTK_RPMB_DEBUG
	printf("dump first hash:\n");
	dump_buf(hash1_ptr, SHA256_SIZE);
	printf("compute second hash ==> hash(o_key_pad ��hash1)\n");
#endif //MTK_RPMB_DEBUG

	/* compute second hash ==> hash(o_key_pad ��hash1) */
	sha256(o_key_pad_ptr, (HMAC_BLOCK_SIZE + SHA256_SIZE), hash2_ptr);

#ifdef MTK_RPMB_DEBUG
	printf("dump second hash:\n");
	dump_buf(hash2_ptr, SHA256_SIZE);
#endif //MTK_RPMB_DEBUG

	memcpy(mac, hash2_ptr, SHA256_SIZE);

	return SIP_SVC_E_SUCCESS;
}

#ifdef MTK_HMAC_TEST_VECTOR

static int32_t hmac_test()
{

	uint32_t key_size = 0;
	uint32_t msg_size = 0;
	u8 *msg_ptr = (u8 *)(LK_SHARED_MEM_ADDR + MSG_OFFSET);
	u8 *mac_result = (u8 *)(LK_SHARED_MEM_ADDR + HASH2_OFFSET);

#if 0
	/* Test vector 1 */
	/* refer to IETF RFC 4231 Test Case 1, https://tools.ietf.org/html/rfc4231#section-4.1 */
	/* Answer: b0344c61d8db38535ca8afceaf0bf12b881dc200c9833da726e9376c2e32cff7 */
	key_size = 20;
	memset(rpmbk, 0x0b, key_size);
	msg_size = 8;
	char test_str[8] = {0x48, 0x69, 0x20, 0x54, 0x68, 0x65, 0x72, 0x65};

	memcpy(msg_ptr, test_str, msg_size);
#endif

	/* Test vector 2 */
	/* refer to IETF RFC 4231 Test Case 2, https://tools.ietf.org/html/rfc4231#section-4.1 */
	/* Answer: 5bdcc146bf60754e6a042426089575c75a003f089d2739839dec58b964ec3843 */
	char test_str[28] = {0x77, 0x68, 0x61, 0x74, 0x20, 0x64, 0x6f, 0x20, 0x79,
	                     0x61, 0x20, 0x77, 0x61, 0x6e, 0x74, 0x20, 0x66, 0x6f,
	                     0x72, 0x20, 0x6e, 0x6f, 0x74, 0x68, 0x69, 0x6e, 0x67,
	                     0x3f
	                    };
	char key[4] = {0x4a, 0x65, 0x66, 0x65};

	key_size = 4;
	msg_size = 28;
	memcpy(rpmbk, key, key_size);
	memcpy(msg_ptr, test_str, msg_size);

#if 0
	/* Test vector 3 */
	/* refer to IETF RFC 4231 Test Case 3, https://tools.ietf.org/html/rfc4231#section-4.1 */
	/* Answer: 773ea91e36800e46854db8ebd09181a72959098b3ef8c122d9635514ced565fe*/
	key_size = 20;
	memset(rpmbk, 0xaa, key_size);
	msg_size = 50;
	memset(msg_ptr, 0xdd, msg_size);
#endif

	hmac_sha256(rpmbk, key_size , msg_ptr, msg_size, mac_result);

	/* compute second hash ==> hash(o_key_pad ��hash1) */
	printf("dump test vector result\n");
	dump_buf(mac_result, SHA256_SIZE);


	return SIP_SVC_E_SUCCESS;
}

#endif

/*
 * rpmb_hmac: calculate HMAC with sepcified offset and size in shared memory.
 * @magic: magic # for verification
 * @size: the size of data that needs to calculate HMAC
 * return 0 for success, otherwise negative status code.
 */
int32_t rpmb_hmac(uint32_t magic, uint32_t size)
{

	/*
	*  shared memory layout
	*  |           |           |     |            |       |         |       |         |    |                 |
	*  | i_key_pad |  message  | ... | o_key_pad  | hash1 | padding | hash2 | padding | iv |sha256 operation |
	*  |           |           |     |            |       |         |       |         |    |                 |
	*    i_key_size   msg_size         o_key_size   sha256   128B     sha256   128B     iv  sha256 mass data |
	*
	*/
	u8 *msg_ptr = (u8 *)(LK_SHARED_MEM_ADDR + MSG_OFFSET);
	u8 *mac_result = (u8 *)(LK_SHARED_MEM_ADDR + HASH2_OFFSET);
	uint32_t random_pattern = 0;

#ifdef MTK_RPMB_DEBUG
	set_uart_flag();
	printf("[%s] entering...\n", __func__);

#endif //MTK_RPMB_DEBUG

	/* return err if it's already invoked in lk */
	if (MTK_RPMB_LEAVING_LK == rpmb_is_in_lk) {
		printf("[%s] no longer in lk, return immediately\n", __func__);
		return SIP_SVC_E_NOT_SUPPORTED;
	} else if (MTK_RPMB_IN_LK == rpmb_is_in_lk) {
		printf("[%s] invoked from lk\n", __func__);
	}

	/* compute random pattern */
	compute_random_pattern(&random_pattern);
	if ((random_pattern != magic) || (random_pattern == 0)) {
		printf("[%s] magic# is incorrect!!\n", __func__);
		return SIP_SVC_E_INVALID_PARAMS;
	}


#ifdef MTK_RPMB_DEBUG
	printf("input magic#:0x%x\n", magic);
	printf("generated random pattern:0x%x\n", random_pattern);
#endif //MTK_RPMB_DEBUG

	/* check valide range */
	if (size > MSG_MAX_SIZE) {
		printf("[%s] size over maximum allowed size\n", __func__);
		return SIP_SVC_E_INVALID_Range;
	}

	/* not allow empty msg in our case */
	if (size == 0) {
		printf("[%s] size is zero\n", __func__);
		return SIP_SVC_E_INVALID_Range;
	}

#ifdef MTK_HMAC_TEST_VECTOR
	hmac_test();
	return SIP_SVC_E_SUCCESS;
#endif // MTK_HMAC_TEST_VECTOR

	read_rpmbk();

	hmac_sha256(rpmbk, RPMB_KEY_SIZE , msg_ptr, size, mac_result);

#ifdef MTK_RPMB_DEBUG
	printf("dump final mac:\n");
	dump_buf(mac_result, SHA256_SIZE);
#endif //MTK_RPMB_DEBUG

	clear_rpmbk();

#ifdef MTK_RPMB_DEBUG
	printf("[%s] leaving...\n", __func__);
	clear_uart_flag();
#endif //MTK_RPMB_DEBUG

	return SIP_SVC_E_SUCCESS;

	/*
	* lk is running as single threaded, so no need to consider sync issue in
	* shared memory at the moment.
	*/
}




