/*
 * Origin.h
 *
 *  Created on: Aug 19, 2012
 *      Author: mariusz
 */

#ifndef ORIGIN_H_
#define ORIGIN_H_

#include "esUtil.h"
#include "Util.h"

class Origin {

private:
	ESContext esContext;
	UserData  userData;

public:
	Origin();
	virtual ~Origin();
	void cleanup();

	int init();
	void drawFrame();
};

#endif /* ORIGIN_H_ */
