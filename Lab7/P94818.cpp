#include <iostream>
#include <cstddef>
using namespace std;
typedef unsigned int nat;

// -------------------------
// Especificació classe Abin
// -------------------------

template <typename T>
class Abin {
  private:
    struct node {
      node* f_esq;
      node* f_dret;
      T info;
    };
    node* _arrel;
    static node* copia_nodes(node* m);
    static void esborra_nodes(node* m);
    // Esp. mètodes privats afegits:
    static node* introBst(node* n, T info);
    static void printBst(node* n, const T K);
    static void consultaBst(node* n, const T &info, bool &res);

  public:
    //constructors
    Abin(): _arrel(NULL) {};
    /* Pre: cert */
    /* Post: el resultat és un arbre sense cap element */
    Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
    /* Pre: cert */
    /* Post: el resultat és un arbre amb un element i dos subarbres */

    // Les tres grans
    Abin(const Abin<T> &a);
    ~Abin();
    Abin<T>& operator=(const Abin<T>& a);

    // Iterador sobre arbres binaris.
    friend class iterador;
    class iterador {
      private:
        Abin<T>::node* _p;

      public:
        friend class Abin;
        iterador(): _p(NULL) {};
        /* Pre: cert */
        /* Post: Construeix un iterador no vàlid. */

        Abin<T> arbre() const;
        /* Pre: cert */
        /* Post: Retorna el subarbre al que apunta l'iterador; llança un error
        si l'iterador no és vàlid. */

        T operator*() const;
        /* Pre: cert */
        /* Post: Retorna l'element en el node al que apunta l'iterador, o
        llança un error si l'iterador no és vàlid. */

        iterador fesq() const;
        /* Pre: cert */
        /* Post: Retorna un iterador al fill esquerre; llança
        un error si l'iterador no és vàlid. */

        iterador fdret() const;
        /* Pre: cert */
        /* Post: Retorna un iterador al fill dret; llança
        un error si l'iterador no és vàlid. */

        /* Operadors de comparació. */
        bool operator==(const iterador &it) const {
          return _p == it._p;
        };
        bool operator!=(const iterador &it) const {
          return _p != it._p;
        };
        static const int IteradorInvalid = 410;
    };

    // Esp. mètodes públics afegits:
    void introBst(T info);
    void printBst();
    bool consultaBst(const T &info);

    //consultors
    bool es_buit() const;
    /* Pre: cert */
    /* Post: el resultat indica si el p.i. és buit o no */

    iterador arrel() const;
    /* Pre: cert */
    /* Post: Retorna un iterador al node arrel. */
    
    iterador final() const;
    /* Pre: cert */
    /* Post: Retorna un iterador no vàlid. */
};

// -------------------------
// Implementació classe Abin
// -------------------------

template <typename T>
typename Abin<T>::node* Abin<T>::copia_nodes(node* m) {
/* Pre: cert */
/* Post: si m és NULL, el resultat és NULL; sinó,
   el resultat apunta al primer node d'un arbre binari
   de nodes que són còpia de l'arbre apuntat per m */
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
void Abin<T>::esborra_nodes(node* m) {
/* Pre: cert */
/* Post: no fa res si m és NULL, sinó allibera
   espai dels nodes de l'arbre binari apuntat per m */
  if (m != NULL) {
    esborra_nodes(m->f_esq);
    esborra_nodes(m->f_dret);
    delete m;
  }
};

template <typename T>
Abin<T>::Abin(Abin<T>& ae, const T& x, Abin<T>& ad) {
/* Pre: cert */
/* Post: el resultat és un arbre amb x com arrel, ae com a fill
esquerre i ad com a fill dret. No fa còpia dels arbres ae i ad */
  _arrel = new node;
  try {
    _arrel->info = x;
  }
  catch (...) {
    delete _arrel;
    throw;
  }
  _arrel->f_esq = ae._arrel;
  ae._arrel = NULL;
  _arrel->f_dret = ad._arrel;
  ad._arrel = NULL;
}

template <typename T>
Abin<T>::Abin(const Abin<T> &a) {
  _arrel = copia_nodes(a._arrel);
};

template <typename T>
Abin<T>::~Abin() {
  esborra_nodes(_arrel);
};

template <typename T>
Abin<T>& Abin<T>::operator=(const Abin<T>& a) {
  if (this != &a) {
    node* aux;
    aux = copia_nodes(a._arrel);
    esborra_nodes(_arrel);
    _arrel = aux;
  }
  return (*this);
};

template <typename T>
bool Abin<T>::es_buit() const {
/* Pre: cert */
/* Post: el resultat indica si el p.i. és buit o no */
  return (_arrel == NULL);
};

template <typename T>
typename Abin<T>::iterador Abin<T>::arrel() const {
/* Pre: cert */
/* Post: Retorna un iterador al node arrel. */
  iterador it;
  it._p = _arrel;
  return it;
};

template <typename T>
typename Abin<T>::iterador Abin<T>::final() const{
/* Pre: cert */
/* Post: Retorna un iterador no vàlid. */
  return iterador();
};

template <typename T>
Abin<T> Abin<T>::iterador::arbre() const {
/* Pre: cert */
/* Post: Retorna el subarbre al que apunta l'iterador; llança un error
si l'iterador no és vàlid. */
  if (_p == NULL)
    throw IteradorInvalid;
  Abin<T> a;
  a._arrel = copia_nodes(_p);;
  return a;
};

template <typename T>
T Abin<T>::iterador::operator*() const {
/* Pre: cert */
/* Post: Retorna l'element en el node al que apunta l'iterador, o
llança un error si l'iterador no és vàlid. */
  if (_p == NULL)
    throw IteradorInvalid;
  return _p->info;
};

template <typename T>
typename Abin<T>::iterador Abin<T>::iterador::fesq() const {
/* Pre: cert */
/* Post: Retorna un iterador al fill esquerre; llança
un error si l'iterador no és vàlid. */
  if (_p == NULL) 
    throw IteradorInvalid;
  iterador it;
  it._p = _p->f_esq;
  return it;
};

template <typename T>
typename Abin<T>::iterador Abin<T>::iterador::fdret() const {
/* Pre: cert */
/* Post: Retorna un iterador al fill dret; llança
un error si l'iterador no és vàlid. */
  if (_p == NULL) 
    throw IteradorInvalid;
  iterador it;
  it._p = _p->f_dret;
  return it;
};

// Implementació mètodes privats

template <typename T>
typename Abin<T>::node* Abin<T>::introBst(node* n, T info){
    node* n2 = NULL;

    if (n != NULL){     // Arbre no buit
        n2 = new node;
        try{
            if (n->info == info) n2 = n;        // Elements repetits s'ignoren
            else if (n->info > info){           // Node de l'arbre es major a l'element que volem introduïr, per tant, tindrem que insertar-ho a la seva esquerra
                n2->info = n->info;
                n2->f_dret = n->f_dret;
                n2->f_esq = introBst(n->f_esq, info);
            }
            else {                              // Node de l'arbre es menor a l'element que volem introduïr, per tant, tindrem que insertar-ho a la seva dreta
                n2->info = n->info;
                n2->f_esq = n->f_esq;
                n2->f_dret = introBst(n->f_dret, info);
            }
        }
        catch(...){
            delete n2;
            throw;
        }
    }
    else {              // Arbre buit
        n2 = new node;
        try{
            n2->info = info;
            n2->f_esq = NULL;
            n2->f_dret = NULL;
            n = n2;
        }
        catch(...){
            delete n2;
            throw;
        }
    }
    return n2;
}

template <typename T>
void Abin<T>::consultaBst(node* n, const T &info, bool &res){
  if (n != NULL){
    //cout << n->info << " "  << info << endl;
    if (info == n->info) res = true;
    else {
      if (info > n->info) consultaBst(n->f_dret, info, res);
      else consultaBst(n->f_esq, info, res);
    }
  }
}

template <typename T>
void Abin<T>::printBst(node* n, const T K){

    if (n!=NULL){
        printBst(n->f_dret,K+1);
        cout.width(10*K);       // Espais entre nodes
        cout << n->info << endl;
        printBst(n->f_esq,K+1);
    }
}
// Impl. mètode públic (truquen al privat)

template <typename T>
void Abin<T>::introBst(T info){
    _arrel = introBst(_arrel, info);
}

template <typename T>
void Abin<T>::printBst(){
    printBst(_arrel, 1);
}

template <typename T>
bool Abin<T>::consultaBst(const T &info){
  bool res = false;
  consultaBst(_arrel, info, res);
  return res;
}

// --------------
// Programa
// --------------

int main() {                      
    Abin<int> T;                // Creació arbre binari
    int n, mida, cont = 0;

    cin >> mida;
    while (cont < mida and cin >> n){
      if (n>=0){
        T.introBst(n);
        cont++;
      }
    }

    while (cin >> n){     
        if (n >=0){
          bool res = T.consultaBst(n);
          cout << n << " " << res << endl;
        }
    }
}