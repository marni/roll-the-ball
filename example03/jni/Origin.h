/*
 * Origin.h
 *
 *  Created on: Aug 19, 2012
 *      Author: mariusz
 */

#ifndef ORIGIN_H_
#define ORIGIN_H_

#include "esUtil.h"
#include "Drawable.h"

class Origin : Drawable {

public:
	Origin();
	virtual ~Origin();

	virtual void init(float width, float height);
	virtual void drawFrame();
};

#endif /* ORIGIN_H_ */
