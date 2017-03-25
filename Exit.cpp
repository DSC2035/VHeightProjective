/*
 * Exit.cpp
 *
 *  Created on: 17.02.2017
 *      Author: test-dev
 */

#include "Exit.h"

extern bool g_finished;

Exit::Exit() {
	// TODO Auto-generated constructor stub

}

Exit::~Exit() {
	// TODO Auto-generated destructor stub
}

const char* Exit::GetDescription()
{
	return "Exit";
}

void Exit::Run()
{
	g_finished = true;
}
