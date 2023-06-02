

#include "DigitalFilter.h"
#include "math.h"


DigitalFilter::DigitalFilter(double R, double C, double tau) 
{
	this->R = R;
	this->C = C;
	this->tau = tau;
}

double DigitalFilter::Filter(double* oldValues, uint16_t lenOldValues, double newValue)
{
	static double t = 0;
	double filteredValue = 0;
	double k = 0;

	if (lenOldValues == 1) {
		if (t > 0) {
			k = R * C;
			tau = exp(- t / k);
			filteredValue = oldValues[0] + (newValue - oldValues[0]) * tau;
		} else {
			filteredValue = newValue;
		}
	}

	t += 0.1;

	return filteredValue;
}