#pragma once
#include "FunctorClassI.h"

#include "InsertNewLine.h"


class AddPLinesSet:
	public FunctorClassI
{
public:
	AddPLinesSet();
	~AddPLinesSet();

	virtual const char* GetDescription();
	virtual void Run();

private:
	void UpdateFigure(cv::Mat& _imag, ImLinePtsVec& _pointVector);
	InsertNewLine m_lineInsertObj;
};

