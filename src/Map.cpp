#include "Map.h"

CRD *Map::createList() {
  return NULL;
}

bool Map::emptyList(CRD *list) {
  if (list == NULL) {
    return true;
  } else {
    return false;
  }
}

void Map::printList(CRD *list) {
  CRD *iterator;
  iterator = list;
  while(!emptyList(iterator)){
    printf("(%d,%d)\n", iterator->x, iterator->z);
    iterator = iterator->next;
  }
}

void Map::insertList(CRD **list, int x, int z) {
  CRD *iterator;
  iterator = *list;

  CRD *newCoord = (CRD*)malloc(sizeof(CRD));

  newCoord->x = x;
  newCoord->z = z;
  newCoord->next = iterator;

  *list = newCoord;
}

void Map::populateBuildingList(CRD **list) {
  int i = 0;
  int x;
  int z;
  printf("altura: %d largura: %d\n", miniMap.info->bmiHeader.biHeight, miniMap.info->bmiHeader.biWidth);
  for(miniMap.ptr = miniMap.bits;  i < miniMap.info->bmiHeader.biHeight * miniMap.info->bmiHeader.biWidth; i++, miniMap.ptr += 3) {
    // White pixel is a building
    if(miniMap.ptr[0] == 255 && miniMap.ptr[1]==255 && miniMap.ptr[2]==255) {
      x = i / miniMap.info->bmiHeader.biWidth;
      z = i % miniMap.info->bmiHeader.biWidth;
      insertList(&buildingList, x, z);
    }
  }
}

Map::Map()
{
  //ctor
  buildingList = createList();
  scale = 10;
}

Map::~Map()
{
  //dtor
}

/**
 *
 */
void Map::setMiniMapTexture(char *path)
{
  miniMap.initTexture(path);
}

/**
 *
 */
void Map::setFloorTexture(char *path)
{
  floor.initTexture(path);
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
}

/**
 *
 */
void Map::setSkyTexture(char *path)
{
  sky.initTexture(path);
}

/**
 *
 */
void Map::renderBackground()
{
  // PRECISAMOS MUDAR PRO TAMANHO DO MINIMAP
  int planeHeight = scale * miniMap.info->bmiHeader.biHeight;
  int planeWidth = scale * miniMap.info->bmiHeader.biWidth;
  int sceneHeight = 8;

  // set things up to render the background with the texture
	glShadeModel(GL_SMOOTH);
	glTexImage2D(sky.type, 0, 4, sky.info->bmiHeader.biWidth, sky.info->bmiHeader.biHeight,
                    0, GL_RGBA, GL_UNSIGNED_BYTE, sky.rgba );
  glEnable(sky.type);

	glPushMatrix();

  //----------------------------------------------------------------------------
  // TOP

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, sceneHeight, 0.0f);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, sceneHeight, 0.0f);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, sceneHeight, planeHeight);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, sceneHeight, planeHeight);

  glDisable(sky.type);
  glEnd();

  //--------------------------------------------
  //SIDES

  glTexImage2D(background.type, 0, 4, background.info->bmiHeader.biWidth, background.info->bmiHeader.biHeight,
                    0, GL_RGBA, GL_UNSIGNED_BYTE, background.rgba );
  glEnable(background.type);

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, 0.0f, 0.0f);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, sceneHeight, 0.0f);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, sceneHeight, 0.0f);

  glEnd();

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, 0.0f, planeHeight);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, 0.0f, planeHeight);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, sceneHeight, planeHeight);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, sceneHeight, planeHeight);

  glEnd();

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, 0.0f, planeHeight);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, sceneHeight, 0.0f);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f, sceneHeight, planeHeight);

  glEnd();

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);   // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, 0.0f, planeHeight);

  glTexCoord2f(0.0f, 0.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, 0.0f, 0.0f);

  glTexCoord2f(0.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, sceneHeight, 0.0f);

  glTexCoord2f(1.0f, 1.0f);  // coords for the texture
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(planeWidth, sceneHeight, planeHeight);

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
  int planeHeight = scale * miniMap.info->bmiHeader.biHeight;
  int planeWidth = scale * miniMap.info->bmiHeader.biWidth;

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
