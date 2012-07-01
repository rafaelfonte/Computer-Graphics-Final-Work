/*
 * Camera.h
 *
 *  Created on: 09/06/2012
 *      Author: Rafael Fonte
 */
 #include <windows.h>
#include <GL/glu.h>

#ifndef CAMERA_H_
#define CAMERA_H_

class Camera {
public:
	Camera();
	Camera(GLdouble * pos, GLdouble * ori);
	virtual ~Camera();

	void visualize();
private:
	GLdouble * position;
	GLdouble * orientation;
};

#endif /* CAMERA_H_ */
