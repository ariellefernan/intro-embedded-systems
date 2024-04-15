#ifndef LAB1_H
#define LAB1_H

// To set up, use and change the data for Timers 0, 1 & 2 for turning on/off LEDs 
// at a rate of 2 seconds, 2 seconds and 5 seconds, respectively, alongside their interrupts.
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0    (*((volatile uint32_t *)0x4003000C)) 
#define GPTMCFG_0    (*((volatile uint32_t *)0x40030000)) 
#define GPTMTAMR_0   (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0  (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0    (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0    (*((volatile uint32_t *)0x40030024)) 
#define GPTMIMR_0    (*((volatile uint32_t *)0x40030018)) 
#define NVIC_EN0     (*((volatile uint32_t *)0xE000E100)) 
#define GPTMCTL_1    (*((volatile uint32_t *)0x4003100C)) 
#define GPTMCFG_1    (*((volatile uint32_t *)0x40031000)) 
#define GPTMTAMR_1   (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_1  (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_1    (*((volatile uint32_t *)0x4003101C)) 
#define GPTMICR_1    (*((volatile uint32_t *)0x40031024))
#define GPTMIMR_1    (*((volatile uint32_t *)0x40031018)) 
#define GPTMCTL_2    (*((volatile uint32_t *)0x4003200C)) 
#define GPTMCFG_2    (*((volatile uint32_t *)0x40032000)) 
#define GPTMTAMR_2   (*((volatile uint32_t *)0x40032004))
#define GPTMTAILR_2  (*((volatile uint32_t *)0x40032028))
#define GPTMRIS_2    (*((volatile uint32_t *)0x4003201C))
#define GPTMICR_2    (*((volatile uint32_t *)0x40032024)) 
#define GPTMIMR_2    (*((volatile uint32_t *)0x40032018)) 

// To set up and change the data for the GPIO registers needed in order to use external 
// LEDS and switches connected to our TIVA Launchpad.
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) // GPIO Ports (Switches and LEDS) 
#define GPIOAMSEL_L  (*((volatile uint32_t *)0x40062528)) 
#define GPIODIR_L    (*((volatile uint32_t *)0x40062400)) 
#define GPIODEN_L    (*((volatile uint32_t *)0x4006251C)) 
#define GPIOAFSEL_L  (*((volatile uint32_t *)0x40062420)) 
#define GPIODATA_L   (*((volatile uint32_t *)0x400623FC))
#define NVIC_EN1     (*((volatile uint32_t *)0xE000E104)) 

// To set up and configure the GPIO registers needed for using our interrupts with 
// the power and pedestrian buttons/switches. 
#define GPIOIS_L     (*((volatile uint32_t *)0x40062404))
#define GPIOIBE_L    (*((volatile uint32_t *)0x40062408))
#define GPIOIEV_L    (*((volatile uint32_t *)0x4006240C))
#define GPIOICR_L    (*((volatile uint32_t *)0x4006241C))
#define GPIOIM_L     (*((volatile uint32_t *)0x40062410))
 
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

// ISR for Timer 0 in keeping track of pressing the power button for 2 seconds. 
void Timer0A_Handler(); 

// ISR for Timer 1 in keeping track of pressing the pedestrian button for 2 seconds. 
void Timer1A_Handler();

// ISR for Timer 2 in keeping track of LEDs turning on & changing states with a 5 second delay.
void Timer2A_Handler(); 

// ISR for Port L that enables and disables the timers needed, whenever the
// power or pedestrian buttons were pressed, or not before or after the timers finished. 
void PortL_Handler();

#endif 