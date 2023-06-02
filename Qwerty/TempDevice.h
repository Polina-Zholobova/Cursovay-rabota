
#pragma once

#include "DHT_sensor.h"
#include "DigitalFilter.h"

#define GPIO_PIN_0          ((uint16_t)0x0001U)  
#define  GPIO_NOPULL        (0x00000000U)  

class TempDevice
{
public:
        TempDevice(IFilter& temFiler, IFilter& humFilter);
	void updateTemp();
        auto getTemp()
        {
          return _temperatureValue;
        }
        void updateHum();
	auto getHum()
        {
          return _humidityValue;
        }

	
private:
	DHT_sensor _sensor;
	iFilter& _humFilter;
        iFilter& _tempFilter;
	double _temperatureValue;
	double _humidityValue;
	
};