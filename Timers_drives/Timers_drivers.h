#ifndef Timers
#define Timers
#pragma(1) // for avoiding the structure padding
#include<stdint.h>
#include"Gpio_drivers.h" // for acessing the RCC_APB2_ENR register

// Addressing the Blocks
typedef struct{
	uint32_t TIM_CR1,
	         TIM_CR2,
					TIM_SMCR,
					TIM_DIER,
					TIM_SR,
					TIM_EGR,
					TIM_CCMR1,
					TIM_CCMR2,
					TIM_CCER,
					TIM_CNT,
					TIM_PSC,
					TIM_ARR,
					TIM_RCR,
					TIM_CCR1,
					TIM_CCR2,
					TIM_CCR3,
					TIM_CCR4,
	        TIM_BDTR,
	        TIM_DCR,
          TIM_DMAR;
	
}timers_block;

#define TIMER1 ((timers_block*)0x40012C00)
#define TIMER2 ((timers_block*)0X40000000)
#define TIMER3 ((timers_block*)0X40000400)
#define TIMER4 ((timers_block*)0X40000800)
// for using as a parameters for Timers in the function calls

#define TIM1 1
#define TIM2 2
#define TIM3 3
#define TIM4 4

// for using as a parameters for Timer channels in the function calls
#define CH1 1
#define CH2 2
#define CH3 3
#define CH4 4

/******SYSTICK TIMER********/
// Inbuilt timer inside the processor not microcontroller
typedef struct{
	uint32_t CTRL,
					LOAD,
					CUR,
					CAL;
					
}Systick_block;

#define SysTick (Systick_block*)0xE000E010; //refer the cortex m3 datasheet not reference manual it is fixed for the processor

// Timers and channel mapping
/*

PA0->TIM2_CH1
PA1->TIM2_CH2
PA2->TIM2_CH3
PA3->TIM2_CH4

PA6->TIM3_CH1
PA7->TIM3_CH2
PB0->TIM3_CH3
PB1->TIM3_CH4

PA8->TIM1_CH1
PA9->TIM1_CH2
PA10->TIM1_CH3
PA11->TIM1_CH4

*/
//Interrupt Handlers names
/*

void TIM1_UP_IRQHandler();
void TIM2_IRQHandler();
void TIM3_IRQHandler();
void TIM4_IRQHandler();

*/
//TIMERS FUNCTION DEFINATIONS
void Systick_Delay_ms(uint32_t time_ms);
void Systick_Interrupt_100ms(void);
void _delay(void); // not for user purpose
void Enable_Timer_Interrupt(uint8_t timer_no,uint32_t time_ms);
timers_block* get_timer_base_address(uint8_t timer_no);
void Start_Timer(uint8_t timer_no);
void Stop_Timer(uint8_t timer_no);
void Clear_Timer_Interrupt_Pen_bit(uint8_t timer_no);
void Enable_Timer_Output_Compare_Toggle(uint8_t timer_no,uint8_t channel, uint16_t time_ms);


#endif
