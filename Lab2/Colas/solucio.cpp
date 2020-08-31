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

#endif
template <typename T>
cua<T>::cua() : _cua(NULL) {   
}

template <typename T>
cua<T>::cua(const cua<T> &c) : _cua(NULL) {
  if (c._cua != NULL) {
    _cua = new node;
    try {
      _cua->info = c._cua->info;
      _cua->seg = copiar(c._cua->seg, c._cua, _cua);
    }
    catch (...) { 
      delete(_cua);
      throw;
    }
  }
}

template <typename T>
typename cua<T>::node* cua<T>::copiar(node* n, node* fi, node* ini) {
  node* aux;
  if (n != fi) {
    aux = new node;
    try {
      aux->info = n->info;
      aux->seg = copiar(n->seg, fi, ini); 
    }
    catch (...) {
      delete aux;
      throw;
    }
  }
  else {
    aux = ini;
  }
  return aux;
}

template <typename T>
cua<T>& cua<T>::operator=(const cua<T> &c) {
  if (this != &c) {
    cua<T> caux(c);
    node* naux = _cua;
    _cua = caux._cua;
    caux._cua = naux;
  }
  return *this;
}

template <typename T>
cua<T>::~cua() throw() {
  if (_cua != NULL) {
    node* fi = _cua;
    _cua = _cua->seg;
    while (_cua != fi) {
      node* aux = _cua;
      _cua = _cua->seg;
      delete aux;
    }
    delete(_cua);
  }
}

template <typename T>
void cua<T>::encuar(const T &x) {
  node* p = new(node); 
  try {
    p->info = x;
  }
  catch (...) {
    delete p;
    throw;
  }
  if (_cua == NULL) {
    p->seg = p;  // cua amb un únic element que s’apunta 
  }              // a sí mateix
  else {
    p->seg = _cua->seg;
    _cua->seg = p;
  }
  _cua = p;
}

template <typename T>
void cua<T>::desencuar() { 
  if (_cua==NULL) {
    throw CuaBuida;
  }
  node* p = _cua->seg;
  if (p == _cua) {
    _cua = NULL; // desencuem una cua que tenia un únic 
  }              // element
  else {  
    _cua->seg = p->seg;
  }
  delete(p);
}

template <typename T>
const T& cua<T>::primer() const { 
  if (_cua==NULL) { 
    throw CuaBuida;
  }
  return (_cua->seg->info);
}

template <typename T>
bool cua<T>::es_buida() const throw() {  
  return (_cua==NULL);
}
#include <iostream>
#include <sstream>
using namespace std;

cua<int> elimina(cua <int> &q1){
    cua <int> q_res;
    int suma = 0;
    while (not q1.es_buida()){
        if (q1.primer() <= suma) q_res.encuar(q1.primer());
        suma+=q1.primer();
        q1.desencuar();
    }
    return q_res;                   // Se devuelve la cola resultante
}

void muestra(cua <int> &q1){
    while (not q1.es_buida()){
        cout << q1.primer();
        q1.desencuar();
        if (not q1.es_buida()) cout << " ";
    }
    cout << endl;
}

int main () {
    string line;
    int num;
    cua <int> q1;

    while (getline(cin, line)){     // Mientras entran líneas por el canal input, se leen y se guardan en un string (line)
        istringstream ss(line);     // Transforma el string line en un flujo de datos (ss)
        while (ss >> num){          // El flujo ss va enviando cada valor, simulando una entrada de datos
            q1.encuar(num);
        }
        q1 = elimina(q1);           // q1 coge el resultado de la función
        muestra(q1);
    }
}