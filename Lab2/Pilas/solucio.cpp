#include <iostream>
#include <sstream>
#include "pila.hpp"
using namespace std;

void muestra(pila& p1, pila& p2){
// p1 es la pila con números pares y p2 con impares
    while (not p1.es_buida()){
        cout << p1.cim();
        p1.desapilar();
        if (not p1.es_buida() and not p2.es_buida()) cout << " ";
    }
    while (not p2.es_buida()){
        cout << p2.cim();
        p2.desapilar();
        if (not p2.es_buida()) cout << " ";
    }
    cout << endl;
}

int main(){
    string line;
    int num;
    pila p1, p2;

    while (getline (cin, line)){        // Mientras entran líneas por el canal input, se leen y se guardan en un string (line)
        istringstream ss(line);         // Transforma el string line en un flujo de datos (ss)
        while (ss >> num){              // El flujo ss va enviando cada valor, simulando una entrada de datos
            if (num%2 == 0) p1.apilar(num);
            else p2.apilar(num);
        }
        muestra(p1, p2);
    }
}