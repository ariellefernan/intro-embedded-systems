/*
 *Arielle Fernandez
 *Student ID: 1924587
 *Date: 2/3/23
 * This program implements Task 2c of Lab 2 for a Traffic Light System. 
 * The system alternates between STOP, GO and WARN states when the system is on. 
 */ 

#include <stdint.h> 
#include "lab2task2c.h" 

enum TrafficLight_States {TL_OFF, TL_STOP, TL_GO, TL_WARN} TrafficLightState; 

int main(void) { 
  GPIO_init();   
  Timer_init(); 
  while (1) { 

  }
  return 0; 
}

void GPIO_init(void) { 
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x0400; // Activate clock for Port L 
    delay++;                     
    delay++;
    GPIOAMSEL_L &= ~0x1F; // Disable analog function of PL0, PL1, PL2, PL3 & PL4  
    GPIODIR_L |= 0x1C; // Set PL2, PL3 & PL4 to output 
    GPIODIR_L &= ~0x3; // Set PL0 & PL1 to input 
    GPIOAFSEL_L &= ~0x1F; // Set PL0, PL1, PL2, PL3 & PL4 to regular port function 
    GPIODEN_L |= 0x1F; // Enable digital functions on PL0, PL1, PL2, PL3 & PL4
    
    GPIOIS_L &= ~0x3; // Settings for switches interrupts 
    GPIOIBE_L &= ~0x3;
    GPIOIEV_L &= ~0x3; 
    GPIOICR_L |= 0x3;
    GPIOIM_L |= 0x3;
    
    NVIC_EN1 |= 0x200000; // Enable switches interrupt  
} 

void Timer_init() { 
  volatile unsigned short delay = 0; 
  RCGCTIMER |= 0x7; 
  delay++; 
  delay++;
  GPTMCTL_0 |= 0x0; // Disable Timer 0 
  GPTMCFG_0 = 0x0; // select 32 bit mode. 
  GPTMTAMR_0 |= 0x1; // one shot mode 
  GPTMTAMR_0 &= ~0x10;  // count down
  GPTMTAILR_0 = 0x1E84800; // 2 second timer for system on/off button 
  GPTMIMR_0 |= 0x1;
  NVIC_EN0 |= 0xA80000; // Enable timers interrupt 
  GPTMCTL_0 |= 0x1;
  
  GPTMCTL_1 |= 0x0; // Disable Timer 1 
  GPTMCFG_1 = 0x0; // select 32 bit mode. 
  GPTMTAMR_1 |= 0x1; // one shot mode 
  GPTMTAMR_1 &= ~0x10; 
  GPTMTAILR_1 = 0x1E84800; // 2 second timer for pedestrian button 
  GPTMIMR_1 |= 0x1;
  GPTMCTL_1 |= 0x1; 
  
  GPTMCTL_2 |= 0x0; // Disable Timer 2 
  GPTMCFG_2 = 0x0; // select 32 bit mode. 
  GPTMTAMR_2 |= 0x2; // periodic mode 
  GPTMTAMR_2 &= ~0x10; // count down
  GPTMTAILR_2 = 0x4C4B400; // 5 second timer for pedestrian button 
  GPTMIMR_2 |= 0x1;
  GPTMCTL_2 |= 0x1; 
  
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

void TickFct_TrafficLight(int powerButton, int pedestrianButton) { // OX1 = system button, 0x2 = pedestrian button 

  switch(TrafficLightState) { // State transitions
    case TL_OFF: // Initial transition
       if (powerButton == 1) { 
            TrafficLightState = TL_STOP; 
       } else { 
         TrafficLightState = TL_OFF; 
       } 
    break; 
                   
    case TL_STOP: 
      if (powerButton == 1) { 
        TrafficLightState = TL_OFF; 
      } 
      else {
        TrafficLightState = TL_GO; 
      }
    break; 
                            
    case TL_GO: 
      if (powerButton == 1) { 
        TrafficLightState = TL_OFF; 
      } 
      else if (pedestrianButton == 1) { 
        TrafficLightState = TL_WARN;
      } else { 
        TrafficLightState = TL_STOP; 
      } 
    break;
    
    case TL_WARN: 
      if (powerButton == 1) { 
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

}

void Timer0A_Handler() { // 2 second timer for power on/off system 
      GPTMICR_0 |= 0x1; // clear flag 
      GPTMCTL_0 &= ~0x1; // Disable Timer 0,
      GPTMCTL_2 &= ~0x1; // Disable Timer 2, disable 5 second timer   
      GPTMTAILR_2 = 0x4C4B400; // reload 5 second timer 
      GPTMCTL_2 |= 0x1; // re-enable 5 second timer 
      TickFct_TrafficLight(1, 0); //  
      GPTMTAILR_0 = 0x1E84800; // reload 2 second timer for system on/off button  
} 

void Timer1A_Handler() { // 2 second timer for pedestrian system 
      GPTMICR_1 |= 0x1; // clear flag 
      GPTMCTL_1 &= ~0x1; // Disable Timer 1
      GPTMCTL_2 &= ~0x1; // Disable Timer 2, disable 5 second timer   
      GPTMTAILR_2 = 0x4C4B400; // reload 5 second timer 
      GPTMCTL_2 |= 0x1; // re-enable 5 second timer 
      TickFct_TrafficLight(0, 1); 
      GPTMTAILR_1 = 0x1E84800; // 2 second timer for pedestrian button 
}

void Timer2A_Handler() { // 5 second timer delay in between LEDs 
   GPTMICR_2 |= 0x1; // clear flag 
   TickFct_TrafficLight(0, 0);
}

void PortL_Handler() { 
  if (systemSwitch_input()) { // If button was pressed, start timer 
     GPTMCTL_0 |= 0x1; // Enable timer
     GPIOICR_L |= 0x1; 
  } else if (!systemSwitch_input() && !((GPTMRIS_0 & 0x1) == 1)){ // if button is released before timer is finished, reset timer 
      GPTMCTL_0 &= ~0x1; // Disable
      GPTMTAILR_0 = 0x1E84800; // Reload
      GPTMCTL_0 |= 0x1; // Enable timer
      GPIOICR_L |= 0x1;
  } else if (pedestrianSwitch_input()){ 
      GPTMCTL_1 |= 0x1;  
      GPIOICR_L |= 0x2;
  } else if (!pedestrianSwitch_input() && !((GPTMRIS_1 & 0x1) == 1)){ 
      GPTMCTL_1 &= ~0x1; // Reset timer 
      GPTMTAILR_1 = 0x1E84800; 
      GPTMCTL_1 |= 0x1; // Enable timer
      GPIOICR_L |= 0x2;
  }  else { 
    GPIOICR_L |= 0x3; 
  } 
} 