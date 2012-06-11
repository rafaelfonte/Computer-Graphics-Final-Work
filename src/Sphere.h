//-----------------------------------------------------------------------------
// sphere
//-----------------------------------------------------------------------------

//#include <stdio.h>
#include <string.h>
#include <gl/glut.h>

#ifndef SPHERE_H
#define SPHERE_H


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CSphere {

//-----------------------------------------------------------------------------
protected:

  /// sphere position
  float m_afPosition[3];

  /// sphere radius
  float m_fRadius;

//-----------------------------------------------------------------------------

public:

  /// constructor
  CSphere();

  /// destructor
  ~CSphere();

  /// initialize the sphere
  bool Init(float *pfPosition, float fRadius);

  /// draw
  void Draw();

  /// chech collision - negative distances means a miss
  float CheckCollisionRay(float *pfPosition, float *pfDirection);

  /// return sphere position
  float *GetPosition() { return m_afPosition; }

  /// set sphere position
  void SetPosition(float *pfPos) { memcpy(m_afPosition, pfPos, sizeof(float) * 3); }
};


#endif //SPHERE_H
