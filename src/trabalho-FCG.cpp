/**
Implementa a movimenta��o simples de uma camera em primeira pessoa para um personagem que anda
sobre um plano.
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <gl/glut.h>
#include "Map.h"
#include "ModelAl.h"
#include "Camera.h"
#include "Car.h"

#define PI 3.14159265

// sound stuff
#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

void mainInit();
void initLight();
void createGLUI();
void mainRender();
void onMouseButton(int button, int state, int x, int y);
void onMouseMove(int x, int y);
void onKeyDown(unsigned char key, int x, int y);
void onKeyUp(unsigned char key, int x, int y);
void onGLUIEvent(int id);
void onWindowReshape(int x, int y);
void mainIdle();
int main(int argc, char **argv);
void setWindow();
void setViewport(GLint left, GLint right, GLint bottom, GLint top);
void updateState();
void updateCam();

/**
Screen dimensions
*/
int windowWidth = 600;
int windowHeight = 480;
//int windowWidth = 1024;
//int windowHeight = 768;

/**
Screen position
*/
int windowXPos = 10;
int windowYPos = 15;

int mainWindowId = 0;

double xOffset = -1.9;
double yOffset = -1.3;
int mouseLastX = 0;
int mouseLastY = 0;

float roty = 0.0f;
float rotx = 0.0f;

bool rightPressed = false;
bool leftPressed = false;
bool upPressed = false;
bool downPressed = false;

bool spacePressed = false;

float speedX = 0.0f;
float speedY = 0.0f;
float speedZ = 0.0f;

float posX = 0.0f;
float posY = 0.0f;
float posZ = 2.0f;

float backgrundColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
Map map;


//GLdouble car_camera_direction[3];

Car * playerCar = new Car(0.0f,0.3f,2.0f,180.0f);
Camera * myCam = new Camera(playerCar->position_pointer,playerCar->car_direction);

CModelAl modelPlayerCar;
CModelAl modelOpponentCar;

/*
variavel auxiliar pra dar varia��o na altura do ponto de vista ao andar.
*/
float headPosAux = 0.0f;

float maxSpeed = 0.25f;

bool crouched = false;
bool running = false;
bool jumping = false;
float jumpSpeed = 0.06;
float gravity = 0.004;
float heightLimit = 0.2;
float posYOffset = 0.2;

void setWindow() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight,0.1f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posX,posY + posYOffset + 0.025 * std::abs(sin(headPosAux*PI/180)),posZ,
		posX + sin(roty*PI/180),posY + posYOffset + 0.025 * std::abs(sin(headPosAux*PI/180)) + cos(rotx*PI/180),posZ -cos(roty*PI/180),
		0.0,1.0,0.0);
}

float calcDistance(float p1[], float p2[]){

	float x = p1[0] - p2[0];
	float y = p1[1] - p2[1];
	float z = p1[2] - p2[2];
	return sqrt(x*x + y*y + z*z);
}

/**
Atualiza a posi��o e orienta��o da camera
*/


float lightPos = 0.0;
int count = 0;

void updateCam() {

	float playerPos[] = {(float)playerCar->position_pointer[0], 0.0,(float) playerCar->position_pointer[2]};
	float enemyPos[] = {(float)map.opponentCar->x,0.0,(float)map.opponentCar->z};


	if(calcDistance(playerPos,enemyPos) < 1.0){
		printf("GAME OVER");
		exit(0);
	}


	myCam->visualize();


}

void initLight() {
  glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light_ambient[] = {backgrundColor[0], backgrundColor[1], backgrundColor[2], backgrundColor[3]};
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[] = {10.0, 10.0, 10.0, 0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
}

void setViewport(GLint left, GLint right, GLint bottom, GLint top) {
	glViewport(left, bottom, right - left, top - bottom);
}


/**
Initialize
*/
void mainInit() {
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,0.0f);
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);

	// habilita o z-buffer
	glEnable(GL_DEPTH_TEST);

  ///////////////////////////////////////////////////////MAPPPPP
  map.setMiniMapTexture("..\\res\\map.bmp");
  map.setSkyTexture("..\\res\\sky.bmp");
  map.setBackgroundTexture("..\\res\\background.bmp");
  map.setFloorTexture("..\\res\\road.bmp");
  map.setWallTexture("..\\res\\wall.bmp");
  map.setCeilingTexture("..\\res\\celling.bmp");
  map.populateLists();
  map.printList(map.buildingList);
  // habilita remocao de faces ocultas

  	modelOpponentCar = CModelAl();
  	//modelPlayerCar = CModelAl();

  	GLdouble position[] = {map.playerCar->x,0.3f,map.playerCar->z};
  	playerCar->initPos(position);
  	//posX = map.playerCar->x;
  	//posZ = map.playerCar->z;

    glFrontFace(GL_CCW);
	modelOpponentCar.Init();
	//modelPlayerCar.Init();

	initLight();

	printf("w - andar \n");
	printf("s - ir pra tras \n");
	printf("mouse - direcao \n");
	printf("r - correr \n");
	printf("c - abaixar \n");
	printf("espaco - pular \n");

}

void renderModels(){

  //glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
	map.renderMap();

	glEnable(GL_CULL_FACE);
	modelOpponentCar.Translate(map.opponentCar->x, 0.3f, map.opponentCar->z);
	modelOpponentCar.Draw();

	playerCar->draw();
	glDisable(GL_CULL_FACE);
}

void printMap(){
	  map.printMiniMap(windowWidth,windowHeight);

	  renderModels();

	  glMatrixMode(GL_PROJECTION);

	  glPopMatrix();

	  glViewport(0,0,windowWidth,windowHeight);

	  glMatrixMode(GL_MODELVIEW);
}

void renderScene() {

	glClearColor(backgrundColor[0],backgrundColor[1],backgrundColor[2],backgrundColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // limpar o depth buffer


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCam();

	renderModels();

	printMap();
	//////////////////////////////////////////////////mappppppppppppppppppppppppppppp
}

void updateState() {

	float posVector[3];
	posVector[0] = (float)playerCar->position_pointer[0];
	posVector[1] = (float)playerCar->position_pointer[1];
	posVector[2] = (float)playerCar->position_pointer[2];

	if(map.hitWall(posVector))
	{
		playerCar->hitWall();
	}

}

/**
Render scene
*/
void mainRender() {
	playerCar->move();
	updateState();
	renderScene();
	glFlush();
	glutPostRedisplay();
	Sleep(20);
}

/**
Handles events from the mouse right button menu
*/
void mainHandleMouseRightButtonMenuEvent(int option) {
	switch (option) {
		case 1 :
			exit(0);
			break;
		default:
			break;
	}
}

/**
Mouse button event handler
*/
void onMouseButton(int button, int state, int x, int y) {
	//printf("onMouseButton button: %d \n", button);
	glutPostRedisplay();
}

/**
Mouse move while button pressed event handler
*/
void onMouseMove(int x, int y) {

	/*mouseLastX = x;
	mouseLastY = y;*/

	glutPostRedisplay();
}

/**
Mouse move with no button pressed event handler
*/
const float windowLowerRelLimit = 0.2f;

void onMousePassiveMove(int x, int y) {

	if(x < windowLowerRelLimit*windowWidth || x > (1.0 - windowLowerRelLimit)*windowWidth || y < windowLowerRelLimit*windowHeight || y > (1.0 - windowLowerRelLimit)*windowHeight)
	{
		if(x < windowLowerRelLimit*windowWidth || x > (1.0 - windowLowerRelLimit)*windowWidth)
			glutWarpPointer(windowWidth/2,windowHeight/2);

		if(y < windowLowerRelLimit*windowHeight || y > (1.0 - windowLowerRelLimit)*windowHeight)
			glutWarpPointer(windowWidth/2,windowHeight/2);

		mouseLastX = windowWidth/2;
		mouseLastY = windowHeight/2;
	}
	else
	{
		roty += x - mouseLastX;

		rotx += y - mouseLastY;

		mouseLastX = x;
		mouseLastY = y;
	}

}

/**
Key press event handler
*/
void onKeyDown(unsigned char key, int x, int y) {
	//printf("%d \n", key);
	switch (key) {
		case 32: //space
			playerCar->brakeCar();
			if (!spacePressed && !jumping) {
				jumping = true;
				speedY = jumpSpeed;
			}
			spacePressed = true;
			break;
		case 119: //w
			playerCar->pressedUp();
			upPressed = true;
			break;
		case 115: //s
			playerCar->pressedDown();
			downPressed = true;
			break;
		case 97: //a
			playerCar->pressedLeft();
			playerCar->pressedUp();
			leftPressed = true;
			break;
		case 100: //d
			playerCar->pressedRight();
			playerCar->pressedUp();
			rightPressed = true;
			break;
		case 99: //c
			crouched = true;
			break;
		case 114: //r
			running = true;
			break;
		default:
			break;
	}

	//glutPostRedisplay();
}

/**
Key release event handler
*/
void onKeyUp(unsigned char key, int x, int y) {
	switch (key) {
		case 32: //space
			spacePressed = false;
			break;
		case 119: //w
			playerCar->unpressedKey();
			upPressed = false;
			break;
		case 115: //s
			playerCar->unpressedKey();
			downPressed = false;
			break;
		case 97: //a
			playerCar->unpressedLeft();
			playerCar->unpressedKey();
			leftPressed = false;
			break;
		case 100: //d
			playerCar->unpressedRight();
			playerCar->unpressedKey();
			rightPressed = false;
			break;
		case 99: //c
			crouched = false;
			break;
		case 114: //r
			running = false;
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}

	//glutPostRedisplay();
}

void onWindowReshape(int x, int y) {
	windowWidth = x;
	windowHeight = y;
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);
}

/**
Glut idle funtion
*/
void mainIdle() {
	/**
	Set the active window before send an glutPostRedisplay call
	so it wont be accidently sent to the glui window
	*/
	glutSetWindow(mainWindowId);
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(windowXPos,windowYPos);

	/**
	Store main window id so that glui can send it redisplay events
	*/
	mainWindowId = glutCreateWindow("Trabalho Final");

	glutDisplayFunc(mainRender);

	glutReshapeFunc(onWindowReshape);

	/**
	Register mouse events handlers
	*/
	glutMouseFunc(onMouseButton);
	glutMotionFunc(onMouseMove);
	glutPassiveMotionFunc(onMousePassiveMove);

	/**
	Register keyboard events handlers
	*/
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);

	//Apagando o cursor
	glutSetCursor(GLUT_CURSOR_NONE);

	mainInit();

	glutMainLoop();

    return 0;
}
