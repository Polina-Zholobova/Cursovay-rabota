
#pragma once

#include "DHT_sensor.h"
#include "DigitalFilter.h"

#define GPIO_PIN_0          ((uint16_t)0x0001U)  
#define  GPIO_NOPULL        (0x00000000U)  

class TempDevice
{
public:
	TempDevice();
	double getTemp();
	double getHum();
	
private:
	DHT_sensor sensor;
	iFilter* filter;
	double* oldValueTemp;
	double newValueTemp;
	double* oldValueHum;
	double newValueHum;
	
};