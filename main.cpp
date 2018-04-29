#include <cstdlib>
#include "funciones.h"
#include "typedefs.h"
#include "imprimir.h"
#include "metodoPotencia.h"
#include "pca.h"
#include <random>

using namespace std;

/*
 * Modo de uso:
 * ./tp2
 * -m <method> 0: kNN , 1: PCA + kNN
 * -i <train_set>
 * -q <test_set>
 * -o <classif>
 */

void test1() {
	unsigned int n = 6;
	unsigned int m = 6;
	matrizReal A = matrizReal(n, vectorReal(m, 0));
	matrizReal B;
	matrizReal autovectores;
	imprimir(A);
	cout << endl;
	for (unsigned int i = 0; i < n; i++) {
		//for (unsigned int j = i; j < m; j++) {
		A[i][i] = 1;
		//}
	}
	imprimir(A);
	cout << endl;
	B = matrizCovarianzas(A);
	imprimir(B);
	cout << endl;
	autovectores = obtenerAlfaVectores(B, 3);
	imprimir(autovectores);
	cout << endl;
}

int main(int argc, char** argv) {
	test1();
	return 0;
}

