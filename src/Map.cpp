#include "Map.h"

Map::Map()
{
  //ctor
}

Map::~Map()
{
  //dtor
}

/**
 *
 */
void Map::setFloorTexture(char *path)
{
  floor.initTexture(path);
  printf("floor = %d\n", floor.type);
}

/**
 *
 */
void Map::setWallTexture(char *path)
{
  wall.initTexture(path);
}

/**
 *
 */
void Map::setBackgroundTexture(char *path)
{
  background.initTexture(path);
  printf("background = %d\n", background.type);
}

/**
 *
 */
void Map::renderBackground()
{
  // PRECISAMOS MUDAR PRO TAMANHO DO MINIMAP
  int planeHeight = 5;
  int planeWidth = 10;
  int sceneHeight = 5;

  // set things up to render the background with the texture
	glShadeModel(GL_SMOOTH);
	glTexImage2D(background.type, 0, 4, background.info->bmiHeader.biWidth, background.info->bmiHeader.biHeight,
                    0, GL_RGBA, GL_UNSIGNED_BYTE, background.rgba );
  glEnable(background.type);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();

  //----------------------------------------------------------------------------
  // TOP

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, sceneHeight, -1.0f);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, sceneHeight, -1.0f);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, sceneHeight, planeHeight + 1.0f);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, sceneHeight, planeHeight + 1.0f);

  glEnd();

  //--------------------------------------------
  //SIDES

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, 0.0f, -1.0f);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, 0.0f, -1.0f);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, sceneHeight, -1.0f);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, sceneHeight, -1.0f);

  glEnd();

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, 0.0f, planeHeight + 1.0f);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, 0.0f, planeHeight + 1.0f);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, sceneHeight, planeHeight + 1.0f);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, sceneHeight, planeHeight + 1.0f);

  glEnd();

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, 0.0f, planeHeight + 1.0f);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, 0.0f, -1.0f);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, sceneHeight, -1.0f);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(-1.0f, sceneHeight, planeHeight + 1.0f);

  glEnd();

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, 0.0f, planeHeight + 1.0f);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, 0.0f, -1.0f);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, sceneHeight, -1.0f);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth + 1.0f, sceneHeight, planeHeight + 1.0f);

  glEnd();

	glDisable(background.type);
	glPopMatrix();
}

/**
 *
 */
void Map::renderFloor()
{
  // PRECISAMOS MUDAR PRO TAMANHO DO MINIMAP
  int planeHeight = 5;
  int planeWidth = 10;

  // set things up to render the floor with the texture
	glShadeModel(GL_SMOOTH);
	glTexImage2D(floor.type, 0, 4, floor.info->bmiHeader.biWidth, floor.info->bmiHeader.biHeight,
                    0, GL_RGBA, GL_UNSIGNED_BYTE, floor.rgba );
	glEnable(floor.type);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  int xQuads = 40;
  int zQuads = 40;
  for (int i = 0; i < xQuads; i++) {
    for (int j = 0; j < zQuads; j++) {
      glBegin(GL_QUADS);
      glTexCoord2f(1.0f, 0.0f);   // coords for the texture
      glNormal3f(0.0f,1.0f,0.0f);
      glVertex3f(i * (float)planeWidth/xQuads, 0.0f, (j+1) * (float)planeHeight/zQuads);

      glTexCoord2f(0.0f, 0.0f);  // coords for the texture
      glNormal3f(0.0f,1.0f,0.0f);
      glVertex3f((i+1) * (float)planeWidth/xQuads, 0.0f, (j+1) * (float)planeHeight/zQuads);

      glTexCoord2f(0.0f, 1.0f);  // coords for the texture
      glNormal3f(0.0f,1.0f,0.0f);
      glVertex3f((i+1) * (float)planeWidth/xQuads, 0.0f, j * (float)planeHeight/zQuads);

      glTexCoord2f(1.0f, 1.0f);  // coords for the texture
      glNormal3f(0.0f,1.0f,0.0f);
      glVertex3f(i * (float)planeWidth/xQuads, 0.0f, j * (float)planeHeight/zQuads);

      glEnd();
    }
  }
	glDisable(floor.type);
	glPopMatrix();
}

/**
 *
 */
void Map::renderWall()
{

}

/**
 *
 */
void Map::renderMap()
{
  //setFloorTexture("..\\res\\road.bmp");
  renderFloor();
  //setBackgroundTexture("..\\res\\sky.bmp");
  renderBackground();
}
