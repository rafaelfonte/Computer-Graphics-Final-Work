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
	turning = false;

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

	if(speedingUp){
		GLdouble lin_speed = linearSpeed();
		for(int i = 0; i < 3; i++)
		{
			speed[i] += acceleration[i];
		}
		if(turning)
		{
			if(going_forward){
				speed[0] = lin_speed*sin(rotY*PI/180.0);
				speed[2] = -lin_speed*cos(rotY*PI/180.0);
			}
			if(going_back){
				speed[0] = -lin_speed*sin(rotY*PI/180.0);
				speed[2] = lin_speed*cos(rotY*PI/180.0);
			}
		}
		if(lin_speed > MAX_LINEAR_SPEED){
			for(int k = 0; k < 3; k++){
				speed[k] = speed[k]*MAX_LINEAR_SPEED/lin_speed;
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
			if(i != 1){
				if((speed[i] < 0.01 && speed[i] >= 0.0) || (speed[i] > -0.01  && speed[i] <= 0.0))
				{
					speed[i] = 0;
				}
				else
				{
					if(speed[i] > 0)
						speed[i] -= 0.01;
					else
						speed[i] += 0.01;
				}
				position[i] += speed[i];
			}
		}
	}

	rotY += rotYSpeed;
	updatePositionPointer();
}

void Car::pressedUp(){

	going_forward = true;
	acceleration[0] = 0.01*sin(rotY*PI/180);
	acceleration[2] = -0.01*cos(rotY*PI/180);

	speedingUp = true;

}

void Car::pressedDown(){

	going_back = true;
	acceleration[0] = -0.01*sin(rotY*PI/180);
	acceleration[2] = 0.01*cos(rotY*PI/180);

	speedingUp = true;
}

void Car::brakeCar(){

	GLdouble lin_Speed = linearSpeed();

	if(lin_Speed > 0.01){
		for(int i = 0; i < 3; i++){
			if(i != 1){
				if(speed[i] > 0)
					speed[i] -= 0.001;
				else
					speed[i] += 0.001;

				acceleration[i] = 0.0f;
			}
		}
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
	turning = true;
	rotYSpeed = -10*linearSpeed();
}

void Car::unpressedLeft(){
	turning = false;
	rotYSpeed = 0.0f;
}

void Car::pressedRight(){
	turning = true;
	rotYSpeed = 10*linearSpeed();
}

void Car::unpressedRight(){
	unpressedLeft();
}

void Car::unpressedKey(){

	going_back = false;
	going_forward = false;
	for(int i = 0; i < 3; i++){
		acceleration[i] = 0;
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

