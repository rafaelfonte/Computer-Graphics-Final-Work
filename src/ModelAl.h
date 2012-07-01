//-----------------------------------------------------------------------------
// modelo do mafioso Al
//-----------------------------------------------------------------------------

#ifndef MODELAL_H
#define MODELAL_H

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "3DObject.h"
#include "Sphere.h"
#include <vector>

using namespace std;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CModelAl {

//-----------------------------------------------------------------------------
protected:

  /// object
  C3DObject *m_poObject;

  ///
  vector<CSphere *> m_vpoSpheres;

  /// position
  float m_afPosition[3];

  /// orientation
  float m_fAngle;

  /// control when the model was hit by a shot
  bool m_bWasHit;

  /// total number of Al's instantiated
  static int m_nTotalAl;

//-----------------------------------------------------------------------------
public:

  /// constructor
  CModelAl();

  /// destructor
  ~CModelAl();

  /// initialize the Al object
  bool Init();

  void resetAngle();

  /// draw the model
  void Draw(bool bnDrawSpheres = false);

  /// check collision
  float CheckCollisionRay(float *pfPosition, float *pfDirection);

  /// rotate the model
  void RotateY(float fAngle);

  /// translate the model
  void Translate(float fX, float fY, float fZ);

  /// return the total number of objects still "alive"
  static int GetTotalCount() { return m_nTotalAl; }

};


#endif //MODELAL_H
