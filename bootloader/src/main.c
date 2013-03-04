/*----------------------------------------------------------------------------*
   LED test
 *----------------------------------------------------------------------------*/
#include <stdint.h>

/* I/O PORT */
#define rGPBCON    (*(uint32_t volatile *)0x56000010) /* Port B control */
#define rGPBDAT    (*(uint32_t volatile *)0x56000014) /* Port B data    */

#define OUTPUT   (0x01)
#define LED1_EN  (OUTPUT << 10)
#define LED2_EN  (OUTPUT << 12)
#define LED3_EN  (OUTPUT << 14)
#define LED4_EN  (OUTPUT << 16)


void delay(unsigned int tt);


int main(int argc, char **argv)
{
   int data;

   rGPBCON = LED1_EN | LED2_EN | LED3_EN | LED4_EN;

   data = 0x0F;

   while(1)
   {
      rGPBDAT = (data<<5);
      data -= 1;
      delay(1);
      if( data < 0x0 )
         data = 0x0F;
   }

   return 0;
}


void delay(unsigned int tt)
{
   unsigned int i;

   for(;tt>0;tt--)
     for(i=0;i<10000;i++);
}
