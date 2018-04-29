#include <cstdlib>
#include "funciones.h"
#include "typedefs.h"
#include "imprimir.h"
#include "metodoPotencia.h"

using namespace std;

/*
 * Modo de uso:
 * ./tp2
 * -m <method> 0: kNN , 1: PCA + kNN
 * -i <train_set> 
 * -q <test_set>
 * -o <classif>
 */
int main(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }

    return 0;
}

