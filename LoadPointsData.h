/*
 * LoadPointsData.h
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#ifndef LOADPOINTSDATA_H_
#define LOADPOINTSDATA_H_

#include "FunctorClassI.h"

class LoadPointsData: public FunctorClassI {
public:
	LoadPointsData();
	virtual ~LoadPointsData();

	virtual const char* GetDescription();
	virtual void Run();
};

#endif /* LOADPOINTSDATA_H_ */
