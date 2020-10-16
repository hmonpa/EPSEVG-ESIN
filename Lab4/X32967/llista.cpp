#include <iostream>
#include "llista.hpp"

Llista::Llista() : _long(0) {
  _prim = new node;
  _prim->seg = _prim;
  _prim->ant = _prim;
}

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

Llista::~Llista() {
  node *p = _prim->seg, *pelim;
  while (p != _prim) {
    pelim = p;
    p = p->seg;
    delete pelim;
  }
  delete _prim;
}

nat Llista::longitud() const {
  return _long;
}

void Llista::mostra() const {
  node *p = _prim->seg;
  cout << "[";
  if (p != _prim) {
    cout << p->info;
    p = p->seg;
  }
  while (p != _prim) {
    cout << " " << p->info;
    p = p->seg;
  }
  cout << "]";
}

void Llista::mostra_invertida() const {
  node *p = _prim->ant;
  cout << "[";
  if (p != _prim) {
    cout << p->info;
    p = p->ant;
  }
  while (p != _prim) {
    cout << " " << p->info;
    p = p->ant;
  }
  cout << "]";
}
