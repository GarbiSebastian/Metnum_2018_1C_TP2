#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "typedefs.h"

using namespace std;

//double normaInfinito(vectorReal &v);
//double norma2_original(vectorReal v);
//double norma2_infinito(vectorReal v);
double norma2(vectorReal v);
//void normalizar_original(vectorReal &v);
//void normalizar_infinito(vectorReal &v);
void normalizar(vectorReal &v);
vectorReal resta(vectorReal &x, vectorReal &y);
vectorReal resta(vectorUchar &x, vectorUchar &y);
double productoInterno(vectorReal &u, vectorReal &v);
matrizReal centrarRespectoALaMedia(matrizReal &A);
vectorReal A_por_v(matrizReal& A, vectorReal& v);
matrizReal multiplicarPorTranspuesta(matrizReal &A);

#endif /* FUNCIONES_H */

