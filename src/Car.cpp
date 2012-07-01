/*
 * Car.cpp
 *
 *  Created on: 03/06/2012
 *      Author: Rafael Fonte
 */

#include "Car.h"
#include <cmath>

Car::Car(GLdouble initPosX,GLdouble initPosY,GLdouble initPosZ,GLdouble initRotY) {
	// TODO Auto-generated constructor stub
	myCarModel = CModelAl();
	myCarModel.Init();

	position[0] = initPosX;
	position[1] = initPosY;
	position[2] = initPosZ;

	for(int i = 0; i < 3; i++){
		speed[i] = 0.0;
		acceleration[i] = 0.0;
	}

	rotY = initRotY;
	rotYSpeed = 0.0;

	updatePositionPointer();

	speedingUp = false;

}

Car::~Car() {
	myCarModel.~CModelAl();
}

void Car::draw(){
	myCarModel.Translate(position[0],0.3f,position[2]);
	myCarModel.resetAngle();
	myCarModel.RotateY(PI + (-(rotY*PI)/180.0f));
	myCarModel.Draw();
}

void Car::hitWall(){

	//TODO: Animation for the "bump"...
	//STOPPING the car
	for(int i = 0; i < 3; i++){
		speed[i] = 0;
		acceleration[i] = 0.0;
	}
	rotYSpeed = 0.0;
}

void Car::move(){

	if(speedingUp == true){
		for(int i = 0; i < 3; i++)
		{
			speed[i] += acceleration[i];
		}

		GLdouble lin_speed = linearSpeed();
		if(lin_speed > MAX_LINEAR_SPEED){
			for(int k = 0; k < 3; k++){
				speed[k] = MAX_LINEAR_SPEED/lin_speed;
			}
			speed[1] = 0;
		}
		for(int j = 0; j < 3; j++)
		{
			position[j] += speed[j];
		}
	}
	else
	{
		for(int i = 0; i < 3; i++)
		{
			if(speed[i] < 0.01 || speed[i] > -0.01)
			{
				speed[i] = 0;
			}
			else
			{
				speed[i] += acceleration[i];
			}
			position[i] += speed[i];
		}
	}

	rotY += rotYSpeed;
	updatePositionPointer();
}

void Car::pressedUp(){

	printf("%f\n", rotY);
	acceleration[0] = 0.01*sin(rotY*PI/180);
	acceleration[2] = -0.01*cos(rotY*PI/180);

	speedingUp = true;

	//printf("%f, %f;   %f, %f\n",position[0],position[2],acceleration[0],acceleration[2]);

}

void Car::pressedDown(){

	acceleration[0] = -0.01*sin(rotY*PI/180);
	acceleration[2] = 0.01*cos(rotY*PI/180);

	speedingUp = true;
}

void Car::brakeCar(){
	if(speed[0] >= 0.0 && speed[2] >= 0.0){
		acceleration[0] = -cos(rotY);
		acceleration[2] = -sin(rotY);
	}
	else
	{
		for(int i = 0; i < 3; i++){
			speed[i] = 0.0f;
			acceleration[i] = 0.0f;
		}
	}
}

GLdouble Car::linearSpeed(){
	GLdouble x = speed[0]*speed[0];
	GLdouble y = speed[1]*speed[1];
	GLdouble z = speed[2]*speed[2];

	return sqrt(x+y+z);
}
void Car::pressedLeft(){
	rotYSpeed = -2*linearSpeed();
}

void Car::unpressedLeft(){
	rotYSpeed = 0.0f;
}

void Car::pressedRight(){
	rotYSpeed = 2*linearSpeed();
}

void Car::unpressedRight(){
	unpressedLeft();
}

void Car::unpressedKey(){

	for(int i = 0; i < 3; i++){
		acceleration[i] = -acceleration[i];
	}
	speedingUp = false;
}

void Car::updatePositionPointer(){
	for(int i = 0; i < 3; i++){
		position_pointer[i] = position[i];
	}
	position_pointer[1] += 1.0f;

	car_direction[0] = 5*sin(rotY*PI/180.0f);
	car_direction[1] = -0.2 - PI/180.0f;
	car_direction[2] = 5*(-cos(rotY*PI/180.0f));
	//printf("POS={%f,%f,%f} DIR={%f,%f,%f} %f\n", position_pointer[0],position_pointer[1],position_pointer[2],
	//		car_direction[0],car_direction[1],car_direction[2], rotY);
}


void Car::initPos(GLdouble init_pos[]){
	for(int i = 0; i < 3; i++){
		position[i] = init_pos[i];
	}
}

