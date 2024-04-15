/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 1/21/23
 * This program is the header file that contains the register definitions 
 * needed to configure & their respective ports, for Lab 1, Task 1a. 
 */

#ifndef LAB2TASK1A_H_ 
#define LAB2TASK1A_H_ 
 
// To set up and change the data for the GPIO registers needed in order to use the
// LEDS on the TIVA LaunchPad. 
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0    (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0    (*((volatile uint32_t *)0x40000000))
#define GPTMTAMR_0   (*((volatile uint32_t *)0x40030004))
#define GPTMAILR_0   (*((volatile uint32_t *)0x40030004))
#define GPTMRIS_0    (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0    (*((volatile uint32_t *)0x40030024))
#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400)) 
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C)) 
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC)) 
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC)) 

// Sets up the LEDS
void GPIO_init();

#endif 