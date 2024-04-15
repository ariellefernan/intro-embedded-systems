/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 1/21/23
 * This program is the header file that contains the register definitions 
 * needed to configure for their respective ports, timers and interrupts for Lab 2, Task 2a. 
 */

#ifndef LAB2TASK2A_H_ 
#define LAB2TASK2A_H_ 
 
// To set up and change the data for the GPIO registers needed in order to use the
// LEDS on the TIVA LaunchPad. 
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0    (*((volatile uint32_t *)0x4003000C)) // Timer 0A
#define GPTMCFG_0    (*((volatile uint32_t *)0x40030000)) 
#define GPTMTAMR_0   (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0  (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0    (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0    (*((volatile uint32_t *)0x40030024))

// To set up and configure our Timers with our interrupts. 
#define GPTMIMR_0    (*((volatile uint32_t *)0x40030018)) 
#define NVIC_EN0     (*((volatile uint32_t *)0xE000E100)) 

// To set up and change the data for the GPIO registers needed in order to use external 
// LEDS and switches connected to our TIVA Launchpad.
#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400)) // 
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C)) 
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC)) 
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC)) 

// Turns on and off LEDs in a sequential pattern. 
void TickFct_Pattern(int counter); 

// Sets up the LEDs 
void GPIO_init();

// Sets up Timer 0
void Timer_init();

// ISR for Timer 0 in implementing the turning on/off of LEDs in a sequential pattern.
void Timer0A_Handler();

#endif 