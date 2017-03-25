#pragma once

#include "FunctorClassI.h"

class CalculateVanishingLine : public FunctorClassI
{
public:
	CalculateVanishingLine();
	~CalculateVanishingLine();

	virtual const char* GetDescription();
	virtual void Run();
};

