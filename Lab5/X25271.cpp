#include "arbreBin.hpp"
#include <iostream>
#include <cstddef>
#include <sstream>
#include <stack>
using namespace std;

bool sumafills(arbreBin<int> T){
    bool propietat = true;
    if (not T.es_buit() and (not T.fe().es_buit() or not T.fd().es_buit())){
        // or if (not T.es_buit()) and not (T.fe().es_buit and T.fd().es_buit())
        int fillesq=0, filldret=0;
        if (not T.fe().es_buit()) fillesq = T.fe().arrel();
        if (not T.fd().es_buit()) filldret = T.fd().arrel();
        int suma = fillesq + filldret;
        //cout << "L'arrel es : " << T.arrel() << " i la suma de fills es: " << suma << endl;
        //cout << "Fill esq: " << endl << T.fe() << endl;
        //cout << "Fill dret: " << endl << T.fd() << endl;
        propietat = T.arrel() == suma and sumafills(T.fe()) and sumafills(T.fd());
    }
    return propietat;
}

int main() {
    arbreBin<int> T;
    cin >> T;
    cout << T << endl;
    cout << (sumafills(T) ? "L'arbre compleix la propietat 'Suma dels fills'." : "L'arbre no compleix la propietat 'Suma dels fills'.") << endl;
}