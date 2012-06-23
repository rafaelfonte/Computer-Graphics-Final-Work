/**
Implementa a movimentação simples de uma camera em primeira pessoa para um personagem que anda
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
//int windowWidth = 600;
//int windowHeight = 480;
int windowWidth = 1024;
int windowHeight = 768;

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

GLdouble car_camera_position[3];
GLdouble car_camera_direction[3];
Camera * myCam = new Camera(car_camera_position,car_camera_direction);

float lastRotY = roty;


CModelAl modelPlayerCar;
CModelAl modelOpponentCar;

/*
variavel auxiliar pra dar variação na altura do ponto de vista ao andar.
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

/**
Atualiza a posição e orientação da camera
*/

float lightPos = 0.0;
int count = 0;

void updateCam() {

	//Atualizando a posição das fontes de luz
	GLfloat light_position[] = {0.0,0.0,0.0,1.0};


	light_position[0] = posX;
	light_position[1] = 10.0f;//10*sin(lightPos*PI/180);
	light_position[2] = posZ;

	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position);
	lightPos+=10.0;
	if(lightPos >= 360.0)
		lightPos = 0.0;

	count++;
	if((count % 30) == 0){
		printf("%f\n", rotx);
	}

	//Limiting camera rotation around the horizontal axis, made by mouse movement.
	if(rotx < -240.0)
		rotx = -240.0;


	car_camera_position[0] = posX;
	car_camera_position[1] = posY + 1.0;
	car_camera_position[2] = posZ;

	car_camera_direction[0] = 5*sin(roty*PI/180);
	car_camera_direction[1] = -0.2 - rotx/180;
	car_camera_direction[2] = 5*(-cos(roty*PI/180));


	myCam->visualize();

	//gluLookAt(posX,posY + posYOffset + 0.025 * std::abs(sin(headPosAux*PI/180)),posZ,
	//	posX + sin(roty*PI/180),posY + posYOffset + 0.025 * std::abs(sin(headPosAux*PI/180)) - rotx/180,posZ -cos(roty*PI/180),
	//	0.0,1.0,0.0);


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
  map.setCellingTexture("..\\res\\celling.bmp");
  map.populateLists();
  map.printList(map.buildingList);
  // habilita remocao de faces ocultas

  	modelOpponentCar = CModelAl();
  	modelPlayerCar = CModelAl();

  	posX = map.playerCar->x;
  	posZ = map.playerCar->z;

    glFrontFace(GL_CCW);
	modelOpponentCar.Init();
	modelPlayerCar.Init();

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
	modelPlayerCar.Translate(posX,0.3f,posZ);//map.playerCar->x, 0.3f, map.playerCar->z);
	//Rotacionando o carro de acordo com a visao.
	modelPlayerCar.RotateY(PI + (-((roty - lastRotY)*PI))/180.0);
	lastRotY = roty;
	modelPlayerCar.Draw();
	glDisable(GL_CULL_FACE);
}

void printMap(){
	  glViewport(0,windowHeight - windowHeight/3,windowWidth/3,windowHeight/3);

	  glMatrixMode(GL_PROJECTION);
	  glPushMatrix();


	  glLoadIdentity();

	  glOrtho( 0.0,map.miniMap.info->bmiHeader.biWidth*map.scale,  0.0, map.miniMap.info->bmiHeader.biHeight*map.scale, 0.1, 100.0);


	  glMatrixMode(GL_MODELVIEW);

	  glLoadIdentity();

	  gluLookAt(0.0,14.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

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
  //printf("x = %f, z = %f\n", posX, posZ);

	updateCam();

	renderModels();

	printMap();
	//////////////////////////////////////////////////mappppppppppppppppppppppppppppp
}
/*
 *
 * TODO:
 * Fazer a lógica de colisão com o inimigo!
 * NÃO ESQUECER: cuidar com o type casting!!!!
 *
 * */

#define buildingWidth 10.0f
#define halfBuildingWidth buildingWidth/2.0

bool hitsWall(float position[]){

	CRD * listRunner = map.buildingList;
	while(listRunner != NULL)
	{
		if(((listRunner->x - halfBuildingWidth) < position[0]) &&
		   ((listRunner->x + halfBuildingWidth) > position[0]) &&
		   ((listRunner->z - halfBuildingWidth) < position[2]) &&
		   ((listRunner->z + halfBuildingWidth) > position[2]))
			return true;
		listRunner = listRunner->next;
	}


	///)

	if(!((0.0 < position[0]) &&
		 (((float)map.miniMap.info->bmiHeader.biWidth*(float)map.scale) > position[0]) &&
		 (0.0 < position[2]) &&
	     (((float)map.miniMap.info->bmiHeader.biHeight*(float)map.scale) > position[2])))
		return true;
	return false;
}

void updateState() {


	float posVector[3];
	posVector[0] = posX;
	posVector[1] = posY;
	posVector[2] = posZ;

	if (upPressed || downPressed) {

		if (running) {
			speedX = 0.05 * sin(roty*PI/180) * 20;
			speedZ = -0.05 * cos(roty*PI/180) * 20;
		} else {
			speedX = 0.05 * sin(roty*PI/180);
			speedZ = -0.05 * cos(roty*PI/180);
		}

		// efeito de "sobe e desce" ao andar
		headPosAux += 8.5f;
		if (headPosAux > 180.0f) {
			headPosAux = 0.0f;
		}

        if (upPressed) {
        	posVector[0] += speedX;
        	posVector[2] += speedZ;
        } else {
        	posVector[0] -= speedX;
        	posVector[2] -= speedZ;
        }

	} else {
		// parou de andar, para com o efeito de "sobe e desce"
		headPosAux = fmod(headPosAux, 90) - 1 * headPosAux / 90;
		headPosAux -= 4.0f;
		if (headPosAux < 0.0f) {
			headPosAux = 0.0f;
		}
	}

	posVector[1] += speedY;
	if (posVector[1] < heightLimit) {
		posVector[1] = heightLimit;
		speedY = 0.0f;
		jumping = false;
	} else {
		speedY -= gravity;
	}

	if (crouched) {
		posYOffset -= 0.01;
		if (posYOffset < 0.1) {
			posYOffset = 0.1;
		}
	} else {
		posYOffset += 0.01;
		if (posYOffset > 0.2) {
			posYOffset = 0.2;
		}
	}

	if(!hitsWall(posVector))
	{
		posX = posVector[0];
		posY = posVector[1];
		posZ = posVector[2];
	}

}

/**
Render scene
*/
void mainRender() {
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
			if (!spacePressed && !jumping) {
				jumping = true;
				speedY = jumpSpeed;
			}
			spacePressed = true;
			break;
		case 119: //w
      upPressed = true;
			break;
		case 115: //s
			downPressed = true;
			break;
		case 97: //a
			leftPressed = true;
			break;
		case 100: //d
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
			upPressed = false;
			break;
		case 115: //s
			downPressed = false;
			break;
		case 97: //a
			leftPressed = false;
			break;
		case 100: //d
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
