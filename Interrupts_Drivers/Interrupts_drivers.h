#ifndef Interrupt_Drivers
#define Interrupt_Drivers
#include<stdint.h>

//BASE ADDRESSES FOR OUR REQURIED REGISTERS

//for selecting the Interrupt Line in EXTI Hardware
#define AFIO (*((volatile uint32_t*)0x40010000)) //base address of the block	
#define AFIO_EXTICR1 	(*((volatile uint32_t*)(&AFIO+0x02))) // AFIO Address + 2*(sizeof(uint32_t))which matches our requried offset
#define AFIO_EXTICR2  (*((volatile uint32_t*)(&AFIO+0x03)))	// AFIO Address + 3*(sizeof(uint32_t))which matches our requried offset
#define AFIO_EXTICR3  (*((volatile uint32_t*)(&AFIO+0x04))) // AFIO Address + 4*(sizeof(uint32_t))which matches our requried offset
#define AFIO_EXTICR4  (*((volatile uint32_t*)(&AFIO+0x05))) // AFIO Address + 5*(sizeof(uint32_t))which matches our requried offset	
//for Handling the Interrupts	
#define EXTI      (*((volatile uint32_t*)0x40010400)) //base address of EXTI block
#define EXTI_IMR 	(*((volatile uint32_t*)(&EXTI+0x00))) // Interrupt mask
#define EXTI_EMR  (*((volatile uint32_t*)(&EXTI+0x01)))	// Event Mask
#define EXTI_RTSR (*((volatile uint32_t*)(&EXTI+0x02)))	// Rising Edge
#define EXTI_FTSR (*((volatile uint32_t*)(&EXTI+0x03))) // Falling Edge
#define EXTI_SIER (*((volatile uint32_t*)(&EXTI+0x04)))	// Software Interrupt Register
#define EXTI_PENR (*((volatile uint32_t*)(&EXTI+0x05)))	//Pending Register




// mapping the NVIC Pins and External Interrupt pins
#define __NVIC_PRIO_BITS          4       /*!< STM32 uses 4 Bits for the Priority Levels    */ // manditory
typedef enum IRQn{

/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  STM32 specific Interrupt Numbers *********************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
  TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
  RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt  
	*/
	          /*******FOR EXTERNAL INTERRUPTS***********/
	
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                 */
	EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
	EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts 
	*/
						/*******FOR EXTERNAL INTERRUPTS END***********/
						
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */
  ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
  USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
  TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt                                 */
  TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt                                */
  TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
  
  RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  USBWakeUp_IRQn              = 42      /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */





}IRQn_Type;

//VALUES TO LOAD TO ENABLE THE EXTI LINE WITH PORT

// FOR AFIO_EXTICR1 Register
//for EXTI0 line
#define EXTI_PA0 (uint32_t)(0x00)
#define EXTI_PB0 (uint32_t)(0x01)
#define EXTI_PC0 (uint32_t)(0x02)
//for EXTI1 line
#define EXTI_PA1 (uint32_t)(0x00<4)
#define EXTI_PB1 (uint32_t)(0x01<4)
#define EXTI_PC1 (uint32_t)(0x02<4)
//for EXTI2 line
#define EXTI_PA2 (uint32_t)(0x00<8)
#define EXTI_PB2 (uint32_t)(0x01<8)
#define EXTI_PC2 (uint32_t)(0x02<8)
//for EXTI3 line
#define EXTI_PA3 (uint32_t)(0x00<12)
#define EXTI_PB3 (uint32_t)(0x01<12)
#define EXTI_PC3 (uint32_t)(0x02<12)


// FOR AFIO_EXTICR2 Register
//for EXTI4 line
#define EXTI_PA4 (uint32_t)(0x00)
#define EXTI_PB4 (uint32_t)(0x01)
#define EXTI_PC4 (uint32_t)(0x02)
//for EXTI5 line
#define EXTI_PA5 (uint32_t)(0x00<4)
#define EXTI_PB5 (uint32_t)(0x01<4)
#define EXTI_PC5 (uint32_t)(0x02<4)
//for EXTI6 line
#define EXTI_PA6 (uint32_t)(0x00<8)
#define EXTI_PB6 (uint32_t)(0x01<8)
#define EXTI_PC6 (uint32_t)(0x02<8)
//for EXTI7 line
#define EXTI_PA7 (uint32_t)(0x00<12)
#define EXTI_PB7 (uint32_t)(0x01<12)
#define EXTI_PC7 (uint32_t)(0x02<12)


// FOR AFIO_EXTICR3 Register
//for EXTI8 line
#define EXTI_PA8 (uint32_t)(0x00)
#define EXTI_PB8 (uint32_t)(0x01)
#define EXTI_PC8 (uint32_t)(0x02)
//for EXTI9 line
#define EXTI_PA9 (uint32_t)(0x00<4)
#define EXTI_PB9 (uint32_t)(0x01<4)
#define EXTI_PC9 (uint32_t)(0x02<4)
//for EXTI10 line
#define EXTI_PA10 (uint32_t)(0x00<8)
#define EXTI_PB10 (uint32_t)(0x01<8)
#define EXTI_PC10 (uint32_t)(0x02<8)
//for EXTI11 line
#define EXTI_PA11 (uint32_t)(0x00<12)
#define EXTI_PB11 (uint32_t)(0x01<12)
#define EXTI_PC11 (uint32_t)(0x02<12)


// FOR AFIO_EXTICR4 Register
//for EXTI12 line
#define EXTI_PA12 (uint32_t)(0x00)
#define EXTI_PB12 (uint32_t)(0x01)
#define EXTI_PC12 (uint32_t)(0x02)
//for EXTI13 line
#define EXTI_PA13 (uint32_t)(0x00<4)
#define EXTI_PB13 (uint32_t)(0x01<4)
#define EXTI_PC13 (uint32_t)(0x02<4)
//for EXTI14 line
#define EXTI_PA14 (uint32_t)(0x00<8)
#define EXTI_PB14 (uint32_t)(0x01<8)
#define EXTI_PC14 (uint32_t)(0x02<8)
//for EXTI15 line
#define EXTI_PA15 (uint32_t)(0x00<12)
#define EXTI_PB15 (uint32_t)(0x01<12)
#define EXTI_PC15 (uint32_t)(0x02<12)

//RESETING INTERRUPT PINS TO GPIO
#define RES_INT_GPIO_0 0xFFFFFFF0;
#define RES_INT_GPIO_1 0xFFFFFF0F;
#define RES_INT_GPIO_2 0xFFFFF0FF;
#define RES_INT_GPIO_3 0xFFFF0FFF;

#define RES_INT_GPIO_4 0xFFFFFFF0;
#define RES_INT_GPIO_5 0xFFFFFF0F;
#define RES_INT_GPIO_6 0xFFFFF0FF;
#define RES_INT_GPIO_7 0xFFFF0FFF;

#define RES_INT_GPIO_8 0xFFFFFFF0;
#define RES_INT_GPIO_9 0xFFFFFF0F;
#define RES_INT_GPIO_10 0xFFFFF0FF;
#define RES_INT_GPIO_11 0xFFFF0FFF;

#define RES_INT_GPIO_12 0xFFFFFFF0;
#define RES_INT_GPIO_13 0xFFFFFF0F;
#define RES_INT_GPIO_14 0xFFFFF0FF;
#define RES_INT_GPIO_15 0xFFFF0FFF;




//RISING EDGE AND FALLING EDGE
typedef enum{
		FALLING, //0
		RISING , //1
		RISING_FALLING //2
}Trigger_edge_type;


//Interrupt Function Declarations

void Configure_GPIO_to_Interrupt_pin(uint8_t port,uint8_t pin,Trigger_edge_type edge);

void Reset_Interrupt_to_GPIO_pin(uint8_t pin);

void Enable_Interrupt(uint8_t pin,IRQn_Type IRQ_number);

//for clearing the Pending bit of Interrupt
void Reset_Interrupt_pen_bit(uint8_t pin);



#endif
