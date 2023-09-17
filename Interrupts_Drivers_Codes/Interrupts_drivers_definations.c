#include"Interrupts_drivers.h"
#include"Gpio_drivers.h"
#include"core_cm3.h" // must and should for interrupts
void Configure_GPIO_to_Interrupt_pin(uint8_t port,uint8_t pin,Trigger_edge_type edge){
	//enable the clock for AFIO Block
	RCC_APB2_ENR |=(1<<0);
		// for PORTA
		if(PORTA==port){
		
		switch(pin){
		
		
			case 0: AFIO_EXTICR1 |=EXTI_PA0; // Configure the corrsponding pin of the corrsponding port as interrupt pin
			 break;
			case 1: AFIO_EXTICR1 |=EXTI_PA1;
				break;
			case 2: AFIO_EXTICR1 |=EXTI_PA2;
				break;
			case 3: AFIO_EXTICR1 |=EXTI_PA3;
				break;
			case 4: AFIO_EXTICR2 |=EXTI_PA4;
				break;
			case 5: AFIO_EXTICR2 |=EXTI_PA5;
				break;
			case 6: AFIO_EXTICR2 |=EXTI_PA6;
				break;
			case 7: AFIO_EXTICR2 |=EXTI_PA7;
				break;
			case 8: AFIO_EXTICR3 |=EXTI_PA8;
				break;
			case 9: AFIO_EXTICR3 |=EXTI_PA9;
				break;
			case 10: AFIO_EXTICR3 |=EXTI_PA10;
				break;
			case 11: AFIO_EXTICR3 |=EXTI_PA11;
				break;
			case 12: AFIO_EXTICR4 |=EXTI_PA12;
				break;
			case 13: AFIO_EXTICR4 |=EXTI_PA13;
				break;
			case 14: AFIO_EXTICR4 |=EXTI_PA14;
				break;
			case 15: AFIO_EXTICR4 |=EXTI_PA15;
				break;
		}
		
		}
		
		if(PORTB==port){
		
		switch(pin){
		
		
			case 0: AFIO_EXTICR1 |=EXTI_PB0; // Configure the corrsponding pin of the corrsponding port as interrupt pin
			 break;
			case 1: AFIO_EXTICR1 |=EXTI_PB1;
				break;
			case 2: AFIO_EXTICR1 |=EXTI_PB2;
				break;
			case 3: AFIO_EXTICR1 |=EXTI_PB3;
				break;
			case 4: AFIO_EXTICR2 |=EXTI_PB4;
				break;
			case 5: AFIO_EXTICR2 |=EXTI_PB5;
				break;
			case 6: AFIO_EXTICR2 |=EXTI_PB6;
				break;
			case 7: AFIO_EXTICR2 |=EXTI_PB7;
				break;
			case 8: AFIO_EXTICR3 |=EXTI_PB8;
				break;
			case 9: AFIO_EXTICR3 |=EXTI_PB9;
				break;
			case 10: AFIO_EXTICR3 |=EXTI_PB10;
				break;
			case 11: AFIO_EXTICR3 |=EXTI_PB11;
				break;
			case 12: AFIO_EXTICR4 |=EXTI_PB12;
				break;
			case 13: AFIO_EXTICR4 |=EXTI_PB13;
				break;
			case 14: AFIO_EXTICR4 |=EXTI_PB14;
				break;
			case 15: AFIO_EXTICR4 |=EXTI_PB15;
				break;
		}
		
		}
		
		if(PORTC==port){
		
		switch(pin){
		
		
			case 0: AFIO_EXTICR1 |=EXTI_PC0; // Configure the corrsponding pin of the corrsponding port as interrupt pin
			 break;
			case 1: AFIO_EXTICR1 |=EXTI_PC1;
				break;
			case 2: AFIO_EXTICR1 |=EXTI_PC2;
				break;
			case 3: AFIO_EXTICR1 |=EXTI_PC3;
				break;
			case 4: AFIO_EXTICR2 |=EXTI_PC4;
				break;
			case 5: AFIO_EXTICR2 |=EXTI_PC5;
				break;
			case 6: AFIO_EXTICR2 |=EXTI_PC6;
				break;
			case 7: AFIO_EXTICR2 |=EXTI_PC7;
				break;
			case 8: AFIO_EXTICR3 |=EXTI_PC8;
				break;
			case 9: AFIO_EXTICR3 |=EXTI_PC9;
				break;
			case 10: AFIO_EXTICR3 |=EXTI_PC10;
				break;
			case 11: AFIO_EXTICR3 |=EXTI_PC11;
				break;
			case 12: AFIO_EXTICR4 |=EXTI_PC12;
				break;
			case 13: AFIO_EXTICR4 |=EXTI_PC13;
				break;
			case 14: AFIO_EXTICR4 |=EXTI_PC14;
				break;
			case 15: AFIO_EXTICR4 |=EXTI_PC15;
				break;
		}
		
		}
		// FOR SETTING THE EDGE OF THE INTERRUPT
		if(FALLING==edge)
			EXTI_FTSR |= (1<<pin);
		
		else if(RISING==edge)
			EXTI_RTSR |= (1<<pin);
		
		else if(RISING_FALLING==edge){
				EXTI_FTSR |= (1<<pin);
				EXTI_RTSR |= (1<<pin);
			
		}

return ;

}

void Reset_Interrupt_pen_bit(uint8_t pin){
		EXTI_PENR |= (1<<pin);
}

void Reset_Interrupt_to_GPIO_pin(uint8_t pin){

					switch(pin){
		
		
			case 0: AFIO_EXTICR1 &=RES_INT_GPIO_0; //RESET THE PIN INTO NORMAL GPIO IRRESPECTIVE OF PORT
			 break;
			case 1: AFIO_EXTICR1 &=RES_INT_GPIO_1;
				break;
			case 2: AFIO_EXTICR1 &=RES_INT_GPIO_2;
				break;
			case 3: AFIO_EXTICR1 &=RES_INT_GPIO_3;
				break;
			case 4: AFIO_EXTICR2 &=RES_INT_GPIO_4;
				break;
			case 5: AFIO_EXTICR2 &=RES_INT_GPIO_5;
				break;
			case 6: AFIO_EXTICR2 &=RES_INT_GPIO_6;
				break;
			case 7: AFIO_EXTICR2 &=RES_INT_GPIO_7;
				break;
			case 8: AFIO_EXTICR3 &=RES_INT_GPIO_8;
				break;
			case 9: AFIO_EXTICR3 &=RES_INT_GPIO_9;
				break;
			case 10: AFIO_EXTICR3 &=RES_INT_GPIO_10;
				break;
			case 11: AFIO_EXTICR3 &=RES_INT_GPIO_11;
				break;
			case 12: AFIO_EXTICR4 &=RES_INT_GPIO_12;
				break;
			case 13: AFIO_EXTICR4 &=RES_INT_GPIO_13;
				break;
			case 14: AFIO_EXTICR4 &=RES_INT_GPIO_14;
				break;
			case 15: AFIO_EXTICR4 &=RES_INT_GPIO_15;
				break;
		}

		Reset_Interrupt_pen_bit(pin); // clear the pending bit
		EXTI_IMR &= ~(1<<pin); //clear the mask

}
void Enable_Interrupt(uint8_t pin,IRQn_Type IRQ_number){

		//disable the max
		EXTI_IMR |= (1<<pin);
		NVIC_EnableIRQ(IRQ_number); // defination in core_cm3.h for enabling in NVIC Hardware

}
