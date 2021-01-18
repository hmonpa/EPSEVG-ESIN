#include <iostream>
#include <sstream>
 #include <cstddef>
 using namespace std;
 typedef unsigned int nat;
 
 template <typename T>
 class deque {
   public:
     deque();
     // Pre: True
     // Post: El p.i. és una deque buida.
 
     deque(const deque &dq);
     // Pre: True
     // Post: El p.i. conté una còpia de dq.
 
     ~deque();
     // Post: Destrueix els elements del p.i.
 
     nat size() const;
     // Pre: True
     // Post: Retorna el nombre d’elements de la deque.
 
     bool empty() const;
     // Pre: True
     // Post: Retorna true si la deque és buida; false en cas contrari.
 
     T front() const;
     // Pre: La deque no és buida.
     // Post: Retorna el primer element de la deque.
 
     T rear() const;
     // Pre: La deque no és buida.
     // Post: Retorna l’últim element de la deque.
 
     void push(T e);
     // Pre: True
     // Post: Insereix un element al davant de la deque.
 
     void inject(T e);
     // Pre: True
     // Post: Insereix un element al darrera de la deque.
 
     void pop();
     // Pre: La deque no és buida.
     // Post: Elimina el primer element de la deque.
 
     void eject();
     // Pre: La deque no és buida.
     // Post: Elimina l’últim element de la deque.
 
   private:
   /* Double-ended queue implementada amb una llista doblement encadenada,
      sense fantasma i no circular. */
     struct node {
       T info;    // Informació del node
       node *seg; // Punter al següent element
       node *ant; // Punter a l’anterior element
     };
     node *_prim; // Punter al primer element
     node *_ult;  // Punter a l’últim element
     nat _long;   // Nombre d’elements
 
     // Aquí va l’especificació dels mètodes privats addicionals
 };
 
 // Aquí va la implementació dels mètodes públics i privats addicionals


     // Cost constant: Accedeix directament al valor
    template <typename T>
     void deque<T>::push(T e)
     // Pre: True
     // Post: Insereix un element al davant de la deque.
     {
         node* p = new node;
         p->info = e;
         if (_prim == NULL){
           p->seg = NULL;
           _ult = p;
         }
         else{
           p->seg = _prim;
           _prim->ant = p;
         }
         p->ant = NULL;


         _prim = p;
         _long++;
     }


     // Cost constant: Accedeix directament al valor
     template <typename T>
     void deque<T>::inject(T e)
     // Pre: True
     // Post: Insereix un element al darrera de la deque.
     {

       node *p = new node;
       p->info = e;


       if (_prim == NULL)
       {
         p->ant = NULL;
         _prim = p;
       }
       else{
          p->ant = _ult;
          _ult->seg = p;
       }
       p->seg = NULL;
       
       _ult = p;
       _long++;
     }

     // Cost constant: Accedeix directament al valor
     template <typename T>
     void deque<T>::pop()
     // Pre: La deque no és buida.
     // Post: Elimina el primer element de la deque.
     {
       if (_prim != NULL)
       {
         node* p = _prim;
         
         if (_long > 1){
           _prim = _prim->seg;
           _prim->ant = NULL;
         }
         else{
           _prim = NULL;
           _ult = NULL;
         }
         delete p;
         _long--;
       }
     }

     // Cost constant: Accedeix directament al valor
     template <typename T>
     void deque<T>::eject()
     // Pre: La deque no és buida.
     // Post: Elimina l’últim element de la deque
     {
       if (_prim != NULL)
       {
         node *p = _ult;

         if (_long > 1){
           _ult = _ult->ant;
           _ult->seg = NULL;
         }
         else
         {
           _ult = NULL;
           _prim = NULL;
         }
         delete p;
         _long--;
       }
     }
/*
template <typename T>
deque<T>::deque() : _long(0) {
  _prim = NULL;
  _ult  = NULL;
}

template <typename T>
deque<T>::deque(const deque &dq) : _long(dq._long) {
  _prim = NULL;
  node *p, *pant = NULL, *p2 = dq._prim;
  while (p2 != NULL) {
    p = new node;
    p->info = p2->info;
    p->seg = NULL;
    p->ant = pant;
    if (pant == NULL)
      _prim = p;
    else
      pant->seg = p;
    pant = p;
    p2 = p2->seg;
  }
  _ult = pant;
}

template <typename T>
deque<T>::~deque() {
  node *p = _prim, *pelim;
  while (p != NULL) {
    pelim = p;
    p = p->seg;
    delete pelim;
  }
}

template <typename T>
nat deque<T>::size() const {
  return _long;
}

template <typename T>
bool deque<T>::empty() const {
  return _prim == NULL;
}

template <typename T>
T deque<T>::front() const {
  return _prim->info;
}

template <typename T>
T deque<T>::rear() const {
  return _ult->info;
}

template <typename T>
void mostra(deque<T> dq) {
// Pre: True
// Post: Mostra els elements de dq pel cout entre claudàtors i separats per espais.
  cout << "[";
  if (not dq.empty()) {
    cout << dq.front();
    dq.pop();
  }
  while (not dq.empty()) {
    cout << " " << dq.front();
    dq.pop();
  }
  cout << "]";
}

template <typename T>
void mostra_invertida(deque<T> dq) {
// Pre: True
// Post: Mostra en ordre invers els elements de dq pel cout entre claudàtors i separats per espais.
  cout << "[";
  if (not dq.empty()) {
    cout << dq.rear();
    dq.eject();
  }
  while (not dq.empty()) {
    cout << " " << dq.rear();
    dq.eject();
  }
  cout << "]";
}


int main() {
  string linea, comanda;
  int n;
  deque<int> dq;

  // Processem comandes
  while (getline(cin, linea)) {
    cout << linea << ": ";
    istringstream ss(linea);
    ss >> comanda;

    if (comanda == "size") {
      cout << dq.size();

    } else if (comanda == "empty") {
      cout << boolalpha << dq.empty();

    } else if (comanda == "front") {
      cout << dq.front();

    } else if (comanda == "rear") {
      cout << dq.rear();

    } else if (comanda == "push") {
      ss >> n;
      cout << n;
      dq.push(n);

    } else if (comanda == "inject") {
      ss >> n;
      cout << n;
      dq.inject(n);

    } else if (comanda == "pop") {
      cout << dq.front();
      dq.pop();

    } else if (comanda == "eject") {
      cout << dq.rear();
      dq.eject();

    } else if (comanda == "mostra") {
      mostra(dq);

    } else if (comanda == "mostra_invertida") {
      mostra_invertida(dq);
    }
    cout<<endl;
  }
  return 0;
}*/
