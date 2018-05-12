#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "funciones.h"
#include "typedefs.h"
#include "imprimir.h"
#include "metodoPotencia.h"
#include "ppmloader.h"
#include "knn.h"
#include "pca.h"

using namespace std;


const string identMetodo = "-m";
const string identTrain = "-i";
const string identTest = "-q";
const string identResult = "-o";
const int mestodoKNN = 0;
const int metodoPSA = 1;
const char delimitador = ',';

int metodo;
string pathTrain;
string pathTest;
string pathResult;

listaImagenes listaTrain;
listaImagenes listaTest;
listaImagenes listaResult;

vector<string> pathImagenesTrain;
vector<string> pathImagenesTest;
vectorUchar idImagenesTrain;
vectorUchar idImagenesTest;

matrizUchar matrizKNNTrain;
matrizUchar matrizKNNTest;
matrizReal matrizPCATrain;
matrizReal matrizPCATest;

bool debug = false;
unsigned int k_vecinos = 3;
unsigned int alfa_componentes = 5;


void cargarDatosDeEntrada(int argc, char** argv);
void leerCSV(string path, listaImagenes &lista);
void escribirCSV(string path, listaImagenes lista);
void leerImagn(string path, int pos, bool esTest);
void inicializarMatriz(int tamTrain, int tamTest);
void agregarAMatriz(uchar* data, int tam, int pos, bool esTest);
void agregarAMatrizKNN(uchar* data, int tam, int pos, bool esTest);
void agregarAMatrizPCA(uchar* data, int tam, int pos, bool esTest);

/*
 * Modo de uso:
 * ./tp2
 * -m <method> 0: kNN , 1: PCA + kNN
 * -i <train_set> 
 * -q <test_set>
 * -o <classif>
 * 
 * -m 0 -i train.csv -qtest.csv -o salida.csv 
 * 
 */
void test1(){
    matrizReal A(2,vectorReal(3,1));
    A[1][2] = 9;
    A[0][0] = 8;
    matrizReal B = matrizCovarianzas(A);
    for(unsigned int i = 0; i < B.size(); i++){
        imprimir(B[i]);
    }
}
int main(int argc, char** argv) {
    test1();
    return 0;
    cargarDatosDeEntrada(argc, argv);
    inicializarMatriz(listaTrain.size(), listaTest.size());

    int pos = 0;
    if (debug) cout << "Lista Train" << endl;
    for (imagen img : listaTrain) {
        if (debug) cout << "pathImagen: " << get<0>(img) << " idImagen: " << get<1>(img) << " pos: " << pos << endl;
        leerImagn(get<0>(img), pos, false);
        pathImagenesTrain[pos] = get<0>(img);
        idImagenesTrain[pos] = get<1>(img);
        pos++;
    }
    if (debug) cout << "Lista test" << endl;
    pos = 0;
    for (imagen img : listaTest) {
        if (debug) cout << "pathImagen: " << get<0>(img) << " idImagen: " << get<1>(img) << " pos: " << pos << endl;
        leerImagn(get<0>(img), pos, true);
        pathImagenesTest[pos] = get<0>(img);
        idImagenesTest[pos] = get<1>(img);
        pos++;
    }
    
    if (debug) {
        cout << "Vector Train" << endl;
        for (unsigned int i = 0; i < pathImagenesTrain.size(); i++) {
            cout << pathImagenesTrain[i] << " , " << idImagenesTrain[i] << endl;
        }
        cout << "Vector test" << endl;
        for (unsigned int i = 0; i < pathImagenesTest.size(); i++) {
            cout << pathImagenesTest[i] << " , " << idImagenesTest[i] << endl;
        }
    }
    vectorReal distancias;
    vector<int> indices;
    switch(metodo){
        case 0:// KNN
            for(unsigned int i = 0;i<matrizKNNTest.size();i++){
                buscar(k_vecinos,matrizKNNTrain,matrizKNNTest[i],indices,distancias);
                listaResult.push_back(imagen(pathImagenesTest[i], votar(41,idImagenesTrain,indices,distancias)));
                cout << pathImagenesTest[i] << " " << (int)idImagenesTest[i] << " " << votar(41,idImagenesTrain,indices,distancias) << endl;
            }
            break;
        case 1:// PCA + KNN
            for(unsigned int i = 0;i<matrizKNNTest.size();i++){
//                matrizReal Vt = obtenerAlfaVectores(matrizCovarianzas(matrizPCATrain),alfa_componentes);
//                buscar(k_vecinos,tc(Vt,matrizPCATrain),tc(Vt,matrizPCATest)[i],indices,distancias);
//                listaResult.push_back(imagen(pathImagenesTest[i], votar(41,idImagenesTrain,indices,distancias)));
//                cout << pathImagenesTest[i] << " " << (int)idImagenesTest[i] << " " << votar(41,idImagenesTrain,indices,distancias) << endl;
            }
            break;
    }
    
    cout << listaResult.size();
    escribirCSV(pathResult,listaResult);

    cout << "Fin" << endl;
    //leerImagn("E:\\Metodos Numericos 2018\\Metnum_2018_1C_TP2\\tp\\1.pgm");
    //guardarImagen();
    return 0;
}

void cargarDatosDeEntrada(int argc, char** argv) {

    for (int i = 0; i < argc; i++) {
        string val = argv[i];
        if (val == identMetodo) {
            metodo = atoi((argv[++i]));
        } else if (val == identTrain) {
            pathTrain = argv[++i];
        } else if (val == identTest) {
            pathTest = argv[++i];
        } else if (val == identResult) {
            pathResult = argv[++i];
        }
    }

    if (debug) {
        cout << "metodo: " << metodo << endl;
        cout << "pathTrain: " << pathTrain << endl;
        cout << "pathTest: " << pathTest << endl;
        cout << "pathResult: " << pathResult << endl;
    }

    leerCSV(pathTrain, listaTrain);
    //escribirCSV(pathResult, listaTrain);
    leerCSV(pathTest, listaTest);

    if (debug) {
        cout << "listaTrain" << endl;
        for (imagen img : listaTrain)
            if (debug) cout << "pathImagen: " << get<0>(img) << " idImagen: " << get<1>(img) << endl;
        cout << "listaTest" << endl;
        for (imagen img : listaTest)
            if (debug) cout << "pathImagen: " << get<0>(img) << " idImagen: " << get<1>(img) << endl;
        cout << "listaResult" << endl;
        for (imagen img : listaResult)
            if (debug) cout << "pathImagen: " << get<0>(img) << " idImagen: " << get<1>(img) << endl;
    }
}

void leerCSV(string path, listaImagenes &lista) {

    ifstream archivo;
    archivo.open(path.c_str(), ios::in);
    if (archivo.fail()) {
        cout << "No se encontró el archivo " << path << endl;
        exit(0);
    }

    string linea, pathImagen, idImagen;
    while (archivo.good()) {
        getline(archivo, linea);
        if (debug) cout << "linea: " << linea << endl;
        stringstream ss(linea);
        getline(ss, pathImagen, delimitador);
        getline(ss, idImagen, delimitador);
        if (debug) cout << "pathImagen: " << pathImagen << " idImagen: " << idImagen << endl;

        if (!pathImagen.empty()) {
            lista.push_back(imagen(pathImagen, stoi(idImagen)));
        }
    }
    archivo.close();
}

void escribirCSV(string path, listaImagenes lista) {

    ofstream archivo;
    archivo.open(path.c_str());

    for (imagen img : lista)
        archivo << get<0>(img) << ", " << get<1>(img) << ", " << endl;
    archivo.close();
}

void leerImagn(string path, int pos, bool esTest) {
    uchar* data = NULL;
    int width = 0, height = 0;
    PPM_LOADER_PIXEL_TYPE pt = PPM_LOADER_PIXEL_TYPE_INVALID;
    std::string filename = path;

    bool ret = LoadPPMFile(&data, &width, &height, &pt, filename.c_str());
    if (debug) {
        cout << "ret: " << ret << endl;
        cout << "width: " << width << endl;
        cout << "height: " << height << endl;
        cout << "pt: " << pt << endl;
        cout << "PPM_LOADER_PIXEL_TYPE_RGB_8B: " << PPM_LOADER_PIXEL_TYPE_RGB_8B << endl;
        cout << "PPM_LOADER_PIXEL_TYPE_RGB_16B: " << PPM_LOADER_PIXEL_TYPE_RGB_16B << endl;
        cout << "PPM_LOADER_PIXEL_TYPE_RGB_32B: " << PPM_LOADER_PIXEL_TYPE_RGB_32B << endl;
        cout << "PPM_LOADER_PIXEL_TYPE_RGB_64B: " << PPM_LOADER_PIXEL_TYPE_RGB_64B << endl;

        cout << "PPM_LOADER_PIXEL_TYPE_GRAY_8B: " << PPM_LOADER_PIXEL_TYPE_GRAY_8B << endl;
        cout << "PPM_LOADER_PIXEL_TYPE_GRAY_16B: " << PPM_LOADER_PIXEL_TYPE_GRAY_16B << endl;
        cout << "PPM_LOADER_PIXEL_TYPE_GRAY_32B: " << PPM_LOADER_PIXEL_TYPE_GRAY_32B << endl;
        cout << "PPM_LOADER_PIXEL_TYPE_GRAY_64B: " << PPM_LOADER_PIXEL_TYPE_GRAY_64B << endl;
    }
    if (!ret || width == 0 || height == 0) assert(false);

    agregarAMatriz(data, width*height, pos, esTest);

    //delete [] data;
    /*char comments[100];
    sprintf(comments, "%s", "Prueba Ale");
    filename = "E:\\Metodos Numericos 2018\\Metnum_2018_1C_TP2\\tp\\prueba.ppm";
    ret = SavePPMFile(filename.c_str(),data,width,height,pt, comments);
    if (!ret)
    {
        std::cout << "ERROR: couldn't save Image to ppm file" << std::endl;
    }*/
}

void inicializarMatriz(int tamTrain, int tamTest) {

    if (debug) cout << "inicializarMatriz tamTrain: " << tamTrain << " tamTest: " << tamTest << endl;

    pathImagenesTest = vector<string>(tamTest, "");
    pathImagenesTrain = vector<string>(tamTrain, "");
    idImagenesTrain = vectorUchar(tamTrain, 0);
    idImagenesTest = vectorUchar(tamTest, 0);

    switch (metodo) {
        case mestodoKNN:
            matrizKNNTrain = matrizUchar(tamTrain, vectorUchar(0, 0));
            matrizKNNTest = matrizUchar(tamTest, vectorUchar(0, 0));
            break;
        case metodoPSA:
            matrizPCATrain = matrizReal(tamTrain, vectorReal(0, 0));
            matrizPCATest = matrizReal(tamTest, vectorReal(0, 0));
            break;
        default:
            break;
    }
}

void agregarAMatriz(uchar* data, int tam, int pos, bool esTest) {
    switch (metodo) {
        case mestodoKNN:
            agregarAMatrizKNN(data, tam, pos, esTest);
            break;
        case metodoPSA:
            agregarAMatrizPCA(data, tam, pos, esTest);
            break;
        default:
            break;
    }
}

void agregarAMatrizKNN(uchar* data, int tam, int pos, bool esTest) {

    if (debug) cout << "agregarAMatrizKNN pos: " << pos << " tam: " << tam << endl;

    vectorUchar vectorUchar(tam, 0);
    for (int i = 0; i < tam; i++) {
        vectorUchar[i] = data[i];
    }
    if (esTest) matrizKNNTest[pos] = vectorUchar;
    else matrizKNNTrain[pos] = vectorUchar;
}

void agregarAMatrizPCA(uchar* data, int tam, int pos, bool esTest) {
    if (debug) cout << "agregarAMatrizPCA pos: " << pos << " tam: " << tam << endl;
    vectorReal vectorDoble(tam, 0);
    for (int i = 0; i < tam; i++) {
        vectorDoble[i] = (double) data[i];
    }
    if (esTest)matrizPCATest[pos] = vectorDoble;
    else matrizPCATrain[pos] = vectorDoble;
}
