
#pragma once
#include "iFilter.h"

class DigitalFilter : public iFilter
{
public:
	DigitalFilter(double timeConstant);
	double Filter(double newValue);
private:
	double _tau;
        doublce _oldValue = 0.0;
};