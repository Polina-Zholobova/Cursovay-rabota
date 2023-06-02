#include "TempDevice.h"

#define filtrR 		10000.0l
#define filtrC 		0.005l
#define filtrTau 	1.0



TempDevice::TempDevice(IFilter& temFiler, IFilter& humFilter) :
                                                              _humFilter(humFilter),
                                                              _tempFilter(tempFilter)
{
}

void TempDevice::updateTemp()
{

   const auto temp = (double)sensor.DHT_getData().temp;
   core_util_critical_section_enter();
   _temperatureValue =  _tempFilter->Filter(temp);
   core_util_critical_section_exit()
}

void TempDevice::updateHum()
{
	const var hum = (double)sensor.DHT_getData().hum;
        _humidityValue = _humFilter->Filter(hum);
}