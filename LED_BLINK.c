#include<stdint.h>
//#include<stm32f10x.h>
//acessing the register address using pointers
#define APB2ENR (*((volatile uint32_t*)(0x40021000+0x18)))
#define GPIOB_CRH (*((volatile uint32_t*)(0x40010C00+0x04)))
#define GPIOB_BSRR (*((volatile uint32_t*)(0x40010C00+0x10)))
//delay function	
void delay(int x){
for(int i=0;i<x;i++)
	for(int j=0;j<20000;j++);
}

int main(){
	// enable clock for port b
	APB2ENR |=(1<<3);
	//configure the ports as output pushpull mode
	GPIOB_CRH &=0x44044444;
	GPIOB_CRH |=0x44344444;
  
		while(1){
			//SET THE BIT 
			GPIOB_BSRR |= (1<<13);
			delay(10);
			//RESET THE BIT
			GPIOB_BSRR &=(~(1<<13));
			GPIOB_BSRR |=1<<(13+16);
			delay(10);
		}
	
return 0;
}
