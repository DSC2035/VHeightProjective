/*
 * DeleteLastPointsArray.h
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#ifndef DELETELASTPOINTSARRAY_H_
#define DELETELASTPOINTSARRAY_H_

#include "FunctorClassI.h"

class DeleteLastPointsArray: public FunctorClassI {
public:
	DeleteLastPointsArray();
	virtual ~DeleteLastPointsArray();

	virtual const char* GetDescription();
	virtual void Run();
};

#endif /* DELETELASTPOINTSARRAY_H_ */
