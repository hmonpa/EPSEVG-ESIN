#include "arbre.hpp"
#include <iostream>
#include <stack>
using namespace std;

template <typename T>
Arbre<T>&  Arbre<T>::operator+(const Arbre<T> &a){

}

Arbre<int> crea(){
    int info, nf;
    cin >> info >> nf;
    stack < Arbre<int> > pila;

    Arbre<int> T(info);

    if (nf > 0){
        for (unsigned int i=0;i<nf;i++){
            Arbre<int> fill = crea();
            pila.push(fill);
        }
        while (!pila.empty()){
            T.afegir_fill(pila.top());
            pila.pop();
        }
    }
    return T;
}

int main () {
    int tam;
    cin >> tam;
    Arbre<int> T1 = crea();
    cin >> tam;
    Arbre<int> T2 = crea();
   
   
}
