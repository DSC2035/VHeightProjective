#pragma once
#include "FunctorClassI.h"
class CalibrateCamera :
	public FunctorClassI
{
public:
	CalibrateCamera();
	~CalibrateCamera();

	virtual const char* GetDescription();
	virtual void Run();
};

