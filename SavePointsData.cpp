/*
 * SavePointsData.cpp
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */


#include <fstream>

#include "definitions.h"

#include "ImageDataClass.h"

#include "SavePointsData.h"




SavePointsData::SavePointsData() {
	// TODO Auto-generated constructor stub

}

SavePointsData::~SavePointsData() {
	// TODO Auto-generated destructor stub
}

const char* SavePointsData::GetDescription()
{
	return "Save point data";
}

void SavePointsData::Run()
{
	//
	std::ofstream ofs;
	ofs.open(ImageDataClass::GetInstance().m_dataFile, std::ofstream::out | std::ofstream::trunc);
	if(!ofs.is_open())
	{
		std::cout << "No succesfull file opening." << std::endl;
		return;
	}

	
	ofs << TAG_DELIM << std::endl;
	ofs << TAG_IMFILE << std::endl;
	ofs << ImageDataClass::GetInstance().GetImageFileName() << std::endl;
	ofs << TAG_END << std::endl;
	

	ofs << TAG_DELIM << std::endl;
	ofs << TAG_IMPDAT << std::endl;
	
	for (auto itPLinesSets  : ImageDataClass::GetInstance().m_imagePlanePLinesPoints)
	{
		for (auto itLines : itPLinesSets)
		{
			for (auto itPts : itLines)
			{
				ofs << itPts.x << std::endl;
				ofs << itPts.y << std::endl;
			}
			ofs << TAG_DELIM << std::endl;
		}
		ofs << TAG_DELIM << std::endl;
	}
	ofs << TAG_END << std::endl;

	ofs << TAG_DELIM << std::endl;
	ofs << TAG_VPTS << std::endl;
	for (auto itLines : ImageDataClass::GetInstance().m_imageVertPLinesPoints)
	{
		for (auto itPts : itLines)
		{
			ofs << itPts.x << std::endl;
			ofs << itPts.y << std::endl;
		}
		ofs << TAG_DELIM << std::endl;
	}
	ofs << TAG_DELIM << std::endl;
	ofs << TAG_END << std::endl;
	ofs << TAG_DELIM << std::endl;

	
	ofs << TAG_DELIM << std::endl;
	ofs << TAG_REFPTS << std::endl;
	ofs << ImageDataClass::GetInstance().m_refPoint0.x << std::endl;
	ofs << ImageDataClass::GetInstance().m_refPoint0.y << std::endl;
	ofs << TAG_DELIM << std::endl;
	ofs << ImageDataClass::GetInstance().m_refPoint1.x << std::endl;
	ofs << ImageDataClass::GetInstance().m_refPoint1.y << std::endl;
	ofs << TAG_DELIM << std::endl;
	ofs << ImageDataClass::GetInstance().m_calibLength << std::endl;
	ofs << TAG_DELIM << std::endl;
	ofs << TAG_END << std::endl;
	ofs << TAG_DELIM << std::endl;

	ofs.close();
}
