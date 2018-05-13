#include <cmath>
#include <cassert>
#include "funciones.h"


using namespace std;

double normaInfinito(vectorReal &v) {
    double norma = 0;
    for (unsigned int i; i < v.size(); i++) {
        norma = max(norma, fabs(v[i]));
    }
    return norma;
}

double norma2_original(vectorReal v) {
    double norma = 0.0;
    for (unsigned int i = 0; i < v.size(); i++) {
        norma += pow(v[i], 2);
    }
    return sqrt(norma);
}

double norma2_infinito(vectorReal v) {
    double norma, normaI;
    normaI = normaInfinito(v);
    vectorReal u(v.size(), 0);
    for (unsigned int i = 0; i < v.size(); i++) {
        u[i] = v[i] / normaI;
    }
    norma = norma2_original(u);
    return norma*normaI;
}

double norma2(vectorReal v) {
    return norma2_original(v);
//    return norma2_infinito(v);
}

void normalizar_original(vectorReal &v) {
    double norma = norma2_original(v);
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i] = v[i] / norma;
    }
}

void normalizar_infinito(vectorReal &v) {
    double norma = norma2_original(v);
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i] = v[i] / norma;
    }
}

void normalizar(vectorReal &v) {
    normalizar_original(v);
}

template<typename T> vectorReal restaAux(vector<T>& x,vector<T>& y){
    assert(x.size()==y.size());
    vectorReal tmp(x.size(), 0.0);
    for (unsigned int i = 0; i < x.size(); i++) tmp[i] = (x[i] - y[i]);
    return tmp;
}

vectorReal resta(vectorReal &x, vectorReal &y) {
    return restaAux(x,y);
}

vectorReal resta(vectorUchar &x, vectorUchar &y) {
    return restaAux(x,y);
}

double productoInterno(vectorReal &u, vectorReal &v) {
    assert(u.size() == v.size());
    double sum = 0;
    for (unsigned int i = 0; i < u.size(); i++) {
        sum += u[i] * v[i];
    }
    return sum;
}

matrizReal centrarRespectoALaMedia(matrizReal &A) {
    //A es de m*n
    unsigned int m = A.size();
    unsigned int n = A[0].size();
    matrizReal B(A.size(),vectorReal(A[0].size(),0));
    double raiz_m_menos_uno = sqrt(m-1);
    vectorReal media(n, 0);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            media[j] += A[i][j] / m;
        }
    }
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            B[i][j] = (A[i][j] - media[j])/raiz_m_menos_uno;
        }
    }
    return B;
}

vectorReal A_por_v(matrizReal& A, vectorReal& v) {
    unsigned int n = A.size();
    unsigned int m = A[0].size();
    assert(m == v.size());
    vectorReal resultado(n, 0.0);
    for (unsigned int i = 0; i < n; i++) {
        resultado[i] = productoInterno(A[i], v);
    }
    return resultado;
}

matrizReal multiplicarPorTranspuesta(matrizReal &A) {
    assert(A.size() > 0);
    assert(A[0].size() > 0);
    unsigned int n = A.size();
    unsigned int m = A[0].size();
    matrizReal res = matrizReal(m, vectorReal(m, 0));
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < m; j++) {
            for (unsigned int k = 0; k < n; k++) {
                res[i][j] += A[k][i] * A[k][j];
            }
        }
    }
    return res;
}