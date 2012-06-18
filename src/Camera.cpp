/*
 * Camera.cpp
 *
 *  Created on: 09/06/2012
 *      Author: Rafael Fonte
 */

#include "Camera.h"


Camera::Camera(){

}
Camera::Camera(GLdouble * pos, GLdouble * ori) {
	position = pos;
	orientation = ori;
	// TODO Auto-generated constructor stub

}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}


void Camera::visualize(){
	gluLookAt(position[0],position[1],position[2],
			position[0]+orientation[0],position[1]+orientation[1],position[2]+orientation[2],
			0.0,1.0,0.0);

}
