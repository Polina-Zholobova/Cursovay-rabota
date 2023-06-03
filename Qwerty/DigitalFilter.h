
#pragma once
#include "iFilter.h"

class DigitalFilter : public iFilter
{
public:
	DigitalFilter(double timeConstant);
	double Filter(double newValue);
private:
	double _tau;
	double _oldValue = 0.0;
};