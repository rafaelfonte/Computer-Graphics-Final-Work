#ifndef MAP_H
#define MAP_H

#include <windows.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <stdbool.h>
#include "Texture.h"
#include "bitmap.h"

// estrutura para armazenar a posi��o dos predios
typedef struct crd {
  int x;
  int z;
  struct crd *next;
} CRD;

using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class Map
{
  //----------------------------------------------------------------------------
  public:

    Map();

    virtual ~Map();

    CRD *buildingList;

    CRD *playerCar;

    CRD *opponentCar;

    CRD *streetList;

    int scale;

    Texture background;

    Texture sky;

    Texture floor;

    Texture wall;

    Texture ceiling;

    Texture miniMap;

    void setMiniMapTexture(char *path);

    void setBackgroundTexture(char *path);

    void setSkyTexture(char *path);

    void setFloorTexture(char *path);

    void setWallTexture(char *path);

    void setCeilingTexture(char *path);

    void renderMap();

    CRD *createList();

    void insertList(CRD **list, int x, int z);

    bool emptyList(CRD *list);

    bool gotPosition(float x, float z, CRD *list);

    void populateLists();

    void printList(CRD *list);

    void printMiniMap(int windowWidth, int windowHeight);

    bool hitWall(float position[]);

  //----------------------------------------------------------------------------
  protected:


  //----------------------------------------------------------------------------
  private:

    void renderBackground();

    void renderFloor();

    void renderWall();

    void makeBuilding(int x, int z);
};

#endif // MAP_H
