#include <iostream>
#include "conjunt_2enters.hpp"
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// Implementación
  // Constructor por defecto (conjunto vacío)
  cj_2enters::cj_2enters(){
      cj_ant = -1;
  }

  // Constructor por copia
  cj_2enters::cj_2enters(const cj_2enters &cj){
      unsigned int i = 0;
      tam = cj.tam; 
      while (i < cj.card()){
          cj2[i] = cj.cj2[i];
          i++;
      }
  }

  // Destructor - No se utiliza al no utilizar mem. dinámica
  cj_2enters::~cj_2enters(){
  }
  
  // Método privado copia
  void cj_2enters::copia(const cj_2enters &cj){
      unsigned int i = 0;
      for (i=0;i<tam;i++){
          cj2[i] = cj.cj2[i];
      }
      cj_ant = cj.cj_ant;
  }

  // Op. asignación - No se utiliza al no utilizar mem. dinámica
  cj_2enters& cj_2enters::operator=(const cj_2enters &cj){
      if (this != &cj){
          copia(cj);
      }
      return *this;
  }

  void cj_2enters::insereix(pair<int, int> pe){
      unsigned int i = tam;                         // i = última posición del conjunto
      if (i < MAX_SIZE and not conte(pe)){          // Menor a MAX_SIZE y evitando repeticiones
          if (i > 0){                               // Conjunto no vacío
            bool ord = false;
            while (i>0 and not ord){
                if (pe >= cj2[i-1]){                // pe >= última posición p.i
                    cj2[i] = pe;
                    ord = true;
                }
                else{                               // pe < última posición p.i
                    cj2[i] = cj2[i-1];
                    cj2[i-1] = pe;
                    i--;
                }                    
            }
          }
          else cj2[i] = pe;                         // CD: Conjunto vacio
          tam++;
      }
  }

  
  void cj_2enters::unir(const cj_2enters& B){
          unsigned int j = 0;
          unsigned int i = 0;
          unsigned int k = 0;
          cj_2enters aux = *this;
          if (tam == 0)                             // CD: p.i. vacío - Coste constante
          { 
                tam = B.tam;                 
                *this = B;
          }
          else if (tam != 0 and B.tam != 0){        
            while (j < B.tam and i < aux.tam){      // Worst-case: Coste lineal
                if(aux.cj2[i] == B.cj2[j]){       
                    //insereix( B.cj2[j] );         // X Coste líneal
                    cj2[k] = B.cj2[j];              // Coste constante
                    j++;
                    i++;
                }
                else if (aux.cj2[i] < B.cj2[j]){
                    //insereix(aux.cj2[i]);
                    cj2[k] = aux.cj2[i];
                    i++;
                }
                else {
                    //insereix(B.cj2[j]);
                    cj2[k] = B.cj2[j];
                    j++;
                }
                k++;
            }
            if (i != aux.tam){                      // Si aux no ha llegado hasta el final
                while (i < aux.tam){
                    //insereix(aux.cj2[i]);
                    cj2[k] = aux.cj2[i];
                    i++;
                    k++;
                }
            }
            else{
                    while (j < B.tam){
                    cj2[k] = B.cj2[j];
                    k++;
                    j++;
                }
            }
            tam = k;
        }
        else {                                  // CD: Conjunto B vacío
            tam = aux.tam;
            *this = aux;
        }
  }

  void cj_2enters::intersectar(const cj_2enters& B){
      cj_2enters aux;
      unsigned int i = 0;
      unsigned int j = 0;
      unsigned int k = 0;
      if (card() != 0 and B.card() != 0){
        while (i<tam and j<B.tam){
                if (cj2[i] == B.cj2[j]){ 
                    aux.cj2[k] = cj2[i];
                    k++;
                    //aux.insereix(cj2[i]);
                    j++;
                    i++;
                }
                else if (cj2[i] < B.cj2[j]) i++;
                else j++;  
        }
      tam = k;
      *this = aux;
     } 
    else tam = 0;                               // CD: Algún conjunto vacío
  }

  void cj_2enters::restar(const cj_2enters& B){
      unsigned int i = 0;
      unsigned int j = 0;
      unsigned int k = 0;
      cj_2enters aux;
      if (card()==0 and B.card()!=0){           // CD1: p.i vacío
          tam = 0;
      } 
      else if (card()!=0 and B.card()==0){      // CD2: Conjunto 2 vacío
          *this = *this;
      }
      else {
        while (i < tam and j < B.tam){          // Coste líneal
              if (cj2[i] == B.cj2[j]){          // Coste constante
                  i++;                          // "
                  j++;
              }
              else if (cj2[i] < B.cj2[j]){  
                  //aux.insereix(cj2[i]);
                  aux.cj2[k] = cj2[i];
                  k++;
                  i++;
              }
              else j++;
          }
          if (i != tam){                        // Coste constante
             while (i < tam){                   // Coste líneal
                //aux.insereix(cj2[i]);
                aux.cj2[k] = cj2[i];
                k++;
                i++;
            } 
          }
    tam = k;
    *this = aux;
    }
  }

  cj_2enters cj_2enters::operator+(const cj_2enters& B) const{      // Unión
      cj_2enters C(*this);                  // Conjunto resultante = p.i
      C.unir(B);                            // unir A B
      return C;
      /*cj_2enters C;
          unsigned int i = 0;       // Recorre p.i
          unsigned int j = 0;       // Recorre B
          unsigned int k = 0;
          while (i < tam and j < B.tam){
              if (cj2[i] == B.cj2[j]){
                  //C.insereix(cj2[i]);
                  C.cj2[k] = cj2[i];
                  k++;
                  i++;
                  j++;
              }
              else if (cj2[i] < B.cj2[j]){
                  //C.insereix(cj2[i]);
                  C.cj2[k] = cj2[i];
                  k++;
                  i++;
              }
              else {
                  //C.insereix(B.cj2[j]);
                  C.cj2[k] = B.cj2[j];
                  k++;
                  j++;
              }
          }
          if (i == tam){
                while (j < B.tam){
                    //C.insereix(B.cj2[j]);
                    C.cj2[k] = B.cj2[j];
                    k++;
                    j++;
                }
          }
          else {
            while (i < tam){
                    //C.insereix(cj2[i]);
                    C.cj2[k] = cj2[i];
                    k++;
                    i++;
            }
          }
        C.tam = k;
      return C;*/
  }

  cj_2enters cj_2enters::operator*(const cj_2enters& B) const{      // Intersección
      cj_2enters C1(*this);                     // Conjunto resultante = p.i
      C1.intersectar(B);                        // intersectar A B
      return C1;                            
      /*unsigned int i = 0;
      unsigned int j = 0;
      unsigned int k = 0;   
    if (card() != 0 and B.card() != 0){
        while (i < tam and j < B.tam){
            if (cj2[i] == B.cj2[j]){
                  //C1.insereix(cj2[i]);
                  C1.cj2[k] = cj2[i];
                  k++;
                  i++;
                  j++;
            } 
            else if (cj2[i] < B.cj2[j]) i++;
            else j++;
        }
    }
      C1.tam = k;
      return C1;*/
  }

  cj_2enters cj_2enters::operator-(const cj_2enters& B) const{      // Resta
      cj_2enters C2(*this);                 // Conjunto resultante = p.i
      C2.restar(B);                         // restar A B
      return C2;
      //if (card() != 0 and B.card() != 0){
      /*  unsigned int i = 0;
        unsigned int j = 0;
        unsigned int k = 0;
          while (i < tam and j < B.tam){
              if (cj2[i] == B.cj2[j]){
                  i++;
                  j++;
              }
              else if (cj2[i] < B.cj2[j]){
                  //C2.insereix(cj2[i]);
                  C2.cj2[k] = cj2[i];
                  k++;
                  i++;
              }
              else j++;
          }
          if (i != tam){
                while (i < tam){
                    //C2.insereix(cj2[i]);
                    C2.cj2[k] = cj2[i];
                    k++;
                    i++;
                }
          }
      //}
      //else C2 = *this;
      C2.tam = k;
      return C2;*/
  }

  bool cj_2enters::conte(pair<int, int> pe) const{
      unsigned int i = 0;
      bool trobat = false;

      if (tam > 0){
          unsigned int mig = tam/2;
          if (cj2[mig] == pe) trobat = true;        // CD: Posición media contiene el valor
          else if (pe < cj2[mig]){                  // Parte inferior
              while (i < mig and not trobat){
                  if (cj2[i] == pe) trobat = true;
                  i++;
              }
          }
          else {                                    // Parte superior
                mig++;                              // Incremento de mig, al no ser igual a la primera comparación
                while (tam >= mig and not trobat){
                    if (cj2[mig] == pe) trobat = true;
                    mig++;
                }
          }
      }
      return trobat;
  }

  pair<int, int> cj_2enters::max() const{
      return cj2[tam-1];
  }

  pair<int, int> cj_2enters::min() const{
      return cj2[0];
  }

  int cj_2enters::card() const{
      return tam;
  }

  bool cj_2enters::operator==(const cj_2enters& B) const{
      unsigned int i = 0;
      bool igual = true;
      if (card() == B.card()){
          while (i < card() and igual){
              if (cj2[i] != B.cj2[i]) igual = false;
              i++;
          }
      }
      else igual = false;                           // CD: Si la cardinalidad no es la misma, son diferentes
      return igual;
  }

  bool cj_2enters::operator!=(const cj_2enters& B) const{
     return not(*this==B); 
  }

  void cj_2enters::print(ostream& os) const{
      os << "[";
      for (unsigned int i=0; i<card();i++)
      {
          os << cj2[i].first << "," << cj2[i].second;
          if (i+1 < card()) os << " ";
      }
      os << "]";
  }