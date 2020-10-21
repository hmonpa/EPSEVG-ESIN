#ifndef _LLISTA_ITR_HPP
#define _LLISTA_ITR_HPP
#include <cstddef>
using namespace std;
typedef unsigned int nat;

template <typename T>
class llista_itr {
private:
  struct node {
    T info;
    node* next;
    node* prev;
  };
  node* _head; // punter al fantasma
  nat _sz;     // mida de la llista

  node* copiar_llista(node* orig, node* orighead, node* h);
  void destruir_llista(node* p, node* h) throw();
  void swap(llista_itr<T>& l) throw();

public:
  // Constructora. Crea una llista buida.
  llista_itr();

  // Tres grans.
  llista_itr(const llista_itr<T>& l);
  llista_itr<T>& operator=(const llista_itr<T>& l);
  ~llista_itr() throw();

  // Iteradors sobre llistes.
  // Un objecte iterador sempre està associat a una llista
  // particular; només poden ser creats mitjançant els mètodes Llista<T>::primer, Llista<T>::ultim i Llista<T>::indef. Cada llista té el seu iterador indefinit propi: L1.indef() != L2.indef()
  friend class iterador;

  class iterador {
  public:
    friend class llista_itr;

    // Per la classe iterador NO cal redefinir els tres grans ja que ens serveixen les implementacions d'ofici.

    // Accedeix a l'element apuntat per l'iterador o  llança una excepció si l'iterador és indefinit.
    const T& operator*() const;

    // Operadors per avançar (pre i postincrement) i per retrocedir (pre i postdecrement); no fan res si l'iterador és indefinit.
    iterador& operator++() throw();
    iterador operator++(int) throw();
    iterador& operator--() throw();
    iterador operator--(int) throw();

    // Operadors d'igualtat i desigualtat entre iteradors.
    bool operator==(iterador it) const throw();
    bool operator!=(iterador it) const throw();

    static const int IteradorIndef = 330;

  private:
    // Constructora. Crea un iterador indefinit.
    // No pot usar-se fora de la classe iterador o de la classe llista_itr.
    iterador() throw();

    node* _p;  // punter al node actual
    node* _h;  // punter al fantasma de la llista per
               // poder saber quan ho hem recorregut tot.
  };

  // Insereix l'element x darrera/davant de l'element apuntat per l'iterador; si l'iterador it és indefinit, insereix_darrera afegeix x com primer de la llista, i insereix_davant afegeix x com últim de la llista; en abstracte un iterador indefinit "apunta" a un element fictici que és al mateix temps predecessor del primer i successor de l'últim.
  void inserir_darrera(const T& x, iterador it);
  void inserir_davant(const T& x, iterador it);

  // Tant esborra_avnc com esborra_darr eliminen l'element apuntat per l'iterador, 
  // menys en el cas que it és indefinit (llavors no fan res); 
  // amb esborra_avnc l'iterador passa a apuntar al successor de l'element eliminat o queda indefinit si l'element eliminat és l'últim; amb esborra_darr l'iterador passa a apuntar al predecessor de l'element
  // eliminat o queda indefinit si l'eliminat és el primer element.
  void esborrar_avnc(iterador& it) throw();
  void esborrar_darr(iterador& it) throw();

  // Longitud de la llista.
  nat longitud() const throw();

  // Retorna cert si i només si la llista és buida.
  bool es_buida() const throw();

  // Retorna un iterador al primer/últim element o un iterador indefinit si la llista és buida.
  iterador primer() const throw();
  iterador ultim() const throw();

  // Retorna un iterador indefinit.
  iterador indef() const throw();
};
#endif
