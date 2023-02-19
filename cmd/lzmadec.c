/*
 * (C) Copyright 2013 Patrice Bouchand <pbfwdlist_gmail_com>
 * lzma uncompress command in Uboot
 *
 * made from existing cmd_unzip.c file of Uboot
 *
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <mapmem.h>
#include <asm/io.h>

#include <lzma/LzmaTools.h>

static char* mem_find_data(char* full_data, unsigned long full_data_len,char* find_data, unsigned long find_data_len)
{
	char* cur = full_data;
	if (full_data == NULL || full_data_len == 0 || find_data == NULL || find_data_len==0 
	||full_data_len <  find_data_len)
	{  
       		return NULL;  
    	}
 	unsigned long  max = full_data_len - find_data_len;
	for(unsigned long i=0;i<=max;i++)
	{
		if(*cur == *find_data)
		{
			if(memcmp(cur, find_data, find_data_len) == 0)
				return cur;
		}
		cur++;
	}
	return NULL;
}
extern char jedecid[3];

static int do_lzmadec(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	unsigned long src, dst;
	SizeT src_len = ~0UL, dst_len = ~0UL;
	int ret;
	char find[8]={0xef,0x60,0x17,0,0,0,0x03,0};
	char *flashid;
	switch (argc) {
	case 4:
		dst_len = simple_strtoul(argv[3], NULL, 16);
		/* fall through */
	case 3:
		src = simple_strtoul(argv[1], NULL, 16);
		dst = simple_strtoul(argv[2], NULL, 16);
		break;
	default:
		return CMD_RET_USAGE;
	}

	ret = lzmaBuffToBuffDecompress(map_sysmem(dst, dst_len), &src_len,
				       map_sysmem(src, 0), dst_len);

	if (ret != SZ_OK)
		return 1;
	printf("Uncompressed size: %ld = %#lX\n", (ulong)src_len,
	       (ulong)src_len);
	setenv_hex("filesize", src_len);
	
	find[1] = jedecid[1];
	find[2] = jedecid[2];
	flashid = mem_find_data(map_sysmem(dst, dst_len),src_len,find,sizeof(find));
	if(flashid != NULL)
	{
		flashid[0] = jedecid[0];
		printf("Find jedec id and patched to winbond! jedec id:0x%02X%02X%02X => 0x%02X%02X%02X\n",
		jedecid[0],jedecid[1],jedecid[2],find[0],find[1],find[2]);
	}
	else
	{
		printf("The flash is not support! jedec id:0x%02X%02X%02X",jedecid[0],jedecid[1],jedecid[2]);
	}
	printf("=================== MAOPAN.CC ===================\n");
	printf("|                                               |\n");
	printf("|                  Enjoy it !                   |\n");
	printf("|                                               |\n");
	printf("=================== MAOPAN.CC ===================\n");

	return 0;
}

U_BOOT_CMD(
	lzmadec,    4,    1,    do_lzmadec,
	"lzma uncompress a memory region",
	"srcaddr dstaddr [dstsize]"
);
