#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "typedefs.h"

using namespace std;

double norma2(vectorReal v);
void normalizar(vectorReal &v);
vectorReal resta(vectorReal &x, vectorReal &y);
vectorReal resta(vectorUchar &x, vectorUchar &y);
double productoInterno(const vectorReal &u,const vectorReal &v);
matrizReal centrarRespectoALaMedia(matrizReal &A);
void centrarRespectoALaMedia(const matrizReal &A, matrizReal&B);
vectorReal A_por_v(matrizReal& A, vectorReal& v);
matrizReal multiplicarPorTranspuesta(matrizReal &A);
void multiplicarPorTranspuesta(const matrizReal &A, matrizReal& B);
matrizReal tc(matrizReal&Vt,matrizReal&A);
void tc(const matrizReal&Vt, const matrizReal&A, matrizReal& transformada);
#endif /* FUNCIONES_H */

