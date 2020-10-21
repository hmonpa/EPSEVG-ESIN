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
     typedef node* llista;       // Una llista es representa amb un punter al primer element

     node *_prim;           // Punter al primer element
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
 
     void split(Llista& L, int x, Llista& la, Llista& lb);
     // Pre: True
     // Post: Es retornen dues llistes amb els elementes menors i majors que x, respectivament i la llista L original queda buida
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

void Llista::split(Llista& L, int x, Llista& la, Llista& lb){
    // Se asume que la lista está ordenada y no está vacía                         
    if (L._prim->elem < x){                         // C1: x es mayor al primer elemento de L
        la._prim = L._prim;                         // Llenado de la
        node* la_act = la._prim;                    
        la._prim->seg = NULL;
        la_act->seg = NULL;
        while (L._prim->elem < x){ 
            L._prim = L._prim->seg;
            la_act->seg = L._prim;
            L._long--;
            la._long++;
            if (L._prim->elem < x) la_act = la_act->seg;
            if (la._prim->seg = NULL) la._prim->seg = la_act;
        }
        while (L._prim->elem == x){                 // ... pueden haber varios elementos x
            L._prim = L._prim->seg;
        }
        if (L._prim != NULL){                       // Llenado de lb
            lb._prim = L._prim;
            node *lb_act = lb._prim;
            lb._prim->seg = NULL;
            lb_act->seg = NULL;
            while (L._prim != NULL){
                L._prim = L._prim->seg;
                lb_act->seg = L._prim;
                L._long--;
                lb._long++;
                if (L._prim != NULL) lb_act = lb_act->seg;
                if (lb._prim->seg = NULL) lb._prim->seg = lb_act;
            }
        }
    }
    else if (L._prim->elem == x){                       // C2: x es igual al primer elemento de L
        while (L._prim->elem==x) {                      // ... pueden haber varios elementos x
            L._prim = L._prim->seg;
        }
        if (L._prim != NULL){                           // Llenado de lb
            lb._prim = L._prim;
            node *lb_act = lb._prim;
            lb._prim->seg = NULL;
            lb_act->seg = NULL;
            while (L._prim != NULL){
                L._prim = L._prim->seg;
                lb_act->seg = L._prim;
                L._long--;
                lb._long++;
                if (L._prim != NULL) lb_act = lb_act->seg;
                if (lb._prim->seg = NULL) lb._prim->seg = lb_act;
            }
        }
    }
    else {                                              // C3: x es menor al primer elemento de L
        lb._prim = L._prim;                             // Llenado de lb
        node *lb_act = lb._prim;
        lb._prim->seg = NULL;
        lb_act->seg = NULL;
        while (L._prim != NULL){
            L._prim = L._prim->seg;
            lb_act->seg = L._prim;
            L._long--;
            lb._long++;
            if (L._prim != NULL) lb_act = lb_act->seg;
            if (lb._prim->seg = NULL) lb._prim->seg = lb_act;
        }
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
         Llista la, lb;
         cout << "Introduce el valor x: " << endl;
         int x;
         cin >> x;

        L.split(L, x, la, lb);
        cout << L.longitud() << " ";
        L.mostra();
        cout << " " << la.longitud() << " ";
        la.mostra();
        cout << " " << lb.longitud() << " ";
        lb.mostra();
    }
 }