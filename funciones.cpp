#include <cmath>
#include <cassert>
#include <assert.h>
#include "funciones.h"
#include <iostream>
#include "imprimir.h"

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

template<typename T> vectorReal restaAux(vector<T>& x, vector<T>& y) {
    assert(x.size() == y.size());
    vectorReal tmp(x.size(), 0.0);
    for (unsigned int i = 0; i < x.size(); i++) tmp[i] = (x[i] - y[i]);
    return tmp;
}

vectorReal resta(vectorReal &x, vectorReal &y) {
    return restaAux(x, y);
}

vectorReal resta(vectorUchar &x, vectorUchar &y) {
    return restaAux(x, y);
}

double productoInterno(const vectorReal &u, const vectorReal &v) {
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
    matrizReal B(A.size(), vectorReal(A[0].size(), 0));
    double raiz_m_menos_uno = sqrt(m - 1);
    vectorReal media(n, 0);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            media[j] += A[i][j] / m;
        }
    }
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            B[i][j] = (A[i][j] - media[j]) / raiz_m_menos_uno;
        }
    }
    return B;
}

void centrarRespectoALaMedia(const matrizReal &A,matrizReal& B) {
    //A es de m*n
    unsigned int m = A.size();
    assert(m>0);
    unsigned int n = A[0].size();
    assert(m==B.size()&&n==B[0].size());
    double raiz_m_menos_uno = sqrt(m - 1);
    vectorReal media(n, 0);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            media[j] += A[i][j] / m;
        }
    }
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            B[i][j] = (A[i][j] - media[j]) / raiz_m_menos_uno;
        }
    }
}

vectorReal A_por_v(matrizReal& A, vectorReal& v) {
    unsigned int m = A.size();
    unsigned int n = A[0].size();
    assert(n == v.size());
    vectorReal resultado(m, 0.0);
    for (unsigned int i = 0; i < m; i++) {
        resultado[i] = productoInterno(A[i], v);
    }
    return resultado;
}

void A_por_v(const matrizReal& A, const vectorReal& v, vectorReal& resultado) {
    unsigned int m = A.size();
    unsigned int n = A[0].size();
    assert(n == v.size());
    assert(m == resultado.size());
    for (unsigned int i = 0; i < m; i++) {
        resultado[i] = productoInterno(A[i], v);
    }
}

void transponer(const matrizReal&A, matrizReal&At) {
    unsigned int m = A.size();
    unsigned int n = A[0].size();
    assert(At.size() == n);
    assert(At[0].size() == m);
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            At[i][j] = A[j][i];
        }
    }
}

matrizReal multiplicarPorTranspuesta(matrizReal &A) {
    unsigned int m = A.size();
    unsigned int n = A[0].size();
    matrizReal At(n, vectorReal(m, 0));
    transponer(A, At);
    matrizReal res = matrizReal(n, vectorReal(n, 0));
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = i; j < n; j++) {
            for (unsigned int k = 0; k < m; k++) {
                res[i][j] += At[i][k] * At[j][k];
            }
            res[j][i] = res[i][j];
        }
    }
    return res;
}

void multiplicarPorTranspuesta(const matrizReal &A,matrizReal& res) {
    unsigned int m = A.size();
    assert(m>0);
    unsigned int n = A[0].size();
    assert(n==res.size()&& n==res[0].size());
    matrizReal At(n, vectorReal(m, 0));
    transponer(A, At);
//    matrizReal res = matrizReal(n, vectorReal(n, 0));
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = i; j < n; j++) {
            for (unsigned int k = 0; k < m; k++) {
                res[i][j] += At[i][k] * At[j][k];
            }
            res[j][i] = res[i][j];
        }
    }
//    return res;
}

matrizReal tc(matrizReal& Vt, matrizReal& A){// Aplica la transformación caracteristica a cada FILA de A
    unsigned int m = A.size(); // cant imágenes
    unsigned int n = Vt.size(); // alfa 
    unsigned int p = A[0].size(); // cant pixeles
    assert(p==Vt[0].size());
    matrizReal res;
    for (unsigned int i = 0; i < m; i++) {
        res.push_back(A_por_v(Vt,A[i]));
    }
    return res;
}

void tc(const matrizReal& Vt, const matrizReal& A, matrizReal& res){// Aplica la transformación caracteristica a cada FILA de A
    unsigned int m = A.size(); // cant imágenes
    unsigned int n = Vt.size(); // alfa 
    unsigned int p = A[0].size(); // cant pixeles
    assert(p==Vt[0].size());// cant pixeles

    assert(m==res.size()&&n==res[0].size());
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            res[i][j] = productoInterno(Vt[j], A[i]);
        }
    }
}
