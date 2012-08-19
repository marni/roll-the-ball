/*
 * Origin.h
 *
 *  Created on: Aug 19, 2012
 *      Author: mariusz
 */

#ifndef ORIGIN_H_
#define ORIGIN_H_

#include "Util.h"

class Origin {

private:
	GLuint programObject;

public:
	Origin();
	virtual ~Origin();

	int init();
	void drawFrame();
};

#endif /* ORIGIN_H_ */
