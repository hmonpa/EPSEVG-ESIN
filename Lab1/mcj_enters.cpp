#include "mcj_enters.hpp"
#include <stdlib.h>
#include <stdio.h>

// Implementació

  // Constructora per defecte
  mcj_enters::mcj_enters(){
    v = vector<int>(MAX_SIZE);
  }

  // Les tres grans
  // Constructor per copia
  mcj_enters::mcj_enters(const mcj_enters &cj){
    t = cj.t;
	  unsigned int i = 0;
		while (i < cj.card()){
		  v[i] = cj.v[i];
		  i++;
	  }
  }

  // Destructor - No s'utilitza al no utilizar memoria dinàmica
  mcj_enters::~mcj_enters(){
  }

  // Operador d'assignació - No s'utilitza al no utilizar memoria dinàmica
  mcj_enters& mcj_enters::operator=(const mcj_enters &cj){
    t = cj.t;
	  unsigned int i = 0;
		while (i < cj.card()){
		  v[i] = cj.v[i];
		  i++;
		}
  }

  /*void mcj_enters::clean(){
    for (unsigned int i = 0; i < MAX_SIZE; i++){
      v[i] = 0;
    }
  }*/

  void mcj_enters::insereix(int e){
    unsigned int i = t;                   // i = última posición 
      if (i < MAX_SIZE){
        if (i != 0){                      // Recorrido desde el final
          bool ordenat = false;
          while (i>0 and not ordenat){    
              if (e >= v[i-1]){
                v[i] = e;
                ordenat = true;
              }
              else {
                v[i] = v[i-1];
                v[i-1] = e;
                i--;
              }
          }
        }
        else v[i] = e;
        t++;
      }
  }

  void mcj_enters::unir(const mcj_enters& B){                   // B es el segundo multiconjunto
    *this = *this+B;
  }

  void mcj_enters::intersectar(const mcj_enters& B){
    *this = *this*B;
  }

  void mcj_enters::restar(const mcj_enters& B){
    *this = *this-B;
  }

  mcj_enters mcj_enters::operator+(const mcj_enters& B) const{    // B es el segundo multiconjunto
    mcj_enters C;      // C = Multiconjunto resultante
    
    if (card() == 0 and B.card() != 0)  C = B;    // Caso directo 1
    else if (card() != 0 and B.card() != 0){      
      unsigned int i = 0;                         // Recorre multiconjunto del p.i.
      unsigned int j = 0;                         // Recorre segundo multiconjunto

      while (i<t and j<B.t){
        if (v[i] == B.v[j]){
          C.insereix(v[i]);
          i++;
          j++;
        }
        else if (v[i] < B.v[j]){
          C.insereix(v[i]);
          i++;
        }
        else {
          C.insereix(B.v[j]);
          j++;
        }
      }

      if (i == t){            // Se ha recorrido el multiconjunto del p.i. en su totalidad
        while (j<B.t){
          C.insereix(B.v[j]);
          j++;
        }
      }
      else {                  // Se ha recorrido el segundo multiconjunto en su totalidad
        while (i<t){
          C.insereix(v[i]);
          i++;
        }
      }
    }
    else C = *this;           // Caso directo 2                      

    return C;
  }

  mcj_enters mcj_enters::operator*(const mcj_enters& B) const{
    mcj_enters C1;     // C = Multiconjunto resultante

    if (card() != 0 and B.card() != 0){
      unsigned int i = 0;                         // Recorre multiconjunto del p.i.
      unsigned int j = 0;                         // Recorre segundo multiconjunto

      while (i < t and j < B.t){
        if (v[i] == B.v[j]){
          C1.insereix(v[i]);
          i++;
          j++;
        }
        else if (v[i] < B.v[j]) i++;
        else j++;
      }
    }
    return C1;
  }

  mcj_enters mcj_enters::operator-(const mcj_enters& B) const{
    mcj_enters C2;

    if (card() != 0 and B.card() != 0){
      unsigned int i = 0;                         // Recorre multiconjunto del p.i.
      unsigned int j = 0;                         // Recorre segundo multiconjunto

      while (i < t and j < B.t){
        if (v[i] == B.v[j]){
          i++;
          j++;
        }
        else if (v[i] < B.v[j]){
          C2.insereix(v[i]);
          i++;
        }
        else j++;
      }
      while (i < t){
        C2.insereix(v[i]);
        i++;
      }
    }
    else C2 = *this;              // Caso directo
    return C2;
  }

  bool mcj_enters::conte(int e) const{
    unsigned int i = 0;
    bool trobat = false;

    if (t>0){
      unsigned int m = t/2;
      if (v[m] == e) trobat = true;
      else if (e < v[m]){
        while (i < m and not trobat){
          if (v[i] == e) trobat = true;
          i++;
        }
      }
      else {
        m++;  // Incremento de m, al no ser igual a e en la primera comparación
        while (t > m and not trobat){
          if (v[m] == e) trobat = true;
          m++;
        }
      }
    }
    return trobat;
  }


  int mcj_enters::max() const{  // Mètode tipus INT, ja que retorna un integer
    return v[t-1];  // Retorna el major valor del vector
  }

  int mcj_enters::min() const{    
    return v[0];    // Retorna el menor valor del vector
  }

  int mcj_enters::card() const{
    return t;       // t = Cardinalitat del multiconjunt (vector)
  }

  bool mcj_enters::operator==(const mcj_enters& B) const{
    unsigned int i = 0;
    bool igual = false;
    if (card() == B.card()){
      igual = true;
      while (i < v.size() and igual){
        if (v[i] != B.v[i]) igual = false;
        i++;
      }
    }
    return igual;
  }

  bool mcj_enters::operator!=(const mcj_enters& B) const{
    unsigned int i = 0;
    bool igual = false;
    if (card() == B.card()){
      igual = true;
      while (i < v.size() and igual){
        if (v[i] != B.v[i]) igual = false;
        i++;
      }
    }
    return not igual;
  }

  void mcj_enters::print(ostream& os) const{
    os << "[";
    for (unsigned int i=0; i<card();i++)
    {
        os << v[i];
        if (i+1 < card()) os << " ";
    }
    os << "]";
  }
