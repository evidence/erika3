ERIKA UART DEMO ON JAILHOUSE for TegraX1
========================================

This demo shows how to send/receive data on Tegra X1 SoC's UART with Erika
 Entrerprise running as a Jailhouse'inmate.

Prerequisites on Linux
----------------------

The baudrate of the UART device which will be used for demo must be set by
Linux using a terminal configurator.
The demo will write and receive bytes on the UARTC which corresponds to the
/dev/ttyTHS2, so the command to enable the device is:
stty -F /dev/ttyTHS2 speed 'baudrate'

Note: this command is needed in order to enable the device's clock source.

Prerequisites on Jailhouse
==========================
The inmate configuration must assign the proper irq in the 'irqchip' section.
For the UARTC the setting is the following:

		/* GIC */ {
			.address = 0x50041000,
                        .pin_base = 32,
                        /* Interrupts:
                           46 for UART b  */
                        .pin_bitmap = {
				0,
				1 << (46-32)
                        },
