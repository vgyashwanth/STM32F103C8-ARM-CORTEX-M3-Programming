#ifndef GPIO_drivers
#define GPIO_drivers  // used to include this header file only one time
#include<stdint.h>
//FOR ENABILING THE CLOCK TO THE BUS
#define RCC_APB2_ENR (*((volatile uint32_t * )(0x40021000+0x18)))

// BASE ADDRESS OF THE PORTS
#define GPIOA  (*((volatile uint32_t * )(0x40010800)))
#define GPIOB  (*((volatile uint32_t * )(0x40010C00)))
#define GPIOC  (*((volatile uint32_t * )(0x40011000)))

//USER DEFINED PORT NAMES

#define PORTA 1
#define PORTB 2
#define PORTC 3

//INPUT AND OUTPUT MODES

#define INPUT 0
#define OUT10 1
#define OUT2  2
#define OUT50 3

// FUNCTIONALITY OF THE PORT DURING INPUT TIME

#define I_ANALOG 0
#define I_FLOAT  1
#define I_PU_PD  2

// FUNCTIONALITY OF THE PORT DURING OUTPUT TIME

#define O_GEN_PUS_PL 0
#define O_GEN_OD    1
#define O_ALT_PUS_PL 2
#define O_ALT_OD    3

// LOGIC LEVELS

#define HIGH 1
#define LOW  0 

// FUNCTION DECLARATIONS

//used to configure the GPIO
void GPIO_Configuration(uint8_t port,uint8_t pin_no, uint8_t dir,uint8_t fun);

//used to write the logic levels to GPIO
void digitalWrite(uint8_t port,uint8_t pin,uint8_t logic_level);

//used to write the logic levels from GPIO
uint8_t digitalRead(uint8_t port,uint8_t pin);

// toggling the function

void Toogle_Pin(uint8_t port, uint8_t pin);


#endif
