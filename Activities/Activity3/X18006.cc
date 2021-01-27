#include <sstream>
using namespace std;

 #include <iostream>
 using namespace std;
 typedef unsigned int nat;
 
 template <typename Clau>
 class dicc {
 
   public:
     // Constructora per defecte. Crea un diccionari buit.
     dicc();
 
     // Destructora
     ~dicc();
 
     // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
     void insereix(const Clau &k);
 
     // Retorna quants elements (claus) té el diccionari.
     nat quants() const;
 
     // Pre: La clau k existeix al diccionari i té predecessor.
     // Post: Retorna la clau predecessora de la clau k.
     Clau predecessor(const Clau &k) const;
 
   private:
     struct node {
       Clau _k;      // Clau
       node* _esq;   // fill esquerre
       node* _dret;  // fill dret
       nat _n;       // Nombre de nodes del subarbre
       node(const Clau &k, node* esq = NULL, node* dret = NULL);
     };
     node *_arrel;
 
     static void esborra_nodes(node* m);
     static node* insereix_bst(node *n, const Clau &k, bool &ins);
 
     // Aquí va l’especificació dels mètodes privats addicionals
     static void predecessor(node *n, const Clau &k, Clau &ant);
 };
 
 

 // Aquí va la implementació dels mètodes públics i privats

 template <typename Clau>
Clau dicc<Clau>::predecessor(const Clau &k) const {
  Clau ant=k-100;
  predecessor(_arrel, k, ant);

  return ant;
}


template <typename Clau>
void dicc<Clau>::predecessor(node *n, const Clau &k, Clau &ant){
  //cout << "ant: " << ant << endl;
  //cout << "nodo act " << n->_k << endl;

  //cout << n << endl;
  if (n != NULL)
  {
    if (n->_k < k)
    {
        if (ant < n->_k)
        {
          ant = n->_k;
          //cout << "predecesor actual: " << ant << endl;
        }
    }
  }

    if (n->_esq != NULL) predecessor(n->_esq, k, ant);
    if (n->_dret != NULL) predecessor(n->_dret, k, ant);
}


template <typename Clau>
dicc<Clau>::dicc() : _arrel(NULL) {}

template <typename Clau>
void dicc<Clau>::esborra_nodes(node* m) {
  if (m != NULL) {
    esborra_nodes(m->_esq);
    esborra_nodes(m->_dret);
    delete m;
  }
}

template <typename Clau>
dicc<Clau>::~dicc() {
  esborra_nodes(_arrel);
}

template <typename Clau>
dicc<Clau>::node::node (const Clau &k, node* esq, node* dret) :
	_k(k), _esq(esq), _dret(dret), _n(1) {
}

template <typename Clau>
void dicc<Clau>::insereix(const Clau &k) {
  bool ins = false;
  _arrel = insereix_bst(_arrel, k, ins);
}

template <typename Clau>
typename dicc<Clau>::node* dicc<Clau>::insereix_bst (node *n, const Clau &k, bool &ins) {
  if (n == NULL) {
    ins = true;
    return new node(k);
  }
  else {
    if (k < n->_k) {
      n->_esq = insereix_bst(n->_esq, k, ins);
    }
    else if (k > n->_k) {
      n->_dret = insereix_bst(n->_dret, k, ins);
    }
    if (ins)
      n->_n++;
    return n;
  }
}

template <typename Clau>
nat dicc<Clau>::quants() const {
  nat n = 0;
  if (_arrel != NULL)
    n = _arrel->_n;
  return n;
}

int main() {
  string linea, comanda;;
  int n;
  while (getline(cin, linea)) {
    dicc<int> d;

    // Obtenim elements 1er diccionari
    istringstream ss1(linea);
    while (ss1 >> n) {
      d.insereix(n);
    }
    cout << d.quants() << endl;

    // Processem comandes
    while (getline(cin, linea) and linea != "----------") {
      cout << linea << ": ";
      istringstream ss2(linea);
      ss2 >> comanda;

      if (comanda == "predecessor") {
        int x;
        ss2 >> x;;
        cout << d.predecessor(x) << endl;
      }
    }
    if (linea == "----------")
      cout << linea << endl;
  }
}