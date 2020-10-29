/*struct node{
    int info;
    node* seg;              // Puntero nulo si el nodo no tiene sucesor
};
typedef node* llista;       // La lista se representa con un puntero al fantasma

void invertir(llista& L, node*p, node* q){
    //Pre:     L no es buida
    //            q i p son diferentes y no apuntan a NULL
    //            q no apunta al último elemento de la lista
    //            p no apunta a un elemento anterior a q
    //Post:    Devuelve la lista con los elementos entre p y q invertidos
    
    node* act = L->seg;
    while (act != p){
        act = act->seg;
    }
    while (act != q){
        p->seg = p->seg->seg;
        act->seg = q->seg;
        q->seg = act;

        act = p->seg;           // nuevo act
    }
}*/
#include <vector>
#include <cstddef>
#include <iostream>
#include <sstream>
using namespace std;
typedef unsigned int nat;

class Llista {
  // Llista doblement encadenada sense fantasma
  private:
   /* struct node {
      int info;  // Informació del node
      node *seg; // Punter al següent element
      node *ant; // Punter a l'anterior element
    };
    node *_prim; // Punter al primer element
    nat _long;   // Nombre d'elements*/

  public:

      struct node {
      int info;  // Informació del node
      node *seg; // Punter al següent element
      node *ant; // Punter a l'anterior element
    };
    node *_prim; // Punter al primer element
    nat _long;   // Nombre d'elements
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
    // Post: Retorna el nombre d'elements del p.i.

    void mostra() const;
    // Pre: True
    // Post: Mostra el p.i. pel canal estàndard de sortida.

    void invertir();
    // Pre:     L no es buida
    //            q i p son diferentes y no apuntan a NULL
    //            q no apunta al último elemento de la lista
    //            p no apunta a un elemento anterior a q
    // Post:    Devuelve la lista con los elementos entre p y q invertidos
};


Llista::Llista() : _prim(NULL), _long(0) {}

// Creació d'una llista doblement encadenada, sense fantasma a partir d'un vector
Llista::Llista(const vector<int> &v){
    _long = v.size();
    _prim = NULL;
    node *prev = NULL, *act;
    if (v.size()!=0){                   // Vector no está vacío
        for (nat i=0;i<v.size();i++){
            act = new node;
            act->info = v[i];     
            //cout << act << endl;
            act->seg = NULL;
            if (prev == NULL){         // Primer elemento
                act->ant = NULL;        // ant del primer elemento cubierto
                _prim = act;
            }
            else {                      // Siguientes elementos
                prev->seg = act;
                act->ant = prev;
            }
            prev = act;
        }
        prev->seg = NULL;               // seg del ultimo elemento cubierto
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

void Llista::invertir(){
    node *p;
    p->info = 4;
    node* q;
    q->info = 6;
    node* act = _prim, *prev = NULL;
    while (act != NULL){
      if (act->info == p->info){
        p = act;
      }
      else if (act->info == q->info){
        q = act;
      }
      act=act->seg;
    }
    act = _prim;
    while (act != p->seg){
        if (prev == NULL) prev = _prim;
        act = act->seg;
        act->ant = prev;
        //prev->seg = act;
        prev = act;
    }
    // act se posiciona delante de p, e irá cambiando de posición hasta que p y q esten juntos
    while (act != q){
        p->seg = p->seg->seg;
        act->seg = q->seg;
        act->ant = q;
        q->seg = act;
        prev = p->seg;
        act = prev;
    }
}

// Programa
int main() {
  string linea;
  while (getline(cin, linea)) {
    vector<int> v;
    istringstream ss(linea);
    int n;
    while (ss >> n) {
      v.push_back(n);
    }
    Llista l(v);
    
    l.invertir();
    cout << l.longitud() << " ";
    l.mostra();
  }
}