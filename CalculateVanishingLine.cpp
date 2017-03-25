#include "definitions.h"

#include "ImageDataClass.h"

#include "CalculateVanishingLine.h"

#include "UtilityFunctions.h"


CalculateVanishingLine::CalculateVanishingLine()
{
}


CalculateVanishingLine::~CalculateVanishingLine()
{
}


const char* CalculateVanishingLine::GetDescription()
{
	return "Calculate vanishing line from set of parallel lines";
}

void CalculateVanishingLine::Run()
{
	//



//	cv::line(ImageDataClass::GetInstance().m_image, pnt, pnt, cv::Scalar(0, 255, 0), 5);
//	ImageDataClass::GetInstance().m_imageUpdated = true;
}