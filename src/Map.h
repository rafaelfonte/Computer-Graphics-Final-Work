#ifndef MAP_H
#define MAP_H

#include <windows.h>
#include <gl/glut.h>
#include "Texture.h"
#include "bitmap.h"

using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class Map
{
  //----------------------------------------------------------------------------
  public:

    Map();

    virtual ~Map();

    Texture background;

    Texture sky;

    Texture floor;

    Texture wall;

    Texture miniMap;

    void setMiniMapTexture(char *path);

    void setBackgroundTexture(char *path);

    void setSkyTexture(char *path);

    void setFloorTexture(char *path);

    void setWallTexture(char *path);

    void renderMap();

  //----------------------------------------------------------------------------
  protected:


  //----------------------------------------------------------------------------
  private:

    void renderBackground();

    void renderFloor();

    void renderWall();
};

#endif // MAP_H
