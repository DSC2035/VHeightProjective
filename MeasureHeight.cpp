#include "definitions.h"

#include "ImageDataClass.h"

#include "MeasureHeight.h"

#include "UtilityFunctions.h"




MeasureHeight::MeasureHeight() : m_ground_set(false)
{
}


MeasureHeight::~MeasureHeight()
{
}


const char* MeasureHeight::GetDescription()
{
	return "Measure vertical distance";
}

void MeasureHeight::Run()
{
	if (ImageDataClass::GetInstance().m_image.empty())  //two pointes per line, last is Z direction
	{
		std::cout << "Load image first" << std::endl;
		return;
	}

	if ((!ImageDataClass::GetInstance().m_refPoint0Set) || (!ImageDataClass::GetInstance().m_refPoint1Set))
	{
		std::cout << "Reference points are not set" << std::endl;
		return;
	}

	//calculate distance
	if (ImageDataClass::GetInstance().m_vanishingPlaneLine == cv::Point3d(0, 0, 0))
	{
		std::cout << "Vanishing line of plane is not calculated, fisrt estimate the line." << std::endl;
		return;
	}

	ImageDataClass::GetInstance().m_event.Flush();

	EventData eventData;
	std::cout << "With a mouse click define the ground point." << std::endl;



	while (true)
	{
		eventData = ImageDataClass::GetInstance().m_event.GetData();
		if (eventData.m_event == NO_EVENT)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else
		{
			switch (eventData.m_event)
			{

			case(cv::EVENT_MOUSEMOVE):
			{
				if (m_ground_set)
				{
					m_current_point = VectorImagePoint(eventData.m_x, eventData.m_y);
					FindNearestVectorPoint();
					ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
					UpdateFigure(ImageDataClass::GetInstance().m_image);
					PrintValue(ImageDataClass::GetInstance().m_image, CalculateDistance());
					ImageDataClass::GetInstance().m_imageUpdated = true;
				}
			}
			break;

			case(cv::EVENT_LBUTTONDOWN):
			{
				//if (!m_ground_set)
				{
					std::cout << "Ground point at: " << eventData.m_x << " " << eventData.m_y << std::endl;
					m_ground_point = cv::Point2i(eventData.m_x, eventData.m_y);
					cv::Vec3d groundRefHom(m_ground_point.x, m_ground_point.y, 1);
					m_refVertical = ImageDataClass::GetInstance().m_verticalVanishingPoint.cross(groundRefHom);
					m_current_point = cv::Point2i(eventData.m_x, eventData.m_y);
					ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
					UpdateFigure(ImageDataClass::GetInstance().m_image);
					ImageDataClass::GetInstance().m_imageUpdated = true;
					m_ground_set = true;
				}
			}
			break;

			case(cv::EVENT_RBUTTONDOWN):
			{
				if (ImageDataClass::GetInstance().m_refPoint0Set && (!ImageDataClass::GetInstance().m_refPoint1Set)) ImageDataClass::GetInstance().m_refPoint0Set = false;
				ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
				ImageDataClass::GetInstance().m_imageUpdated = true;
				m_ground_set = false;
				return;
			}
			break;
			}
		}
	}
}


void MeasureHeight::FindNearestVectorPoint()
{
	cv::Point2i mouse_pos = m_current_point;
	cv::Point3d horizonMouseLine = cv::Point3d(m_current_point.x, m_current_point.y, 1).cross(cv::Point3d(m_current_point.x + 100, m_current_point.y, 1));
	cv::Point3d verticalMouseLine = cv::Point3d(m_current_point.x, m_current_point.y, 1).cross(cv::Point3d(m_current_point.x, m_current_point.y + 100, 1));

	cv::Point3d crossPntHor = m_refVertical.cross(horizonMouseLine);
	cv::Point3d crossPntVer = m_refVertical.cross(verticalMouseLine);

	crossPntHor.x /= crossPntHor.z;
	crossPntHor.y /= crossPntHor.z;

	crossPntVer.x /= crossPntVer.z;
	crossPntVer.y /= crossPntVer.z;



	if (Points2D_distance(m_current_point, cv::Point2i(crossPntHor.x, crossPntHor.y)) <
		Points2D_distance(m_current_point, cv::Point2i(crossPntVer.x, crossPntVer.y)))

		m_current_point = cv::Point2i(crossPntHor.x, crossPntHor.y);
	else
		m_current_point = cv::Point2i(crossPntVer.x, crossPntVer.y);
}

void MeasureHeight::UpdateFigure(cv::Mat& _imag)
{
	cv::line(_imag, m_ground_point, m_current_point, cv::Scalar(0, 255, 0), 1);
}

double MeasureHeight::Points2D_distance(cv::Point2i& _p1, cv::Point2i& _p2)
{
	return sqrt((_p1.x - _p2.x)*(_p1.x - _p2.x) + (_p1.y - _p2.y)*(_p1.y - _p2.y));
}

void MeasureHeight::PrintValue(cv::Mat& _imag, double _height)
{
	std::string text = std::to_string(_height);
	int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 1;
	int thickness = 2;

	cv::Point2i textCoord = m_current_point + cv::Point2i(20, -10);

	int baseline = 0;
	cv::Size textSize = cv::getTextSize(text, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;

	/*
	// center the text
	cv::Point textOrg((img.cols - textSize.width) / 2,
		(img.rows + textSize.height) / 2);/*/

	// draw the box
	cv::rectangle(_imag, textCoord + cv::Point(0, baseline),
		textCoord + cv::Point(textSize.width, -textSize.height),
		cv::Scalar(0, 0, 255));
	// ... and the baseline first
	/*cv::line(_imag, textCoord + cv::Point(0, thickness),
		textCoord + cv::Point(textSize.width, thickness),
		cv::Scalar(0, 0, 255));*/

	cv::line(_imag, m_current_point, textCoord,
		cv::Scalar(0, 0, 255));

	// then put the text itself
	putText(_imag, text, textCoord, fontFace, fontScale,
		cv::Scalar(255, 0, 0)/*cv::Scalar::all(255)*/, thickness, 8);
}

double MeasureHeight::CalculateDistance()
{

	cv::Point3d u = (cv::Vec3d(m_ground_point.x, m_ground_point.y, 1).cross(cv::Vec3d(ImageDataClass::GetInstance().m_refPoint0.x, ImageDataClass::GetInstance().m_refPoint0.y, 1))).cross(ImageDataClass::GetInstance().m_vanishingPlaneLine);
	u.x /= u.z; u.y /= u.z; u.z /= u.z;

//	std::cout << "u.x: " << u.x << " u.y: " << u.y << " u.z: " << u.z << std::endl;
	cv::line(ImageDataClass::GetInstance().m_image, cv::Point2i(u.x, u.y), cv::Point2i(u.x, u.y), cv::Scalar(255, 0, 0), 5);

	cv::Point3d v = ImageDataClass::GetInstance().m_verticalVanishingPoint;
	v.x /= v.z; v.y /= v.z; v.z /= v.z;


	cv::Point3d t1s = (cv::Point3d(ImageDataClass::GetInstance().m_refPoint1.x, ImageDataClass::GetInstance().m_refPoint1.y, 1).cross(u)).cross(cv::Point3d(m_ground_point.x, m_ground_point.y, 1).cross(v));
	t1s.x /= t1s.z; t1s.y /= t1s.z; t1s.z /= t1s.z;

	//cv::line(g_image, cv::Point2i(t1s.x, t1s.y), cv::Point2i(t1s.x, t1s.y), cv::Scalar(255, 255, 0), 5);

	double vLength = CalculateP2Pdistance(cv::Point2d(m_ground_point.x, m_ground_point.y), cv::Point2d(v.x, v.y));
	double t1Length = CalculateP2Pdistance(cv::Point2d(m_ground_point.x, m_ground_point.y), cv::Point2d(t1s.x, t1s.y));
	double t2Length = CalculateP2Pdistance(cv::Point2d(m_ground_point.x, m_ground_point.y), cv::Point2d(m_current_point.x, m_current_point.y)); 


	return (t2Length*(vLength - t1Length))/(t1Length*(vLength - t2Length)) *ImageDataClass::GetInstance().m_calibLength;

	/*cv::Point3d l32ndPnt = cv::Point3d(v.x + (m_ground_point - g_refPoint0).x, v.y + (m_ground_point - g_refPoint0).y, v.z);

	cv::Point3d t1k = (cv::Point3d(g_refPoint1.x, g_refPoint1.y, 1).cross(u)).cross(cv::Point3d(m_ground_point.x, m_ground_point.y, 1).cross(l32ndPnt));
	t1k.x /= t1k.z; t1k.y /= t1k.z; t1k.z /= t1k.z;

	cv::Point3d t2k = (cv::Point3d(g_refPoint1.x, g_refPoint1.y, 1).cross(cv::Point3d(m_current_point.x, m_current_point.y, 1))).cross(cv::Point3d(m_ground_point.x, m_ground_point.y, 1).cross(l32ndPnt));
	t2k.x /= t2k.z; t2k.y /= t2k.z; t2k.z /= t2k.z;

	double vLength = Calculatep2Distance(cv::Point2d(m_ground_point.x, m_ground_point.y), cv::Point2d(v.x, v.y));
	double t1Length = Calculatep2Distance(cv::Point2d(m_ground_point.x, m_ground_point.y), cv::Point2d(t1k.x, t1k.y));
	double t2Length = Calculatep2Distance(cv::Point2d(m_ground_point.x, m_ground_point.y), cv::Point2d(t2k.x, t2k.y));
	return t2Length/t1Length*g_calibLength;*/
}

