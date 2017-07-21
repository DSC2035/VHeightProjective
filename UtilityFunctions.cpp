
#include "ImageDataClass.h"

#include "UtilityFunctions.h"

cv::Point3d CalculateVPointFromPLinesSet(ImPLinesVec& _linesVec)
{
	//simplified calculation from first and last points of the first and last lines

	cv::Point3d firstLinePt0(_linesVec.front().front().x, _linesVec.front().front().y, 1);
	cv::Point3d firstLinePt1(_linesVec.front().back().x, _linesVec.front().back().y, 1);

	cv::Point3d lastLinePt0(_linesVec.back().front().x, _linesVec.back().front().y, 1);
	cv::Point3d lastLinePt1(_linesVec.back().back().x, _linesVec.back().back().y, 1);

	cv::Point3d vpoint = (firstLinePt0.cross(firstLinePt1)).cross(lastLinePt0.cross(lastLinePt1));

	/*vpoint.x /= vpoint.z;
	vpoint.y /= vpoint.z;
	vpoint.z /= vpoint.z;*/
	Homogenize3DPoint<cv::Point3d>(vpoint);

	return vpoint;
}

VectorReal CalculateLineFromPts(VecRealVec& _ptsVec)
{
	//simple implementation

	VectorReal pt = _ptsVec.front().cross(_ptsVec.back());
	Homogenize3DPoint(pt);
	return pt;
}


void DrawLine(cv::Mat& _imag, cv::Point3d & _line, cv::Scalar _color)
{
	
	int width = _imag.cols;
	int height = _imag.rows;

	cv::Point3d pt[2];
	int index = 0;
	
	cv::Point3d  ptLine = _line.cross(cv::Point3d(0, 0, 1).cross(cv::Point3d(0, height, 1)));
	Homogenize3DPoint(ptLine);
	if ((ptLine.y >= 0) || (ptLine.y <= height))
	{
		pt[index] = ptLine;
		index++;
	}

	ptLine = _line.cross(cv::Point3d(width, 0, 1).cross(cv::Point3d(width, height, 1)));
	Homogenize3DPoint(ptLine);
	if ((ptLine.y >= 0) || (ptLine.y <= height))
	{
		pt[index] = ptLine;
		index++;
	}

	if (index < 2)
	{
		ptLine = _line.cross(cv::Point3d(0, 0, 1).cross(cv::Point3d(width, 0, 1)));
		Homogenize3DPoint(ptLine);
		if ((ptLine.x >= 0) || (ptLine.x <= width))
		{
			pt[index] = ptLine;
			index++;
		}
	}

	if (index < 2)
	{
		ptLine = _line.cross(cv::Point3d(0, height, 1).cross(cv::Point3d(width, height, 1)));
		Homogenize3DPoint(ptLine);
		if ((ptLine.x >= 0) || (ptLine.x <= width))
		{
			pt[index] = ptLine;
			index++;
		}
	}

	cv::line(_imag, cv::Point(pt[0].x, pt[0].y), cv::Point(pt[1].x, pt[1].y), _color, 3);

	//cv::line(_imag, cv::Point(0, 0), cv::Point(width, height), cv::Scalar(255, 0, 0), 3);

}

