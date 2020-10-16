#include <vector>
#include <cstddef>
#include <iostream>
#include <sstream>
using namespace std;
typedef unsigned int nat;
 
 class Llista {
   // Llista simplement encadenada, sense fantasma i no circular.
   private:
     struct node {
       int elem;  // elemrmació del node
       node *seg; // Punter al següent element
     };
     node *_head; // Punter al element fantasma
     nat _long; // Nombre d'elements
 
   public:
     Llista();
     // Pre: True
     // Post: El p.i. és una llista buida.
 
     Llista(const vector<int> &v);
     // Pre: True
     // Post: El p.i. conté els elements de v amb el mateix ordre.
 
     ~Llista();
     // Post: Destrueix els elements del p.i.
 
     nat longitud() const;
     // Pre: True
     // Post: Retorna el nombre d’elements del p.i.
 
     void mostra() const;
     // Pre: True
     // Post: Mostra el p.i. pel canal estàndard de sortida.
 
     void eliminaparells();
     // Pre: True
     // Post: elements parells eliminats

     void eliminaparells_fantasma();
     // Pre: True
     // Post: elements parells eliminats
 };

Llista::Llista() : _head(NULL), _long(0) {}

Llista::Llista(const vector<int> &v){
    _long = v.size();
    node *act;
    _head = new node;                               // Nodo ghost
    _head->seg = NULL;
    node *ant = _head;                              // anterior apunta al ghost
    if (v.size() != 0){
        for (nat i = 0; i<v.size();i++){
                act = new node;
                act->elem = v[i];
                act->seg = NULL;
                if (_head->seg == NULL){                  // primer elemento
                    _head->seg = act;               // elemento siguiente al ghost = actual
                }
                else {                              // siguientes elementos
                    ant->seg = act;
                }
                ant = act;                          // avanzamos elemento anterior
        }
        ant->seg = NULL;                            // el último elemento apunta a NULL
    }
}

Llista::~Llista() {
  node *p = _head, *pelim;
  while (p != NULL) {
    pelim = p;
    p = p->seg;
    delete pelim;
  }
}

void Llista::mostra() const {
  node *p = _head->seg;
  cout << "[";
  if (p != NULL) {
    cout << p->elem;
    p = p->seg;
  }
  while (p != NULL) {
    cout << " " << p->elem;
    p = p->seg;
  }
  cout << "]" << endl;
}

nat Llista::longitud() const {
  return _long;
}

//  Sin fantasma
/*
void Llista::eliminaparells(){
    node *ant = NULL, *act = _head;
    while (act != NULL){
        if (ant == NULL){                   // Analizando el primer elemento
            if(act->elem %2 == 0){      // Si es par...
                _head = _head->seg;
                node *aux = act;
                act = _head;
                delete(aux);
            }
            else {                          // Si es impar...
                act = act->seg;
                ant = _head;
            }
        }
        else {                              // Analizando siguientes elementos
            if (act->elem %2 == 0){         // Si es par...
                ant->seg = act->seg;
                node *aux = act;
                act = act -> seg;           // se avanza actual, antes de borrar aux (apunta al mismo sitio)
                delete(aux);
            }
            else{                           // Si es impar...
                ant = act;
                act = act->seg;
            }
        }
    }
}*/

 // Con fantasma
void Llista::eliminaparells_fantasma(){
    node *ant = _head, *act = _head->seg;
    while (act != NULL){      
        if(act->elem %2 == 0){      // Par
            ant->seg = act->seg;
            delete(act);
        }
        else {                      // Impar
            ant = act;
        }
        act = ant->seg;    
    }
}

 int main(){
     string line;
     while (getline(cin,line)){
         vector<int> v;
         istringstream ss(line);
         int n;
         while (ss >> n){
             v.push_back(n);
         }
         /*Llista l1(v);
         l1.eliminaparells();
         cout << "Mètode elimina parells sense fantasma: " << endl;
         l1.mostra();*/
         cout << "--------------------------------------" << endl;
         Llista l2(v);
         l2.eliminaparells_fantasma();
         cout << "Mètode elimina parells amb element fantasma: " << endl;
         l2.mostra();
         cout << endl;
     }
 }