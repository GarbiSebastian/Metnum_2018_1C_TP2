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
const string identK_vecinos = "-k";
const string identAlfa_componentes = "-a";
const int metodoKNN = 0;
const int metodoPCA = 1;
const int metodoKNN_uchar = 2;
const int metodoPCA_inverso = 3;
const char delimitador = ',';
const int sujetos = 41;
const int imagenesXsujeto = 10;

int metodo = -1;
string pathTrain;
string pathTest;
string pathResult;

listaImagenes listaTrain;
listaImagenes listaTest;
listaImagenes listaResult;

vector<string> pathImagenesTrain;
vector<string> pathImagenesTest;
vectorEntero idImagenesTrain;
vectorEntero idImagenesTest;

matrizUchar matrizKNNTrain;
matrizUchar matrizKNNTest;
matrizReal matrizPCATrain;
matrizReal matrizPCATest;

bool debug = false;
unsigned int k_vecinos = 1;
unsigned int alfa_componentes = 20;


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
 * -o <resultado>
 * -k <k vecinos>
 * -a <alfa componentes principales>
 *
 * -m 0 -i train.csv -qtest.csv -o salida.csv
 *
 */
int main(int argc, char** argv) {

    if (argc < 8) {
        cout << "v 2" << endl;
        cout << "Error de cantidad de parametros" << endl;
        cout << "modo de uso: ./tp2 -m <metodo> -i <train_set> -q <test_set> -o <resultado> [-k <k vecinos>] [-a <alfa componentes principales>]" << endl;
        cout
                << "Metodo 0: KNN (DOUBLES)" << endl
                << "Metodo 1: PCA + KNN" << endl
                << "Metodo 2: KNN (UNSIGNED CHAR)" << endl
                << "Metodo 3: PCA(X*Xt) + KNN" << endl;
        exit(0);
    }

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
    vectorEntero indices;
    clock_t inicio = clock();
    switch (metodo) {
        case metodoKNN:
        {// KNN (DOUBLE)
            for (unsigned int i = 0; i < matrizPCATest.size(); i++) {
                buscar(k_vecinos, matrizPCATrain, matrizPCATest[i], indices, distancias);
                listaResult.push_back(imagen(pathImagenesTest[i], votar(sujetos, idImagenesTrain, indices, distancias)));
            }
            break;
        }
        case metodoPCA:
        {// PCA + KNN
            unsigned int m = matrizPCATrain.size();
            unsigned int n = matrizPCATrain[0].size();
            unsigned int t = matrizPCATest.size();
            matrizReal cov(n, vectorReal(n, 0));
            vectorReal media(n, 0);
            calcularMedias(matrizPCATrain, media);
            matrizCovarianzas(matrizPCATrain, cov, media); //centra la matriz train y calcula cov
            centrarRespectoA(matrizPCATest, media, m); // centro la matriz test 

//            /*borrar*/unsigned int alfas_n = 8, vecinos_n = 5; //borrar
//            /*borrar*/int alfas[alfas_n] = {1, 2, 3, 5, 7, 10, 20, 30}; //borrar
//            /*borrar*/alfa_componentes = alfas[alfas_n - 1]; //borrar

            cout << "X m " << matrizPCATrain.size() << " X n " << matrizPCATrain[0].size() << endl;
            
            matrizReal Vt;
            obtenerAlfaVectores(cov, alfa_componentes, Vt);
            
            cout << "Vt m " << Vt.size() << " Vt n " << Vt[0].size() << endl;
            exit(0);

//            /*borrar*/int vecinos[vecinos_n] = {1, 2, 3, 5, 7}; //borrar
//            /*borrar*/for (unsigned int alfa_i = 0; alfa_i < alfas_n; alfa_i++) {//borrar
//                /*borrar*/ alfa_componentes = alfas[alfa_i]; //borrar
//                /*borrar*/ cout << "alfa: " << alfa_componentes << endl; //borrar

                matrizReal nuevoTrain(m, vectorReal(alfa_componentes, 0));
                matrizReal nuevoTest(t, vectorReal(alfa_componentes, 0));
                tc(Vt, matrizPCATrain, nuevoTrain);
                tc(Vt, matrizPCATest, nuevoTest);
//                /*borrar*/ for (unsigned int vecino_i = 0; vecino_i < vecinos_n; vecino_i++) {//borrar
//                    /*borrar*/ k_vecinos = vecinos[vecino_i]; //borrar
//                    /*borrar*/ cout << "k: " << k_vecinos << endl; //borrar
                    for (unsigned int i = 0; i < nuevoTest.size(); i++) {
                        buscar(k_vecinos, nuevoTrain, nuevoTest[i], indices, distancias);
//                        /*borrar*/ listaResult.push_back(imagen(to_string(k_vecinos) + " " + to_string(alfa_componentes) + " " + pathImagenesTest[i], votar(sujetos, idImagenesTrain, indices, distancias))); //borrar
                        /*DESCOMENTAR*/ //                        listaResult.push_back(imagen(pathImagenesTest[i], votar(sujetos, idImagenesTrain, indices, distancias)));//descomentar
                        listaResult.push_back(imagen(pathImagenesTest[i], votar(sujetos, idImagenesTrain, indices, distancias)));//descomentar
                    }
//                    /*borrar*/                }//borrar
//                /*borrar*/
//            }//borrar
            break;
        }
        case metodoKNN_uchar:
        {// KNN (UNSIGNED CHAR)
            for (unsigned int i = 0; i < matrizKNNTest.size(); i++) {
                buscar(k_vecinos, matrizKNNTrain, matrizKNNTest[i], indices, distancias);
                listaResult.push_back(imagen(pathImagenesTest[i], votar(sujetos, idImagenesTrain, indices, distancias)));
            }
            break;
        }
        case metodoPCA_inverso:
        {// PCA(inverso) + KNN
            unsigned int m = matrizPCATrain.size();
            unsigned int n = matrizPCATrain[0].size();
            unsigned int t = matrizPCATest.size();
            matrizReal cov(m, vectorReal(m, 0));
            vectorReal media(n, 0);
            cout << "que onda" << endl;
            calcularMedias(matrizPCATrain, media);
            cout << "sarasa 1 " << endl;
            matrizCovarianzasInversa(matrizPCATrain, cov, media); //centra la matriz train y calcula cov
            cout << "cov inversa fin" << endl;
            centrarRespectoA(matrizPCATest, media, m); // centro la matriz test 

//            /*borrar*/unsigned int alfas_n = 8, vecinos_n = 5; //borrar
//            /*borrar*/int alfas[alfas_n] = {1, 2, 3, 5, 7, 10, 20, 30}; //borrar
//            /*borrar*/alfa_componentes = alfas[alfas_n - 1]; //borrar

            matrizReal Vt2;
            obtenerAlfaVectores(cov, alfa_componentes, Vt2);
            matrizReal V;
            obtenerVtDesdeVt2(Vt2,V,matrizPCATrain);
            matrizReal Vt(V[0].size(),vectorReal(V.size(),0));
            transponer(V,Vt);
            cout << "Vt m " << Vt.size() << " Vt n " << Vt[0].size() << endl;
//            exit(0);
//            /*borrar*/int vecinos[vecinos_n] = {1, 2, 3, 5, 7}; //borrar
//            /*borrar*/for (unsigned int alfa_i = 0; alfa_i < alfas_n; alfa_i++) {//borrar
//                /*borrar*/ alfa_componentes = alfas[alfa_i]; //borrar
//                /*borrar*/ cout << "alfa: " << alfa_componentes << endl; //borrar

                matrizReal nuevoTrain(m, vectorReal(alfa_componentes, 0));
                matrizReal nuevoTest(t, vectorReal(alfa_componentes, 0));
                tc(Vt, matrizPCATrain, nuevoTrain);
                tc(Vt, matrizPCATest, nuevoTest);
//                /*borrar*/ for (unsigned int vecino_i = 0; vecino_i < vecinos_n; vecino_i++) {//borrar
//                    /*borrar*/ k_vecinos = vecinos[vecino_i]; //borrar
//                    /*borrar*/ cout << "k: " << k_vecinos << endl; //borrar
                    for (unsigned int i = 0; i < nuevoTest.size(); i++) {
                        buscar(k_vecinos, nuevoTrain, nuevoTest[i], indices, distancias);
//                        /*borrar*/ listaResult.push_back(imagen(to_string(k_vecinos) + " " + to_string(alfa_componentes) + " " + pathImagenesTest[i], votar(sujetos, idImagenesTrain, indices, distancias))); //borrar
                        /*DESCOMENTAR*/ //                        listaResult.push_back(imagen(pathImagenesTest[i], votar(sujetos, idImagenesTrain, indices, distancias)));//descomentar
                        listaResult.push_back(imagen(pathImagenesTest[i], votar(sujetos, idImagenesTrain, indices, distancias)));//descomentar
                    }
//                    /*borrar*/                }//borrar
//                /*borrar*/
//            }//borrar
            break;
        }
    }
    clock_t fin = clock();
    if (debug) cout << "listaResult.size(): " << listaResult.size() << endl;
    escribirCSV(pathResult, listaResult);
    cout << "tiempo: " << (fin - inicio) / CLOCKS_PER_SEC << endl;
    cout << "Fin" << endl;
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
        } else if (val == identK_vecinos) {
            k_vecinos = atoi(argv[++i]);
        } else if (val == identAlfa_componentes) {
            alfa_componentes = atoi(argv[++i]);
        }
    }

    if (pathTrain.empty()) {
        cout << "No se a indicado el archivo Train." << endl;
        exit(0);
    } else if (pathTest.empty()) {
        cout << "No se a indicado el archivo Test." << endl;
        exit(0);
    } else if (pathResult.empty()) {
        cout << "No se a indicado el archivo Result." << endl;
        exit(0);
    } else if (metodo == -1) {
        cout << "No se a indicado el metodo a utilizar." << endl;
        exit(0);
    } else {
        if (true) {
            //if (debug) {
            cout << "metodo: " << metodo << endl;
            cout << "pathTrain: " << pathTrain << endl;
            cout << "pathTest: " << pathTest << endl;
            cout << "pathResult: " << pathResult << endl;
            cout << "k_vecinos: " << k_vecinos << endl;
            cout << "alfa_componentes: " << alfa_componentes << endl;
        }

        leerCSV(pathTrain, listaTrain);
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
}

void leerCSV(string path, listaImagenes &lista) {

    ifstream archivo;
    archivo.open(path.c_str(), ios::in);
    if (archivo.fail()) {
        cout << "No se encontr� el archivo " << path << endl;
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

    for (imagen img : lista) {
        //        cout << get<0>(img) << ", " << get<1>(img) << ", " << endl;
        archivo << get<0>(img) << ", " << get<1>(img) << ", " << endl;
    }
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
    idImagenesTrain = vectorEntero(tamTrain, 0);
    idImagenesTest = vectorEntero(tamTest, 0);

    switch (metodo) {
        case metodoKNN_uchar:
            matrizKNNTrain = matrizUchar(tamTrain, vectorUchar(0, 0));
            matrizKNNTest = matrizUchar(tamTest, vectorUchar(0, 0));
            break;
        case metodoPCA:
        case metodoPCA_inverso:
        case metodoKNN:
            matrizPCATrain = matrizReal(tamTrain, vectorReal(0, 0));
            matrizPCATest = matrizReal(tamTest, vectorReal(0, 0));
            break;
        default:
            break;
    }
}

void agregarAMatriz(uchar* data, int tam, int pos, bool esTest) {
    switch (metodo) {
        case metodoKNN_uchar:
            agregarAMatrizKNN(data, tam, pos, esTest);
            break;
        case metodoPCA:
        case metodoPCA_inverso:
        case metodoKNN:
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
