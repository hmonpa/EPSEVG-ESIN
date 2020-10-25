#include "abin.hpp"
#include <iostream>
using namespace std;

Abin<int> crea_preordre(){
    int n;
    cin >> n;
    Abin<int> T;
    if (n != -1){
        Abin<int> fe = crea_preordre();
        Abin<int> fd = crea_preordre();
        T = Abin<int>(fe,n,fd);
    }
    return T;
}

int comptanodes(const Abin<int>::iterador &it1,const Abin<int>::iterador &it2, int &cont){
    if (it1 != it2){
        comptanodes(it1.fesq(), it2, ++cont);
        comptanodes(it1.fdret(), it2, ++cont);
    }
    return cont;
}

int main() {
    Abin<int> T = crea_preordre();
    Abin<int>::iterador it1 = T.arrel();
    Abin<int>::iterador it2 = T.final();
    int cont = 1;
    int n = comptanodes(it1, it2, cont);
    cout << endl << "Numero de nodes de l'arbre es: " << n << endl;

}