#pragma once
#include "FunctorClassI.h"
class MeasureHeight :
	public FunctorClassI
{
public:
	MeasureHeight();
	~MeasureHeight();

	virtual const char* GetDescription();
	virtual void Run();

private:
	void UpdateFigure(cv::Mat& _imag);
	void FindNearestVectorPoint();
	double Points2D_distance(cv::Point2i&, cv::Point2i&);
	double CalculateDistance();
	void PrintValue(cv::Mat&, double);

	cv::Point2i m_current_point;
	cv::Point2i m_ground_point;
	cv::Vec3d m_refVertical;
	bool m_ground_set;
};

