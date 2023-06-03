

#include "DigitalFilter.h"
#include "math.h"

constexpr int DampingTime = 10.0;

DigitalFilter::DigitalFilter(double timeConstant) :  _tau( exp(- DampingTime / (timeConstant) ))
{

}

double DigitalFilter::Filter(double newValue)
{
		static double filteredValue = UINT32_MAX;
	
    if (filteredValue != UINT32_MAX) {
				filteredValue = _oldValue + (newValue - _oldValue) * _tau;
    } else {
				filteredValue = newValue;
    }
    _oldValue = filteredValue;
    return filteredValue;
}