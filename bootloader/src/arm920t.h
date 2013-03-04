#ifndef ARM920T_H
#define ARM920T_H

#define PSR_MODE_USR    (0x10)
#define PSR_MODE_FIQ    (0x11)
#define PSR_MODE_IRQ    (0x12)
#define PSR_MODE_SVC    (0x13)
#define PSR_MODE_ABT    (0x17)
#define PSR_MODE_UND    (0x1B)
#define PSR_MODE_SYS    (0x1F)
#define PSR_MASK_FIQ    (1<<6)
#define PSR_MASK_IRQ    (1<<7)

#define WRREG(dst, val, reg1, reg2) \
    ldr     reg1, =dst;\
    ldr     reg2, =val;\
    str     reg2, [reg1]

#define CHAGE_MODE(newmode, reg) \
    mrs     reg,cpsr;\
    bic     reg,reg,#(0x1f);\
    orr     reg,reg,#(newmode);\
    msr     cpsr,reg

#define RETURN \
    mov     pc, lr

#endif /*ARM920T_H*/
