

#include "UsartUser.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"


#define SYS_FREQUENCY 72000000L 
 

UsartUser::UsartUser()
{
}

void UsartUser::Init()
{
	 //Clock
	 RCC->AHBENR  |= RCC_AHBENR_GPIOCEN;            
	 RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_SYSCFGEN;       

	 //AF
	 GPIOC->AFR[0]   = 0;

	 //TX (PC4)
	 GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_0 | GPIO_OSPEEDER_OSPEEDR4_1; 
	 GPIOC->OTYPER  |= 0;                                                                          
	 GPIOC->PUPDR   |= 0;                                                                           
	 GPIOC->AFR[0]  |= (0x07<<(4*4));     									//AF7 Configurations
	 GPIOC->MODER   |= GPIO_MODER_MODER4_1;  
	 
	 //RX (PC5)
	 GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR5_1; 
	 GPIOC->OTYPER  |= 0; 
	 GPIOC->PUPDR   |= 0;
	 GPIOC->AFR[0]  |= (0x07<<(4*5));     								//AF7 Configuration
	 GPIOC->MODER   |= GPIO_MODER_MODER5_1;

	 //USART
	 long baudrate  = 9600;
	 long baudratio = SYS_FREQUENCY / baudrate;
	 
	 USART1->CR1  = 0;                                                                                                                   
	 USART1->CR2  = 0;                                                                                                                   
	 USART1->CR3  = 0;                                                                                                                   
	 USART1->BRR  = baudratio & 0xFFFF;                                                                                                  
	 USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE);       //TX, RX Enable, Interrupts Enable
	 USART1->CR1 |=  USART_CR1_UE;  
}

void UsartUser::Send(char* msg)
{
	uint8_t i = 0;
	while(msg[i]) {
		while (!(USART1->ISR & USART_ISR_TC)); 
		USART1->TDR = msg[i];
		i++;
	}
}