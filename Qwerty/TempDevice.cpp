#include "TempDevice.h"

#define filtrR 		10000.0l
#define filtrC 		0.005l
#define filtrTau 	1.0

TempDevice::TempDevice(iFilter& tempFilter, iFilter& humFilter) :
                                                              _humFilter(humFilter),
                                                              _tempFilter(tempFilter)
{
}

void TempDevice::updateTemp()
{
   const auto temp = (double)_sensor.DHT_getData().temp;
	//core_util_critical_section_enter();
	__disable_irq();
   _temperatureValue =  _tempFilter.Filter(temp);
	__enable_irq();
}

void TempDevice::updateHum()
{
	const auto hum = (double)_sensor.DHT_getData().hum;
	//core_util_critical_section_enter();
	__disable_irq();
	_humidityValue = _humFilter.Filter(hum);
	//core_util_critical_section_exit();
	__enable_irq();
}