#include <iostream>
#include "conjunt_2enters.hpp"
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// Implementación

  void cj_2enters::insertafinal(const pair<int,int> &x) {	
		node *p_aux = new node;
		p_aux->info = x;
		if (prim == NULL and ult == NULL) {         // p.i vacío
			prim = p_aux;
			ult = p_aux;
			p_aux->seg = NULL;
		}
		else {
			ult->seg = p_aux;	
			ult = p_aux;
			ult->seg = NULL;
		}
  }

  // Constructor por defecto (conjunto vacío)
  cj_2enters::cj_2enters(){
      prim = NULL;
      ult = NULL;
  }

  // Constructor por copia
  cj_2enters::cj_2enters(const cj_2enters &cj){
    prim = NULL;
    ult = NULL;
    node *p_prox, *p_ant, *p_aux;

    if (cj.prim != NULL){               // Si el conjunto cj no está vacío
        prim = new node;                // prim apunta a un nuevo nodo sin información
        prim->info = cj.prim->info;     // el campo info del nodo apuntado por prim, tiene el mismo contenido que el campo info del nodo apuntado por cj.prim
        p_prox = cj.prim->seg;          // p_prox apunta al siguiente nodo a cj.prim
        p_ant = prim;                   // p_ant apunta al mismo nodo que prim

        while (p_prox != NULL){
            p_aux = new node;           // p_aux apunta a un nuevo nodo vacío
            p_aux->info = p_prox->info; // el campo info del objeto apuntado por p_aux, apunta al campo info del objeto apuntado por p_prox (tiene el mismo valor)
            p_ant->seg = p_aux;         // el campo siguiente de p_ant, apunta al mismo objeto que p_aux
            p_ant = p_aux;              // p_ant se itera y apunta al mismo objeto que p_aux
            p_prox = p_prox->seg;       // p_prox se itera y apunta a su campo siguiente
        }

        ult = p_ant;                    // el último objeto de la lista es p_ant
        ult->seg = NULL;                // el siguiente al último, apunta a NULL
    }
  }

  // Destructor 
  cj_2enters::~cj_2enters(){
      while (prim != NULL){
          node *p_aux = prim;
          prim = prim->seg;
          delete p_aux;
      }
      delete prim;
  }

  // Op. asignación
  cj_2enters& cj_2enters::operator=(const cj_2enters &cj){
      if (this != &cj){                 // Si no son el mismo objeto (dif. @ de memoria)
          cj_2enters aux(cj);           // Llamamos al constructor por copia
          node* prim_aux = prim;
          node* ult_aux = ult;
          prim = aux.prim;              // swap de los punteros del p.i y aux
          ult = aux.ult;                // cómo aux queda apuntando al antiguo p.i, la destructora lo borrará
          aux.prim = prim_aux;
          aux.ult = ult_aux;
      }
      return *this;
  }

  void cj_2enters::insereix(pair<int, int> pe){
      if (not conte(pe)){
          node *p_aux = new node;
          p_aux->info = pe;
          if (prim == NULL and ult == NULL){            // CD: p.i vacío
                prim = p_aux;
                ult = p_aux;
                p_aux->seg = NULL;
          }
          else {
              bool ins = false;
              node *p_ant = prim;
              node *p_act = prim->seg;

              if (pe < prim->info){                     // pe < primer nodo de la lista
                  p_aux->seg = prim;
                  prim = p_aux;
                  ins = true;
              }
              else if (pe > ult->info and not ins){     // pe > último nodo de la lista
                  ult->seg = p_aux;
                  ult = p_aux;
                  ult->seg = NULL;
                  ins = true;
              }
              while (not ins and p_act != NULL){        // pe > primer nodo && pe < último nodo
                  if (pe < p_act->info){
                      p_ant->seg = p_aux;
                      p_aux->seg = p_act;
                      ins = true;
                  }
                  else {
                      p_ant = p_ant->seg;               // Iteración de p_ant y p_act (si pe == algún nodo)
                      p_act = p_act->seg;
                  }
              }
          }
      }
  }

  
  void cj_2enters::unir(const cj_2enters& B){
      node *p1 = prim;
      node *p2 = B.prim;
      cj_2enters Caux;
      while (p1 != NULL and p2 != NULL){
          if (p1->info < p2->info){
              Caux.insertafinal(p1->info);
              p1 = p1->seg;
          }
          else if (p1->info > p2->info){
              Caux.insertafinal(p2->info);
              p2 = p2->seg;

          }
          else {
              Caux.insertafinal(p1->info);
              p1 = p1->seg;
              p2 = p2->seg;
          }
      }
      while (p1 != NULL){                                   // Conjunto B ha llegado al final
              Caux.insertafinal(p1->info);
              p1 = p1->seg;
      }
      while (p2 != NULL){                                   // Conjunto p.i ha llegado al final
              Caux.insertafinal(p2->info);
              p2 = p2->seg;
      }
      *this = Caux;
  }

  void cj_2enters::intersectar(const cj_2enters& B){
      node *p1 = prim;
      node *p2 = B.prim;
      cj_2enters Caux;
      while (p1 != NULL and p2 != NULL){
          if (p1->info == p2->info){
              Caux.insertafinal(p1->info);
              p1 = p1->seg;
              p2 = p2->seg;
          }
          else if (p1->info < p2->info) p1 = p1->seg;
          else p2 = p2->seg;
      }
      *this = Caux;
  }

  void cj_2enters::restar(const cj_2enters& B){
      node *p1 = prim;
      node *p2 = B.prim;
      cj_2enters Caux;
      while (p1 != NULL and p2 != NULL){
          if(p1->info == p2->info){
              p1 = p1->seg;
              p2 = p2->seg;
          }
          else if (p1->info < p2->info){
              Caux.insertafinal(p1->info);
              p1 = p1->seg;
          }
          else p2 = p2->seg;
      }
      while (p1 != NULL){
          Caux.insertafinal(p1->info);
          p1 = p1->seg;
      }
      *this = Caux;
  }

  cj_2enters cj_2enters::operator+(const cj_2enters& B) const{      // Unión
      cj_2enters C(*this);
      C.unir(B);
      return C;
  }

  cj_2enters cj_2enters::operator*(const cj_2enters& B) const{      // Intersección
      cj_2enters C(*this);
      C.intersectar(B);
      return C;
  }

  cj_2enters cj_2enters::operator-(const cj_2enters& B) const{      // Resta
      cj_2enters C(*this);
      C.restar(B);
      return C;
  }

  bool cj_2enters::conte(pair<int, int> pe) const{
    node *p_iterador = prim;
    bool trobat = false;
    while (p_iterador != NULL and not trobat){
        if(p_iterador->info == pe) trobat = true;
        p_iterador = p_iterador->seg;
    }
    return trobat;
  }

  pair<int, int> cj_2enters::max() const{
    pair<int,int> max = prim->info;
    node *p_iterador = prim;
    while (p_iterador != NULL){
        if(p_iterador->info > max) max = p_iterador->info;
        p_iterador = p_iterador->seg;
    }
    return max;
  }

  pair<int, int> cj_2enters::min() const{
    pair<int,int>min = prim->info;
    node *p_iterador = prim;
    while (p_iterador != NULL){
        if(p_iterador->info < min) min = p_iterador->info;
        p_iterador = p_iterador->seg;
    }
    return min;
  }

  int cj_2enters::card() const{
    unsigned int i = 0;
    node *p_iterador = prim;
    while (p_iterador != NULL){
        p_iterador = p_iterador->seg;
        i++;
    }
    return i;
  }

  bool cj_2enters::operator==(const cj_2enters& B) const{
    bool igual = true;
    if (card() == B.card()){
        node* p1 = prim;
        node* p2 = B.prim;
        while (p1 != NULL and igual){
            if (p1->info != p2->info)  igual = false;
            p1 = p1->seg;
            p2 = p2->seg;
        }
    }
    else igual = false;
    return igual;
  }

  bool cj_2enters::operator!=(const cj_2enters& B) const{
    return not(*this == B);
  }

  void cj_2enters::print(ostream& os) const{
      os << "[";
      node *p_iterador = prim;
      while (p_iterador != NULL){
          os << p_iterador->info.first << "," << p_iterador->info.second;
          if (p_iterador->seg != NULL) cout << " ";
          p_iterador = p_iterador->seg; 
      }
      os << "]";
  }