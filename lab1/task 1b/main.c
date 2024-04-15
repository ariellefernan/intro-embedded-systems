/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 1/21/23
 * This program implements Task 1b of Lab 1. Whenever a switch is pressed 
 * on the TIVA Launchpad, it's respective LED turns on, and when it's not pressed, 
 * it turns off.
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
     if ((GPIODATA_J & 0X2) == 0) { // If Switch 2 (SW2) pressed, LED 2 (D2) is on. 
        GPIODATA_N |= 0x1; 
      } else { // Otherwise, LED 2 is off. 
        GPIODATA_N &= ~0x1; 
      }   
     if ((GPIODATA_J & 0x1) == 0) { // If Switch 1 (SW1) is pressed, LED 1 (D1) is on.
        GPIODATA_N |= 0x2; 
     } else { // Otherwise, LED 1 is off. 
       GPIODATA_N &= ~0x2; 
     }
   }  
    return 0; 
} 

void GPIO_init() {
  volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x1120;  // Enable PortJ GPIO 
    delay++;           // Delay 2 more cycles before accessing  Timer registers 
    delay++;           
    GPIODIR_N = 0x3;   // Set PN0 and PN1 to output (LEDS 1 & 2)
    GPIODEN_N = 0x3;   // Set PN0 and PN1 to digital port 
    GPIODIR_J = 0x0; // Set PJ1 and PJ0 to input. (Switches (SW) 1 & 2)
    GPIODEN_J = 0X3;  // Set PJ0 and PJ1 to digital port
    GPIOLOCK_J = 0x3; // Sets PJ0 and PJ1 to be locked. 
    GPIOCR_J = 0x3; // Set PJ0 and PJ1 to allow other registers to be written.
    GPIOPUR_J = 0x3; // Sets PJO and PJ1 pull-up resistors to be enabled. 
}
