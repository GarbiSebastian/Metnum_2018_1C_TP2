#include <cmath>
#include <cassert>
#include "funciones.h"

using namespace std;

double normaInfinito(vectorReal &v){
    double norma= 0;
    for(unsigned int i;i<v.size();i++){
        norma = max(norma,fabs(v[i]));
        
    }
    return norma;
}

double norma2_original(vectorReal v){
	double norma=0.0;
	for(unsigned int i = 0; i < v.size();i++){
		norma+= pow(v[i],2);
	}
	return sqrt(norma);
}

double norma2_infinito(vectorReal v){
    double norma,normaI;
    normaI=normaInfinito(v);
    vectorReal u(v.size(),0);
    for(unsigned int i = 0; i < v.size();i++){
        u[i]=v[i]/normaI;
	}
    norma = norma2_original(u);
    return norma*normaI;    
}

double norma2(vectorReal v){
    return norma2_infinito(v);
}

void normalizar_original(vectorReal &v){
	double norma = norma2_original(v);
	for(unsigned int i = 0; i < v.size();i++){
		v[i]= v[i]/norma;
	}
}

void normalizar_infinito(vectorReal &v){
	double norma = norma2_infinito(v);
	for(unsigned int i = 0; i < v.size();i++){
		v[i]= v[i]/norma;
	}
}

void normalizar(vectorReal &v){
	normalizar_infinito(v);
}

vectorReal resta(vectorReal &x, vectorReal &y) {
	//assert(x.size()==y.size());
	vectorReal tmp(x.size(),0.0);
	for (unsigned int i = 0; i < x.size(); i++) tmp[i] = (x[i] - y[i]);
	return tmp;
}

double productoInterno(vectorReal &u, vectorReal &v) {
	assert(u.size()==v.size());
	double sum = 0;
	for (unsigned int i = 0; i < u.size(); i++) {
		sum += u[i] * v[i];
	}
	return sum;
}

vectorReal centrarRespectoALaMedia(matrizReal &A){
	//A es de m*n
	unsigned int m = A.size();
	unsigned int n = A[0].size();
	vectorReal media(n,0);
	for(unsigned int i = 0; i < m;i++){
		for(unsigned int j = 0; j < n;j++){
			media[j]+=A[i][j]/m;
		}
	}
	for(unsigned int i = 0; i < m;i++){
		for(unsigned int j = 0; j < n;j++){
			A[i][j] = A[i][j] - media[j];
		}
	}
	return media;
}

vectorReal A_por_v(matrizReal& A, vectorReal& v) {
	int n = A.size();
	int m = A[0].size();
	assert(m == v.size());
	vectorReal resultado(n, 0.0);
	for (int i = 0; i < n; i++) {
		resultado[i] = productoInterno(A[i],v);
	}
	return resultado;
}