#ifndef DMA_driver
#define DMA_driver
#include<stdint.h>

 //DMA GENERERIC BLOCK
typedef struct{

	uint32_t DMA_ISR,
					DMA_IFCR;


}dma_block;

//DMA CHANNEL
typedef struct{
		uint32_t  DMA_CCR,
							DMA_CNDTR,
							DMA_CPAR,
							DMA_CMAR;
	
}dma_ctrl_block;

//DMA1 HAS ONLY 7 INDEPENDENT CHANNELS
#define _DMA1     (dma_block*)0x40020000
#define DMA1_CH1 (dma_ctrl_block*)(0x40020000+0x008)
#define DMA1_CH2 (dma_ctrl_block*)(0x40020000+0x01C)
#define DMA1_CH3 (dma_ctrl_block*)(0x40020000+0x030)
#define DMA1_CH4 (dma_ctrl_block*)(0x40020000+0x044)
#define DMA1_CH5 (dma_ctrl_block*)(0x40020000+0x058)
#define DMA1_CH6 (dma_ctrl_block*)(0x40020000+0x06C)
#define DMA1_CH7 (dma_ctrl_block*)(0x40020000+0x080)

//DMA2 HAS ONLY 5 INDEPENDENT CHANNELS
#define _DMA2     (dma_block*)0x40020400 
#define DMA2_CH1 (dma_ctrl_block*)(0x40020400+0x008)
#define DMA2_CH2 (dma_ctrl_block*)(0x40020400+0x01C)
#define DMA2_CH3 (dma_ctrl_block*)(0x40020400+0x030)
#define DMA2_CH4 (dma_ctrl_block*)(0x40020400+0x044)
#define DMA2_CH5 (dma_ctrl_block*)(0x40020400+0x058)
// FOR FUNCTION PARAMETERS
#define DMA1 1
#define DMA2 2 

//FUNCTIONS DEFINATIONS
dma_ctrl_block* getdma_ctrl(uint8_t dma, uint8_t channel);
void Start_DMA_transfer(uint8_t dma,uint8_t channel,void* source_address,void* destination_address,uint8_t data_block_size_bits, uint16_t no_of_blocks);
void Stop_DMA_transfer(uint8_t dma, uint8_t channel);
#endif
