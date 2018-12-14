Tests description
=================

-------------------------------------------------------------------------------------
File name     |   ISR name     |      ISR nb.         | ISR code        | ISR type
in tests/     |   in HAL.h     |      in HAL.c        | in code.c       | in conf.oil
-------------------------------------------------------------------------------------
act.h         |                |                      |                 |
actl.h        |                |                      |                 |
intdisable.h  |                |                      |                 |
intenable.h   |                |                      |                 |
isr2entry.h   | DEMO_HAL_ISR_0 | ISRENTRY_ISR2   0x21 | isrentry_isr2   | 2       1
isrentry.h    | DEMO_HAL_ISR_1 | ISRENTRY_ISR1   0x22 | isrentry_isr1   | 1       4
isrexit.h     | DEMO_HAL_ISR_2 | ISREXIT_ISR1    0x23 | isrexit_isr1    | 1       5
istentry.h    | DEMO_HAL_ISR_3 | ISTENTRY_ISR2   0x24 | istentry_isr2   | 2       2
istexit.h     | DEMO_HAL_ISR_4 | ISTEXIT_ISR2    0x25 | istexit_isr2    | 2       3
terml.h       |                |                      |                 |

