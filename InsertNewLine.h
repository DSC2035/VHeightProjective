/*
 * InsertNewLine.h
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#pragma once

#include "definitions.h"
#include "FunctorClassI.h"


class InsertNewLine{
public:
	InsertNewLine();
	virtual ~InsertNewLine();

	ImLinePtsVec InsertLine(int _numpoints);

private:
	VectorImagePoint m_current_point;
	void UpdateOverlayFigure(cv::Mat&, std::vector<VectorImagePoint>&);
	int m_numpointsAdded;
};

