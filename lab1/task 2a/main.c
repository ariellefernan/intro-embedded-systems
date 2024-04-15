/*
 *Arielle Fernandez
 *Student ID: 1924587
 *Date: 1/20/23
 * This program implements Task 2 of Lab 1 for a Traffic Light System. 
 * The system alternates between STOP, GO and WARN states when the system is on. 
 */ 

#include <stdint.h> 
#include "lab1.h" 

enum TrafficLight_States {TL_OFF, TL_STOP, TL_GO, TL_WARN} TrafficLightState; 

// Creates approximately a 0.3 second delay when changing in between LEDS. 
void delay() {
     for (int j = 0; j < 1000000; j++) { 
     } 
}

int main(void) { 
  GPIO_init(); 
  while (1) {
    TickFct_TrafficLight();  
  }
  return 0; 
}

void GPIO_init(void) 
{ 
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x0400; // Activate clock for Port L 
    delay++;                       
    delay++;
    GPIOAMSEL_L &= ~0x1F; // Disable analog function of PL0, PL1, PL2, PL3 & PL4  
    GPIODIR_L |= 0x1C; // Set PL2, PL3 & PL4 to output 
    GPIODIR_L &= ~0x3; // Set PL0 & PL1 to input 
    GPIOAFSEL_L &= ~0x1F; // Set PL0, PL1, PL2, PL3 & PL4 to regular port function 
    GPIODEN_L |= 0x1F; // Enable digital functions on PL0, PL1, PL2, PL3 & PL4 
    
} 
 
void REDLED_on(void) 
{ 
    GPIODATA_L |= 0x04; 
} 
 
void REDLED_off(void) 
{ 
    GPIODATA_L &= ~0x04; 
} 
void GREENLED_on(void) 
{ 
    GPIODATA_L |= 0x10; 
} 
 
void GREENLED_off(void) 
{ 
    GPIODATA_L &= ~0x10; 
} 

void YELLOWLED_on(void) 
{ 
    GPIODATA_L |= 0x08; 
} 
 
void YELLOWLED_off(void) 
{ 
    GPIODATA_L &= ~0x08; 
} 


unsigned long systemSwitch_input() 
{ 
  return (GPIODATA_L & 0x1); // 0x1 (pressed) or 0 (not pressed) 
} 

unsigned long pedestrianSwitch_input() 
{ 
  return (GPIODATA_L & 0x2); // 0x2 (pressed) or 0 (not pressed) 
} 

void TickFct_TrafficLight() { // OX1 = system button, 0x2 = pedestrian button 

  switch(TrafficLightState) { // State transitions
    case TL_OFF: // Initial transition 
       if (systemSwitch_input()) { 
         TrafficLightState = TL_GO; 
       } else {
         TrafficLightState = TL_OFF;  
       }             
    break; 
                   
    case TL_STOP: 
      if (systemSwitch_input()) { 
        TrafficLightState = TL_OFF;
      } 
      else {
        TrafficLightState = TL_GO; 
      }
    break; 
                            
    case TL_GO: 
      if (systemSwitch_input()) { 
        TrafficLightState = TL_OFF; 
      } 
      else if (pedestrianSwitch_input()) { 
        TrafficLightState = TL_WARN;
      } else { 
        TrafficLightState = TL_STOP;
      } 
    break;
    
    case TL_WARN: 
      if (systemSwitch_input()) { 
        TrafficLightState = TL_OFF;
      } else { 
        TrafficLightState = TL_STOP;
      } 
    break;       
  } 
  
  switch(TrafficLightState) { // State actions
   
    case TL_OFF: 
      REDLED_off(); 
      YELLOWLED_off();
      GREENLED_off(); 
      break;
       
    case TL_STOP: 
       REDLED_on(); 
       YELLOWLED_off();
       GREENLED_off();
       break;
       
    case TL_WARN:
       REDLED_off(); 
       YELLOWLED_on();
       GREENLED_off();
       break;   
         
     case TL_GO: 
       REDLED_off(); 
       YELLOWLED_off();
       GREENLED_on();
       break; 
  } 
  delay();
}

