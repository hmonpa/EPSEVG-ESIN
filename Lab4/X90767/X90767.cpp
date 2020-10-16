#include "llista.hpp"

Llista::Llista(const vector<int> &v){
    _prim = NULL;
    _long = v.size();
    node *act, *ant = NULL;
    if (v.size() != 0){
        for (nat i = 0; i<v.size();i++){
                act = new node;
                act->info = v[i];
                act->seg = NULL;
                if (ant == NULL){                   // Primer elemento
                    _prim = act;  
                }
                else {                              // Otros elementos
                    ant->seg = act;
                }
                ant = act;                          // Avanzamos elemento anterior
                //_long++;                          // size de la llista ++
        }
        ant->seg = NULL;
    }
}