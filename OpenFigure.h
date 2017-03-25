/*
 * OpenFigure.h
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#ifndef OPENFIGURE_H_
#define OPENFIGURE_H_

#include "FunctorClassI.h"

class OpenFigure: public FunctorClassI {
public:
	OpenFigure();
	virtual ~OpenFigure();

	virtual const char* GetDescription();
	virtual void Run();
};


#endif /* OPENFIGURE_H_ */
