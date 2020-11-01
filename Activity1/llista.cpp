#include <iostream>
#include "llista.hpp"

Llista::Llista() : _prim(NULL), _long(0) {}
   
Llista::Llista(const vector<int> &v) : _prim(NULL), _long(v.size()) {
  node *p, *pant = NULL;
  for (int i=0; i<v.size(); i++) {
    p = new node;
    p->info = v[i];
    p->seg = NULL;
    if (pant == NULL)
      _prim = p;
    else
      pant->seg = p;
    pant = p;
  }
}

Llista::~Llista() {
  node *p = _prim, *pelim;
  while (p != NULL) {
    pelim = p;
    p = p->seg;
    delete pelim;
  }
}

nat Llista::longitud() const {
  return _long;
}

void Llista::mostra() const {
  node *p = _prim;
  cout << "[";
  if (p != NULL) {
    cout << p->info;
    p = p->seg;
  }
  while (p != NULL) {
    cout << " " << p->info;
    p = p->seg;
  }
  cout << "]" << endl;
}

void Llista::eliminaposicionsparells(){
// Pre: True
// Post: S’han eliminat els elements del p.i. de les posicions parells
// Exemple: [2 5 3 8 1] quedaria [2 3 1]
  if (_long>0){
    node* ant = NULL;
    node* act = _prim;
    nat cont = 1;
    if (act->seg != NULL){    // mas de un elemento
      ant = act;
      act = act -> seg;
      ant->seg = act;
      cont++;
    while (ant->seg != NULL){
      if (cont%2==0){
        node* aux = act;
        act = act -> seg;
        ant->seg = act;
        delete(aux);
        _long--;
      }
      else {            // posición impar
        ant = act;
        act = act->seg;
      }
      cont++;
    }
    ant->seg = NULL;
    }
  }
}