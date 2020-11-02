#include <iostream>
#include <stack>
#include <cstddef>
using namespace std;

// Especificación
template <typename T>
class Arbre {
private:
  Arbre(): _arrel(NULL) {};
  struct node {
    T info;
    node* primf;
    node* seggerm;
  };
  node* _arrel;
  static node* copia_arbre(node* p);
  static void destrueix_arbre(node* p) throw(); 

  // Mètode sumaArb afegit
  static node* sumaArb(node *n1, node *n2);
  // Mètode preordre afegit (amb punter)
  static void preordre(node *n);

public:
  // Construeix un Arbre format per un únic node que conté a x.
  Arbre(const T &x);

  // Tres grans.
  Arbre(const Arbre<T> &a);
  Arbre& operator=(const Arbre<T> &a);
  ~Arbre() throw();

  // Col·loca l'Arbre donat com a primer fill de l'arrel de l'arbre sobre el que s'aplica el mètode i l'arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
  void afegir_fill(Arbre<T> &a);

  // Iterador sobre arbre general.
  friend class iterador;
  class iterador {
  public:
    friend class Arbre;

    // Construeix un iterador no vàlid.
    iterador() throw();

    // Retorna el subarbre al que apunta l'iterador; llança un error si l'iterador no és vàlid.
    Arbre<T> arbre() const;

    // Retorna l'element del node al que apunta l'iterador o llança un error si l'iterador no és vàlid.
    T operator*() const;

    // Retorna un iterador al primogenit del node al que apunta; llança un error si l'iterador no és vàlid.
	  iterador primogenit() const;

    // Retorna un iterador al següent germà del node al que apunta; llança un error si l'iterador no és vàlid.
    iterador seg_germa() const;

    // Operadors de comparació.
    bool operator==(const iterador &it) const {
      return _p == it._p;
    };
    bool operator!=(const iterador &it) const {
      return _p != it._p;
    };
    static const int IteradorInvalid = 410;

  private:
    Arbre<T>::node* _p;
  };
    
  // Retorna un iterador al node arrel de l'Arbre (un iterador no vàlid si l'arbre no és vàlid).
  iterador arrel() const throw();

  // Retorna un iterador no vàlid.
  iterador final() const throw();

  static const int ArbreInvalid = 400;

  // Operador + afegit
  Arbre& operator+(const Arbre<T> &a);
  // Mètode preordre afegit
  void preordre();
};

// Implementación
// La còpia es fa seguint un recorregut en preordre.
template <typename T>				
typename Arbre<T>::node* Arbre<T>::copia_arbre(node* p) { 
  node* aux = NULL;
  if (p != NULL) {
    aux = new node;
    try {
      aux -> info = p -> info;
      aux -> primf = aux -> seggerm = NULL;
      aux -> primf = copia_arbre(p -> primf);
      aux -> seggerm = copia_arbre(p -> seggerm);
    }
    catch (...) {
      destrueix_arbre(aux);
    }
  }
  return aux;
}

// La destrucció es fa seguint un recorregut en postordre.
template <typename T>	
void Arbre<T>::destrueix_arbre(node* p) throw() { 
  if (p != NULL) {
    destrueix_arbre(p -> primf);
    destrueix_arbre(p -> seggerm);
    delete p;
  }
}

// Construcció d'un arbre que conté un sol element x a l'arrel.
template <typename T>	
Arbre<T>::Arbre(const T &x) {
  _arrel = new node; 
  try {
    _arrel -> info = x;
    _arrel -> seggerm = NULL;
    _arrel -> primf = NULL;
  } 
  catch (...) {
    delete _arrel;
    throw;
  }
}

template <typename T>	
Arbre<T>::Arbre(const Arbre<T> &a) { 
  _arrel = copia_arbre(a._arrel);
}

template <typename T>	
Arbre<T>&  Arbre<T>::operator=(const Arbre<T> &a) { 
  Arbre<T> tmp(a);
  node* aux = _arrel;
  _arrel = tmp._arrel;
  tmp._arrel = aux;
  return *this;
}

template <typename T>	
Arbre<T>::~Arbre() throw() { 
  destrueix_arbre(_arrel);
}

template <typename T>	
void Arbre<T>::afegir_fill(Arbre<T> &a) { 
  if (_arrel == NULL or a._arrel == NULL or 
    a._arrel -> seggerm != NULL) {
    throw ArbreInvalid;
  }
  a._arrel -> seggerm = _arrel -> primf;
  _arrel -> primf = a._arrel;
  a._arrel = NULL;
}

template <typename T>
typename Arbre<T>::iterador Arbre<T>::arrel() const throw() { 
  iterador it;
  it._p = _arrel;
  return it;
}

template <typename T>	
typename Arbre<T>::iterador Arbre<T>::final() const throw() { 
  return iterador();
}

template <typename T>				
Arbre<T>::iterador::iterador() throw(): _p(NULL) { 
}

template <typename T>	
T Arbre<T>::iterador::operator*() const { 
  if (_p == NULL) {
    throw IteradorInvalid;
  }
  return _p -> info;
}

template <typename T>	
typename Arbre<T>::iterador Arbre<T>::iterador::primogenit() const { 
  if (_p == NULL) {
    throw IteradorInvalid;
  }
  iterador it;
  it._p = _p -> primf;
  return it;
}

template <typename T>	
typename Arbre<T>::iterador Arbre<T>::iterador::seg_germa() const { 
  if (_p == NULL) {
    throw IteradorInvalid;
  }
  iterador it;
  it._p = _p -> seggerm;
  return it;
}

template <typename T>	
Arbre<T> Arbre<T>::iterador::arbre() const { 
  if (_p == NULL) {
    throw IteradorInvalid;
  }
  Arbre<T> a;
  a._arrel = _p;
  Arbre<T> aux(a);
  a._arrel = NULL;
  return aux;
}

// Operador + afegit
template <typename T>
Arbre<T>&  Arbre<T>::operator+(const Arbre<T> &a){
    _arrel = sumaArb(_arrel,a._arrel);
    return *this;
}

// Mètode sumaArb afegit
template <typename T>
typename Arbre<T>::node* Arbre<T>::sumaArb(node *n1, node *n2){
    // n1 apunta a l'arrel del p.i, n2 apunta a l'arrel de a
    node* aux = NULL;
    if (n1 != NULL and n2 != NULL){         // CR1: Cap arbre es buit
        aux = new node;
        try{
            aux->info = n1->info+n2->info;
            aux->primf = NULL;
            aux->seggerm = NULL;
            aux->primf = sumaArb(n1->primf, n2->primf);
            aux->seggerm = sumaArb(n1->seggerm, n2->seggerm);
        }
        catch(...){
            destrueix_arbre(aux);
        }
    }
    else if (n1 != NULL and n2 == NULL){    // CR2: p.i no buit, arbre 2 buit
        aux = new node;
        try{
            aux->info = n1->info;
            aux->primf = NULL;
            aux->seggerm = NULL;
            aux->primf = sumaArb(n1->primf, aux->primf);
            aux->seggerm = sumaArb(n1->seggerm, aux->seggerm);
        }
        catch(...){
            destrueix_arbre(aux);
        }
    }
    else if (n1 == NULL and n2 != NULL){    // CR3: p.i buit, arbre 2 no buit
        aux = new node;
        try{
            aux->info = n2->info;
            aux->primf = NULL;
            aux->seggerm = NULL;
            aux->primf = sumaArb(n2->primf, aux->primf);
            aux->seggerm = sumaArb(n2->seggerm, aux->seggerm);
        }
        catch(...){
            destrueix_arbre(aux);
        }
    }
    return aux;
}

// Mètode preordre afegit
template <typename T>
void Arbre<T>::preordre(){
    preordre(_arrel);           // Truca al mètode preordre amb punter (el següent mètode del codi), passant-li l'arrel del p.i
}

// Mètode preordre afegit (amb punter)
template <typename T>
void Arbre<T>::preordre(node *n){
    if (n != NULL){
        cout << " " << n->info;
        preordre(n->primf);
		    preordre(n->seggerm);
    }
}

// Programa
Arbre<int> crea(){
    int info, nf;
    cin >> info >> nf;
    stack < Arbre<int> > pila;

    Arbre<int> T(info);

    if (nf > 0){
        for (unsigned int i=0;i<nf;i++){
            Arbre<int> fill = crea();
            pila.push(fill);
        }
        while (!pila.empty()){
            T.afegir_fill(pila.top());
            pila.pop();
        }
    }
    return T;
}

int main () {
    int tam;
    cin >> tam;
    Arbre<int> T1 = crea();
    cin >> tam;
    Arbre<int> T2 = crea();
    T1+T2;
    T1.preordre();              // Truca al mètode preordre per l'arbre T1, després trucarà al mètode preordre passant-li a un punter a l'arrel de T1
    cout << endl;
}
