/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 2/3/23
 * This program is the header file that contains the register definitions 
 * needed to configure for their respective ports, timers and interrupts for Lab 2, Task 2b. 
 */

#ifndef LAB2TASK2BH_ 
#define LAB2TASK2B_H_ 
 
// To set up and change the data for the GPIO registers needed in order to use the
// LEDS and switches on the TIVA LaunchPad. 
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) // LEDS
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC))
#define GPIODEN_J    (*((volatile uint32_t *)0x4006051C)) // Switches
#define GPIODATA_J   (*((volatile uint32_t *)0x400603FC)) 
#define GPIODIR_J    (*((volatile uint32_t *)0x40060400)) 
#define GPIOLOCK_J   (*((volatile uint32_t *)0x40060520))
#define GPIOCR_J     (*((volatile uint32_t *)0x40060524))
#define GPIOPUR_J    (*((volatile uint32_t *)0x40060510))

// To set up and change the data for the GPIO registers needed in order to use the
// switches interrupts on the TIVA LaunchPad. 
#define GPIOIS_J     (*((volatile uint32_t *)0x40060404)) 
#define GPIOIBE_J    (*((volatile uint32_t *)0x40060408))
#define GPIOIEV_J    (*((volatile uint32_t *)0x4006040C))
#define GPIOICR_J    (*((volatile uint32_t *)0x4006041C))
#define GPIOIM_J     (*((volatile uint32_t *)0x40060410))

// To set up and change the data for the timers needed in order to use the
// LEDS on the TIVA LaunchPad. 
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0    (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0    (*((volatile uint32_t *)0x40030000)) 
#define GPTMTAMR_0   (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0  (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0    (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0    (*((volatile uint32_t *)0x40030024))

// To set up and configure our Timers and switches on the TIVA 
// LaunchPad with our interrupts. 
#define GPTMIMR_0    (*((volatile uint32_t *)0x40030018)) 
#define NVIC_EN0     (*((volatile uint32_t *)0xE000E100)) 
#define NVIC_EN1     (*((volatile uint32_t *)0xE000E104)) 

// Sets up the LEDS and switches. 
void GPIO_init();

// Sets up Timer 0
void Timer_init();

// ISR for Timer 0 in implementing the turning on/off of LEDs in a sequential pattern.
void Timer0A_Handler(); 

// ISR for Port J in for using the switches to change LED behavior. 
void PortJ_Handler();

#endif 
