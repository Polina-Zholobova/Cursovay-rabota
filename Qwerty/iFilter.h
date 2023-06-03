
#pragma once

#include "stdint.h"

class iFilter 
{
public:
   virtual double Filter(double newValue) = 0;
};