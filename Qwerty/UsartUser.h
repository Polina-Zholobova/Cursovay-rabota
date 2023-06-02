
#pragma once

#include "iUsart.h"

class UsartUser : public iUsart
{
public:
		UsartUser();
		void Init();
		void Send(char* msg);
};
