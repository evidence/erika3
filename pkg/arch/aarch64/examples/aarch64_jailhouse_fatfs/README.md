FATFS DEMO ON JAILHOUSE for TegraX2
========================================

This demo shows how to use FatFs API from Erika Entrerprise running as a
Jailhouse'inmate.
The FAT file system is built on a portion of memory which can be private
in a Erika data section (e.g. stack, bss) or shared with Linux.
The latter case requires the root cell to share a memregion with Erika adding
the following section to both inmates' configurations.

'memregion':
		/* shared memregion */ {
			.phys_start = SOME_ADDRESS,
			.virt_start = 0xSOME_ADDRESS,
			.size = 0x80000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE
				|  JAILHOUSE_MEM_ROOTSHARED,
		},

NOTE: in the FatFs source code the macros "FF_USE_MKFS" must be enabled.
