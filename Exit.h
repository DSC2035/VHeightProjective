/*
 * Exit.h
 *
 *  Created on: 17.02.2017
 *      Author: test-dev
 */

#ifndef EXIT_H_
#define EXIT_H_

#include "FunctorClassI.h"

class Exit: public FunctorClassI {
public:
	Exit();
	virtual ~Exit();

	virtual const char* GetDescription();
	virtual void Run();
};

#endif /* EXIT_H_ */
