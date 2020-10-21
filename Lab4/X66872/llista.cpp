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
  cout << "]";
}

void Llista::separa(Llista &l2){
  if (_long > 0){                     // lista no vacía
    node* act = _prim;                // Recorre p.i

    if (act->seg != NULL){            // si hay más de un elemento
      l2._prim = act->seg;
      act->seg = act->seg->seg;
      l2._prim->seg = NULL;           // no dejamos el puntero colgando
      node* l2_act = l2._prim;        // Recorre l2
      _long--;                        // p.i disminuye una posición, ya que hay una que no recorre
      l2._long++;                     // l2 aumenta una posición, ya que recorre una
      nat pos = 1;      // inicializado a 1, ya que vamos a empezar mirando posición impar
      while (act->seg != NULL){
        if (pos%2==0){                // posición par, irá a l2
          l2_act->seg = act->seg;
          act->seg = act->seg->seg;
          l2_act->seg->seg = NULL;
          l2_act = l2_act->seg;       // se itera l2_act
          _long--;    
          l2._long++;
        }
        else {                        // posición impar, se queda en el p.i
          act = act->seg;             // se itera act
        }
        pos++;
      }
    }
  }
}