#ifndef _LLISTA_ITR_HPP
#define _LLISTA_ITR_HPP
#include <cstddef>
using namespace std;
typedef unsigned int nat;

// Especificación 
template <typename T>
class llista_itr {
private:
  struct node {
    T info;
    node* next;
    node* prev;
  };
  node* _head; // punter al fantasma
  nat _sz;     // mida de la llista

  node* copiar_llista(node* orig, node* orighead, node* h);
  void destruir_llista(node* p, node* h) throw();
  void swap(llista_itr<T>& l) throw();

public:
  // Constructora. Crea una llista buida.
  llista_itr();

  // Tres grans.
  llista_itr(const llista_itr<T>& l);
  llista_itr<T>& operator=(const llista_itr<T>& l);
  ~llista_itr() throw();

  // Iteradors sobre llistes.
  // Un objecte iterador sempre està associat a una llista
  // particular; només poden ser creats mitjançant els mètodes Llista<T>::primer, Llista<T>::ultim i Llista<T>::indef. Cada llista té el seu iterador indefinit propi: L1.indef() != L2.indef()
  friend class iterador;

  class iterador {
  public:
    friend class llista_itr;

    // Per la classe iterador NO cal redefinir els tres grans ja que ens serveixen les implementacions d'ofici.

    // Accedeix a l'element apuntat per l'iterador o  llança una excepció si l'iterador és indefinit.
    const T& operator*() const;

    // Operadors per avançar (pre i postincrement) i per retrocedir (pre i postdecrement); no fan res si l'iterador és indefinit.
    iterador& operator++() throw();
    iterador operator++(int) throw();
    iterador& operator--() throw();
    iterador operator--(int) throw();

    // Operadors d'igualtat i desigualtat entre iteradors.
    bool operator==(iterador it) const throw();
    bool operator!=(iterador it) const throw();

    static const int IteradorIndef = 330;

  private:
    // Constructora. Crea un iterador indefinit.
    // No pot usar-se fora de la classe iterador o de la classe llista_itr.
    iterador() throw();

    node* _p;  // punter al node actual
    node* _h;  // punter al fantasma de la llista per
               // poder saber quan ho hem recorregut tot.
  };

  // Insereix l'element x darrera/davant de l'element apuntat per l'iterador; si l'iterador it és indefinit, insereix_darrera afegeix x com primer de la llista, i insereix_davant afegeix x com últim de la llista; en abstracte un iterador indefinit "apunta" a un element fictici que és al mateix temps predecessor del primer i successor de l'últim.
  void inserir_darrera(const T& x, iterador it);
  void inserir_davant(const T& x, iterador it);

  // Tant esborra_avnc com esborra_darr eliminen l'element apuntat per l'iterador, 
  // menys en el cas que it és indefinit (llavors no fan res); 
  // amb esborra_avnc l'iterador passa a apuntar al successor de l'element eliminat o queda indefinit si l'element eliminat és l'últim; amb esborra_darr l'iterador passa a apuntar al predecessor de l'element
  // eliminat o queda indefinit si l'eliminat és el primer element.
  void esborrar_avnc(iterador& it) throw();
  void esborrar_darr(iterador& it) throw();

  // Longitud de la llista.
  nat longitud() const throw();

  // Retorna cert si i només si la llista és buida.
  bool es_buida() const throw();

  // Retorna un iterador al primer/últim element o un iterador indefinit si la llista és buida.
  iterador primer() const throw();
  iterador ultim() const throw();

  // Retorna un iterador indefinit.
  iterador indef() const throw();
};
#endif

// Implementación
template <typename T>
llista_itr<T>::llista_itr() {
  _head = new node;
  _head->next = _head->prev = _head;
  _sz = 0;
}

template <typename T>
llista_itr<T>::llista_itr(const llista_itr<T> &l) {
  _head = new node;
  _head->next = copiar_llista(l._head->next, l._head, _head);
  _head->next->prev = _head;
  _sz = l._sz;
}

template <typename T>
typename llista_itr<T>::node*
llista_itr<T>::copiar_llista(node* orig, node* orig_head, node* h) {
  node* dst = h;
  if (orig != orig_head) {
    dst = new node;
    try {
      dst->info = orig->info;
      dst->next = copiar_llista(orig->next, orig_head, h);
      dst->next -> prev = dst;
    }
    catch (...) {
      delete dst;
      throw;
    }
  }
  return dst;
}

template <typename T>
llista_itr<T>& llista_itr<T>::operator=(const llista_itr<T> & l) {
  if (this != &l) {
    llista_itr<T> aux = l;
    swap(aux);
  }
  return *this;
}

template <typename T>
void llista_itr<T>::swap(llista_itr<T> &l) throw() {
  node* auxn = _head;
  _head = l._head;
  l._head = auxn;
  int auxs = _sz;
  _sz = l._sz;
  l._sz = auxs;
}

template <typename T>
void llista_itr<T>::destruir_llista(node* p, node* h) throw() {
  if (p != h) {
    destruir_llista(p->next, h);
    delete p;
  }
}

template <typename T>
llista_itr<T>::~llista_itr() throw() {
  destruir_llista(_head->next, _head);
  delete _head;
}

// El constructor per defecte de la classe iterador és privat per tal
// d'obligar a crear els iteradors mitjançant els mètodes primer, final i indef de la classe.
template <typename T>
llista_itr<T>::iterador::iterador() throw() {
}

// Operador preincrement ++a
template <typename T>
typename llista_itr<T>::iterador& llista_itr<T>::iterador::operator++() throw() {
  if (_p != _h) {
    _p = _p->next;
  }
  return *this;
}

// Operador postincrement a++
template <typename T>
typename llista_itr<T>::iterador llista_itr<T>::iterador::operator++(int) throw() {
  iterador tmp(*this);
  ++(*this); // es crida al mètode de preincrement
  return tmp;
}

template <typename T>
bool llista_itr<T>::iterador::operator==(iterador it) const throw() {
  return (_p == it._p) and (_h == it._h);
}

template <typename T>
bool llista_itr<T>::iterador::operator!=(iterador it) const throw() {
  return not (*this == it);
}

// Operador predecrement --a
template <typename T>
typename llista_itr<T>::iterador&
llista_itr<T>::iterador::operator--() throw() {
  if (_p != _h) {
    _p = _p->prev;
  }
  return *this;
}

// Operador postdecrement a--
template <typename T>
typename llista_itr<T>::iterador llista_itr<T>::iterador::operator--(int) throw() {
  iterador tmp(*this);
  --(*this); // es crida al mètode de predecrement
  return tmp;
}

template <typename T>
const T& llista_itr<T>::iterador::operator*() const {
  if (_p == _h) {
    throw IteradorIndef;
  }
  return _p->info;
}

template <typename T>
void llista_itr<T>::inserir_davant(const T& x, iterador it) {
  node* nn = new node;
  // no sabem com és el tipus T. Cap la possibilitat
  // que usi memòria dinàmica i per tant cal comprovar
  // que tot vagi bé.
  try {
    nn->info = x;
  }
  catch(...) {
    delete nn;
    throw;
  }
  nn->next = it._p->next;
  nn->prev = it._p;
  it._p->next = nn;
  nn->next->prev = nn;
  ++_sz;
}

template <typename T>
void llista_itr<T>::inserir_darrera(const T& x, iterador it) {
  node* nn = new node;
  try {
    nn -> info = x;
  }
  catch(...) {
    delete nn;
    throw;
  }
  nn->prev = it._p->prev;
  nn->next = it._p;
  it._p -> prev = nn;
  nn -> prev -> next = nn;
  ++_sz;
}

template <typename T>
void llista_itr<T>::esborrar_avnc(iterador& it) throw() {
  if (it._p != _head) {
    node* todel = it._p;
    todel->prev->next = todel->next;
    todel->next->prev = todel->prev;
    delete todel;
    --_sz;
    it._p = it._p -> next;
  }
}

template <typename T>
void llista_itr<T>::esborrar_darr(iterador& it) throw() {
  if (it._p != _head) {
    node* todel = it._p;
    todel->prev->next = todel->next;
    todel->next->prev = todel->prev;
    delete todel;
    --_sz;
    it._p = it._p->prev;
  }
}

template <typename T>
nat llista_itr<T>::longitud() const throw() {
  return _sz;
}

template <typename T>
bool llista_itr<T>::es_buida() const throw() {
  return _sz == 0;
}

template <typename T>
typename llista_itr<T>::iterador llista_itr<T>::primer() const throw() {
  iterador it;
  it._p = _head->next;
  it._h = _head;
  return it;
}

template <typename T>
typename llista_itr<T>::iterador llista_itr<T>::ultim() const throw() {
  iterador it;
  it._p = _head -> prev;
  it._h = _head;
  return it;
}

template <typename T>
typename llista_itr<T>::iterador llista_itr<T>::indef() const throw() {
  iterador it;
  it._p = _head;
  it._h = _head;
  return it;
}

// Programa 
#include <iostream>
using namespace std;

bool es_capicua(int n){
    llista_itr<int> l1;
    int modul;
    bool capi = true;

    while (n > 0){
        modul = n%10;
        l1.inserir_darrera(modul, l1.primer());
        n=n/10;
    }
    llista_itr<int>::iterador it1 = l1.primer();
    llista_itr<int>::iterador it2 = l1.ultim();
    while (it1 != it2 and capi){
        if (*it1 != *it2) capi = false;
        it1++;
        it2--;
    }
    return capi;
}


int main() {
    int n;
    while (cin >> n) cout << (es_capicua(n) ? "true" : "false") << endl;
}
