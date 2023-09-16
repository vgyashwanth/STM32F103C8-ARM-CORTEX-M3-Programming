#include"Gpio_drivers.h"

void GPIO_SET(uint8_t port,uint8_t pin_no, uint8_t dir,uint8_t fun){

	// used for storing the target register address
volatile uint32_t* t_reg;
	
	uint8_t t_pin = pin_no; // used for pin shifiting
	
	// offset for register shifiting
	uint8_t offset = 0x00;
	//when we are accesing the CRH register
	if(pin_no > 7){
		
		offset = 0x01;
		t_pin = t_pin-8;
	
	}
//ENABLING THE BUS CLOCK
		//acessing GPIOA
		if(1==port){
			RCC_APB2_ENR |=(1<<2);
			t_reg = &GPIOA + offset; // GPIOA base address + offset*(sizeof(uint32_t)) and store back into t_reg
		}
		//acessing GPIOB
		if(2==port){
			RCC_APB2_ENR |=(1<<3);
			t_reg = &GPIOB + offset;
		}
		//acessing GPIOC
		if(3==port){
			RCC_APB2_ENR |=(1<<4);
			t_reg = &GPIOC + offset;
		}
		
//SET THE DIRECTION AND MODE
	
		//first clear the region
		(*t_reg) &= ~(0xf<<(t_pin*4)); // each shift require the 4-bit shift
		//set the direction
		(*t_reg) |= dir<<(t_pin*4);
		//set the function
		(*t_reg) |= fun<<(t_pin*4+2);// +2 because we need that shift for storing the fun values in the exact position
	

}

void digitalWrite(uint8_t port, uint8_t pin, uint8_t logic_level){
		uint8_t offset = 0x03; // 3*sizoef(uint32_t)==C our requried offset is C 
		volatile uint32_t * reg;
		if(1==port)
			reg = &GPIOA + offset;
		if(2==port)
			reg = &GPIOB + offset;
		if(3==port)
			reg = &GPIOC + offset;
		// set the value in the register
		if(logic_level)
		(*reg)|=(1<<pin);
		else
		(*reg)&=~(1<<pin);
			

}
uint8_t digitalRead(uint8_t port,uint8_t pin){
	
		uint8_t offset = 0x02; // 2*sizoef(uint32_t)==0x08 our requried offset is 0x08 
		volatile uint32_t * reg;
		if(1==port)
			reg = &GPIOA + offset;
		if(2==port)
			reg = &GPIOB + offset;
		if(3==port)
			reg = &GPIOC + offset;
		return ( ( (*reg)&(1<<pin) ) >> pin);

}
