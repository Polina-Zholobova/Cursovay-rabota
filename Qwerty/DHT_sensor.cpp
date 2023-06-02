#include "DHT_sensor.h"
#include "cmsis_os2.h"

DHT_sensor::DHT_sensor()
{
	RCC->AHBENR |= RCC_AHBENR_GPIODEN;
	initGpio();
}

void DHT_sensor::initGpio()
{
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0;
	GPIOD->OTYPER  |= GPIO_OTYPER_OT_0;   
	GPIOD->PUPDR   |= 0;
}

void DHT_sensor::lineDown()
{
	GPIOD->BRR  = GPIO_BRR_BR_0;
}

void DHT_sensor::lineUp()
{
	GPIOD->BSRR = GPIO_BSRR_BS_0;
}

void DHT_sensor::goToOutput()
{
	lineUp();  
	GPIOD->MODER = GPIO_MODER_MODER0_0; 
}

void DHT_sensor::goToInput()
{    
	GPIOD->MODER = 0;
}

bool DHT_sensor::getLine()
{
	bool bitstatus = 0;

	if((GPIOD->IDR & 1) != 0) {
			bitstatus = 1;
	}	else {
			bitstatus = 0;
	}
	
	return bitstatus;
}

DHT_data DHT_sensor::DHT_getData()
{
	DHT_data data = {-128.0f, -128.0f};
	
	
	goToOutput();
	lineDown();
	osDelay(18);
	lineUp();
	goToInput();	


	#ifdef DHT_IRQ_CONTROL
	__disable_irq();
	#endif
	
	uint16_t timeout = 0;
	
	while(getLine()) {
		timeout++;
		if (timeout > DHT_TIMEOUT) {
			#ifdef DHT_IRQ_CONTROL
			__enable_irq();
			#endif

			//lastHum = -128.0f;
			//lastTemp = -128.0f;
			data.hum = lastHum;
			data.temp = lastTemp;

			return data;
		}
	}
	timeout = 0;
	
	while(!getLine()) {
		timeout++;
		if (timeout > DHT_TIMEOUT) {
			#ifdef DHT_IRQ_CONTROL
			__enable_irq();
			#endif

			//lastHum = -128.0f;
			//lastTemp = -128.0f;
			data.hum = lastHum;
			data.temp = lastTemp;

			return data;
		}
	}
	timeout = 0;
	while(getLine()) {
		timeout++;
		if (timeout > DHT_TIMEOUT) {
			#ifdef DHT_IRQ_CONTROL
			__enable_irq();
			#endif
			return data;
		}
	}
	
	uint8_t rawData[5] = {0,0,0,0,0};
	for(uint8_t a = 0; a < 5; a++) {
		for(uint8_t b = 7; b != 255; b--) {
			uint16_t hT = 0, lT = 0;
			while(!getLine() && lT != 65535) lT++;
			timeout = 0;
			while(getLine() && hT != 65535) hT++;
			if(hT > lT) rawData[a] |= (1<<b);
		}
	}

    #ifdef DHT_IRQ_CONTROL
	__enable_irq();
    #endif

	if((uint8_t)(rawData[0] + rawData[1] + rawData[2] + rawData[3]) == rawData[4]) {
		data.hum = (float)rawData[0];
		data.temp = (float)rawData[2] + ((float)rawData[3] * 0.1);	
	}
	
	#if DHT_POLLING_CONTROL == 1
	lastHum = data.hum;
	lastTemp = data.temp;
	#endif

	return data;
}
