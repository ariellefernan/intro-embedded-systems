/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 2/3/23
 * This program implements Task 1a of Lab 2. All 4 LEDS on the TIVA Launchpad
 * turn on and off in a sequential pattern, with a 1 second delay in-between.
 * They light up one-by-one until they
 * are all turned on, and then turn off one-by-one until they're all 
 * turned off. This behavior continuously repeats. 
 */

#include <stdint.h> 
#include "lab2task1a.h" 

int main(void){ 
  GPIO_init();
  Timer_init(); 
  int counter = 0; // Counter variable to keep track of LEDs turning on/off. 
   while (1) {    
      if ((GPTMRIS_0 & 0x1) == 1) { 
          GPTMICR_0 |= 0x1; // Clear flag 
          // Function to execute LEDs in a periodic pattern. 
          TickFct_Pattern(counter);
          if (counter == 7) {
            counter = 0;
          } else { 
            counter++; 
          } 
      } 
   }
   return 0;
}    

void GPIO_init() { 
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x1020;  // Enable Ports F & N GPIO 
    delay++;           // Delay 2 more cycles before accessing  Timer registers 
    delay++;           
    GPIODIR_F = 0x11;   // Set PF0 and PF4 to output (LEDS 3 & 4)
    GPIODEN_F = 0x11;   // Set PF0 to digital port 
    GPIODIR_N = 0x3;   // Set PN0 and PN1 to output (LEDS 1 & 2)
    GPIODEN_N = 0x3;   // Set PN0 and PN1 to digital port 
} 

void Timer_init() { 
  RCGCTIMER |= 0x1; 
  GPTMCTL_0 |= 0x0; // Disable Timer 0 
  GPTMCFG_0 = 0x0; // Select 32 bit mode. 
  GPTMTAMR_0 |= 0x2; 
  GPTMTAMR_0 &= ~0x10; 
  GPTMTAILR_0 = 0xF42400; 
  GPTMCTL_0 |= 0x1; // Enable Timer 0
} 

void TickFct_Pattern(int counter) {
      if (counter == 0) {
         GPIODATA_N = 0x0;
         GPIODATA_F = 0x0;
      } 
      else if (counter == 1) { 
         GPIODATA_N = 0x2;
      } 
      else if (counter == 2) { 
         GPIODATA_N = 0x3; // Turns on LED 1 & LED 2 (D2)
      } 
      else if (counter == 3) {
        GPIODATA_F = 0x10; // Turns on LED1, 2 and 3
      } else if (counter == 4){
         GPIODATA_F = 0x11;  
      } else if (counter == 5) {
        GPIODATA_F = 0x10; // Turns off LED 3.
      } else if (counter == 6) {
        GPIODATA_N = 0x3; // Turns on LED 1 & LED 2 (D2)
        GPIODATA_F = 0x00; // Turns off LED 3 & 4 
      } else {
        GPIODATA_N = 0x2;
      }    
} 