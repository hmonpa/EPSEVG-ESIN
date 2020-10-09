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
#include <vector>
using namespace std;

int read(){
    int num;
    cin >> num;
    return num;
}

void muestra(vector<cua <string> > &cs, int n){
    cout << endl << "CONTINGUTS FINALS" << endl << "-----------------" << endl;
    for (int i=0; i<n; i++){
        cout << "cua " << i+1 << ":";
        while (not cs[i].es_buida()){
            cout << " " << cs[i].primer();
            cs[i].desencuar();
        }
        cout << endl;
    }
}

int main() {
    int n = read();
    vector<cua <string> > cs(n);        // Vector de colas de strings, con tamaño n
    string line;
    getline(cin,line);
    // Introducción de N colas con sus respectivos nombres:
    for (int i=0; i<n; i++){            
        getline(cin,line);              // Mientras se recorren todas las colas, se leen datos de entrada y se guardan en un string (line)
        istringstream ss(line);         // Transforma el string line en un flujo de datos (ss)
        string name;

        while (ss >> name)  cs[i].encuar(name);     // El flujo ss va enviando cada valor, simulando una entrada de datos y mete dichos datos en el vector de colas cs
    }
    // Una vez introducidas las N colas:
    cout << "SORTIDES" << endl << "--------" << endl;
    while (cin >> line){
        if (line == "SURT"){
            int numc = read()-1;        // Indicamos la cola a la que hace referencia en el vector cs
            if (numc >= 0 and numc < n and not cs[numc].es_buida()){    // Si la cola está entre 1 y N, y la cola no está vacía, el cliente sale de la cola
                cout << cs[numc].primer() << endl;
                cs[numc].desencuar();
            }
        }
        else if (line == "ENTRA"){      // Si la cola está entre 1 y N, el cliente entra a la cola
            string name;
            cin >> name;
            int numc = read()-1;        // Indicamos la cola a la que hace referencia en el vector cs
            if (numc >= 0 and numc < n){
                cs[numc].encuar(name);
            }
        }
    }
    muestra(cs,n);
}