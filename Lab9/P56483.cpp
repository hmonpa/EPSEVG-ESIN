#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int n, m;
    //cout << "Introdueix vertexs i arestes:" << endl;
    cin >> n >> m;
    vector<vector<int>> vec(m);         // Vector de vectors, un vector per a cada aresta

    for (int i=0; i < m; i++){
        int u, v;
        //cout << "Introdueix un par de vertexs:" << endl;
        cin >> u >> v;

        if (i == 0){
            vec[i].push_back(u);
            vec[i].push_back(v);
        }
        else{
            bool afegits = false;
            for (int j=0; not afegits && j< vec.size(); j++){              // Recorro vector de vectores
                int k = 0, contU = 0, contV = 0;
                

                for (int k=0; k<vec[j].size();k++){         // Recorro cada vector j desde la posicion 0
                
                    if (contU != 1){
                        if (u == vec[j][k]){                // Si u es igual a la posicion k del vector
                            contU=1;                       // contador U se pone a 1, contiene ese valor
                        }
                    }
                    if (contV != 1){
                        if (v == vec[j][k]) contV=1;       // Si v es igual a la posicion k del vector, contador V se pone a 1, contiene ese valor  
                    }
                }                                           // Final del recorrido del vector j
                //if (k==vec[j].size()){
                    if (contU==0 and contV==1){             // Si se ha encontrado V, pero no U en el vector, añado u
                        vec[j].push_back(u);
                        afegits = true;
                    }
                    else if (contU==1 and contV==0){        // Si se ha encontrado U, pero no V, añado u
                        vec[j].push_back(v); 
                        afegits = true;
                    }
                    else if (contU==1 and contV==1){        // Si se ha encontrado U, pero no V, añado u
                        afegits = true;
                    }
                    else if (contV==0 and contU==0){        // Si no se ha encontrado ninguna o las dos, no hace nada
                       
                        //if (j+1<vec.size()){
                          //  vec[j].push_back(u);
                            //vec[j].push_back(v);
                           //afegits = true;
                        //}
                    }
                //}
            }
        }
    }

    int x, y;
    cin >> x >> y;
    bool cami = false;
    for (int i=0; i< vec.size(); i++){
        int k = 0, contX = 0, contY = 0;
        cout << "Vector " << i << ": ";
        while(k < vec[i].size()){
            cout << vec[i][k] << " ";
            if (x == vec[i][k]) contX++;
            if (y == vec[i][k]) contY++;
            k++;
        }
        cout << endl;
        if (contX == 1 and contY == 1) cami = true;
    }

    if (cami) cout << "yes" << endl;
    else cout << "no" << endl;
}

/*
#include <iostream>
#include <vector>
using namespace std;


int main() {
    //cout << "Introduce vértices y aristas: " << endl;
    int n, m;
    cin >> n >> m;
    int m_orig = m;

    vector<vector<int>> v(n);
    bool camino = false;
    for (int i=0; i < m; i++){
        int u, v;
        //cout << "Introduce un par de vértices" << endl;
        cin >> u >> v;
        if (m == m_orig){
            v[i].push_back(u);
            v[i].push_back(v);
        } 
        else{
            for (int i=0; i < v.size(); i++){
                for(int i=0; i<v[i].size();i++){
                    if (u)
                }
            }
            /*for(int i=0;&& i<unidos.size();i++){
                if(u==unidos[i] and v!=unidos){
                    unidos.push_back(v);
                    units = true;
                } 
                if (v==unidos[i]){
                    unidos.push_back(u);
                    units = true;
                }
            }
            if (not units)
            {
                if (separados.size() == 0){
                    for(int i=0; i<separados.size();i++){
                        if(u==separados[i]){
                            separados.push_back(v);
                        } 
                        if (v==separados[i]){
                            separados.push_back(u);
                        }
                    }
                }
                else {
                    bool igual = false;
                    for(int i=0; not igual && i<separados.size();i++){
                        if(u==separados[i]){
                            separados.push_back(v);
                            igual = true;
                        } 
                        if (v==separados[i]){
                            separados.push_back(u);
                            igual = true;
                        }
                    }
                }
            }
        }
        // Hay camino entre los dos nodos?
        if (i == m){
            //cout << "Introduce dos vértices para hay camino" << endl;
            int x, y;
            int cont = 0;
            cin >> x >> y;
            for(int i=0;i<unidos.size();i++){
                cout << unidos[i] << " ";
                if (x == unidos[i]) cont++;
                if (y == unidos[i]) cont++;
            }
            cout << endl << endl;
            if (cont = 2) camino = true;
            cont = 0;
            if (not camino)
            {
                for(int i=0;i<separados.size();i++){
                    cout << separados[i] << " ";
                    if (x == separados[i]) cont++;
                    if (y == separados[i]) cont++;
                }
            }
            if (cont = 2) camino = true;
        }
    }
    
    if (camino) cout << "yes";
    else cout << "no";


        
}*/