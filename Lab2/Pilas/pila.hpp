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
