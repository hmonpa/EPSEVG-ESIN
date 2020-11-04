 #include <stack>
 #include <iostream>
 #include <cstdlib>
 #include <vector>
 using namespace std;
 typedef unsigned int nat;

// --------------
// Especificació
// --------------

 template <typename T>
 class Arbre {
 
 public:
   // Construeix un Arbre format per un únic node que conté a x.
   Arbre(const T &x);
 
   // Tres grans.
   Arbre(const Arbre<T> &a);
   Arbre& operator=(const Arbre<T> &a);
   ~Arbre() throw();
 
   // Col·loca l’Arbre donat com a darrer fill de l’arrel de l’arbre sobre el que s’aplica el mètode i l’arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
   void afegir_darrer_fill(Arbre<T> &a);
 
   static const int ArbreInvalid = 400;
 
   // Escriu una línia amb els elements del nivell i, d’esquerra a dreta.
   // Cada element ha de sortir precedit d’un espai.
   void nivell(nat i) const;
 
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
 
   // Aquí va l’especificació dels mètodes privats addicionals
   static void nivell(nat i, node* m, nat niv);
 };

// --------------
// Implementació
// --------------

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

template <typename T>	
void Arbre<T>::destrueix_arbre(node* p) throw() { 
  if (p != NULL) {
    destrueix_arbre(p -> primf);
    destrueix_arbre(p -> seggerm);
    delete p;
  }
}

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
void Arbre<T>::afegir_darrer_fill(Arbre<T> &a) { 
  if (_arrel == NULL or a._arrel == NULL) {
    throw ArbreInvalid;
  }
  node *p = _arrel -> primf;
  if (p == NULL) {
    _arrel -> primf = a._arrel;
  } else {
    while (p -> seggerm != NULL) {
      p = p -> seggerm;
    }
    p -> seggerm = a._arrel;
  }
  a._arrel = NULL;
}


 // Aquí va la implementació del mètode nivell
 template <typename T>	
 void Arbre<T>::nivell(nat i) const {
   int niv = 0;
   nivell(i, _arrel, niv);
 }

 // Mètode nivell amb punter: i es el nivell que es passa des del main, m es un punter a l'arrel i niv es el nivell inicial (0)
 template <typename T>	
 void Arbre<T>::nivell(nat i, node* m, nat niv){
   if (m != NULL){
     //if (m->primf !=NULL) cout << "Node " << m->info << " te com a fill: " << m->primf->info << " i està al nivell : " << niv << endl;
     //else cout << "Node " << m->info << " es una fulla" <<  " i està al nivell : " << niv << endl;
     if (niv == i)    cout << " " << m->info;         // Nivell (niv) = i (nivell introduït per l'usuari)
     if (niv < i)     nivell(i,m->primf, niv+1);      // Nivell es menor a i, incrementem niv
     if (niv <= i)    nivell(i, m->seggerm, niv);     // niv es menor o igual, recorrem el/s seg. germàns i anem imprimim              
   }
}

// --------------
// Programa
// --------------

// Llegeix un arbre general des de cin i el retorna.
Arbre<int> arbre() {
  int valor, nf;
  cin >> valor >> nf;
  Arbre<int> a(valor);
  while (nf>0) {
    Arbre<int> af = arbre();
    a.afegir_darrer_fill(af);
    nf--;
  }
  return a;
}

int main() {
  int n;
  Arbre<int> a(arbre());
  while (cin >> n) {
    a.nivell(n);
    cout << endl;
  }
  return 0;
}
