#include"DMA_drivers.h"
#include"Gpio_drivers.h"

dma_ctrl_block* getdma_ctrl(uint8_t dma, uint8_t channel){
			dma_ctrl_block * t_dma = 0x00; // for storing the base address of the dma_ctrl_block
			if(DMA1==dma){
				// enable the clock to DMA1 block
				RCC_AHB_ENR |= (1U<<0);
				switch(channel){
				
					
						case 1: t_dma = DMA1_CH1;
										break;
						case 2: t_dma = DMA1_CH2;
										break;
				
						case 3: t_dma = DMA1_CH3;
										break;
				
						case 4: t_dma = DMA1_CH4;
										break;
				
						case 5: t_dma = DMA1_CH5;
										break;
				
						case 6: t_dma = DMA1_CH6;
										break;
				
						case 7: t_dma = DMA1_CH7;
										break;
				
				}
			}
				if(DMA2==dma){
				// enable the clock to DMA2 block
				RCC_AHB_ENR |= (1U<<1);
				switch(channel){
				
					
						case 1: t_dma = DMA2_CH1;
										break;
						case 2: t_dma = DMA2_CH2;
										break;
				
						case 3: t_dma = DMA2_CH3;
										break;
				
						case 4: t_dma = DMA2_CH4;
										break;
				
						case 5: t_dma = DMA2_CH5;
										break;
				
				
				}
			}
			
			return t_dma;

}

void Start_DMA_transfer(uint8_t dma,uint8_t channel,void* source_address,void* destination_address,uint8_t data_block_size_bits, uint16_t no_of_blocks){

			dma_ctrl_block* DMA = getdma_ctrl(dma,channel); // get the DMA base address
			DMA->DMA_CPAR = (uint32_t)source_address; // typcasting address to uint_32t and storing source address
	    DMA->DMA_CMAR = (uint32_t)destination_address; // storing destination address
			DMA->DMA_CNDTR = no_of_blocks; // No of blocks need to transfer
			DMA->DMA_CCR |= (1U<<5)|(1U<<7); // Enabling memory increment mode and cyclic mode
			switch(data_block_size_bits){
			
				case 8: DMA->DMA_CCR |=(0U<<8)|(0U<<10);//setting peripheral and memory block size
								break;		
				case 16: DMA->DMA_CCR |=(1U<<8)|(1U<<10);
								break;
				case 32: DMA->DMA_CCR |=(2U<<8)|(2U<<10);
								break;
			}
	
			//Start the DMA
			DMA->DMA_CCR |=(1U<<0); //enabling the channel




}
void Stop_DMA_transfer(uint8_t dma, uint8_t channel){

	dma_ctrl_block* DMA = getdma_ctrl(dma,channel); 
	DMA->DMA_CCR &= ~1U; //disabling the channel


}
