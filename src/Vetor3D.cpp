//-----------------------------------------------------------------------------
// operações comuns para vetores 3D
//-----------------------------------------------------------------------------


#include "Vetor3D.h"
#include <math.h>


//-----------------------------------------------------------------------------
// normaliza o vetor 3D
//-----------------------------------------------------------------------------
void Normaliza3D(float *pfVetor) 
{
	  float fAux;

	  fAux = pfVetor[0] * pfVetor[0] +
			 pfVetor[1] * pfVetor[1] +
			 pfVetor[2] * pfVetor[2];

	  fAux = sqrt(fAux);

	  pfVetor[0] /= fAux;
	  pfVetor[1] /= fAux;
	  pfVetor[2] /= fAux;
}


//-----------------------------------------------------------------------------
// rotaciona o vetor 3D em torno do eixo Y
//-----------------------------------------------------------------------------
void RotacionaEmY3D(float *pfVetor, float fAnguloEmRadianos) 
{
  float fSeno, fCosseno, fAux;

  fSeno    = sin(fAnguloEmRadianos);
  fCosseno = cos(fAnguloEmRadianos);

  fAux = pfVetor[0];
  pfVetor[0] = pfVetor[0] * fCosseno + pfVetor[2] * fSeno;
  pfVetor[2] = pfVetor[2] * fCosseno - fAux * fSeno;
}


//-----------------------------------------------------------------------------
// dot product
//-----------------------------------------------------------------------------
float Dot(float *pfP0, float *pfP1) 
{
	return (pfP0[0] * pfP1[0] + pfP0[1] * pfP1[1] + pfP0[2] * pfP1[2]);
}


//-----------------------------------------------------------------------------
// cross product (V1 X V2) - right hand
//-----------------------------------------------------------------------------
void Cross(float *pfResult, float *pfV1, float *pfV2) 
{
	  pfResult[0] = pfV1[1] * pfV2[2] - pfV1[2] * pfV2[1];
	  pfResult[1] = pfV1[2] * pfV2[0] - pfV1[0] * pfV2[2];
	  pfResult[0] = pfV1[0] * pfV2[1] - pfV1[1] * pfV2[0];
}
