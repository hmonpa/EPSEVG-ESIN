#include <iostream>
#include <sstream>
#include "cua.hpp"
using namespace std;

cua<int> elimina(cua <int> &q1){
    cua <int> q_res;
    int suma = 0;
    while (not q1.es_buida()){
        if (q1.primer() <= suma) q_res.encuar(q1.primer());
        suma+=q1.primer();
        q1.desencuar();
    }
    return q_res;                   // Se devuelve la cola resultante
}

void muestra(cua <int> &q1){
    while (not q1.es_buida()){
        cout << q1.primer();
        q1.desencuar();
        if (not q1.es_buida()) cout << " ";
    }
    cout << endl;
}

int main () {
    string line;
    int num;
    cua <int> q1;

    while (getline(cin, line)){     // Mientras entran líneas por el canal input, se leen y se guardan en un string (line)
        istringstream ss(line);     // Transforma el string line en un flujo de datos (ss)
        while (ss >> num){          // El flujo ss va enviando cada valor, simulando una entrada de datos
            q1.encuar(num);
        }
        q1 = elimina(q1);           // q1 coge el resultado de la función
        muestra(q1);
    }
}