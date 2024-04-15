/* 
 * Arielle Fernandez
 * Student ID: 1924587 
 * Date: 2/3/23
 * This program is the header file that contains the register definitions 
 * needed to configure for their respective ports and timers, for Lab 2, Task 1b. 
 */

#ifndef LAB2TASK1B_H
#define LAB2TASK1B_H

// To set up, use and change the data for Timers 0, 1 & 2 for turning on/off LEDs 
// at a rate of 2 seconds, 2 seconds and 5 seconds, respectively.
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0    (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0    (*((volatile uint32_t *)0x40030000)) 
#define GPTMTAMR_0   (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0  (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0    (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0    (*((volatile uint32_t *)0x40030024))
#define GPTMCTL_1    (*((volatile uint32_t *)0x4003100C)) 
#define GPTMCFG_1    (*((volatile uint32_t *)0x40031000)) 
#define GPTMTAMR_1   (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_1  (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_1    (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_1    (*((volatile uint32_t *)0x40031024))
#define GPTMCTL_2    (*((volatile uint32_t *)0x4003200C)) 
#define GPTMCFG_2    (*((volatile uint32_t *)0x40032000)) 
#define GPTMTAMR_2   (*((volatile uint32_t *)0x40032004))
#define GPTMTAILR_2  (*((volatile uint32_t *)0x40032028))
#define GPTMRIS_2    (*((volatile uint32_t *)0x4003201C))
#define GPTMICR_2    (*((volatile uint32_t *)0x40032024)) 

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

void Timer_init();

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

// Handler function that completes tasks for our FSM, based on if the 
// power button was pressed, or not & if its timer finished. 
void powerButtonHandler();

// Handler function that completes tasks for our FSM, based on if the 
// pedestriation button was pressed, or not & if its timer finished. 
void pedestrianButtonHandler();

#endif 