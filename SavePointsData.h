/*
 * SavePointsData.h
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#ifndef SAVEPOINTSDATA_H_
#define SAVEPOINTSDATA_H_

#include "FunctorClassI.h"

class SavePointsData: public FunctorClassI {
public:
	SavePointsData();
	virtual ~SavePointsData();

	virtual const char* GetDescription();
	virtual void Run();
};

#endif /* SAVEPOINTSDATA_H_ */
