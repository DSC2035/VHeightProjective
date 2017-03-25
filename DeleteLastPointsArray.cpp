/*
 * DeleteLastPointsArray.cpp
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#include "ImageDataClass.h"

#include "DeleteLastPointsArray.h"


DeleteLastPointsArray::DeleteLastPointsArray() {
	// TODO Auto-generated constructor stub

}

DeleteLastPointsArray::~DeleteLastPointsArray() {
	// TODO Auto-generated destructor stub
}

const char* DeleteLastPointsArray::GetDescription()
{
	return "Delete last set of parallel lines on plane";
}

void DeleteLastPointsArray::Run()
{
	ImageDataClass::GetInstance().m_imagePlanePLinesPoints.pop_back();

}
