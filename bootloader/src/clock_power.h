#ifndef CLOCK_POWER_H
#define CLOCK_POWER_H

/*
 * - FCLK for CPU (ARM920T)
 * - HCLK for the AHB bus peripherals (ARM920T, memory controller, interrupt controller,
 *   LCD controller, DMA and USB host block)
 * - PCLK for the APB bus peripherals (peripherals such as WDT, IIS, I2C, PWM timer,
 *   MMC interface, ADC, UART, GPIO, RTC and SPI)
 *
 * Two PLLs:
 * MPLL for FCLK, HCLK, PCLK
 * UPLL for USB block (48Mhz or 96Mhz)
 *
 * Four Power Mode:
 * NORMAL - supplies clocks to CPU and all peripherals
 * SLOW   - non-PLL mode. use external clock XTIpll or EXTCLK as FCLK
 * IDLE   - disconnects FCLK only to the CPU, supplies to all peripherals
 * SLEEP  - disconnects the internal power except wake-up logic
 *          The wakeup from SLEEP mode can be issued by the EINT[15:0] or by RTC alarm interrupt.
 *
 * OM[3:2]     MPLL State  UPLL State  Main Clock source   USB Clock Source
 * 00          On          On          Crystal             Crystal          <=== MINI2440
 * 01          On          On          Crystal             EXTCLK
 * 10          On          On          EXTCLK              Crystal
 * 11          On          On          EXTCLK              EXTCLK
 *
 */

#define LOCKTIME        0x4C000000  /* PLL lcok time count register */
#define U_LTIME(val)    (val << 16)
#define M_LTIME(val)    (val)

#define MPLLCON         0x4C000004  /* MPLL configuration register */
#define UPLLCON         0x4C000008  /* UPLL configuration register */
#define PLL_48MHZ       ((0x38<<12)|(2<<4)|2)
#define PLL_96MHZ       ((0x38<<12)|(2<<4)|1)
#define PLL_271MHZ      ((0xad<<12)|(2<<4)|2)
#define PLL_304MHZ      ((0x44<<12)|(1<<4)|1)
#define PLL_405MHZ      ((0x7f<<12)|(2<<4)|1)
#define PLL_532MHZ      ((0x7d<<12)|(1<<4)|1)

#define CLKCON          0x4C00000C  /* clock generator control register */
#define CLKEN_AC97      (1<<20)
#define CLKEN_CAM       (1<<19)
#define CLKEN_SPI       (1<<18)
#define CLKEN_IIS       (1<<17)
#define CLKEN_IIC       (1<<16)
#define CLKEN_ADC       (1<<15)
#define CLKEN_RTC       (1<<14)
#define CLKEN_GPIO      (1<<13)
#define CLKEN_UART2     (1<<12)
#define CLKEN_UART1     (1<<11)
#define CLKEN_UART0     (1<<10)
#define CLKEN_SDI       (1<<9)
#define CLKEN_PWM       (1<<8)
#define CLKEN_USBDEV    (1<<7)
#define CLKEN_USBHOST   (1<<6)
#define CLKEN_LCDC      (1<<5)
#define CLKEN_NAND      (1<<4)
#define CLK_SLEEP       (1<<3)
#define CLK_IDLE        (1<<2)

#define CLKSLOW         0x4C000010
#define UCLK_OFF        (1<<7)
#define MPLL_OFF        (1<<5)
#define SLOW_MODE       (1<<4)
#define SLOW_VAL        (4)

#define CLKDIVN         0x4C000014  /* clock divisor register */
#define FCLK_HCLK_PCLK      ((0<<1)|0)
#define FCLK_HCLK_2PCLK     ((0<<1)|1)
#define FCLK_2HCLK_2PCLK    ((1<<1)|0)
#define FCLK_2HCLK_4PCLK    ((1<<1)|1)
#define FCLK_3HCLK_3PCLK    ((3<<1)|0)  /* HCLK3_HALF/HCLK4_HALF must be 0/0 */
#define FCLK_3HCLK_6PCLK    ((3<<1)|1)  /* HCLK3_HALF/HCLK4_HALF must be 0/0 */
#define FCLK_6HCLK_6PCLK    ((3<<1)|0)  /* HCLK3_HALF/HCLK4_HALF must be 1/0 */
#define FCLK_6HCLK_12PCLK   ((3<<1)|1)  /* HCLK3_HALF/HCLK4_HALF must be 1/0 */
#define FCLK_4HCLK_4PCLK    ((2<<1)|0)  /* HCLK3_HALF/HCLK4_HALF must be 0/0 */
#define FCLK_4HCLK_8PCLK    ((2<<1)|1)  /* HCLK3_HALF/HCLK4_HALF must be 0/0 */
#define FCLK_8HCLK_8PCLK    ((2<<1)|0)  /* HCLK3_HALF/HCLK4_HALF must be 0/1 */
#define FCLK_8HCLK_16PCLK   ((2<<1)|1)  /* HCLK3_HALF/HCLK4_HALF must be 0/1 */

#define CAMDIVN         0x4C000018  /* Camera clock divider register */
#define DVS_EN          (1 << 12)
#define HCLK4_HALF      (1 << 9)
#define HCLK3_HALF      (1 << 8)
#define CAMCLK_SEL      (1 << 4)
#define CAMCLK_DIV(val) (val)
#endif /*CLOCK_POWER_H*/
