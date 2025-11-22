/* startup.s - Minimal ARM7 startup for LPC2129 */
.syntax unified
.cpu arm7tdmi

.section .text
.global _start

_start:
    LDR SP, =0x00004000       /* Set stack pointer (RAM end) */
    BL main                    /* Call main function */
    B .                        /* Infinite loop if main returns */

.section .vectors, "a"
vectors:
    .word _start
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0

