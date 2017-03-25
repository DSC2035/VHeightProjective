/*
 * InsertNewLine.cpp
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#include "definitions.h"

#ifndef _WIN32 
#include <unistd.h>
#endif // !1


#include <iostream>

#include "ImageDataClass.h"

#include "InsertNewLine.h"




InsertNewLine::InsertNewLine() 
{
}

InsertNewLine::~InsertNewLine() 
{
}


ImLinePtsVec InsertNewLine::InsertLine(int _numPointsPerLine)
{
	m_numpointsAdded = 0;
	ImageDataClass::GetInstance().m_event.Flush();

	ImLinePtsVec newPointsVector;
	//
	EventData eventData;
	std::cout << "With a mouse click define the point of line." << std::endl;
	while(true)
	{
		eventData = ImageDataClass::GetInstance().m_event.GetData();
		if(eventData.m_event == NO_EVENT)
		{
			cv::waitKey(100);
		}else
		{
			//std::cout << "in the switch statement" << std::endl;
			switch(eventData.m_event)
			{

			case(cv::EVENT_MOUSEMOVE):
				{
					m_current_point = VectorImagePoint(eventData.m_x, eventData.m_y);
					ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
					UpdateOverlayFigure(ImageDataClass::GetInstance().m_image, newPointsVector);
					ImageDataClass::GetInstance().m_imageUpdated = true;
				}
				break;

				case(cv::EVENT_LBUTTONDOWN):
				{
					/*if(!g_imagePointsArray.size())
					{
						g_imagePointsArray.push_back(std::vector<VectorImagePoint>{});
					}*/
					std::cout << "Inserting new point at: " << eventData.m_x << " " << eventData.m_y << std::endl;
					newPointsVector.push_back(VectorImagePoint(eventData.m_x, eventData.m_y));
					UpdateOverlayFigure(ImageDataClass::GetInstance().m_image, newPointsVector);
					//ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
					ImageDataClass::GetInstance().m_imageUpdated = true;
					++m_numpointsAdded;
					if (m_numpointsAdded && (m_numpointsAdded == _numPointsPerLine)) return newPointsVector;
			
				}
				break;

				case(cv::EVENT_RBUTTONDOWN): 
				{
					if (!_numPointsPerLine)
					{
						//number of points per line was not defined,
						//in case of insufficient number of points (0-1) we clear array and return empty one
						if (newPointsVector.size() < 2) newPointsVector.clear();
						return newPointsVector;
					}
					else
					{
						//insertion of line is interrupted clear array&figure and return
						if (newPointsVector.size()>0) newPointsVector.clear();
						ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
						ImageDataClass::GetInstance().m_imageUpdated = true;
						return newPointsVector;
					}
				}
				break;

			}
		}
	}
}




void InsertNewLine::UpdateOverlayFigure(cv::Mat& _imag, std::vector<VectorImagePoint>& _pointVector)
{

	if(_pointVector.size() > 0)
	{
		auto pointStart = _pointVector.begin();
		auto pointNext = pointStart;
		while (pointNext != _pointVector.end())
		{
			cv::line(_imag, *pointStart, *pointNext, cv::Scalar(255, 0, 0), 3, cv::LineTypes::LINE_4);
			pointStart = pointNext;
			pointNext++;
		}
		cv::line(_imag, _pointVector.back(), m_current_point, cv::Scalar(0, 0, 255), 3);
	}
}

