#include "definitions.h"
#include "ImageDataClass.h"
#include "UtilityFunctions.h"


ImageDataClass::ImageDataClass(): m_refPoint0Set(false), m_refPoint1Set(false), m_openCVWindowName("MainWindow")
{
	m_dataFile = "Data.dat";
}

ImageDataClass::~ImageDataClass()
{
}

ImageDataClass& ImageDataClass::GetInstance()
{
	static 	ImageDataClass instance;
	return instance;
}

bool ImageDataClass::CalculatePlaneVanishingLine()
{
	//
	if (m_imagePlanePLinesPoints.size()<2)
	{
		std::cout << "Set of parallel lines on plane not suffucient for estimation of vanishing line" << std::endl;
		return false;
	}

	m_vanishingPlanePoints.clear();

	auto iterPLinesSet = m_imagePlanePLinesPoints.begin();

	for (iterPLinesSet; iterPLinesSet != m_imagePlanePLinesPoints.end(); iterPLinesSet++)
	{
		m_vanishingPlanePoints.push_back(CalculateVPointFromPLinesSet(*iterPLinesSet));
	}

	std::cout << "calculated vanishing plane points" << std::endl;
	for (auto it : m_vanishingPlanePoints)
	{
		std::cout << "x= " << it.x << std::endl;
		std::cout << "y= " << it.y << std::endl;
		std::cout << "z= " << it.z << std::endl;
		std::cout << std::endl;

	}

	if (m_vanishingPlanePoints.size() > 1)
	{
		m_vanishingPlaneLine = CalculateLineFromPts(m_vanishingPlanePoints);
		return true;
	}
	else return false;
}

bool ImageDataClass::CalculateVertVanishingPoint()
{
	//
	if (m_imageVertPLinesPoints.size()<2)
	{
		std::cout << "Set of vertical parallel lines not suffucient for estimation of vanishing point" << std::endl;
		return false;
	}

	m_verticalVanishingPoint = CalculateVPointFromPLinesSet(m_imageVertPLinesPoints);

	std::cout << std::endl;
	std::cout << "Vertical vanishing point is estimated at:" << std::endl;
	std::cout << "x= " << m_verticalVanishingPoint.x << std::endl;
	std::cout << "y= " << m_verticalVanishingPoint.y << std::endl;
	std::cout << std::endl;
	return true;
}

void ImageDataClass::RedrawLines()
{
	//
	ResetImage();

	for (auto itPLSet : m_imagePlanePLinesPoints)
	{
		for (auto iterLine : itPLSet)
		{
			auto pt0 = iterLine.begin();
			auto pt1 = pt0;
			pt1++;
			while (pt1 != iterLine.end())
			{
				cv::line(m_image0, *pt0, *pt1, cv::Scalar(0, 0, 255), 3);
				pt0 = pt1;
				pt1++;
			}
		}
	}

	for (auto iterLine : m_imageVertPLinesPoints)
	{
		auto pt0 = iterLine.begin();
		auto pt1 = pt0;
		pt1++;
		while (pt1 != iterLine.end())
		{
			cv::line(m_image0, *pt0, *pt1, cv::Scalar(0, 0, 255), 3);
			pt0 = pt1;
			pt1++;
		}
	}


	if (m_vanishingPlaneLine != cv::Point3d(0,0,0))
	{
		DrawLine(m_image0, m_vanishingPlaneLine, cv::Scalar(0, 255, 0));
	}

	if (m_refPoint0Set&&m_refPoint1Set)
	{
		cv::line(m_image0, m_refPoint0, m_refPoint1, cv::Scalar(0, 255, 0), 3);
	}


	ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
	ImageDataClass::GetInstance().m_imageUpdated = true;
}


bool ImageDataClass::OpenFigure(std::string& _strName)
{
	if (m_imageFileName == _strName) return true;
	m_imageData = cv::imread(_strName, CV_LOAD_IMAGE_COLOR);   // Read the file
	if (!ImageDataClass::GetInstance().m_imageData.data)                              // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return false;
	} 

	m_imageData.copyTo(m_image0);
	m_image0.copyTo(m_image);
	m_imageFileName = _strName;
	m_imageUpdated = true;
	return true;
}

void ImageDataClass::ResetImage(void)
{
	//
	m_imageData.copyTo(m_image0);
	m_image0.copyTo(m_image);
	m_imageUpdated = true;
}