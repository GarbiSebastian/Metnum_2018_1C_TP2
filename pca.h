/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   pca.h
 * Author: panda
 *
 * Created on 28 de abril de 2018, 17:44
 */

#ifndef PCA_H
#define PCA_H
#include "typedefs.h"
#include "funciones.h"
#include "metodoPotencia.h"

matrizReal matrizCovarianzas(matrizReal &imagenes);
matrizReal obtenerAlfaVectores(matrizReal &A, unsigned int alfa);
//void A_menos_vvt(matrizReal &A, vectorReal &v);

#endif /* PCA_H */
