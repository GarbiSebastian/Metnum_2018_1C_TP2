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
matrizEntero matrizKNN;
matrizReal matrizPSA;

bool debug = true;

void cargarDatosDeEntrada(int argc, char** argv);
void leerCSV(string path, listaImagenes &lista);
void escribirCSV(string path, listaImagenes lista);
void leerImagn(string path, int pos);
void inicializarMatriz(int tam);
void agregarAMatriz(uchar* data, int tam, int pos);
void agregarAMatrizKNN(uchar* data, int tam, int pos);
void agregarAMatrizPSA(uchar* data, int tam, int pos);

/*
 * Modo de uso:
 * ./tp2
 * -m <method> 0: kNN , 1: PCA + kNN
 * -i <train_set> 
 * -q <test_set>
 * -o <classif>
 */
int main(int argc, char** argv) {

    cargarDatosDeEntrada(argc, argv);
    inicializarMatriz(listaTrain.size());
    int pos = 0;
    for (imagen img : listaTrain) {
        if (debug) cout << "pathImagen: " << get<0>(img) << " idImagen: " << get<1>(img) << " pos: " << pos << endl;
        leerImagn(get<0>(img), ++pos);
    }

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
    //escribirCSV(pathTest, listaTrain);
    //leerCSV(pathTest, listaTest);

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
    for (imagen img : listaTrain)
        archivo << get<0>(img) << ", " << get<1>(img) << ", " << endl;
    archivo.close();
}

void leerImagn(string path, int pos) {
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

    agregarAMatriz(data, width*height, pos);

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

void inicializarMatriz(int tam) {
    switch (metodo) {
        case mestodoKNN:
            matrizKNN = matrizEntero(tam, vectorEntero(0, 0));
            break;
        case metodoPSA:
            matrizPSA = matrizReal(tam, vectorReal(0, 0));
            break;
        default:
            break;
    }
}

void agregarAMatriz(uchar* data, int tam, int pos) {
    switch (metodo){
        case mestodoKNN:
            agregarAMatrizKNN(data, tam, pos);
            break;
        case metodoPSA:
            agregarAMatrizPSA(data, tam, pos);
            break;
        default:
            break;
    }
}

void agregarAMatrizKNN(uchar* data, int tam, int pos) {
    vectorEntero vectorUchar(tam, 0);
    for (int i = 0; i < tam; i++) {
        vectorUchar[i] = data[i];
    }
    matrizKNN[pos] = vectorUchar;
}

void agregarAMatrizPSA(uchar* data, int tam, int pos) {
    vectorReal vectorDoble(tam, 0);
    for (int i = 0; i < tam; i++) {
        vectorDoble[i] = (double) data[i];
    }
    matrizPSA[pos] = vectorDoble;
}
