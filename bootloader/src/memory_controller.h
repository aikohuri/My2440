#ifndef MEMORY_CONTROLLER_H
#define MEMORY_CONTROLLER_H

/*
 * Bus width & wait status control register
 */
#define BWSCON          0x48000000

/* BWSCON */
#define DW8             (0x0)
#define DW16            (0x1)
#define DW32            (0x2)
#define WAIT            (0x1<<2)
#define UBLB            (0x1<<3)

#define B1_BWSCON       (DW32 << 4)
#define B2_BWSCON       (DW16 << 8)
#define B3_BWSCON       ((DW16 + WAIT + UBLB)<<12)
#define B4_BWSCON       ((DW16 + WAIT + UBLB)<<16)
#define B5_BWSCON       (DW16 << 20)
#define B6_BWSCON       (DW32 << 24)
#define B7_BWSCON       (DW32 << 28)
#define BWSCON_DATA     (0 + B1_BWSCON + B2_BWSCON + B3_BWSCON + B4_BWSCON + B5_BWSCON + B6_BWSCON + B7_BWSCON)

/* BANK0CON */
#define B0_Tacs         (0x0 << 13)   /*  0clk */
#define B0_Tcos         (0x0 << 11)   /*  0clk */
#define B0_Tacc         (0x7 << 8)    /* 14clk */
#define B0_Tcoh         (0x0 << 6)    /*  0clk */
#define B0_Tah          (0x0 << 4)    /*  0clk */
#define B0_Tacp         (0x0 << 2)
#define B0_PMC          (0x0)    /* normal */
#define BANKCON0_DATA   (B0_Tacs | B0_Tcos | B0_Tacc | B0_Tcoh | B0_Tah | B0_Tacp | B0_PMC)

/* BANK1CON */
#define B1_Tacs         (0x0 << 13)   /*  0clk */
#define B1_Tcos         (0x0 << 11)   /*  0clk */
#define B1_Tacc         (0x7 << 8)    /* 14clk */
#define B1_Tcoh         (0x0 << 6)    /*  0clk */
#define B1_Tah          (0x0 << 4)    /*  0clk */
#define B1_Tacp         (0x0 << 2)
#define B1_PMC          (0x0)
#define BANKCON1_DATA   (B1_Tacs|B1_Tcos|B1_Tacc|B1_Tcoh|B1_Tah|B1_Tacp|B1_PMC)

#define B2_Tacs         (0x0 << 13)
#define B2_Tcos         (0x0 << 11)
#define B2_Tacc         (0x7 << 8) 
#define B2_Tcoh         (0x0 << 6) 
#define B2_Tah          (0x0 << 4) 
#define B2_Tacp         (0x0 << 2)
#define B2_PMC          (0x0)
#define BANKCON2_DATA   (B2_Tacs|B2_Tcos|B2_Tacc|B2_Tcoh|B2_Tah|B2_Tacp|B2_PMC)

#define B3_Tacs         (0x0 << 13)     /*  0clk */
#define B3_Tcos         (0x3 << 11)     /*  4clk */
#define B3_Tacc         (0x7 << 8)      /* 14clk */
#define B3_Tcoh         (0x1 << 6)      /*  1clk */
#define B3_Tah          (0x3 << 4)      /*  4clk */
#define B3_Tacp         (0x0 << 2)      /*  2clk */
#define B3_PMC          (0x0)           /* normal */
#define BANKCON3_DATA   (B3_Tacs|B3_Tcos|B3_Tacc|B3_Tcoh|B3_Tah|B3_Tacp|B3_PMC)

#define B4_Tacs         (0x0 << 13)
#define B4_Tcos         (0x3 << 11)
#define B4_Tacc         (0x7 << 8) 
#define B4_Tcoh         (0x1 << 6) 
#define B4_Tah          (0x3 << 4) 
#define B4_Tacp         (0x0 << 2) 
#define B4_PMC          (0x0)      
#define BANKCON4_DATA   (B4_Tacs|B4_Tcos|B4_Tacc|B4_Tcoh|B4_Tah|B4_Tacp|B4_PMC)

#define B5_Tacs         (0x0 << 13)     /*  0clk */
#define B5_Tcos         (0x0 << 11)     /*  0clk */
#define B5_Tacc         (0x7 << 8)      /* 14clk */
#define B5_Tcoh         (0x0 << 6)      /*  0clk */
#define B5_Tah          (0x0 << 4)      /*  0clk */
#define B5_Tacp         (0x0 << 2)
#define B5_PMC          (0x0)           /* normal */
#define BANKCON5_DATA   (B5_Tacs|B5_Tcos|B5_Tacc|B5_Tcoh|B5_Tah|B5_Tacp|B5_PMC)

#define SDRAM_MT        (0x3 << 15)     /* SDRAM */
#define SDRAM_Trcd      (0x0 << 2)      /* 2clk */
#define SDRAM_SCAN_9    (0x1)           /* 9bit */
#define SDRAM_SCAN_10   (0x2)           /* 10bit */

#define SDRAM_128MB     (SDRAM_MT|SDRAM_Trcd|SDRAM_SCAN_10)
#define SDRAM_64MB      (SDRAM_MT|SDRAM_Trcd|SDRAM_SCAN_9)
#define BANKCON6_DATA   SDRAM_64MB
#define BANKCON7_DATA   SDRAM_64MB

/* REFRESH parameter */
#define REFEN           (0x1 << 23)    /* Refresh enable */
#define TREFMD          (0x0 << 22)    /* CBR(CAS before RAS)/Auto refresh */
#define Trp             (0x1 << 20)    /* 3clk */
#define Trc             (0x3 << 18)    /* 7clk */
#define Tchr            (0x0 << 16)    /* unused */

#define REFCNT          (1012)    /* period=10.37us, HCLK=100Mhz, (2048+1-10.37*100) */

#define REFRESH_DATA    (REFEN|TREFMD|Trp|Trc|Tchr|REFCNT)
#define BANKSIZE_DATA   (0xb2)    /* enable burst */
#define MRSRB6_DATA     (0x30)
#define MRSRB7_DATA     (0x30)

#endif /*MEMORY_CONTROLLER_H*/
