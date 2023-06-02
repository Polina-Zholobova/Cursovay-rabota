
#pragma once

#include "stdint.h"

class iFilter 
{
public:
		virtual double Filter(double* oldValues, uint16_t lenOldValues, double newValue) = 0;
};