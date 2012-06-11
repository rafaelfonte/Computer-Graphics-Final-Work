//-----------------------------------------------------------------------------
// operações comuns para vetores 3D
//-----------------------------------------------------------------------------

#ifndef VETOR3D_H
#define VETOR3D_H

//-----------------------------------------------------------------------------
// funções comuns para uso com os vetores
//-----------------------------------------------------------------------------

// normaliza o vetor 3D
void Normaliza3D(float *pfVetor);

// rotaciona o vetor 3D em torno do eixo Y
void RotacionaEmY3D(float *pfVetor, float fAnguloEmRadianos);

// dot product
float Dot(float *pfP0, float *pfP1);

/// cross product (V1 X V2)
void Cross(float *pfResult, float *pfV1, float *pfV2);


#endif // VETOR3D_H
