 #include <iostream>
 #include <iostream>
 #include <cstdlib>
 using namespace std;
 typedef unsigned int nat;

 // --------------
 // Especificació
 // --------------

 template <typename T>
 class Abin {
   public:
     Abin(): _arrel(NULL) {};
     // Pre: cert
     // Post: el resultat és un arbre sense cap element
     Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
     // Pre: cert
     // Post: el resultat és un arbre amb un element i dos subarbres
 
     // Les tres grans
     Abin(const Abin<T> &a);
     ~Abin();
     Abin<T>& operator=(const Abin<T>& a);
 
     // Escriu una línia amb els elements del nivell i-èssim, d’esquerra 
     // a dreta. Cada element ha de sortir precedit d’un espai.
     void nivell(nat i) const;
 
   private:
     struct node {
       node* f_esq;
       node* f_dret;
       T info;
     };
     node* _arrel;
     static node* copia_nodes(node* m);
     static void esborra_nodes(node* m);
 
     // Aquí va l’especificació dels mètodes privats addicionals
     static void nivell(nat i, node* n, nat niv);
 };
 
// --------------
// Implementació
// --------------

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

// Aquí va la implementació del mètode nivell
 template <typename T>	
 void Abin<T>::nivell(nat i) const{
   int niv = 0;
   nivell(i, _arrel, niv);
 }

 template <typename T>	
 void Abin<T>::nivell(nat i, node* n, nat niv){
   if (n != NULL){
     if (i == niv){
       cout << " " << n->info;
     }
     else{
       niv++;
       nivell(i, n->f_esq, niv);  // o nivell(i, n->f_esq, niv+1);
       nivell(i, n->f_dret, niv); // o nivell(i, n->f_dret, ++niv);   // pero NO así: nivell(i, n->f_dret, niv++);
     }
   }
 }

// --------------
// Programa
// --------------

// Llegeix un arbre binari des de cin i el retorna.
Abin<int> llegir_arbre() {
  Abin<int> a;
  int valor;
  cin >> valor;
  if (valor != -1) {
    Abin<int> ae = llegir_arbre();
    Abin<int> ad = llegir_arbre();
    a = Abin<int>(ae, valor, ad);
  }
  return a;
}

int main() {
  Abin<int> a(llegir_arbre());
  nat n;
  while (cin >> n) {
    a.nivell(n);
    cout << endl;
  }
  return 0;
}
