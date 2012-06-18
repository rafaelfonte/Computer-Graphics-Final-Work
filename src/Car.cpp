/*
 * Car.cpp
 *
 *  Created on: 03/06/2012
 *      Author: Rafael Fonte
 */

#include "Car.h"

Car::Car(GLdouble initPosX,GLdouble initPosY,GLdouble initPosZ,GLdouble initRotY) {
	// TODO Auto-generated constructor stub
	myCarModel = CModelAl();
	myCarModel.Init();

	position[0] = initPosX;
	position[1] = initPosY;
	position[3] = initPosZ;

	rotY = initRotY;
}

Car::~Car() {
	// TODO Auto-generated destructor stub
	myCarModel.~CModelAl();
}

void Car::draw(){
	myCarModel.Translate(posX,posY,posZ);
	myCarModel.RotateY(rotY);
	myCarModel.Draw();
}
