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
const char delimitador = ',';


string metodo;
string pathTrain;
string pathTest;
string pathResult;

listaImagenes listaTrain;
listaImagenes listaTest;
listaImagenes listaResult;

bool debug = true;

void cargarDatosDeEntrada(int argc, char** argv);
void leerCSV(string path, listaImagenes &lista);
void escribirCSV(string path, listaImagenes lista);
void leerImagn(string path);
/*
 * Modo de uso:
 * ./tp2
 * -m <method> 0: kNN , 1: PCA + kNN
 * -i <train_set> 
 * -q <test_set>
 * -o <classif>
 */
int main(int argc, char** argv) {

    //cargarDatosDeEntrada(argc, argv);
    leerImagn("E:\\Metodos Numericos 2018\\Metnum_2018_1C_TP2\\tp\\1.pgm");
    return 0;
}


void cargarDatosDeEntrada(int argc, char** argv){
    
    for(int i = 0; i < argc; i++ ){
        string val = argv[i];
        if(val == identMetodo){
            metodo = argv[++i];
        }else if(val == identTrain){
            pathTrain = argv[++i];
        }else if(val == identTest){
            pathTest = argv[++i];
        }else if(val == identResult){
            pathResult = argv[++i];
        }
    }
    
    if(debug){
        cout << "metodo: " << metodo << endl;
        cout << "pathTrain: " << pathTrain << endl;
        cout << "pathTest: " << pathTest << endl;
        cout << "pathResult: " << pathResult << endl;
    }
    
    leerCSV(pathTrain, listaTrain);
    //escribirCSV(pathTest, listaTrain);
    leerCSV(pathTest, listaTest);
    
    if(debug){
        cout << "listaTrain" << endl;
        for(imagen img : listaTrain)
            if(debug) cout << "pathImagen: " << get<0>(img) << " idImagen: " << get<1>(img) << endl;
        cout << "listaTest" << endl;
        for(imagen img : listaTest)
            if(debug) cout << "pathImagen: " << get<0>(img) << " idImagen: " << get<1>(img) << endl;
        cout << "listaResult" << endl;
        for(imagen img : listaResult)
            if(debug) cout << "pathImagen: " << get<0>(img) << " idImagen: " << get<1>(img) << endl;   
    }
}

void leerCSV(string path, listaImagenes &lista){

    ifstream archivo;
    archivo.open(path,ios::in);
    if(archivo.fail()){
        cout << "No se encontró el archivo " << path<< endl;
        exit(0);
    }
    
    string linea, pathImagen, idImagen;
    while (archivo.good()) {
        getline(archivo, linea);        
        if(debug) cout << "linea: " << linea << endl;
        stringstream ss(linea);
	getline(ss,pathImagen,delimitador);
        getline(ss,idImagen,delimitador);
        if(debug) cout << "pathImagen: " << pathImagen << " idImagen: " << idImagen << endl;
        
        if(!pathImagen.empty()){
            lista.push_back(imagen(pathImagen, stoi(idImagen)));
        }
    }
    archivo.close();
}

void escribirCSV(string path, listaImagenes lista){

    ofstream archivo;
    archivo.open(path);
    for(imagen img : listaTrain)
        archivo << get<0>(img) << ", " << get<1>(img) << ", " << endl;
    archivo.close();
}


void leerImagn(string path)
{
    uchar* data = NULL;
    string tipo;
    int ancho = 0, alto = 0, nivelesDeGrices = 0;
    PPM_LOADER_PIXEL_TYPE pt = PPM_LOADER_PIXEL_TYPE_INVALID;
    string filename = path;
    
    ifstream archivo;
    archivo.open(filename);
    
    archivo >> tipo;
    archivo >> ancho;
    archivo >> alto;
    archivo >> nivelesDeGrices;
    //getline(archivo,data);
    //archivo >> data;
    
    cout << "Tipo: " << tipo << "Tendria que ser P5" << endl;
    cout << "Ancho: " << ancho << "Tendria que ser 92" << endl;
    cout << "Alto: " << alto << "Tendria que ser 112" << endl;
    cout << "NivelesDeGrices: " << nivelesDeGrices << "Tendria que ser 255" << endl;
    
    
    bool ret = LoadPPMFile(&data, &ancho, &alto, &pt, filename.c_str());
    cout << "Bool " << ret << endl;
    cout << "ancho " << ancho << endl;
    cout << "alto " << alto << endl;
    cout << "pt " << pt << endl;
    cout << "filename " << filename << endl;
    if (!ret || ancho == 0|| alto == 0|| pt!=PPM_LOADER_PIXEL_TYPE_RGB_8B)
    {
        cout << "boom" << endl;
    } 
    cout << "ok" << endl;
} 