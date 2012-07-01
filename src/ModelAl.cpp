//-----------------------------------------------------------------------------
// modelo do mafioso Al
//-----------------------------------------------------------------------------

#include <windows.h>
#include <gl/glut.h>
#include "ModelAl.h"
#include "Vetor3D.h"


//#pragma comment(lib, "OpenGL32.lib")

//-----------------------------------------------------------------------------
// static var initialization
//-----------------------------------------------------------------------------
int CModelAl::m_nTotalAl = 0;


//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------


CModelAl::CModelAl() {

  m_poObject = NULL;
  m_fAngle = 0.0f;
  memset(m_afPosition, 0, sizeof(float) * 3);
  m_bWasHit = false;
}


//-----------------------------------------------------------------------------
// destructor
//-----------------------------------------------------------------------------
CModelAl::~CModelAl()
{
  //aux vars
  vector<CSphere *>::iterator itpoSpheres;

  if (m_poObject) {
    delete m_poObject;
    m_poObject = NULL;
  }

  for (itpoSpheres = m_vpoSpheres.begin(); itpoSpheres != m_vpoSpheres.end(); itpoSpheres++)
    delete (*itpoSpheres);

  m_vpoSpheres.clear();
}

//-----------------------------------------------------------------------------
// initialize the Al object
//-----------------------------------------------------------------------------
bool CModelAl::Init()
{
  //aux vars
  CSphere *poSphere;
  float afSpherePos[3];

  m_poObject = new C3DObject();

//if (!m_poObject->Load("../res/al.obj")) {
  if (!m_poObject->Load("../res/porsche.obj")) {
	  printf("Problem loading model!");
	  return false;
  }

  m_nTotalAl++;

  // heade
  afSpherePos[0] = 0.0f;
  afSpherePos[1] = 0.65f;
  afSpherePos[2] = 0.0f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.35f);
  m_vpoSpheres.push_back(poSphere);

  // chest
  afSpherePos[0] = 0.0f;
  afSpherePos[1] = 0.1f;
  afSpherePos[2] = 0.0f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.5f);
  m_vpoSpheres.push_back(poSphere);

  // right arm
  afSpherePos[0] = -0.5f;
  afSpherePos[1] = 0.25f;
  afSpherePos[2] = -0.1f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.2f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = -0.65f;
  afSpherePos[1] = 0.12f;
  afSpherePos[2] = -0.1f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.17f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = -0.72f;
  afSpherePos[1] = 0.0f;
  afSpherePos[2] = 0.0f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.13f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = -0.8f;
  afSpherePos[1] = -0.15f;
  afSpherePos[2] = 0.1f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.15f);
  m_vpoSpheres.push_back(poSphere);

  // left arm
  afSpherePos[0] = 0.5f;
  afSpherePos[1] = 0.25f;
  afSpherePos[2] = -0.1f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.2f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = 0.65f;
  afSpherePos[1] = 0.12f;
  afSpherePos[2] = -0.1f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.17f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = 0.72f;
  afSpherePos[1] = 0.0f;
  afSpherePos[2] = 0.0f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.13f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = 0.8f;
  afSpherePos[1] = -0.15f;
  afSpherePos[2] = 0.1f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.15f);
  m_vpoSpheres.push_back(poSphere);

  //right leg
  afSpherePos[0] = -0.2f;
  afSpherePos[1] = -0.45f;
  afSpherePos[2] = 0.025f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.18f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = -0.25f;
  afSpherePos[1] = -0.6f;
  afSpherePos[2] = 0.05f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.15f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = -0.25f;
  afSpherePos[1] = -0.8f;
  afSpherePos[2] = 0.05f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.13f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = -0.26f;
  afSpherePos[1] = -0.95f;
  afSpherePos[2] = 0.17f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.13f);
  m_vpoSpheres.push_back(poSphere);

  //right leg
  afSpherePos[0] = 0.2f;
  afSpherePos[1] = -0.45f;
  afSpherePos[2] = 0.025f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.18f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = 0.25f;
  afSpherePos[1] = -0.6f;
  afSpherePos[2] = 0.05f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.15f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = 0.25f;
  afSpherePos[1] = -0.8f;
  afSpherePos[2] = 0.05f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.13f);
  m_vpoSpheres.push_back(poSphere);

  afSpherePos[0] = 0.26f;
  afSpherePos[1] = -0.95f;
  afSpherePos[2] = 0.17f;
  poSphere = new CSphere();
  poSphere->Init(afSpherePos, 0.13f);
  m_vpoSpheres.push_back(poSphere);

  return true;
}


//-----------------------------------------------------------------------------
// draw the model
//-----------------------------------------------------------------------------
void CModelAl::Draw(bool bnDrawSpheres)
{
  //aux vars
  vector<CSphere *>::iterator itpoSpheres;

  if (m_bWasHit)
    return;

  glPushMatrix();
  glTranslatef(m_afPosition[0], m_afPosition[1], m_afPosition[2]);
  glRotatef((float)(m_fAngle * RAD_TO_PI), 0.0f, 1.0f, 0.0f);
  m_poObject->Draw();
  glPopMatrix();

  if (bnDrawSpheres) {
	  for (itpoSpheres = m_vpoSpheres.begin(); itpoSpheres != m_vpoSpheres.end(); itpoSpheres++) {
		  (*itpoSpheres)->Draw();
	}
  }
}


//-----------------------------------------------------------------------------
// check collision
//-----------------------------------------------------------------------------
float CModelAl::CheckCollisionRay(float *pfPosition, float *pfDirection)
{
  //aux vars
  vector<CSphere *>::iterator itpoSpheres;
  float fDist = -1.0f, fAux;

  for (itpoSpheres = m_vpoSpheres.begin(); itpoSpheres != m_vpoSpheres.end(); itpoSpheres++) {
    fAux = (*itpoSpheres)->CheckCollisionRay(pfPosition, pfDirection);
    if (fDist < 0.0f || (fDist > fAux && fAux >= 0.0f)) {
		fDist = fAux;
	}
  }

  if (fDist >= 0.0f) {

    if (!m_bWasHit)
      m_nTotalAl--;

    m_bWasHit = true;
  }

  return fDist;
}


//-----------------------------------------------------------------------------
// rotate the model
//-----------------------------------------------------------------------------
void CModelAl::RotateY(float fAngle) {

  //aux vars
  vector<CSphere *>::iterator itpoSpheres;
  float *pfSphere, afAux[3];

  m_fAngle += fAngle;

  for (itpoSpheres = m_vpoSpheres.begin(); itpoSpheres != m_vpoSpheres.end(); itpoSpheres++) {

    pfSphere = (*itpoSpheres)->GetPosition();
    afAux[0] = pfSphere[0] - m_afPosition[0];
    afAux[1] = pfSphere[1] - m_afPosition[1];
    afAux[2] = pfSphere[2] - m_afPosition[2];

    RotacionaEmY3D(afAux, fAngle);
    afAux[0] += m_afPosition[0];
    afAux[1] += m_afPosition[1];
    afAux[2] += m_afPosition[2];

    (*itpoSpheres)->SetPosition(afAux);
  }
}


//-----------------------------------------------------------------------------
// translate the model
//-----------------------------------------------------------------------------
void CModelAl::Translate(float fX, float fY, float fZ) {

  //aux vars
  vector<CSphere *>::iterator itpoSpheres;
  float *pfSphere;

  for (itpoSpheres = m_vpoSpheres.begin(); itpoSpheres != m_vpoSpheres.end(); itpoSpheres++) {

    pfSphere = (*itpoSpheres)->GetPosition();
    pfSphere[0] = pfSphere[0] - m_afPosition[0] + fX;
    pfSphere[1] = pfSphere[1] - m_afPosition[1] + fY;
    pfSphere[2] = pfSphere[2] - m_afPosition[2] + fZ;
  }

  m_afPosition[0] = fX;
  m_afPosition[1] = fY;
  m_afPosition[2] = fZ;
}

void CModelAl::resetAngle(){
	m_fAngle = 0.0f;
}
