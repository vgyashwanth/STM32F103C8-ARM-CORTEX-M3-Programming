#include"Timers_drivers.h"
#include"Interrupts_drivers.h"
#include"core_cm3.h" //must and should when we are using interrupt and included in the same c file not in other file and at last for safer side

/********************Assumed clock frequency is 72Mhz*********************************/

void _delay(void){

	SysTick->LOAD = 72464-1; // one time load	for 1 milli second delay 
	SysTick->VAL = 0x00; //clear the counter flag
	SysTick->CTRL |= (1U<<2)|(1U<<0); //start the timer with processor clock	
	while((SysTick->CTRL&1U<<16 )==0);
	
}
void Systick_Delay_ms(uint32_t time_ms){
		 
			for(int i=0;i<time_ms;i++){
				_delay();
			
			}
		
}

void Systick_Interrupt_100ms(void){
		__disable_irq();
	
			SysTick->LOAD = 7246400-1; // one time load	for 100 milli second delay
			
			SysTick->VAL = 0x00; //clear the counter flag
			SysTick->CTRL |= (1U<<2)|(1U<<0)|(1U<<1); //start the timer with processor clock	with interrupt
	
	  __enable_irq();

}

timers_block* get_timer_base_address(uint8_t timer_no){

				timers_block* tim = 0x00;
	switch(timer_no){
	
		case TIM1: tim = TIMER1;
						
							 RCC_APB2_ENR |=(1U<<11); // for enabling clock to timer1 block	
								break;
		case TIM2: tim = TIMER2;
								RCC_APB1_ENR |=(1U<<0); // for enabling clock to timer2 block
								break;
		case TIM3: tim = TIMER3;
								RCC_APB1_ENR |=(1U<<1); // for enabling clock to timer3 block
								break;
		case TIM4: tim = TIMER4;
							  RCC_APB1_ENR |=(1U<<3); // for enabling clock to timer4 block
	}
		return tim;
	
}






void Enable_Timer_Interrupt(uint8_t timer_no,uint32_t time_ms){

	
		timers_block * tim = get_timer_base_address(timer_no);
		tim->TIM_PSC = (72)*1000;
		tim->TIM_ARR = (time_ms-1);
		tim->TIM_CNT = 0X0000;
	  tim->TIM_DIER |=0X0001; // Update interrupt enable
		__disable_irq();
		switch(timer_no){
			case TIM1: NVIC_EnableIRQ(TIM1_UP_IRQn);
									break;
			case TIM2: NVIC_EnableIRQ(TIM2_IRQn);
									break;
			case TIM3: NVIC_EnableIRQ(TIM3_IRQn);
									break;
			case TIM4: NVIC_EnableIRQ(TIM4_IRQn);
									break;
		}
	
	  __enable_irq();
}

void Start_Timer(uint8_t timer_no){

			timers_block* tim = get_timer_base_address(timer_no);
	    tim->TIM_CR1 |=(1U<<7)|(1U<<0);  //enabling the timer 

}
void Stop_Timer(uint8_t timer_no){

	    timers_block* tim = get_timer_base_address(timer_no);
	    tim->TIM_CR1 &=~((1U<<7)|(1U<<0));  //clear the bits of the timer

}
void Clear_Timer_Interrupt_Pen_bit(uint8_t timer_no){
	timers_block* tim = get_timer_base_address(timer_no);
	tim->TIM_SR &= ~(0x0001);
}
void Enable_Timer_Output_Compare_Toggle(uint8_t timer_no,uint8_t channel, uint16_t time_ms){
				//enable the clock for AFIO Block WHEN GPIO IS USED FOR ANY ALTERNATE FUNCTION
	  RCC_APB2_ENR |=(1<<0); //because all ports connected to APB2 BUS
			// set the mode
		timers_block* tim = get_timer_base_address(timer_no);
			//Initilizing the Timer
		tim->TIM_PSC = (72-1); //prescaler value to convert  72Mhz to 1Mhz 
		tim->TIM_CNT = 0;
		tim->TIM_ARR = 50000; //0.5sec we can change the value max = 65535 microseconds because of 16 bit
	
		switch(channel){
			// for setting the toggling mode and enable the channel
			case CH1: tim->TIM_CCMR1 |= 0x0030;  //toggle mode
								tim->TIM_CCER  |=(0x01<<0); //activate the channel
								tim->TIM_CCR1  = (time_ms);
								break;
			case CH2: tim->TIM_CCMR1 |= 0x3000;
								tim->TIM_CCER  |= (0x01<<4);
		          	tim->TIM_CCR2  = (time_ms);
								break;
			case CH3: tim->TIM_CCMR2 |= 0x0030;
								tim->TIM_CCER  |= (0x01<<8);
			          tim->TIM_CCR3  = (time_ms);
			case CH4: tim->TIM_CCMR2 |= 0X3000;
								tim->TIM_CCER  |= (0x01<<12);
		          	tim->TIM_CCR4  = (time_ms);
			 
		}
			// for connecting output pins with channels
				tim->TIM_BDTR |=0x8000; //connect the channel
		



}



 



