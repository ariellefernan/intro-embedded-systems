/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 1/21/23
 * This program implements Task 1b of Lab 1. Whenever a switch is pressed 
 * on the TIVA Launchpad, it's respective LED turns on, and when it's not pressed, 
 * it turns off.
 */

#include <stdint.h> 
#include "lab2task2b.h" 

// Toggle for blinking LED (turning on and off) 
int toggle = 0;

int main(void){ 
  GPIO_init(); 
  Timer_init(); 
   while (1) { 
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
    GPIODEN_J = 0x3;  // Set PJ0 and PJ1 to digital port
    GPIOLOCK_J = 0x3; // Sets PJ0 and PJ1 to be locked. 
    GPIOCR_J = 0x3; // Set PJ0 and PJ1 to allow other registers to be written.
    GPIOPUR_J = 0x3; // Sets PJO and PJ1 pull-up resistors to be enabled.    
    GPIOIS_J &= ~0x3; 
    GPIOIBE_J &= ~0x3;
    GPIOIEV_J &= ~0x3; 
    GPIOICR_J |= 0x3;
    GPIOIM_J |= 0x3;
    NVIC_EN1 |= 0x80000; // Configuring switches interrupt    
}

void Timer_init() { 
  volatile unsigned short delay = 0; 
  RCGCTIMER |= 0x1; 
  delay++;
  delay++;
  GPTMCTL_0 |= 0x0; // Disable Timer 0 
  GPTMCFG_0 = 0x0; // select 32 bit mode. 
  GPTMTAMR_0 |= 0x2; 
  GPTMTAMR_0 &= ~0x10; 
  GPTMTAILR_0 = 0xF42400;  // At a rate of 1 HZ 
  GPTMIMR_0 |= 0x1; 
  NVIC_EN0 |= 0x80000; // Enable Timer 0A interrupt 
  GPTMCTL_0 |= 0x1; // Enable Timer 0 
} 

void Timer0A_Handler() {
  GPTMICR_0 |= 0x1; // Clear flag  
  if (toggle % 2 == 1) { 
    GPIODATA_N |= 0x2; // Turn on LED
  } else {
    GPIODATA_N &= ~0x2; // Turn off LED
  }
  toggle++;     
} 

void PortJ_Handler() { 
  if ((GPIODATA_J & 0x2) == 0) { // If Switch 2 (SW2) pressed, LED 2 (D2) is on. 
     GPTMTAILR_0 = 0xF42400; // reload 1 second timer 
     GPTMCTL_0 |= 0x1; // re-enable timer 
     GPIODATA_N &= ~0x1; // LED 2 turns off 
  }  
   if ((GPIODATA_J & 0x1) == 0) { // If Switch 1 (SW1) is pressed, LED 2 (D2) is on. 
      GPIODATA_N |= 0x1; // LED 2 turns on
      GPIODATA_N &= ~0x2; // LED 1 turns off
      GPTMCTL_0 &= ~0x1; // Disable Timer 0  
   }  
} 