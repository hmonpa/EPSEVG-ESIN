#include <iostream>
#include <vector>
using namespace std;

vector<double> merge(vector <double> v1, vector<double> v2){
    unsigned int cont1 = 0, cont2 = 0;
    vector<double> v(v1.size() + v2.size());

    for (int i=0; i<v.size(); i++){
        if (cont1 >= v1.size() and cont2 < v2.size()){
            v[i] = v2[cont2];
            cont2++;
        }
        else if (cont2 >= v2.size() and cont1 < v1.size()){
            v[i] = v1[cont1];
            cont1++;
        }
        else if (v1[cont1] < v2[cont2] and cont1 < v1.size()){
            v[i] = v1[cont1];
            cont1++;
        }
        else if (v1[cont1] > v2[cont2] and cont2 < v2.size()){
            v[i] = v2[cont2];
            cont2++;
        }
    }
    return v;
}

void ordena_per_fusio(vector<double>& v){
    int mida = v.size();
    vector<double> v2(mida/2);
    unsigned int m = mida/2;
    if (mida%2 != 0) m++;
    vector<double> v1(m);                               // Dos vectors de tamany mida/2 (o un mida/2 i l'altre (mida/2)+1)

    for (int i=0; i<m; i++){
        if (i < v2.size()){
            v2[v2.size()-i-1] = v[mida-i-1];
        }
        v1[i] = v[i];
    }
    if (v1.size() > 1) ordena_per_fusio(v1);            // Partir
    if (v2.size() > 1) ordena_per_fusio(v2);
    v = merge(v1, v2);
}


int main() {
    int n;
    while (cin >> n) {
        vector<double> v(n);
        for (int i=0; i<n; ++i) {
            cin >> v[i];
        }
        ordena_per_fusio(v);
        for (int i=0; i<n; ++i) {
            cout << " " << v[i];
        }
        cout << endl;
    }
}
