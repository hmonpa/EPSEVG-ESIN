#ifndef ARBREBIN_HPP
#define ARBREBIN_HPP

#include <string>
#include <cstdlib>
#include <iostream>
#include <stack>

/// -----------------------------------------
///
///  Declaració operacions tipus ARBRE BINARI
///
/// -----------------------------------------

template <typename T>
class arbreBin {

  private:
    struct node {
      node* f_esq;
      node* f_dret;
      T info;
    };
    node* _arrel;

    static node* copia_nodes(node* m);
    /* Pre: cert */
    /* Post: si m és NULL, el resultat és NULL; sinó,
       el resultat apunta al primer node d'un arbre binari
       de nodes que són còpia de l'arbre apuntat per m */
    static void esborra_nodes(node* m);
    /* Pre: cert */
    /* Post: no fa res si m és NULL, sinó allibera
       espai dels nodes de l'arbre binari apuntat per m */

  public:
    //constructors
    arbreBin();
    /* Pre: cert */
    /* Post: el resultat és un arbre sense cap element */
    arbreBin(const arbreBin<T> &a);
    /* Pre: cert */
    /* Post: el resultat és una còpia de l'arbre rebut */
    arbreBin(const T &x,const arbreBin<T> &ae,const arbreBin<T> &ad);
    /* Pre: cert */
    /* Post: el resultat és un arbre amb un element i dos
       subarbres */

    //destructor: esborra automàticament els objectes locals
    //en sortir d'un àmbit de visibilitat
    ~arbreBin();

    //modificadors
    void a_buit();
    /* Pre: cert */
    /* Post: el paràmetre implícit no té cap element */
    arbreBin<T>& operator=(const arbreBin<T> &a);
    /* Pre: cert */
    /* Post: operació d'assignació d'arbres  */

    //consultors
    const T& arrel() const;
    /* Pre: el paràmetre implícit no és buit */
    /* Post: el resultat és l'arrel del paràmetre implícit */
    arbreBin<T> fe() const;
    /* Pre: el paràmetre implícit no és buit */
    /* Post: el resultat és el fill esquerre del p.i. original */
    arbreBin<T> fd() const;
    /* Pre: el paràmetre implícit no és buit */
    /* Post: el resultat és el fill dret del p.i. original */
    bool es_buit() const;
    /* Pre: cert */
    /* Post: el resultat indica si el p.i. és buit o no */

    // operador << d'escriptura
    template <class U> friend std::ostream& operator<<(std::ostream&, const arbreBin<U> &a);
    /* Pre: cert */
    /* Post: s'han escrit al canal estandard de sortida els elements d'a*/

    // operador >> de lectura
    template <class U> friend std::istream& operator>>(std::istream&, arbreBin<U> &a);
    /* Pre: a és buit; el canal estàndard d'entrada conté la mida de
       l'arbre i els nodes en postordre d'un arbre binari A; per cada
       node s'indica el seu valor i el nombre de fills */
    /* Post: a = A */
};


/// ------------------------------------------
///
///  Codificació operacions tipus ARBRE BINARI
///
/// ------------------------------------------

//privades ----------------------
template <typename T>
typename arbreBin<T>::node* arbreBin<T>::copia_nodes(node* m) {
  node* n;
  if (m == NULL) n = NULL;
  else {
    n = new node;
    try {
      n->info = m->info;
      n->f_esq = copia_nodes(m->f_esq);
      n->f_dret = copia_nodes(m->f_dret);
    } catch(...) {
      delete n;
      throw;
    }
  }
  return n;
};

template <typename T>
void arbreBin<T>::esborra_nodes(node* m) {
  if (m != NULL) {
    esborra_nodes(m->f_esq);
    esborra_nodes(m->f_dret);
    delete m;
  }
};

//constructors ----------------------
template <typename T>
arbreBin<T>::arbreBin()
/* Pre: cert */
/* Post: el resultat és un arbre sense cap element */
{
  _arrel = NULL;
}

template <typename T>
arbreBin<T>::arbreBin(const arbreBin<T>& a)
/* Pre: cert */
/* Post: el resultat és una còpia de a */
{
  _arrel = copia_nodes(a._arrel);
}

template <typename T>
arbreBin<T>::arbreBin(const T& x, const arbreBin<T>& ae, const arbreBin<T>& ad)
/* Pre: cert */
/* Post: el resultat és un arbre amb x com arrel, ae com a fill
esquerre i ad com a fill dret */
{
  _arrel = new node;
  try {
    _arrel->info = x;
    _arrel->f_esq = copia_nodes(ae._arrel);
    _arrel->f_dret = copia_nodes(ad._arrel);
  }
  catch (...) {
    delete _arrel;
    throw;
  }
}

//destructor ----------------------
template <typename T>
arbreBin<T>::~arbreBin() {
  esborra_nodes(_arrel);
}

//modificadors ----------------------
template <typename T>
void arbreBin<T>::a_buit()
/* Pre: cert */
/* Post: el paràmetre implícit no té cap element */
{
  esborra_nodes(_arrel);
  _arrel = NULL;
}

template <typename T>
arbreBin<T>& arbreBin<T>::operator=(const arbreBin<T>& a) {
  if (this != &a) {
    node* aux;
    aux = copia_nodes(a._arrel);
    esborra_nodes(_arrel);
    _arrel = aux;
  }
  return (*this);
}

//consultors ----------------------
template <typename T>
const T& arbreBin<T>::arrel() const {
/* Pre: el paràmetre implícit no és buit */
/* Post: el resultat és l'arrel del paràmetre implícit */
  if (this->es_buit()) {
    std::cout<<"ERROR - Operació 'arrel' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return _arrel->info;
}

template <typename T>
arbreBin<T> arbreBin<T>::fe() const
/* Pre: el paràmetre implícit no és buit */
/* Post: el resultat és el fill esquerre del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operació 'fe' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  arbreBin<T> a;
  a._arrel = copia_nodes(_arrel->f_esq);
  return a;
}

template <typename T>
arbreBin<T> arbreBin<T>::fd() const
/* Pre: el paràmetre implícit no és buit */
/* Post: el resultat és el fill dret del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operació 'fd' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  arbreBin<T> a;
  a._arrel = copia_nodes(_arrel->f_dret);
  return a;
}

template <typename T>
bool arbreBin<T>::es_buit() const
/* Pre: cert */
/* Post: el resultat indica si el p.i. és buit o no */
{
  return (_arrel == NULL);
}


/// ============================================== ///
///           Definició operacions friend          ///

// operador << d'escriptura
std::string dep = ""; 
template <class U>
std::ostream& operator<<(std::ostream &os , const arbreBin<U> &x) {
/* Pre: cert */
/* Post: s'han escrit al canal estàndard de sortida els elements de x */
  std::string d1=dep;
  if (x.es_buit()) 
    os << ".";
  else {
    os << "["<<x.arrel() << "]\n" << d1 << " \\__";
    dep = d1+" |  ";
    os << x.fd();
    os << "\n" << d1 << " \\__";
    dep = d1+"    ";
    os << x.fe();
  }
  dep = d1;
  return os;
}

// operador >> de lectura
template <class U>
std::istream& operator>>(std::istream &is, arbreBin<U> &x)
/* Pre: x és buit; el canal estàndard d'entrada conté la mida de
   l'arbre i els nodes en postordre d'un arbre binari X; per cada
   node s'indica el seu valor i el nombre de fills */
/* Post: x = X */ 
{  
  U node;
  int size, nf;
  std::stack<arbreBin<U> > p;

  is >> size;  
  while (size > 0) {
    is >> node >> nf;
    if (nf == 0) {  //fills buits
      p.push(arbreBin<U>(node, arbreBin<U>(), arbreBin<U>()));
    } else if (nf == -1) {    //nf=-1 --> nomes un fill, l'esquerre
      arbreBin<U> fe = p.top();
      p.pop();
      p.push(arbreBin<U>(node, fe, arbreBin<U>()));
    }
    else if (nf == 1) {       //nf=1 --> nomes un fill, el dret
      arbreBin<U> fd = p.top();
      p.pop();
      p.push(arbreBin<U>(node, arbreBin<U>(), fd));
    } else {                  //nf=2 --> dos fills no buits
      arbreBin<U> fd = p.top();
      p.pop();
      arbreBin<U> fe = p.top();
      p.pop();
      p.push(arbreBin<U>(node, fe, fd));
    }
    --size;
  }
  if (not p.empty()) x = p.top();
  return is;
}

#endif

