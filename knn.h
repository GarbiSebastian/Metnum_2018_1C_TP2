#include "typedefs.h"
#include <math.h>

using namespace std;

void buscar(int k_vecinos, matrizReal & train, vectorReal & imagen, vectorEntero & indices , vectorReal &distancias);
int votar(unsigned int cant_categorias, vectorUchar & labels, vectorEntero & indices , vectorReal &distancias);
void buscar(int k_vecinos, matrizUchar & train, vectorUchar & imagen, vectorEntero & indices , vectorReal &distancias);
