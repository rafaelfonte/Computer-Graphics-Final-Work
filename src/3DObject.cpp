//-----------------------------------------------------------------------------
// handle de objetos
//-----------------------------------------------------------------------------

#include "3DObject.h"
#include <malloc.h>


//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------
C3DObject::C3DObject() {

  m_poModel = NULL;
}


//-----------------------------------------------------------------------------
// destructor
//-----------------------------------------------------------------------------
C3DObject::~C3DObject() {

  if (m_poModel) {

    free(m_poModel);
    m_poModel = NULL;
  }
}


//-----------------------------------------------------------------------------
// initialize the class
//-----------------------------------------------------------------------------
bool C3DObject::Init() {

  if (m_poModel) {

    free(m_poModel);
    m_poModel = NULL;
  }

  return true;
}


//-----------------------------------------------------------------------------
// load a model
//-----------------------------------------------------------------------------
bool C3DObject::Load(const char *pszFilename) {

  //aux vars
  char aszFilename[256];
  strcpy(aszFilename, pszFilename);

  if (m_poModel) {

    free(m_poModel);
    m_poModel = NULL;
  }

  m_poModel = glmReadOBJ(aszFilename);
  if (!m_poModel)
    return false;

  glmUnitize(m_poModel);
  glmFacetNormals(m_poModel);
  glmVertexNormals(m_poModel, 90.0);

  return true;
}


//-----------------------------------------------------------------------------
// draw the object
//-----------------------------------------------------------------------------
void C3DObject::Draw() {

  if (m_poModel)
    glmDraw(m_poModel, GLM_SMOOTH | GLM_MATERIAL);
}
