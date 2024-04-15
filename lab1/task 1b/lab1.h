/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 1/21/23
 * This program is the header file that contains the register definitions 
 * needed to configure & their respective ports, for Lab 1, Task 1b. 
 */

#ifndef LAB1_H_ 
#define LAB1_H_ 
 
// To set up and change the data for the GPIO registers needed in order to use the
// LEDS and switches on the TIVA LaunchPad. 
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC)) 
#define GPIODEN_J    (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J   (*((volatile uint32_t *)0x400603FC))
#define GPIODIR_J    (*((volatile uint32_t *)0x40060400)) 
#define GPIOLOCK_J   (*((volatile uint32_t *)0x40060520))
#define GPIOCR_J     (*((volatile uint32_t *)0x40060524))
#define GPIOPUR_J    (*((volatile uint32_t *)0x40060510)) 

// Sets up the LEDS and switches. 
void GPIO_init();

#endif 
