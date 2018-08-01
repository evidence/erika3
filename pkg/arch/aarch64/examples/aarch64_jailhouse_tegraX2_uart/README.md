ERIKA UART DEMO ON JAILHOUSE for TegraX2
========================================

This demo shows how to send/receive data on  Tegra X2 SoC's UART with Erika
 Entrerprise running as a Jailhouse'inmate.

Prerequisites on Linux
----------------------

The baudrate of the UART device which will be used for demo must be set by
Linux using a terminal configurator.
The demo will write and receive bytes on the UARTC which corresponds to the
/dev/ttyTHS2, so the command to enable the device is:
stty -F /dev/ttyTHS2 speed 'baudrate'

Another command is needed in order to enable the device's clock source:
sudo bash -c "echo 1 > /sys/kernel/debug/bpmp/debug/clk/uartc/state"
 

Prerequisites on Jailhouse
==========================
The inmate configuration must assign the proper irq in the 'irqchip' section.
For the UARTC the setting is the following:

		{ /* UART setting C 
			irq is 114*/
			.address = 0x03881000,
			.pin_base = 32,
			.pin_bitmap = {
				0,
				0,
				0,
				0x1 << (114 - 96)
			},

Furthermore the UARTC's registers must be reachable on the inmate's side through
 a 'memregion':
		/* UARTC memregion */ {
			.phys_start = 0x0c280000,
			.virt_start = 0x0c280000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE
				| JAILHOUSE_MEM_IO | JAILHOUSE_MEM_ROOTSHARED,
		},

