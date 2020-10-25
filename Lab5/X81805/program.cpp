#include "arbreBin.hpp"
#include <iostream>
#include <cstddef>
#include <sstream>
using namespace std;
/*
arbreBin<int> crea(){
    int n;
    cin >> n;
    arbreBin<int> T;
    if (n != 0){
        arbreBin<int> fe = crea();
        arbreBin<int> fd = crea();
        T = arbreBin<int>(n,fe,fd);
    }
    return T;
}
*/

/*void postordre(const arbreBin<int> &it1,const arbreBin<int> &it2){
    if (it1 != it2){
        // Se llama recursivamente, cuando no hay ningún hijo izq ni der, escribe el último
        // El it2 se mantiene apuntando a final (iterador no válido)
        postordre(it1.fe(), it2);
        postordre(it1.fd(), it2);
        cout << " ";
        cout << *it1;
    }
}*/

int main() {
    //arbreBin<int> T = crea();
    arbreBin<int> T;
    string line;
    istringstream s1(line);
    int n;
    cout << "Tamaño del árbol: " << endl;
    while(s1 >> n){
     //   T = n;
    }

    cout << T;
}