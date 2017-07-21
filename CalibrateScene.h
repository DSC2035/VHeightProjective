#pragma once
#include "definitions.h"
#include "FunctorClassI.h"

extern cv::Point2i refPoint;
extern float calibLength;

class CalibrateScene :
	public FunctorClassI
{
public:
	CalibrateScene();
	~CalibrateScene();

	virtual const char* GetDescription();
	virtual void Run();
private:
	void UpdateFigure(cv::Mat& _imag);
	void FindNearestVectorPoint();
	cv::Point2i m_current_point;
	cv::Vec3d m_refVertical;
};

