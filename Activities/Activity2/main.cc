#include <iostream>
#include <stack>
 #include <cstdlib>
 #include <string>
 using namespace std;
 typedef unsigned int nat;
 
 template <typename T>
 class Arbre {
 
 public:
   // Construeix un Arbre format per un únic node que conté a x.
   Arbre(const T &x);
 
   // Tres grans.
   Arbre(const Arbre<T> &a);
   Arbre& operator=(const Arbre<T> &a);
   ~Arbre() throw();
 
   // Col·loca l’Arbre donat com a primer fill de l’arrel de l’arbre sobre el que s’aplica el mètode i l’arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
   void afegir_fill(Arbre<T> &a);
 
   static const int ArbreInvalid = 400;
 
   // Comprova que el contingut de cada node coincideix amb la suma dels nodes
   // dels seus fills, exceptuant les fulles (els de grau 0).
   bool es_arbre_suma();
 
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
   static bool es_arbre_suma(node*p, int suma, bool res, int cont);
 };
 
 // Aquí va la implementació del mètode es_arbre_suma


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
bool Arbre<T>::es_arbre_suma(){
    int suma = 0;
    bool res = true;

    return es_arbre_suma(_arrel, suma, res, 1);
}

template <typename T>	
bool Arbre<T>::es_arbre_suma(node*p, int suma, bool res, int cont){

  if (p != NULL){
    node* pare;                                     // Punter pare per comparar amb la variable suma
      if (cont != 1) {                              // Comptem l'arrel a part, per no tenir en compte la variable suma
        cout << "Nodo " << p->info << endl;
        suma+=p->info;                              // Suma es guarda la informació de cada node
        cout << "Suma: " << suma << endl;
        cout << "---------------" << endl;
      }
      if (p->seggerm != NULL) es_arbre_suma(p->seggerm, suma, res, cont);   // Si n'hi ha mes germans...
      
      if (p->primf != NULL){    // Si no hi han mes germans, pero si fills
        pare = p;
        if (cont != 1){
          if (suma != pare->info){
            res = false;
          }
        }
        es_arbre_suma(p->primf, 0, res, ++cont);      // Al trucar al seg fill, cont s'incrementa i suma passa a valer 0
      } 
      res = suma==pare->info;                         // el bool res es true quan es compleix que suma es igual al valor de pare
  }
  return res;
}

// Llegeix un arbre general des de cin i el retorna.
Arbre<int> arbre() {
  int valor, nf;
  cin >> valor >> nf;
  Arbre<int> a(valor);
  stack<Arbre<int> > pa;
  while (nf>0) {
    pa.push(arbre());
    nf--;
  }
  while (not pa.empty()) {
    a.afegir_fill(pa.top());
    pa.pop();
  }
  return a;
}

int main() {
  Arbre<int> a(arbre());
  if (a.es_arbre_suma())
    cout << "SI és arbre suma\n";
  else
    cout << "NO és arbre suma\n";
  return 0;
}
