//-----------------------------------------------------------------------------
// sphere
//-----------------------------------------------------------------------------

#include <windows.h>
#include <gl/glut.h>
#include "Vetor3D.h"
#include "Sphere.h"
#include <math.h>


//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------
CSphere::CSphere() {

  memset(m_afPosition, 0, sizeof(float) * 3);
  m_fRadius = 0.0f;
}


//-----------------------------------------------------------------------------
// destructor
//-----------------------------------------------------------------------------
CSphere::~CSphere() {
}


//-----------------------------------------------------------------------------
// initialize the sphere
//-----------------------------------------------------------------------------
bool CSphere::Init(float *pfPosition, float fRadius) {

  memcpy(m_afPosition, pfPosition, sizeof(float) * 3);
  m_fRadius = fRadius;

  return true;
}


//-----------------------------------------------------------------------------
// draw
//-----------------------------------------------------------------------------
void CSphere::Draw() {

  glPushMatrix();
  glTranslatef(m_afPosition[0], m_afPosition[1], m_afPosition[2]);
  glDisable(GL_LIGHTING);
  glEnable(GL_BLEND);
  glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
  glutSolidSphere(m_fRadius, 10, 10);
  glDisable(GL_BLEND);
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

//-----------------------------------------------------------------------------
// chech collision
//-----------------------------------------------------------------------------
float CSphere::CheckCollisionRay(float *pfPosition, float *pfDirection) {

  return -1.0f;
}
