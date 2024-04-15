/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 1/21/23
 * This program is the header file that contains the register definitions 
 * needed to configure & their respective ports, for Lab 1, Task 1a. 
 */

#ifndef LAB1_H_ 
#define LAB1_H_ 
 
// To set up and change the data for the GPIO registers needed in order to use the
// LEDS on the TIVA LaunchPad. 
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400)) 
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C)) 
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC)) 
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC)) 

// Sets up the LEDS
void GPIO_init();

#endif 


 