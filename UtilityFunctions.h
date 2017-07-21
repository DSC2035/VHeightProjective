#pragma once
#include "definitions.h"

cv::Point3d CalculateVPointFromPLinesSet(ImPLinesVec&);

VectorReal CalculateLineFromPts(VecRealVec&);

template<typename T1, typename T2> double CalculateP2Pdistance(T1&& _p1, T2&& _p2)
{
	return sqrt((_p1.x - _p2.x)*(_p1.x - _p2.x) + (_p1.y - _p2.y)*(_p1.y - _p2.y));
}

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
