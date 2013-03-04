#include "s3c2440.h"

    .global _start
    .func   _start

_start:
/*
 * reset vector
 */
    b   reset   /* Reset: relative branch allows remap */
    b   .       /* Undefined Instruction */
    b   .       /* Software Interrupt    */
    b   .       /* Prefetch Abort        */
    b   .       /* Data Abort            */
    b   .       /* Reserved              */
    b   .       /* IRQ                   */
    b   .       /* FIQ                   */

reset:
    /*
     * set the cpu to SVC32 mode
     */
    CHAGE_MODE(PSR_MASK_IRQ | PSR_MASK_FIQ | PSR_MODE_SVC, r0)

    /*
     * turn off the watchdog
     */
    WRREG(WTCON, 0, r0, r1)

    /*
     * disable all interrupts
     */
    WRREG(INTMSK, 0xFFFFFFFF, r0, r1)

    /*
     * disable all subinterrupts
     */
    WRREG(INTSUBMSK, 0x7FFF, r0, r1)

    /* FCLK:HCLK:PCLK = 1:2:4 */
    /* default FCLK is 120 MHz ! */
    ldr     r0, =CLKDIVN
    mov     r1, #3
    str     r1, [r0]

    /*
     * flush v4 I/D caches
     */
    mov     r0, #0
    mcr     p15, 0, r0, c7, c7, 0    /* flush v3/v4 cache */
    mcr     p15, 0, r0, c8, c7, 0    /* flush v4 TLB */

    /*
     * disable MMU stuff and caches
     */
    mrc     p15, 0, r0, c1, c0, 0
    bic     r0, r0, #0x00002300    @ clear bits 13, 9:8 (--V- --RS)
    bic     r0, r0, #0x00000087    @ clear bits 7, 2:0 (B--- -CAM)
    orr     r0, r0, #0x00000002    @ set bit 2 (A) Align
    orr     r0, r0, #0x00001000    @ set bit 12 (I) I-Cache
    mcr     p15, 0, r0, c1, c0, 0

    /*
     * calculate the ROM code address after remapping
     */
    ldr     lr, =startMain
    ldr     r4, =0x40000000      /* ROM address after remapping */
    add     lr, lr, r4

    ldr     r0, =SMRDATA
    ldmia   r0, {r1-r13}
    ldr     r0, =BWSCON

    /*
     * remap and jump to ROM code
     */
    stmia   r0, {r1-r13}  /* Memory bank control registers must be set using store multiples */
    mov     pc, lr

startMain:
    /*
     * Enter the C code
     */
    ldr     r12, =main
    mov     lr, pc           /* set the return address */
    bx      r12             /* the target code can be ARM or THUMB */

    swi     0xFFFFFF        /* cause exception if main() ever returns */

    .size   _start, . - _start
    .endfunc

    .ltorg
/*
 * the literal pools origin
 */
SMRDATA:
    .word BWSCON_DATA
    .word BANKCON0_DATA
    .word BANKCON1_DATA
    .word BANKCON2_DATA
    .word BANKCON3_DATA
    .word BANKCON4_DATA
    .word BANKCON5_DATA
    .word BANKCON6_DATA
    .word BANKCON7_DATA
    .word REFRESH_DATA
    .word BANKSIZE_DATA
    .word MRSRB6_DATA
    .word MRSRB7_DATA

    .end

