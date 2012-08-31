/*
 * Origin.h
 *
 *  Created on: Aug 19, 2012
 *      Author: mariusz
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "esUtil.h"
#include "Drawable.h"

class Sphere : public Drawable {

public:
	Sphere();
	virtual ~Sphere();

	virtual void init(float width, float height);
	virtual void drawFrame(ESMatrix *);
};

#endif /* SPHERE_H_ */
