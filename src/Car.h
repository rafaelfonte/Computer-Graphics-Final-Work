/*
 * Car.h
 *
 *  Created on: 03/06/2012
 *      Author: Rafael Fonte
 */
#include <GL/glut.h>
#include "ModelAl.h"
#include <cmath>

#define PI 3.14159265

#ifndef CAR_H_
#define CAR_H_

//TODO: Fine-tune this value
#define MAX_LINEAR_SPEED 1.0f
#define MAX_ROTATIONAL_SPEED 1.0f

class Car {
public:
	Car(GLdouble initPosX,GLdouble initPosY,GLdouble initPosZ,GLdouble initRotY);
	virtual ~Car();

	void pressedUp();

	void hitWall();

	void move();

	void draw();

	void pressedDown();

	void brakeCar();

	void pressedLeft();

	void pressedRight();

	void unpressedLeft();

	void unpressedRight();

	void unpressedKey();

	void initPos(GLdouble init_pos[]);

	GLdouble position_pointer[3];

	GLdouble car_direction[3];

private:
	CModelAl myCarModel;
	GLdouble position[3];
	GLdouble speed[3];
	GLdouble acceleration[3];

	GLdouble rotY;
	GLdouble rotYSpeed;
	GLdouble rotYAcceleration;

	GLdouble linearSpeed();

	bool speedingUp;

	void updatePositionPointer();

};

#endif /* CAR_H_ */
