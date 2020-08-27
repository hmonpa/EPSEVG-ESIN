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
