#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>

using namespace std;

typedef vector<double> vectorReal;
typedef vector< vectorReal > matrizReal;

double normaInfinito(vectorReal &v);
double norma2_original(vectorReal v);
double norma2_infinito(vectorReal v);
void normalizar_original(vectorReal &v);
void normalizar_infinito(vectorReal &v);
vectorReal resta(vectorReal &x, vectorReal &y);
double productoInterno(vectorReal &u, vectorReal &v);
vectorReal centrarRespectoALaMedia(matrizReal &A);


#endif /* FUNCIONES_H */

