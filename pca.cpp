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
#include "constantes.h"

void A_menos_vvt(matrizReal &A, vectorReal &v, double a) {
	unsigned int m = A.size();
	assert(m > 0 && m == v.size());
	assert(m == A[0].size());
	for (unsigned int i = 0; i < m; i++) {
		for (unsigned int j = 0; j < m; j++) {
			A[i][j] = A[i][j] - a * (v[i] * v[j]);
		}
	}
}

//matrizReal matrizCovarianzas(matrizReal &imagenes) {
//	assert(imagenes.size() > 0);
//	matrizReal B = centrarRespectoALaMedia(imagenes);
//	return multiplicarPorTranspuesta(B);
//}

//void matrizCovarianzas(const matrizReal &imagenes, matrizReal& cov) {
//	unsigned int m = imagenes.size();
//	assert(m > 0);
//	unsigned int n = imagenes[0].size();
//	assert(n == cov.size() && n == cov[0].size());
//	matrizReal B(m, vectorReal(n, 0));
//	centrarRespectoALaMedia(imagenes, B);
//	multiplicarPorTranspuesta(B, cov);
//}

void matrizCovarianzas(matrizReal &imagenes, matrizReal& cov, const vectorReal& medias) {
	unsigned int m = imagenes.size();
	assert(m > 0);
	unsigned int n = imagenes[0].size();
	assert(n == cov.size() && n == cov[0].size());
	//matrizReal B(m, vectorReal(n, 0));
	centrarRespectoA(imagenes,medias,m);
	multiplicarPorTranspuesta(imagenes, cov);
}

matrizReal obtenerAlfaVectores(matrizReal &A, unsigned int alfa) {
	matrizReal res;
	vectorReal v;
	assert(alfa <= A.size());
	matrizReal B = A;
	double autovalor;
	int iteraciones = 1000;
	//double epsilon = 1 / pow(10, 12);
	for (unsigned int i = 0; i < alfa; i++) {
		//		cout << "*************" << endl;
		//		for (unsigned int i = 0; i < A.size(); i++) {
		//			imprimir(B[i], cout);
		//		}
		//		cout << "-------------" << endl;

		autovalor = metodoPotencia(B, v, iteraciones, epsilon);
		res.push_back(v);
		A_menos_vvt(B, v, autovalor);
	}
	return res;
}

void obtenerAlfaVectores(matrizReal &A, unsigned int alfa, matrizReal& res) {
	assert(alfa <= A.size());
	vectorReal v;
	int iteraciones = 1000;
	//double epsilon = 1 / pow(10, 12);
	double autovalor;
	for (unsigned int i = 0; i < alfa; i++) {
		autovalor = metodoPotencia(A, v, iteraciones, epsilon);
		res.push_back(v);
		A_menos_vvt(A, v, autovalor);
	}
}


