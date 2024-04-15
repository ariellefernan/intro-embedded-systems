/*
 * Arielle Fernandez
 *Student ID: 1924587
 *Date: 1/21/23
 * This program is the header file that contains the register definitions 
 * needed to configure & their respective ports/pins, for Lab 1, Task 2. 
 */

#ifndef LAB1_H
#define LAB1_H

// To set up and change the data for the GPIO registers needed in order to use external 
// LEDS and switches connected to our TIVA Launchpad.
#define RCGCGPIO         (*((volatile uint32_t *)0x400FE608)) 
#define GPIOAMSEL_L      (*((volatile uint32_t *)0x40062528)) 
#define GPIODIR_L        (*((volatile uint32_t *)0x40062400)) 
#define GPIODEN_L        (*((volatile uint32_t *)0x4006251C)) 
#define GPIOAFSEL_L      (*((volatile uint32_t *)0x40062420)) 
#define GPIODATA_L       (*((volatile uint32_t *)0x400623FC))

// Sets up the external LEDS and switches
void GPIO_init();

// Turns on Red LED
void REDLED_on(void); 

// Turns off Red LED
void REDLED_off(void);

// Turns on Green LED
void GREENLED_on(void);

// Turns off Green LED
void GREENLED_off(void);

// Turns on Yellow LED
void YELLOWLED_on(void);

// Turns off Yellow LED 
void YELLOWLED_off(void);

// Returns if the button for turning the system on is pressed, or not.
unsigned long systemSwitch_input(void);

// Returns if the button for signaling when a pedestrian is crossing, is pressed, or not.
unsigned long pedestrianSwitch_input(void);

// Tick function that contains the state actions and transitions for 
// Traffic Light System  FSM design. 
void TickFct_TrafficLight();

#endif 
