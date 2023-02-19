/*
 * Copyright (C) 2016 Stefan Roese <sr@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _CONFIG_MVEBU_ARMADA_H
#define _CONFIG_MVEBU_ARMADA_H

#include <asm/arch/soc.h>

#define CONFIG_IMAGE_FORMAT_LEGACY 1
/*
 * High Level Configuration Options (easy to change)
 */

#define	CONFIG_SYS_TEXT_BASE	0x00000000

/* additions for new ARM relocation support */
#define CONFIG_SYS_SDRAM_BASE	0x00000000


/* auto boot */
#define CONFIG_PREBOOT			"i2c dev 0; i2c probe 46; if test $? = 0; then echo \"=========== POWER OFF NOW !!! ===========\"; "\
					"gpio clear GPIO14; sleep 1; echo \"======== Please unplug the power ========\"; "\
					"i2c mw 0x46 0x34 0xff; i2c mw 0x46 0x35 0x00; i2c mw 0x46 0x36 0x00; i2c mw 0x46 0x31 0x11; "\
					"i2c mw 0x46 0x38 0x00; i2c mw 0x46 0x37 0x00; while true; do; done;" \
					"fi; "\
					"gpio set GPIO221; gpio set GPIO20; "\
					"i2c mw 0x45 0x01 0x01; i2c mw 0x45 0x30 0x07; "\
					"i2c mw 0x45 0x31 0x01; i2c mw 0x45 0x34 0xff"

#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, \
					  115200, 230400, 460800, 921600 }

/* Default Env vars */
#define CONFIG_IPADDR			192.168.1.150	/* In order to cause an error */
#define CONFIG_SERVERIP			192.168.1.100	/* In order to cause an error */
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_GATEWAYIP		0.0.0.0
#define CONFIG_HAS_ETH1
#define CONFIG_HAS_ETH2
#define CONFIG_ETHPRIME			"eth0"
#define CONFIG_ROOTPATH                 "/srv/nfs/" /* Default Dir for NFS */
#define CONFIG_ENV_OVERWRITE		/* ethaddr can be reprogrammed */
#define CONFIG_EXTRA_ENV_SETTINGS	"bootcmd=" \
					"run syno_bootargs; " \
					"sf probe; " \
					"sf read 0x1000000 0x0D5000 0x306000; " \
					"lzmadec 0x1000000 0x2000000; " \
					"sf read 0x3000000 0x3DB000 0x410000; " \
					"sf read 0x1000000 0xD1000 0x4000; "\
					"i2c mw 0x45 0x33 0x01; i2c mw 0x45 0x3d 0x10; i2c mw 0x45 0x3e 0x10; i2c mw 0x45 0x34 0x00; i2c mw 0x45 0x36 0xff; "\
					"booti 0x2000000 0x3000000 0x1000000\0"\
					"kernel_addr=0x7000000\0"	\
					"initrd_addr=0x1100000\0"	\
					"initrd_size=0x2000000\0"	\
					"fdt_addr=0x6000000\0"	\
					"loadaddr=0x8000000\0"		\
					"fdt_high=0xffffffffffffffff\0"	\
					"scriptaddr=0x6d00000\0"	\
					"hostname=marvell\0"		\
					"initrd_image=uInitrd\0"	\
					"ramdisk_addr_r=0x8000000\0"	\
					"ramfs_name=-\0"		\
					"fdt_name=fdt.dtb\0"		\
					"netdev=eth0\0"			\
					"ethaddr=00:51:82:11:22:00\0"	\
					"eth1addr=00:51:82:11:22:01\0"	\
					"eth2addr=00:51:82:11:22:02\0"	\
					"eth3addr=00:51:82:11:22:03\0"	\
					"image_name=Image\0"		\
					"console=" CONFIG_DEFAULT_CONSOLE "\0"\
					"boot_targets=sata usb mmc0\0"	\
					"boot_prefixes=/ /boot/\0"	\
					"syno_bootargs=setenv bootargs console=ttyS0,115200 ip=off initrd=0x3000000 root=/dev/sda1 rw syno_usb_vbus_gpio=36@d0058000.usb3@1@0,37@d005e000.usb@1@0 syno_castrated_xhc=d0058000.usb3@1 swiotlb=2048 syno_hw_version=DS120j syno_fw_version=M.301 syno_hdd_powerup_seq=1 ihd_num=1 netif_num=1 syno_hdd_enable=40 syno_hdd_act_led=10 flash_size=8\0" \
/*
 * For booting Linux, the board info and command line data
 * have to be in the first 8 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_CMDLINE_TAG		/* enable passing of ATAGs  */
#define CONFIG_INITRD_TAG		/* enable INITRD tag */
#define CONFIG_SETUP_MEMORY_TAGS	/* enable memory tag */

#define	CONFIG_SYS_CBSIZE	1024	/* Console I/O Buff Size */
#define	CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE \
		+sizeof(CONFIG_SYS_PROMPT) + 16)	/* Print Buff */

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN	(8 << 20) /* 8MiB for malloc() */

/*
 * Other required minimal configurations
 */
#define CONFIG_SYS_LONGHELP
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMDLINE_EDITING
#define CONFIG_ARCH_CPU_INIT		/* call arch_cpu_init() */
#define CONFIG_SYS_LOAD_ADDR	0x00800000	/* default load adr- 8M */
#define CONFIG_SYS_MEMTEST_START 0x00800000	/* 8M */
#define CONFIG_SYS_MEMTEST_END	0x00ffffff	/*(_16M -1) */
#define CONFIG_SYS_RESET_ADDRESS 0xffff0000	/* Rst Vector Adr */
#define CONFIG_SYS_MAXARGS	32	/* max number of command args */

#define CONFIG_SYS_ALT_MEMTEST

/* End of 16M scrubbed by training in bootrom */
#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_TEXT_BASE + 0xFF0000)

/*
 * SPI Flash configuration
 */
#define CONFIG_ENV_SPI_BUS		0
#define CONFIG_ENV_SPI_CS		0

/* SPI NOR flash default params, used by sf commands */
#define CONFIG_SF_DEFAULT_SPEED		1000000
#define CONFIG_SF_DEFAULT_MODE		SPI_MODE_0
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE

/* Environment in SPI NOR flash */
#ifdef CONFIG_MVEBU_SPI_BOOT
#define CONFIG_ENV_IS_IN_SPI_FLASH
/* Environment in NAND flash */
#elif defined(CONFIG_MVEBU_NAND_BOOT)
#define CONFIG_ENV_IS_IN_NAND
/* Environment in MMC */
#elif defined(CONFIG_MVEBU_MMC_BOOT)
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_PART		1 /* 0 - DATA, 1 - BOOT0, 2 - BOOT1 */
#endif

/* Assume minimum flash/eMMC boot partition size of 4MB
 * and save the environment at the end of the boot device
*/
#ifdef CONFIG_SPI_FLASH_SPANSION
#define CONFIG_ENV_SIZE				(256 << 10) /* 256KiB */
#define CONFIG_ENV_SECT_SIZE		(256 << 10) /* 256KiB sectors */
#else
#define CONFIG_ENV_SIZE				( 16 << 10) /* 16KiB */
#define CONFIG_ENV_SECT_SIZE		( 16 << 10) /* 16KiB sectors */
#endif
#ifdef CONFIG_MVEBU_NAND_BOOT
#define CONFIG_ENV_OFFSET		0x400000
#else
#define CONFIG_ENV_OFFSET		(0x14000 - CONFIG_ENV_SIZE)
#endif

#define CONFIG_USB_MAX_CONTROLLER_COUNT (CONFIG_SYS_USB_EHCI_MAX_ROOT_PORTS + \
					 CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS)

/* USB ethernet */
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_USB_ETHER_MCS7830
#define CONFIG_USB_ETHER_RTL8152
#define CONFIG_USB_ETHER_SMSC95XX

/*
 * SATA/SCSI/AHCI configuration
 */
#define CONFIG_SCSI
#define CONFIG_SCSI_AHCI
#define CONFIG_SCSI_AHCI_PLAT
#define CONFIG_LIBATA
#define CONFIG_LBA48
#define CONFIG_SYS_64BIT_LBA

#define CONFIG_SYS_SCSI_MAX_SCSI_ID	2
#define CONFIG_SYS_SCSI_MAX_LUN		1
#define CONFIG_SYS_SCSI_MAX_DEVICE	(CONFIG_SYS_SCSI_MAX_SCSI_ID * \
					 CONFIG_SYS_SCSI_MAX_LUN)

/* MMC/SD IP block */
#define CONFIG_SUPPORT_VFAT

/*
 * The EEPROM ST M24C64 has 32 byte page write mode and takes up to 10 msec.
 */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 10

/*
 * nm01 catdisk Config
 */
#define CONFIG_BOARD_TYPES
#define CONFIG_FAT_WRITE

#endif /* _CONFIG_MVEBU_ARMADA_H */
