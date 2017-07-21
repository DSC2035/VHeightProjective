#include "definitions.h"

#include "UtilityFunctions.h"

#include "ImageDataClass.h"

#include "CalibrateScene.h"





CalibrateScene::CalibrateScene()
{
}


CalibrateScene::~CalibrateScene()
{
}


const char* CalibrateScene::GetDescription()
{
	return "Calibrate Scene";
}

void CalibrateScene::Run()
{
	if (ImageDataClass::GetInstance().m_image.empty())  //two pointes per line, last is Z direction
	{
		std::cout << "Load image first" << std::endl;
		return;
	}

	if (!ImageDataClass::GetInstance().m_vanishingPlanePoints.size())  //two pointes per line
	{
		std::cout << "No data is available for scene calibration, Calibrate the camera first" << std::endl;
		return;
	}

	ImageDataClass::GetInstance().m_refPoint0 = cv::Point2i();
	ImageDataClass::GetInstance().m_refPoint1 = cv::Point2i();
	ImageDataClass::GetInstance().m_refPoint0Set = false;
	ImageDataClass::GetInstance().m_refPoint1Set = false;

	ImageDataClass::GetInstance().m_vanishingPlaneLine = CalculateLineFromPts(ImageDataClass::GetInstance().m_vanishingPlanePoints);

	ImageDataClass::GetInstance().m_event.Flush();

	EventData eventData;
	std::cout << "With a mouse click define the reference point on the ground." << std::endl;

	ImageDataClass::GetInstance().RedrawLines();

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
					if (ImageDataClass::GetInstance().m_refPoint0Set)
					{
						m_current_point = VectorImagePoint(eventData.m_x, eventData.m_y);
						FindNearestVectorPoint();
						ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
						UpdateFigure(ImageDataClass::GetInstance().m_image);
						ImageDataClass::GetInstance().m_imageUpdated = true;
					}
				}
				break;

				case(cv::EVENT_LBUTTONDOWN):
				{

					if (!ImageDataClass::GetInstance().m_refPoint0Set)
					{

						std::cout << "Inserting first reference point at: " << eventData.m_x << " " << eventData.m_y << std::endl;
						ImageDataClass::GetInstance().m_refPoint0 = cv::Point2i(eventData.m_x, eventData.m_y);
						cv::Vec3d baseRefHom(ImageDataClass::GetInstance().m_refPoint0.x, ImageDataClass::GetInstance().m_refPoint0.y, 1);
						m_refVertical = ImageDataClass::GetInstance().m_verticalVanishingPoint.cross(baseRefHom);
						m_current_point = cv::Point2i(eventData.m_x, eventData.m_y);
						ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
						UpdateFigure(ImageDataClass::GetInstance().m_image);
						ImageDataClass::GetInstance().m_imageUpdated = true;
						ImageDataClass::GetInstance().m_refPoint0Set = true;
					}
					else
					{
						if (ImageDataClass::GetInstance().m_refPoint0Set&&(!ImageDataClass::GetInstance().m_refPoint1Set))
						//set reference ground point
						m_current_point = cv::Point2i(eventData.m_x, eventData.m_y);
						FindNearestVectorPoint();
						std::cout << "Inserting second reference point at: " << m_current_point.x << " " << m_current_point.y << std::endl;
						ImageDataClass::GetInstance().m_refPoint1 = m_current_point;
						UpdateFigure(ImageDataClass::GetInstance().m_image0);
						ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
						ImageDataClass::GetInstance().m_imageUpdated = true;
						ImageDataClass::GetInstance().m_refPoint1Set = true;
						std::cout << std::endl << "Set reference length: ";
						InpStream::GetInpStream() >> ImageDataClass::GetInstance().m_calibLength;
						return;
					}
				}
				break;

				case(cv::EVENT_RBUTTONDOWN):
				{
					if (ImageDataClass::GetInstance().m_refPoint0Set&&(!ImageDataClass::GetInstance().m_refPoint1Set)) ImageDataClass::GetInstance().m_refPoint0Set = false;
					ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
					ImageDataClass::GetInstance().m_imageUpdated = true;
					return;
				}
				break;
			}
		}
	}


}

void CalibrateScene::FindNearestVectorPoint()
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

//	m_current_point = cv::Point2i(crossPntHor.x, crossPntHor.y);
	double hordistance = CalculateP2Pdistance(m_current_point, cv::Point2i(crossPntHor.x, crossPntHor.y));
	double verdistance = CalculateP2Pdistance(m_current_point, cv::Point2i(crossPntVer.x, crossPntVer.y));

//	std::cout << "Vertical distance: " << verdistance << std::endl;
//	std::cout << "Horizontal distance: " << hordistance << std::endl;

	if (hordistance < verdistance)	m_current_point = cv::Point2i(crossPntHor.x, crossPntHor.y);
	else 
		m_current_point = cv::Point2i(crossPntVer.x, crossPntVer.y);
}

void CalibrateScene::UpdateFigure(cv::Mat& _imag)
{
	cv::line(_imag, ImageDataClass::GetInstance().m_refPoint0, m_current_point, cv::Scalar(0, 255, 0), 3);
}

