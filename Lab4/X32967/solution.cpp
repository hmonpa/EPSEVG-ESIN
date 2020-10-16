#include "llista.hpp"
// Creació d'una llista doblement encadenada, circular i amb fantasma a partir d'un vector
Llista::Llista(const vector<int> &v){
    _long = v.size();
    _prim = new node;                                       // Nodo ghost
    _prim->ant = _prim;                                     // anterior apunta al ghost
    _prim->seg = _prim;
    node *act;
    node *prev = _prim;                                     // Nodo previo
    if (v.size() != 0){
        for (nat i = 0; i<v.size();i++){
            act = new node;                                 // Nodo actual
            act->ant = prev;                                // Puntero anterior apunta al elemento previo
            act->info = v[i];
            prev->seg = act;
            prev = act;
            if (i==v.size()-1){                              // Si es el último elemento...
                prev->seg = _prim;
                _prim->ant = prev;
            }
        }
    }
}
