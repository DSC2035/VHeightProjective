#pragma once


class FunctorClassI {
public:
	FunctorClassI();
	virtual ~FunctorClassI();

	virtual const char* GetDescription() = 0;
	virtual void Run() = 0;
};


