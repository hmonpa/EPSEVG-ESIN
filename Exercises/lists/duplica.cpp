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
       int elem;            // informació del node
       node *seg;           // Punter null si el node no té successor
     };
     node *_prim;           // Punter al primer element
     //typedef node* llista;    // Una llista es representa amb un punter al primer element
     nat _long;             // Nombre d'elements
 
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
 
     void duplica();
     // Pre: True
     // Post: S’han duplicat els elements del p.i.
     // Exemple: [2 5 3] quedaria [2 2 5 5 3 3]
 };

Llista::Llista() : _prim(NULL), _long(0) {}

Llista::Llista(const vector<int> &v){
    _prim = NULL;
    _long = v.size();
    node *act, *ant = NULL;
    if (v.size() != 0){
        for (nat i = 0; i<v.size();i++){
                act = new node;
                act->elem = v[i];
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
    cout << p->elem;
    p = p->seg;
  }
  while (p != NULL) {
    cout << " " << p->elem;
    p = p->seg;
  }
  cout << "]" << endl;
}

void Llista::duplica(){
    node* act = _prim;
    node* ant = NULL;
    while (act != NULL){
        if (ant == NULL){               // 1er elemento
            _prim = new node;
            _prim->elem = act->elem;    // copia
            _prim->seg = act;
            _long++;
        }
        else {                          // siguientes elementos
            ant->seg = new node;
            ant->seg->elem = act->elem;
            ant->seg->seg = act;
            _long++;
        }
        ant = act;
        act = act->seg;
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
         Llista L(v);
         L.duplica();
         L.mostra();
    }
 }