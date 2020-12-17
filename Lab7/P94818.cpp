#include <iostream>
#include <cstddef>
#include <vector>
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

    // Especificació mètodes privats afegits:
    static node* introBst(node* n, T info);
    static void printBst(node* n, const T K);
    static void fulles(node* n, vector<int> &valors);
    static void nivell(node* n, nat num, nat nivact, bool &trobat);
    static void equivalents(node *n, bool &trobat);
    static void es_avl(node*n, int &cont1, int &cont2);


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

    // Especificació mètodes públics afegits:
    void introBst(T info);
    void printBst();
    vector<int> fulles() const;
    void nivell(nat n);
    void equivalents();
    bool es_avl();

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


// Mètode afegir nodes a un BST
template <typename T>
void Abin<T>::introBst(T info){
    _arrel = introBst(_arrel, info);
}

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

// Mètode imprimir BST
template <typename T>
void Abin<T>::printBst(){
    printBst(_arrel, 1);
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

// Mètode fulles de l'arbre a un vector
template <typename T>
vector <int> Abin<T>::fulles() const{
  vector<int> valors;
  fulles(_arrel, valors);

  return valors;
}

template <typename T>
void Abin<T>::fulles(node* n, vector<int> &valors){
  if (n != NULL){
    if (n->f_esq == NULL and n->f_dret == NULL){
      valors.push_back(n->info);
    }
    fulles(n->f_esq, valors);
    fulles(n->f_dret, valors);
  }
}

// Mètode nivells de l'arbre
template <typename T>
void Abin<T>::nivell(nat n){
  bool trobat = false;
  nivell(_arrel, n, 0, trobat);
  if (not trobat){
    cout << "El nivell introduït no existeix" << endl;
  }
}

template <typename T>
void Abin<T>::nivell(node* n, nat num, nat nivact, bool &trobat){
  if (n != NULL){
    if (num == nivact){
      cout << n->info << " ";
      trobat = true;
    }
    else {
      nivact++;
      nivell(n->f_esq, num, nivact, trobat);
      nivell(n->f_dret, num, nivact, trobat);
    }
  }
}


// Mètode equivalents (FDRET - FESQ = PARE)
template <typename T>
void Abin<T>::equivalents(){
  bool trobat = true;
  equivalents(_arrel,trobat);
  if (trobat) cout << "El BST es totalment equivalent" << endl;
  else        cout << "No es un BST equivalent" << endl;
}

template <typename T>
void Abin<T>::equivalents(node* n, bool &trobat){
  if (n!=NULL and trobat){
    if (n->f_esq != NULL and n->f_dret != NULL)
    {
      //cout << "Resultado act: " << n->f_dret->info-n->f_esq->info << endl;
      if (n->info != n->f_dret->info-n->f_esq->info){
        //cout << "NO concuerda " << endl;
        trobat = false;
      }
      else{
        equivalents(n->f_esq, trobat);
        equivalents(n->f_dret, trobat);
      }
    }

  }
}

// Mètode comprova si es AVL
template <typename T>
bool Abin<T>::es_avl(){
  int cont_fesq = 0;
  int cont_fdret = 0;
  bool avl = true;
  es_avl(_arrel, cont_fesq, cont_fdret);

  int contTotal = cont_fesq - cont_fdret;
  if (contTotal < -1 || contTotal > 1){
    avl = false;
  }
  return avl;
}

template <typename T>
void Abin<T>::es_avl(node* n, int &cont1, int &cont2){
  if (n!=NULL){

    if (n->f_esq != NULL){
      cont1++;
      es_avl(n->f_esq, cont1, cont2);
    }
    if (n->f_dret != NULL){
      cont2++;
      es_avl(n->f_dret, cont1, cont2);
    }
  }
}

// --------------
// Programa
// --------------

int main() {
    nat quants;
    nat num;                    // Node introduït
    Abin<int> T;                // Creació arbre binari
    cout << "Introduce numero de elementos del BST: " << endl;
    cin >> quants;
    cout << "Introduce los nodos " << endl;
    for (int i=0;i<quants;i++){
        cin >> num;  
        T.introBst(num);
    }
    T.printBst();
    cout << endl << endl;
    //cout << "Nombre de nodes amb els dos fills buits: " <<  T.fulles() << endl;
    vector<int> v;
    T.equivalents();

    v = T.fulles();
    cout << "Numero de hojas: " << v.size() << endl;
    for (int i=0; i<v.size(); i++){
      cout << v[i] << " ";
    }
    cout << endl << endl;
    cout << "Introduce un nivel del que quieres ver sus nodos: " << endl;
    nat niv;
    cin >> niv;
    T.nivell(niv);
    cout << endl;
    cout << (T.es_avl() ? "Es un AVL" : "No es un AVL");
}