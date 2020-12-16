#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
using namespace std;
typedef unsigned int nat;

// cuaprio.hpp

template <typename Elem, typename Prio>
class CuaPrio {
public:
  // Constructora, crea una cua buida.                                    
  CuaPrio();

  // Tres grans.
  CuaPrio(const CuaPrio &p);
  CuaPrio& operator=(const CuaPrio &p);
  ~CuaPrio() throw();

  // Afegeix l'element x amb prioritat p a la cua de prioritat.
  void insereix(const Elem &x, const Prio &p);

  // Retorna un element de mínima prioritat en la cua de prioritat. Llança un error si la cua és buida.
  Elem min() const;

  // Retorna la mínima prioritat present en la cua de prioritat. Llança un error si la cua és buida. 
  Prio prio_min() const;

  // Elimina un element de mínima prioritat de la cua de prioritat. Llança un error si la cua és buida.
  void elim_min();

  // Retorna cert si i només si la cua és buida.
  bool es_buida() const throw();

  static const int CuaPrioBuida = 320;

  // --- MÈTODE AFEGIT ---
  void heap_sort(vector<Elem> &v);

private:

  nat _nelems;                  // Nombre d'elements en el heap.  
  vector<pair<Elem, Prio> > _h; // Vector de pair d'Elem i Prio. La component 0 no s'usa.

  void enfonsar (nat p) throw();
  void surar (nat p) throw();
};


// cuaprio.t

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>::CuaPrio() : _nelems(0) {
  Elem x;
  Prio p;
  _h.push_back(make_pair(x, p));
}

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>::CuaPrio(const CuaPrio &p) : _nelems(p._nelems), _h(p._h) {
}

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>& CuaPrio<Elem, Prio>::operator=(const CuaPrio &p) {
  _nelems = p._nelems;
  _h = p._h;
}

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>::~CuaPrio() throw() {
}
  
template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::insereix(const Elem &x, const Prio &p) {
  _h.push_back(make_pair(x, p));
  ++_nelems; 
  surar(_nelems);
}

template <typename Elem, typename Prio>
Elem CuaPrio<Elem, Prio>::min() const {
  if (_nelems == 0) throw CuaPrioBuida;
  return _h[1].first;
}

template <typename Elem, typename Prio>
Prio CuaPrio<Elem, Prio>::prio_min() const {
  if (_nelems == 0) throw CuaPrioBuida;
  return _h[1].second;
}

template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::elim_min() {
  if (_nelems == 0) throw CuaPrioBuida;
  swap(_h[1], _h[_nelems]);
  _h.pop_back();
  --_nelems;
  enfonsar(1);
}

template <typename Elem, typename Prio>
bool CuaPrio<Elem, Prio>::es_buida() const throw() {
  return _nelems == 0;
}

// Enfonsa al node j-èssim fins a restablir l’ordre del monticle a _h; els subarbres del node j són heaps.
template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::enfonsar(nat j) throw() {
  nat hj;
  // si j no té fill esquerre ja hem acabat
  if (2*j <= _nelems) {
  hj = 2*j;
    if (hj < _nelems and _h[hj].second > _h[hj+1].second) { 
      ++hj;
    }
    // hj apunta al fill de mínima prioritat de j. 
    // Si la prioritat de j és major que la prioritat del 
    // seu fill menor cal intercanviar i seguir enfonsant.
    if (_h[j].second > _h[hj].second) {
      swap(_h[j], _h[hj]);
      enfonsar(hj);
    }
  }
}

// Fa surar el node p-èssim fins a restablir l’ordre del monticle; tots els nodes excepte el p-èssim satisfan la propietat 3.
template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::surar(nat p) throw() {
  nat q;
  bool fi = false;
  while (p > 1 and not fi) {
    q = p / 2;
    if (_h[q].second > _h[p].second) {
      swap(_h[p], _h[q]);
      p = q;
    }
  else {
      fi = true;
    }
  }
}


// Programa

template <typename Elem, typename Prio>
void CuaPrio<Elem,Prio>::heap_sort(vector<Elem> &v){
    CuaPrio<Elem, Prio> c1;

    for (int i=0; i<v.size(); i++){     // Crea el Heap
        c1.insereix(v[i], v[i]);        // Elemento - Prioridad
    }                                   // ej: Elem. 3 - prioridad 3, 10 - prioridad 10... Siendo prioridad 3 > 10
    
    for (int i=v.size()-1; i>=0; i--){ 
        //cout << "Elemento Prioridad minima: " << c1.min() << endl;      // Elemento
        //cout << "Prioridad minima: " << c1.prio_min() << endl;          // Prioridad
        v[i] = c1.min();
        c1.elim_min();
    }
}

void max_heap(vector<int> v){
    // Primer elemento >= siguientes 
    for (int i=0;i<v.size();i++){
        if (i!=v.size()-1) cout << v[i] << " ";
        else cout << v[i];
    }
    cout << endl;
}

void min_heap(vector<int> v){
    // Primer elemento <= siguientes
    stack<int> pila;
    for (int i=0;i<v.size();i++){
        pila.push(v[i]);
    }

    while (not pila.empty()){
        if (pila.size() != 1) cout << pila.top() << " ";
        else cout << pila.top();
        pila.pop();
    }
    cout << endl;
}

int main () {
    string linea;
    CuaPrio<int, int> c;
    int n;
    vector<int> v;

    while (getline(cin,linea)){
        istringstream ss1(linea);
        while (ss1 >> n){
            v.push_back(n);
        }
    }
    c.heap_sort(v);
    min_heap(v);
    max_heap(v);
}