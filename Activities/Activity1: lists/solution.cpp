#include "llista.hpp"
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