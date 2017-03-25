#pragma once
#include "FunctorClassI.h"
class CalculateCamPos :
	public FunctorClassI
{
public:
	CalculateCamPos();
	~CalculateCamPos();
	virtual const char* GetDescription();
	virtual void Run();
};

