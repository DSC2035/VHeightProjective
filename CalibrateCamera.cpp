#include "definitions.h"

#include "ImageDataClass.h"
#include "CalibrateCamera.h"




CalibrateCamera::CalibrateCamera()
{
}


CalibrateCamera::~CalibrateCamera()
{
}

const char* CalibrateCamera::GetDescription()
{
	return "Calibrate camera";
}

void CalibrateCamera::Run()
{
	/*
	std::cout << "perform affine measurements of the scene";

	if (!ImageDataClass::GetInstance().m_imagePointsArray.size())
	{
		std::cout << "Points data is empty, define points on rectangulars" << std::endl;
		return;
	}

	cv::Point3d homImPoints[4];
	
	auto iterOuter = ImageDataClass::GetInstance().m_imagePointsArray.begin();

	int planeIndex = 0;
	int pointIndex = 0;
	for (iterOuter; (iterOuter != ImageDataClass::GetInstance().m_imagePointsArray.end())&&(planeIndex < MaxNumberOfPlanes*4); iterOuter++)
	{
		auto iterInner = (*iterOuter).begin();

		int loopIndex = 0;
		for (iterInner; (iterInner != (*iterOuter).end())&&(loopIndex < 2); iterInner++)
		{
			//
			homImPoints[pointIndex] = cv::Point3d((*iterInner).x, (*iterInner).y, 1);
			++loopIndex;
			++pointIndex;
		}
		std::cout << "pointIndex : " << pointIndex << std::endl;
		if (pointIndex == 4)
		{
			cv::Point3d line1 = homImPoints[0].cross(homImPoints[1]);
			cv::Point3d line2 = homImPoints[2].cross(homImPoints[3]);

			cv::Point3d crossPoint = line1.cross(line2);

			crossPoint.x /= crossPoint.z;
			crossPoint.y /= crossPoint.z;
			crossPoint.z /= crossPoint.z;
			cv::Point2i pnt = cv::Point2i(crossPoint.x, crossPoint.y);

			std::cout << "cross product, x= " << pnt.x << "  y= " << pnt.y << std::endl;

			ImageDataClass::GetInstance().vanishingPlanePoints.push_back(crossPoint);
			cv::line(ImageDataClass::GetInstance().m_image, pnt, pnt, cv::Scalar(0, 255, 0), 5);
			ImageDataClass::GetInstance().m_imageUpdated = true;
			pointIndex = 0;
		}
		++planeIndex;
	}

	int numVanishLines = ImageDataClass::GetInstance().vanishingPlanePoints.size() / 2;

	for (int i = 0; i < numVanishLines; i++)
	{
		//
		ImageDataClass::GetInstance().vanishingPlaneLines.push_back(ImageDataClass::GetInstance().vanishingPlanePoints[i * 2].cross(vanishingPlanePoints[i * 2 + 1]));
	}
	*/
}