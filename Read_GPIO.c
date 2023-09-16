#include<stdint.h>
//#include<stm32f10x.h>
//acessing the register address using pointers
#define APB2ENR (*((volatile uint32_t*)(0x40021000+0x18)))
#define GPIOB_CRH (*((volatile uint32_t*)(0x40010C00+0x04)))
#define GPIOB_BSRR (*((volatile uint32_t*)(0x40010C00+0x10)))
#define GPIOB_READ (*((volatile uint32_t*)(0x40010C00+0x08)))
//delay function	
void delay(int x){
for(int i=0;i<x;i++)
	for(int j=0;j<20000;j++);
}

int main(){
	// enable clock for port b
	APB2ENR |=(1<<3);
	//configure GPIOB 13 as output and GPIOB 12 as input
	GPIOB_CRH &=0x44004444;
	GPIOB_CRH |=0x44384444;

		while(1){
			//monitoring the status
				uint8_t status = GPIOB_READ&(1<<12);
		
				if(0==status)
					GPIOB_BSRR |=(1<<13);
				else{
					
					GPIOB_BSRR &= ~(1<<13);
					GPIOB_BSRR |= 1<<(13+16);

				}
			
		}
	
return 0;
}
