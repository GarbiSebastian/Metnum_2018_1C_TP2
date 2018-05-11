/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   pca.cpp
 * Author: panda
 *
 * Created on 28 de abril de 2018, 17:44
 */

#include <cassert>

#include "pca.h"

matrizReal matrizCovarianzas(matrizReal &imagenes) {
	assert(imagenes.size() > 0);
	centrarRespectoALaMedia(imagenes);
	return multiplicarPorTranspuesta(imagenes);
}

matrizReal obtenerAlfaVectores(matrizReal &A, unsigned int alfa) {
	matrizReal res;
	vectorReal v;
	assert(alfa <= A.size());
	matrizReal B = A;
	int iteraciones = 1000;
	double epsilon = 1 / pow(10, 12);
	for (unsigned int i = 0; i < alfa; i++) {
		metodoPotencia(B, v, iteraciones, epsilon);
		res.push_back(v);
		A_menos_vvt(B, v);
	}
	return res;
}

void A_menos_vvt(matrizReal &A, vectorReal &v) {
	assert(0 < v.size());
	assert(A.size() == v.size());
	assert(A[0].size() == v.size());
	unsigned int m = A.size();

	for (unsigned int i = 0; i < m; i++) {
		for (unsigned int j = 0; j < m; j++) {
			A[i][j] = A[i][j] - v[i] * v[j];
		}
	}
}
