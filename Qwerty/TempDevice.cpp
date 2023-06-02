#include "TempDevice.h"

#define filtrR 		10000.0l
#define filtrC 		0.005l
#define filtrTau 	1.0



TempDevice::TempDevice()
{
	filter = new DigitalFilter(filtrR, filtrC, filtrTau);
	oldValueTemp = new double(1);
	oldValueHum = new double(1);
	oldValueTemp[0] = 0;
	oldValueHum[0] = 0;
}

double TempDevice::getTemp()
{
	oldValueTemp[0] = newValueTemp;
	newValueTemp 		= (double)sensor.DHT_getData().temp;
	//return newValueTemp;
	return filter->Filter(oldValueTemp, 1, newValueTemp);
}

double TempDevice::getHum()
{
	oldValueHum[0] = newValueHum;
	newValueHum 		= (double)sensor.DHT_getData().hum;
	return filter->Filter(oldValueHum, 1, newValueHum);
}