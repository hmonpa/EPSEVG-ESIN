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
     // lista es un puntero a nodo (alias), por tanto, lista contiene un puntero al primer elemento

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
 
     //void split(Llista& L, int x, Llista& la, Llista& lb);
     void split (llista& L, int x, llista& la, llista& lb);
     // Pre: True
     // Post: Es retornen dues llistes amb els elementes menors i majors que x, respectivament i la llista L original queda buida

     Llista crea();
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

void Llista::split(llista& L, int x, llista& la, llista& lb){
    node* ant = NULL, *act = L;
    // Mientras haya nodos a mirar y sean menores a x
    while (act != NULL and act->elem < x){          // OJO: En este orden (Primero comparación != NULL), si no, si es NULL, el programa peta
        if (ant == NULL){           // 1er elemento
            la = act;               // la se representa apuntando al primer elemento y la lista durará hasta llegar a NULL
        }
        ant = act;
        act = act->seg;
    }
    if (ant != NULL){               // fin de la
        ant->seg = NULL;
    }
    while (act != NULL and act->elem == x){     // elementos iguales a x
        ant = act;
        act = act->seg;
        delete(ant);
    }
    lb = act;                       // no hace falta recorrer hasta el final, simplemente se asigna lb al elemento actual
                                    // ... y por tanto es el primer elemento de lb, que durará hasta que llegue a NULL
}

/*llista Llista::crea(){
    int longitud;
    node* ant = NULL, *act;
    llista l = NULL;
    cin >> longitud;
    for (nat i=0; i<longitud;i++){
        act = new node;
        act->seg = NULL;
        cin >> act->elem;
        if (ant == NULL){
            l = act;
        }
        else {
            ant->seg = act;
        }
        ant = act;
    }
    return l;
}*/

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