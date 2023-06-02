

#include "DigitalFilter.h"
#include "math.h"

constexpr int DampingTime = 10.0;

DigitalFilter::DigitalFilter(double timeConstant) :  _tau( exp(- DampingTime / (timeConstant) ))
{

}

double DigitalFilter::Filter(double newValue)
{
    if (t > 0)
    {
	filteredValue = oldValue + (newValue - oldValues) * tau;
    } else
    {
	filteredValue = newValue;
    }
    _oldValue = filteredValue;
    return filteredValue;
}