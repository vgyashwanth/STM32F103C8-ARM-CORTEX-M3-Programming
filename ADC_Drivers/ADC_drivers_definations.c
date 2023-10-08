#include"Timers_drivers.h"
#include"Gpio_drivers.h" //For enabling the clock to the buses
#include"DMA_drivers.h" //during scan mode for ADC
#include"ADC_drivers.h"
#include"stdlib.h" // for dynamic memory allocation

uint32_t answer=0; // for storing our result;
adc_block *ADC  = 0x00;  //for storing the address of selected ADC
uint8_t SQR_reg_pointer = 1; // keep a track on storing channels in SQR_register
uint8_t no_of_pins_left_to_assign = 0; //keep a track on no of pins yet to assign
uint8_t MAX = 0; // storing the max no of channels to assign
uint16_t * Arr = 0x00; //for storing the dynamic array Address
adc_block* get_adc(uint8_t adc_no){

				adc_block * t_ADC = 0X00;
		switch(adc_no){
			 // ENABLE clock to ADC1 Peripheral and AFIO block
			case ADC1: RCC_APB2_ENR |=(1U<<0)|(1U<<9);
								 RCC_CFGR |= (1U<<15); // setting ADC Clock prescaler to 6 72/6 12Mhz < 14Mhz valid
								 t_ADC = _ADC1; // Storing the base address of ADC1	
			           break;
			case ADC2: RCC_APB2_ENR |=(1U<<0)|(1U<<10); // ENABLE clock to ADC2 Peripheral and AFIO block
								 RCC_CFGR |= (1U<<15);	 // setting ADC Clock prescaler to 6 72/6 12Mhz < 14Mhz valid
							   t_ADC = _ADC2;
								 break;
			
		}
		return t_ADC;
		
}

uint8_t get_channel_no(uint8_t pin,uint8_t port){
	
	uint8_t channel = 0;

	if(PORTA==port){
	
		switch(pin){
			case 0: channel = 0;
							break;
			case 1: channel = 1;
							break;
			case 2: channel = 2;
							break;
			case 3: channel = 3;
							break;
			case 4: channel = 4;
							break;
			case 5: channel = 5;
							break;
			case 6: channel = 6;
							break;
			case 7: channel = 7;
			
		}
	}
	if(PORTB==port){
		switch(pin){
			
			case 0: channel = 8;
							break;
			case 1: channel = 9;
		}
	}

	if(PORTC==port){
		switch(pin){
			case 0: channel = 10;
							break;
			case 1: channel = 11;
							break;
			case 2: channel = 12;
							break;
			case 3: channel = 13;
							break;
			case 4: channel = 14;
							break;
			case 5: channel = 15;
		}
	
	
	}	
	
	return channel;


    }
// time taken to complete one conversion
void Set_Sampling_rate(uint8_t channel){

		switch(channel){
		
			case 0: ADC->ADC_SMPR2|=7U<<0;
							break;
			case 1: ADC->ADC_SMPR2|=7U<<3;
							break;
			case 2: ADC->ADC_SMPR2|=7U<<6;
							break;
			case 3: ADC->ADC_SMPR2|=7U<<9;
							break;
			case 4: ADC->ADC_SMPR2|=7U<<12;
							break;
			case 5: ADC->ADC_SMPR2|=7U<<15;
							break;
			case 6: ADC->ADC_SMPR2|=7U<<18;
							break;
			case 7: ADC->ADC_SMPR2|=7U<<21;
							break;
			case 8: ADC->ADC_SMPR2|=7U<<24;
							break;
			case 9: ADC->ADC_SMPR2|=7U<<27;
							break;
		 case 10: ADC->ADC_SMPR1|=7U<<0;
							break;
			case 11: ADC->ADC_SMPR1|=7U<<3;
							break;
			case 12: ADC->ADC_SMPR1|=7U<<6;
							break;
			case 13: ADC->ADC_SMPR1|=7U<<9;
							break;
			case 14: ADC->ADC_SMPR1|=7U<<12;
							break;
			case 15: ADC->ADC_SMPR1|=7U<<15;
							
		
		}

}
void Store_SQR(uint8_t channel, uint8_t cur_point){
		
					if(cur_point>=1 && cur_point<=6){ // condtion for checking in which register i need to store
							ADC->ADC_SQR3 &= ~(31U<<(5*(cur_point-1))); //shifiting 5 bits and clearing that portion
							ADC->ADC_SQR3 |= (channel<<(5*(cur_point-1))); //setting the channel bits in that position
						
					}
					if(cur_point>=7 && cur_point<=12){ // condtion for checking in which register i need to store
							ADC->ADC_SQR2 &= ~(31U<<(5*(cur_point-1))); //shifiting 5 bits and clearing that portion
							ADC->ADC_SQR2 |= (channel<<(5*(cur_point-1))); //setting channel the bits in that position
						
					}
					if(cur_point>=13 && cur_point<=16){ // condtion for checking in which register i need to store
							ADC->ADC_SQR1 &= ~(31U<<(5*(cur_point-1))); //shifiting 5 bits and clearing that portion
							ADC->ADC_SQR1 |= (channel<<(5*(cur_point-1))); //setting channel the bits in that position
						
					}
						


}

	

void Configure_ADC_Continuous_Scan_mode(uint8_t adc, uint8_t no_of_pins){
			
			no_of_pins_left_to_assign = no_of_pins;  // keep a track on assigned pins
			MAX = no_of_pins;
			ADC = get_adc(adc); // get ADC base address and store in global variable for interrupt purpose
			ADC->ADC_CR1 |= 1U<<8;  //scan mode
			ADC->ADC_CR2 |= (1U<<1)|(1U<<8); //Setting up in continous mode and enable DMA, we are using DMA2-CHANNEL-1 to transfer the data
			Arr = (uint16_t*)malloc(no_of_pins*sizeof(uint16_t)); // memory allocated to store the data of ADC in scan mode
			ADC->ADC_SQR1 = (no_of_pins-1)<<20; // Setting the Scan Length
			//Start the DMA transfer
			Start_DMA_transfer(DMA2,1,(void*)&(ADC->ADC_DATA),(void*)Arr,16,no_of_pins);
}

void Analog_pin(uint8_t pin,uint8_t port){
	
	if(no_of_pins_left_to_assign>0 && SQR_reg_pointer<=MAX){
		
		uint8_t channel = get_channel_no(pin,port); // getting channel no of the corrsponding pin
		Set_Sampling_rate(channel);  //set the sampling rate of the corrsponding channel
		Store_SQR(channel,SQR_reg_pointer); // store the channels in SQR registers
		no_of_pins_left_to_assign--; // decrement the channels left to assign
		SQR_reg_pointer++; // shift the pointer
		
	}
	
}

void ADC_Start(adc_block* ADC){
	
			ADC->ADC_CR2 |= 1U<<0; // Wakeup from Sleep mode
			Systick_Delay_ms(1);
			ADC->ADC_CR2 |= 1U<<0; // Start conversion
			Systick_Delay_ms(1);
			// Calibration of ADC
	  	ADC->ADC_CR2 |= 1U<<2;
	while(ADC->ADC_CR2 &= 1U<<2); //wait until the calibration is done;
	


}

void ADC_Stop(adc_block* ADC){
	
		ADC->ADC_CR2 &= ~1U; // clear the ADC start bit

}



