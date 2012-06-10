//-----------------------------------------------------------------------------
// handle de objetos
//-----------------------------------------------------------------------------

#ifndef _3DOBJECT_H
#define _3DOBJECT_H

//#include <stdio.h>
#include <string.h>
#include "glm.h"


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class C3DObject {

//-----------------------------------------------------------------------------
protected:

  /// model
  GLMmodel* m_poModel;


//-----------------------------------------------------------------------------
public:

  /// constructor
  C3DObject();

  /// destructor
  ~C3DObject();

  /// initialize the class
  bool Init();

  /// load a model
  bool Load(const char *pszFilename);

  /// draw the object
  void Draw();
};


#endif // _3DOBJECT_H
