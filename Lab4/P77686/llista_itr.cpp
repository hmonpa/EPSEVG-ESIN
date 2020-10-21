#include "llista_itr.hpp"

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
