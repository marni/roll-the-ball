/*
 * Drawable.h
 *
 *  Created on: Aug 27, 2012
 *      Author: mariusz
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "esUtil.h"

class Drawable {

protected:
	ESContext esContext;
	UserData userData;

public:
	Drawable();
	virtual ~Drawable();

	virtual void init(float width, float height);

	virtual void cleanup();
	virtual void drawFrame() = 0;
};

#endif /* DRAWABLE_H_ */
