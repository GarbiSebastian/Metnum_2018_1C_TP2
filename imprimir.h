#ifndef imprimir_h
#define imprimir_h
#include "typedefs.h"
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

//template<typename T>
//void imprimir(vector< vector< T > > &m,ostream &out){
//	for(unsigned int i=0; i< m.size();i++){
//		imprimir(m[i],out);
//	}
//}
//
//template<typename T>
//void imprimir(vector< vector< T > > &m){
//	imprimir(m,cout);
//}

template<typename T>
void imprimir(vector<T> &v, ostream &out, bool transpuesto) {
	out << scientific;
	out << setprecision(6);
	if (transpuesto) {
		for (unsigned int i = 0; i < v.size(); i++) {
			//			out << (double)v[i] << endl;
			out << v[i] << endl;
		}
	} else {
		//		out << (double)v[0];
		//		out << (int)v[0];
		for (unsigned int i = 0; i < v.size(); i++) {
			//			out << " " << (double)v[i];
			out << " " << v[i];
		}
		out << endl;
	}
}

template<typename T>
void imprimir(vector<T> &v, ostream &out) {
	imprimir(v, out, false);
}

template<typename T>
void imprimir(vector<T> &v) {
	imprimir(v, cout);
}

#endif