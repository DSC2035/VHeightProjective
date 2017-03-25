#pragma once

#include "definitions.h"

#include "CVEvent.h"

class ImageDataClass
{
public:
	~ImageDataClass();

	static ImageDataClass& GetInstance();

	bool CalculatePlaneVanishingLine();
	bool CalculateVertVanishingPoint();
	bool OpenFigure(std::string& _strName);
	void ResetImage(void);

	const std::string& GetImageFileName(void) { return m_imageFileName; }

	void RedrawLines();

	const char* m_openCVWindowName;
	const char* m_dataFile;
	cv::Mat m_imageData;
	cv::Mat m_image0;
	cv::Mat m_image;
	bool m_imageUpdated = true;
	ImPLinesVec		m_imageVertPLinesPoints;
	ImPLinesSetsVec m_imagePlanePLinesPoints;
	std::vector<std::vector<VectorReal>> m_pointsCoordinates;
	CV_Event m_event;

	cv::Point3d m_vanishingPlaneLine;
	cv::Point3d m_verticalVanishingPoint;
	VecRealVec m_vanishingPlanePoints;

	cv::Point2i m_refPoint0;
	cv::Point2i m_refPoint1;
	double m_calibLength;
	bool m_refPoint0Set;
	bool m_refPoint1Set;


private:
	ImageDataClass();
	std::string m_imageFileName;
};

