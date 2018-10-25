This example shows ERIKA3 with two tasks writing in mutual exclusion on the serial interface.

The specific platform can be specified in the OIL file through the PLATFORM field.
In case of PLATFORM = JAILHOUSE, ERIKA3 is running as Jailhouse inmate.
In case of PLATFORM = BARE, ERIKA3 is compiled for running as bare-metal. The resulting elf file must be used with a multiboot-compliant bootloaders (i.e., GRUB) for creating, for example, a Qemu/Xen image.

The hardware board can be specified in the OIL file through the BOARD_DATA field (e.g. BOARD_DATA = VBOX_3610;).
