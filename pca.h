#ifndef PCA_H
#define PCA_H
#include "typedefs.h"
#include "funciones.h"
#include "metodoPotencia.h"
#include "imprimir.h"


//matrizReal matrizCovarianzas(matrizReal &imagenes);
//void matrizCovarianzas(const matrizReal &imagenes, matrizReal& cov);
void matrizCovarianzas(matrizReal &imagenes, matrizReal& cov, const vectorReal& medias);
void matrizCovarianzasInversa(matrizReal &imagenes, matrizReal& cov, const vectorReal& medias);
//matrizReal obtenerAlfaVectores(matrizReal &A, unsigned int alfa);
void obtenerAlfaVectores(matrizReal &A, unsigned int alfa, matrizReal& res);
void obtenerVtDesdeVt2(matrizReal& Vt, matrizReal& Vt2, matrizReal& X);
//void A_menos_vvt(matrizReal &A, vectorReal &v);

#endif /* PCA_H */
