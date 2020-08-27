#include "pila.hpp"

// -------------------------
// MÈTODES PRIVATS DE CLASSE
// -------------------------

void pila::esborra_pila(node *n) {
   if (n != NULL) {
      esborra_pila(n->seg); // p-$>$seg equival a (*p).seg 
      delete n; // allibera la memòria de l'objecte apuntat per \emph{n}.
   }
}

// és necessari posar ¿pila::node¿ com tipus del resultat per què ¿node¿ 
// està definit de la classe pila
pila::node* pila::copia_pila(const node* origen) {
   node* desti = NULL;
   if (origen != NULL) {
      desti = new node;
      desti->info = origen->info;
      
      // copia la resta de la cadena
      desti->seg = copia_pila(origen->seg);  
   }
   return desti; 
}

// -------------------------
// MÈTODES PÚBLICS
// -------------------------
pila::pila() : _cim(NULL) { }

// genera una còpia de la pila apuntada per 'p.\_cim'
pila::pila(const pila& p) {
   _cim = copia_pila(p._cim);
}

// allibera la memòria de la pila apuntada per '\_cim'
pila::~pila() {
   esborra_pila(_cim);
}

pila& pila::operator=(const pila& p) {
   if (this != &p) {
      node* aux = copia_pila(p._cim); 
      esborra_pila(_cim);
      _cim = aux;
   }
   return *this; // retorna una referència a la pila que invoca el mètode.
}

void pila::apilar(int x) {
   node* n = new node;
   n->info = x;
   n->seg = _cim; // connecta el nou node amb el primer node de la pila i
                  // fa que aquest sigui el cim
   _cim = n;
}

void pila::desapilar() {
   node* n = _cim;
   if (_cim != NULL) {
      _cim = _cim->seg;
      delete n;
   }
   // faltaria tractar l'error de pila buida
}

int pila::cim() const {
   if (_cim != NULL) {
      return _cim->info;
   }
   // faltaria tractar l'error de pila buida
}

bool pila::es_buida() const {
   return _cim == NULL;
}
