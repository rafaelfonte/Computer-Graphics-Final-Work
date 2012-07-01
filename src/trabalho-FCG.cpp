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
#include "Car.h"

#include <al/alut.h>


#include <time.h>  //Cálculos de tempo

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib")

#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

ALfloat listenerPos[]={0.0,0.0,4.0};
ALfloat listenerVel[]={0.0,0.0,0.0};
ALfloat listenerOri[]={0.0,0.0,1.0,
						0.0,1.0,0.0};

ALfloat source0Pos[]={ -2.0, 0.0, 0.0};
ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

ALuint  buffer[NUM_BUFFERS];
ALuint  source[NUM_SOURCES];
ALuint  environment[NUM_ENVIRONMENTS];
ALsizei size,freq;
ALenum  format;
ALvoid  *data;

GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;//GLUT_BITMAP_TIMES_ROMAN_24;

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------

#define MAX_MINUTES 0
#define MAX_SECONDS 15

void printw (float x, float y, float z, char * string)
{

    glRasterPos2f (x, y);

    for (int i = 0; string[i] != '\0'; i++)
    	glutBitmapCharacter(font_style, string[i]);
}

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
float opponentSpeed = 0.5f;
int opponentDirection = 0; // Sempre começa pela esquerda
/**
 * Controla a direção que o oponente se movimentava (importante para as curvas e posicionamento do carro)
 * 0: para a esquerda +Z
 * 1: para a direita -Z
 * 2: para cima +X
 * 3: para baixo -X
 */

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

/*
 * TIME VARIABLES
 * */
clock_t t_start,t_current;


void initSound() {

	printf("Initializing OpenAl \n");

	// Init openAL
	alutInit(0, NULL);

	alGetError(); // clear any error messages

    // Generate buffers, or else no sound will happen!
    alGenBuffers(NUM_BUFFERS, buffer);

    if(alGetError() != AL_NO_ERROR)
    {
        printf("- Error creating buffers !!\n");
        exit(1);
    }
    else
    {
        printf("init() - No errors yet.\n");
    }

	alutLoadWAVFile("..\\res\\Full On The Mouth - Another (Road Rash 64 Soundtrack) - YouTube.wav",&format,&data,&size,&freq,(char*)false);
    alBufferData(buffer[0],format,data,size,freq);

	alGetError(); /* clear error */
    alGenSources(NUM_SOURCES, source);

    if(alGetError() != AL_NO_ERROR)
    {
        printf("- Error creating sources !!\n");
        exit(2);
    }
    else
    {
        printf("init - no errors after alGenSources\n");
    }

	listenerPos[0] = posX;
	listenerPos[1] = posY;
	listenerPos[2] = posZ;

	source0Pos[0] = posX;
	source0Pos[1] = posY;
	source0Pos[2] = posZ;

	alListenerfv(AL_POSITION,listenerPos);
    alListenerfv(AL_VELOCITY,listenerVel);
    alListenerfv(AL_ORIENTATION,listenerOri);

	alSourcef(source[0], AL_PITCH, 1.0f);
    alSourcef(source[0], AL_GAIN, 1.0f);
    alSourcefv(source[0], AL_POSITION, source0Pos);
    alSourcefv(source[0], AL_VELOCITY, source0Vel);
    alSourcei(source[0], AL_BUFFER,buffer[0]);
    alSourcei(source[0], AL_LOOPING, AL_TRUE);

	printf("Sound ok! \n\n");
}


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
Atualiza a posição e orientação da camera
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

	srand(time(NULL));
  ///////////////////////////////////////////////////////MAPPPPP
  map.setMiniMapTexture("..\\res\\map.bmp");
  map.setSkyTexture("..\\res\\sky.bmp");
  map.setBackgroundTexture("..\\res\\background.bmp");
  map.setFloorTexture("..\\res\\road.bmp");
  map.setWallTexture("..\\res\\wall.bmp");
  map.setCeilingTexture("..\\res\\celling.bmp");
  map.populateLists();
  map.printList(map.buildingList);

  	modelOpponentCar = CModelAl();
  	//modelPlayerCar = CModelAl();

  	GLdouble position[] = {map.playerCar->x,0.3f,map.playerCar->z};
  	playerCar->initPos(position);

    glFrontFace(GL_CCW);
	modelOpponentCar.Init();

	initLight();

	t_start = clock();

	initSound();
	alSourcePlay(source[0]);

	printf("w - andar \n");
	printf("s - ir pra tras \n");
	printf("mouse - direcao \n");
	printf("r - correr \n");
	printf("c - abaixar \n");
	printf("espaco - pular \n");

}

void randomDirection() {

  bool validDirection = false;
  int newDirection;

  while (!validDirection) {
    newDirection = rand() % 4;
    switch (newDirection) {
      case 0: // Deve ir para a esquerda. A direção antiga n pode ser direita
        if (opponentDirection != 1) {
          // Testa se tem rua pra onde deve ir
          if (map.gotPosition(map.opponentCar->x, map.opponentCar->z + map.scale, map.streetList)) {
            opponentDirection = newDirection;
            modelOpponentCar.resetAngle();
            modelOpponentCar.RotateY(PI + (-(0.0f*PI)/180.0f));
            validDirection = true;
          }
        }
        break;
      case 1: // Deve ir para a direita. A direção antiga n pode ser esquerda
        if (opponentDirection != 0) {
          // Testa se tem rua pra onde deve ir
          if (map.gotPosition(map.opponentCar->x, map.opponentCar->z - map.scale, map.streetList)) {
            opponentDirection = newDirection;
            modelOpponentCar.resetAngle();
            modelOpponentCar.RotateY(PI + (-(180.0f*PI)/180.0f));
            validDirection = true;
          }
        }
        break;
      case 2: // Deve ir para cima. A direção antiga n pode baixo
        if (opponentDirection != 3) {
          // Testa se tem rua pra onde deve ir
          if (map.gotPosition(map.opponentCar->x + map.scale, map.opponentCar->z, map.streetList)) {
            opponentDirection = newDirection;
            modelOpponentCar.resetAngle();
            modelOpponentCar.RotateY(PI + (-(90.0f*PI)/180.0f));
            validDirection = true;
          }
        }
        break;
      case 3: // Deve ir para baixo. A direção antiga n pode cima
        if (opponentDirection != 2) {
          // Testa se tem rua pra onde deve ir
          if (map.gotPosition(map.opponentCar->x - map.scale, map.opponentCar->z, map.streetList)) {
            opponentDirection = newDirection;
            modelOpponentCar.resetAngle();
            modelOpponentCar.RotateY(PI + (-(270.0f*PI)/180.0f));
            validDirection = true;
          }
        }
        break;
      default: // Se perdeu
        break;
    }
  }


}

void moveOpponent() {
  if (map.gotPosition(map.opponentCar->x, map.opponentCar->z, map.streetList)) {
      //printf("O oponente está em cima de um hotspot!\n");
      randomDirection();
  }
  switch (opponentDirection) {
    case 0: // Para a esquerda +Z
      map.opponentCar->z += opponentSpeed;
      break;
    case 1: // Para a direita -Z
      map.opponentCar->z -= opponentSpeed;
      break;
    case 2: // Para cima +X
      map.opponentCar->x += opponentSpeed;
      break;
    case 3: // Para baixo -X
      map.opponentCar->x -= opponentSpeed;
      break;
    default: // Se perdeu
      break;
  }
	modelOpponentCar.Translate(map.opponentCar->x, 0.3f, map.opponentCar->z);
	modelOpponentCar.Draw();
}

void renderModels(){

	glEnable(GL_LIGHTING);
	map.renderMap();

	glEnable(GL_CULL_FACE);
	moveOpponent();

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

void testTime(int minutes, int seconds){
	if(minutes == MAX_MINUTES && seconds == MAX_SECONDS)
		exit(0);
}

void printTime(){

	t_current = clock();

	int total_seconds = (t_current - t_start)/(CLOCKS_PER_SEC);
	int minutes = (total_seconds - total_seconds%60)/60;
	int seconds = total_seconds%60;


	char lol[200];
	sprintf(lol,"TIME ELAPSED: %02d:%02d",minutes,seconds);
	glViewport((int)((float)windowWidth/3),windowHeight - windowHeight/3,windowWidth/3,windowHeight/3);

	if(MAX_MINUTES - minutes == 0 && MAX_SECONDS - seconds < 10){
		glColor3f(1.0,((float)(MAX_SECONDS-seconds))/10.0,((float)(MAX_SECONDS-seconds))/10.0);
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	printw(-0.9,0.3,-0.3,lol);
	glViewport(0,0,windowWidth,windowHeight);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	testTime(minutes,seconds);
	//glPopMatrix();

	//glMatrixMode(GL_MODELVIEW);

}


/**
Render scene
*/
void mainRender() {
	playerCar->move();
	updateState();
	renderScene();
	printTime();
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
