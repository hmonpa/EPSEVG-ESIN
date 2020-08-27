#ifndef _CUA_HPP
#define _CUA_HPP
#include <cstddef>
using namespace std;

template <typename T>
class cua {
private: 
  struct node {
    T info;
    node* seg;
  };
  node* _cua;

  node* copiar(node* n, node* fi, node* ini);

public:
  // Construeix una cua buida.
  cua();

  // Tres grans: constructora per còpia, operador d'assignació i destructora.
  cua(const cua<T> &c);
  cua<T>& operator=(const cua<T> &c);
  ~cua() throw();

  // Afegeix un element al final de la cua. 
  void encuar(const T &x);

  // Treu el primer element de la cua. Llança un error si la cua és buida.
  void desencuar();

  // Obté el primer element de la cua. Llança un error si la cua és buida.
  const T& primer() const;

  // Consulta si la cua és buida o no.
  bool es_buida() const throw();

  static const int CuaBuida = 310;
};

#include "cua.t"
#endif
