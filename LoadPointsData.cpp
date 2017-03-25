/*
 * LoadPointsData.cpp
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#include <fstream>
#include <string>

#include "definitions.h"
#include "ImageDataClass.h"
#include "LoadPointsData.h"



LoadPointsData::LoadPointsData() {
	// TODO Auto-generated constructor stub

}

LoadPointsData::~LoadPointsData() {
	// TODO Auto-generated destructor stub
}

const char* LoadPointsData::GetDescription()
{
	return "Load point data";
}

void LoadPointsData::Run()
{
	//
	//
	std::ifstream ifs;
	ifs.open(ImageDataClass::GetInstance().m_dataFile);
	if (!ifs.is_open())
	{
		std::cout << "No succesfull file opening." << std::endl;
		return;
	}

	ImageDataClass::GetInstance().m_refPoint0Set = false;
	ImageDataClass::GetInstance().m_refPoint1Set = false;

	std::string str;
	while (std::getline(ifs,str))
	{

		if (str == TAG_IMFILE)
		{
			std::getline(ifs, str);
			if(str != TAG_END)
			{
				ImageDataClass::GetInstance().OpenFigure(str);
				std::getline(ifs, str);
			}
			std::getline(ifs, str);
		}

		if (str == TAG_IMPDAT)
		{
			ImPLinesVec plinesVec;
			std::getline(ifs, str);
			while (str != TAG_END)
			{
				ImLinePtsVec ptsVec;
				while (str != TAG_DELIM)
				{
					int x, y;
					x = std::stoi(str);
					std::getline(ifs, str);
					y = std::stoi(str);
					std::getline(ifs, str);
					ptsVec.push_back(cv::Vec2i(x, y));

				}
				plinesVec.push_back(ptsVec);
				std::getline(ifs, str);
				if (str == TAG_DELIM)
				{
					ImageDataClass::GetInstance().m_imagePlanePLinesPoints.push_back(plinesVec);
					plinesVec.clear();
					std::getline(ifs, str);
				}
			}
		}

		if (str == TAG_VPTS)
		{
			std::getline(ifs, str);
			while (str != TAG_END)
			{
				ImLinePtsVec ptsVec;
				while (str != TAG_DELIM)
				{
					int x, y;
					x = std::stoi(str);
					std::getline(ifs, str);
					y = std::stoi(str);
					std::getline(ifs, str);
					ptsVec.push_back(cv::Point(x, y));
				}
				ImageDataClass::GetInstance().m_imageVertPLinesPoints.push_back(ptsVec);
				ptsVec.clear();
				std::getline(ifs, str);
				if(str == TAG_DELIM) std::getline(ifs, str);
			}
		}


		if (str == TAG_REFPTS)
		{
			std::getline(ifs, str);

			int x, y;
			x = std::stoi(str);
			std::getline(ifs, str);
			y = std::stoi(str);
			std::getline(ifs, str);
			ImageDataClass::GetInstance().m_refPoint0 = cv::Point(x,y);
			ImageDataClass::GetInstance().m_refPoint0Set = true;

			std::getline(ifs, str);

			x = std::stoi(str);
			std::getline(ifs, str);
			y = std::stoi(str);
			std::getline(ifs, str);
			ImageDataClass::GetInstance().m_refPoint1 = cv::Point(x, y);
			ImageDataClass::GetInstance().m_refPoint1Set = true;

			std::getline(ifs, str);

			ImageDataClass::GetInstance().m_calibLength = std::stod(str);


			while (str != TAG_END)
			{
				std::getline(ifs, str);
			}
		}

	}
	ifs.close();

	ImageDataClass::GetInstance().CalculatePlaneVanishingLine();
	ImageDataClass::GetInstance().CalculateVertVanishingPoint();
	ImageDataClass::GetInstance().RedrawLines();
}
