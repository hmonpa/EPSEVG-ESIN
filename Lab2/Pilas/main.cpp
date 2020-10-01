#ifndef _PILA_HPP
#define _PILA_HPP
#include <cstddef>
using namespace std;

class pila {
  public: 
     pila();	          // constructor
     
     // tres grans
     pila(const pila& p); // constructor per còpia
     ~pila();             // destructor
     pila& operator=(const pila& p); // operador assignació
    
     void apilar(int x);
     void desapilar();
     int cim() const;
     bool es_buida() const;
    
  private:
     struct node { // definició de tipus privat
        node* seg; // punter al següent 'node'
        int info;
     };
     
     node* _cim; // la pila consisteix en un punter al node del cim
                 
     // mètode privat de classe per alliberar memòria; allibera la cadena de 
     // nodes que s'inicia en el node \emph{n}. 
     static void esborra_pila(node* n);
     
     // mètode privat de classe per realitzar còpies; còpia tota la cadena de nodes 
     // a partir del node apuntat per \emph{origen} i retorna un punter al node inicial de 
     // la còpia; la paraula reservada const indica que no es pot modificar el valor
     // apuntat pel punter \emph{origen}.
     static node* copia_pila(const node* origen);
};
#endif

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
#include <iostream>
#include <sstream>
using namespace std;

void muestra(pila& p1, pila& p2){
// p1 es la pila con números pares y p2 con impares
    while (not p1.es_buida()){
        cout << p1.cim();
        p1.desapilar();
        if (not p1.es_buida() or not p2.es_buida()) cout << " ";
    }
    while (not p2.es_buida()){
        cout << p2.cim();
        p2.desapilar();
        if (not p2.es_buida()) cout << " ";
    }
    cout << endl;
}

int main(){
    string line;
    int num;
    pila p1, p2;

    while (getline (cin, line)){        // Mientras entran líneas por el canal input, se leen y se guardan en un string (line)
        istringstream ss(line);         // Transforma el string line en un flujo de datos (ss)
        while (ss >> num){              // El flujo ss va enviando cada valor, simulando una entrada de datos
            if (num%2 == 0) p1.apilar(num);
            else p2.apilar(num);
        }
        muestra(p1, p2);
    }
}