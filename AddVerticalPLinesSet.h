#pragma once
#include "FunctorClassI.h"

#include "InsertNewLine.h"

class AddVerticalPLinesSet :
	public FunctorClassI
{
public:
	AddVerticalPLinesSet();
	~AddVerticalPLinesSet();

	virtual const char* GetDescription();
	virtual void Run();

private:
	InsertNewLine m_lineInsertObj;
	void UpdateFigure(cv::Mat& _imag, ImLinePtsVec& _pointVector);
};

