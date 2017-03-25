/*
 * OpenFigure.cpp
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#include <iostream>
#include <sstream>

#include "definitions.h"

#include "ImageDataClass.h"

#include "OpenFigure.h"


OpenFigure::OpenFigure() {
	// TODO Auto-generated constructor stub

}

OpenFigure::~OpenFigure() {
	// TODO Auto-generated destructor stub
}

const char* OpenFigure::GetDescription()
{
	return "Open Figure";
}

void OpenFigure::Run()
{
	while(true)
	{
		std::cout << std::endl;
		std::cout << "Insert path and filename(q - quit): ";
		std::string str;

		InpStream::GetInpStream() >> str;
		if((str == "q")||(str == "Q")) return;
		ImageDataClass::GetInstance().OpenFigure(str);

		return;
	}
}


