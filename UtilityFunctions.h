#pragma once
#include "definitions.h"

cv::Point3d CalculateVPointFromPLinesSet(ImPLinesVec&);

VectorReal CalculateLineFromPts(VecRealVec&);

void DrawLine(cv::Mat& , cv::Point3d&, cv::Scalar _color);

template<typename T> void Homogenize3DPoint(T& _t)
{
	if (_t.z != 0.0)
	{
		_t.x /= _t.z;
		_t.y /= _t.z;
		_t.z /= _t.z;
	}
}
