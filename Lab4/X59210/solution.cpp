#include "llista.hpp"
// Creació d'una llista amb fantasma a partir d'un vector
Llista::Llista(const vector<int> &v){
    _long = v.size();
    node *act;
    _prim = new node;                               // Nodo ghost
    _prim->seg = NULL;
    node *ant = _prim;                              // anterior apunta al ghost
    if (v.size() != 0){
        for (nat i = 0; i<v.size();i++){
                act = new node;
                act->info = v[i];
                act->seg = NULL;
                if (_prim->seg == NULL){                  // primer elemento
                    _prim->seg = act;               // elemento siguiente al ghost = actual
                }
                else {                              // siguientes elementos
                    ant->seg = act;
                }
                ant = act;                          // avanzamos elemento anterior
        }
        ant->seg = NULL;                            // el último elemento apunta a NULL
    }
}