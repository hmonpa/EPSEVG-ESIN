#include <iostream>
#include <vector>
using namespace std;

bool hiha_cami(const vector<vector<int>> vecs, vector<bool> col, int x, int y){
    bool cami = x == y;                 // T = x==y    - F = x!=y
    col[x] = true;

    for (int i=0; i<vecs[x].size() and not cami; i++){      // Recorre el vector de vectores   
        int succ = vecs[x][i];                              
        if (not col[succ]) cami = hiha_cami(vecs, col, succ, y);    // Llama recursivamente a la función
    }

    return cami;
}

int main() {
    string line;
    int n, m;
    
    //cout << "Introduce vértices y aristas" << endl;
    cin >> n >> m;
    getline(cin, line);

    vector<vector<int>> vecs(n);        // Vector de vectores de enteros
    vector<bool> col(n, false);         // Vector col, almacena un vértice en cada vector, quedando una matriz de adyacencia
    int u, v;
    for (int i=0; i<m; i++){
        cin >> u >> v;
        vecs[u].push_back(v);           // Por cada arista, en la posición de un vértice almacena el siguiente, hacia donde hay un arco
    }   
    getline(cin,line);

    // Comprobación de si hay camino entre x e y
    int x, y;   
    cin >> x >> y;
    if (hiha_cami(vecs, col, x, y)) cout << "yes" << endl;
    else cout << "no" << endl;
}
