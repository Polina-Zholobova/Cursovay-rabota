
#pragma once
#include "iFilter.h"

class DigitalFilter : public iFilter
{
public:
	DigitalFilter(double R, double C, double tau);
	double Filter(double* oldValues, uint16_t lenOldValues, double newValue);
private:
	double R;
	double C;
	double tau;
};