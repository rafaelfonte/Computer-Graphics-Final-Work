/*
 * Car.h
 *
 *  Created on: 03/06/2012
 *      Author: Rafael Fonte
 */
#include <GL/glut.h>
#include "ModelAl.h"

#ifndef CAR_H_
#define CAR_H_

class Car {
public:
	Car(GLdouble initPosX,GLdouble initPosY,GLdouble initPosZ,GLdouble initRotY);
	virtual ~Car();

	void draw();
private:
	CModelAl myCarModel;
	GLdouble position[3];

	GLdouble rotY;

};

#endif /* CAR_H_ */
