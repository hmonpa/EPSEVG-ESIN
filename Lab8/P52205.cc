#include <iostream>
#include <vector>
using namespace std;

vector<double> fusionar(vector <double> v1, vector<double> v2){
    unsigned int c1 = 0, c2 = 0;
    vector<double> v(v1.size() + v2.size());

    for (int i=0; i<v.size(); i++){
        if (c1 >= v1.size() and c2 < v2.size()){
            v[i] = v2[c2];
            c2++;
        }
        else if 
    }
}

void ordena_per_fusio(vector<double>& v){
    int mida = v.size();
    vector<double> v1(mida/2);
    unsigned int mig = mida/2;
    if (mida%2 != 0) mig++;
    vector<double> v2(mig);

    for (int i=0; i<mig; i++){
        if (i < v1.size()) v1[v1.size()-i-1] = v[mida-i-1];
        v2[i] = v[i];
    }
    if (v2.size() > 1) ordena_per_fusio(v2);
    if (v1.size() > 1) ordena_per_fusio(v1);

    v = fusionar(v2, v1);
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
