// HomographieProj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
* main.cpp
*
*  Created on: 15.02.2017
*      Author: test-dev
*/


#include <iostream>
#include <memory>

//#include <functional>
//#include <regex>
//*/

#include <iostream>
#include <thread>
#include <sstream>

#include "definitions.h"
#include "ImageDataClass.h"

#include "FunctorClassI.h"
#include "OpenFigure.h"
#include "AddPLinesSet.h"
#include "SavePointsData.h"
#include "LoadPointsData.h"
#include "InsertNewLine.h"
#include "DeleteLastPointsArray.h"
#include "CalculateCamPos.h"
#include "CalibrateCamera.h"
#include "CalibrateScene.h"
#include "MeasureHeight.h"
#include "CalculateVanishingLine.h"
#include "AddVerticalPLinesSet.h"

#include "Exit.h"

#define VectorReal cv::Vec3d


bool g_finished = false;

void ImageShowFunc();
void CallBackFunc(int event, int x, int y, int flags, void* userdata);

std::stringstream InpStream::m_stream;



std::vector<std::unique_ptr<FunctorClassI>> CommandsVec;  //vector of

int main(int _num_args, char* _args[])
{



	CommandsVec.emplace_back(new OpenFigure);
	CommandsVec.emplace_back(new LoadPointsData);
	CommandsVec.emplace_back(new AddPLinesSet);
	CommandsVec.emplace_back(new DeleteLastPointsArray);

	//CommandsVec.emplace_back(new CalibrateCamera);
	//CommandsVec.emplace_back(new CalculateCamPos);
	//CommandsVec.emplace_back(new CalculateVanishingLine);

	CommandsVec.emplace_back(new AddVerticalPLinesSet);
	CommandsVec.emplace_back(new CalibrateScene);
	CommandsVec.emplace_back(new MeasureHeight);
	CommandsVec.emplace_back(new SavePointsData);

	CommandsVec.emplace_back(new Exit);

	std::thread imagethread(ImageShowFunc);

	InpStream::m_stream.clear();
//	InpStream::m_stream << "0 F:/Figures2/figure1.jpg 2";
//	InpStream::m_stream << "0 F:/Vankovka_4.jpg 2";
	InpStream::m_stream << "1 6";


	while (!g_finished)
	{
		std::cout << std::endl;
		int i = 0;
		for (auto&& it : CommandsVec)
		{
			std::cout << i << "	:" << it->GetDescription() << std::endl;
			i++;
		}
		std::cout << "insert command: ";
		int num;
		InpStream::GetInpStream() >> num;
		std::cout << std::endl  << "Command: " << num << std::endl << std::endl;

		if ((num<0) || (num >= CommandsVec.size())) continue;
		CommandsVec.at(num)->Run();
	}

	ImageDataClass::GetInstance().m_imageUpdated = true;
	if (imagethread.joinable()) imagethread.join();

	return 0;
}

void ImageShowFunc()
{
	cv::namedWindow(ImageDataClass::GetInstance().m_openCVWindowName, cv::WINDOW_AUTOSIZE);// Create a window for display.
	cv::setMouseCallback(ImageDataClass::GetInstance().m_openCVWindowName, CallBackFunc, NULL);

	while (!g_finished)
	{

		while (!ImageDataClass::GetInstance().m_imageUpdated)
		{
			cv::waitKey(50);
		}
		if((ImageDataClass::GetInstance().m_image.cols>0)||(ImageDataClass::GetInstance().m_image.rows>0))	imshow(ImageDataClass::GetInstance().m_openCVWindowName, ImageDataClass::GetInstance().m_image);                   // Show our image inside it.
		ImageDataClass::GetInstance().m_imageUpdated = false;
		//cv::waitKey(1000);
	}
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	ImageDataClass::GetInstance().m_event.SetData(event, x, y, flags, userdata);
}