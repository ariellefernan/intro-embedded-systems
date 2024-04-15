/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 1/21/23
 * This program implements Task 1a of Lab 1. All 4 LEDS on the TIVA Launchpad
 * turn on and off in a sequential pattern. They light up one-by-one until they
 * are all turned on, and then turn off one-by-one until they're all 
 * turned off. This behavior continuously repeats. 
 */

#include <stdint.h> 
#include "lab1.h" 

// Creates approximately a 0.3 second delay when changing in between LEDS. 
void delay() {
     for (int j = 0; j < 1000000; j++) {
     } 
}

int main(void){ 
  GPIO_init();
   while (1) {
      GPIODATA_N = 0x2; // Turns on LED 1 (D1)
      delay();
      GPIODATA_N = 0x3; // Turns on LED 1 & LED 2 (D2)
      delay();
      GPIODATA_F = 0x10; // Turns LED 3 (D3) while LEDS 1 & 2 are still on. 
      delay();
      GPIODATA_F = 0x11; // Turns on LED 4 (D4) while LEDS 1, 2 & 3 are on.
      delay();
      GPIODATA_F = 0x10; // Turns off LED 4.
      delay();
      GPIODATA_F = 0x0; // Turns off LED 3. 
      delay();
      GPIODATA_N = 0x3; // Turns off LED 2. 
      delay();
      GPIODATA_N = 0x2; // Turns off LED 1. 
      delay();
      GPIODATA_N = 0x0; // Turns off all LEDS. 
      delay(); 
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
   


