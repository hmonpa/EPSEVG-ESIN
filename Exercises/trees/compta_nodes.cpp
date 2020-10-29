// 5.2 Implementa una funció que compti el nombre de nodes d’un arbre binari donat.
// Versión con clase arbreBin
#include "arbreBin.hpp"
// Tipo función
int compta_nodes(arbreBin<int> a){
    int cont = 0;
    if (not a.es_buit()){
        // Recorregut en preordre
        cont++;                         // Suma el actual
        cont+=compta_nodes(a.fe());     // Suma el hijo izq
        cont+=compta_nodes(a.fd());     // Suma el hijo der
    }
    return cont;
}

// Tipo acción
/*void compta_nodes(arbreBin<int> a, int &cont){
    if (not a.es_buit()){
        cont++;
        cont+=compta_nodes(a.fe(),cont);
        cont+=compta_nodes(a.fd(),cont);
    }
}*/

// Versión con clase Abin
// Versión 1: Función externa de la clase mediante métodos públicos (iteradores)
#include "abin.hpp"
int compta_nodes(Abin<int>::iterador it, Abin<int>::iterador fi){
    int cont = 0;
    if (it != fi){
        cont++;
        cont+=compta_nodes(it.fesq(), fi);
        cont+=compta_nodes(it.fdret(), fi);
    }
    return cont;
}

int compta_nodes(Abin<int> a){
    return compta_nodes(a.arrel(), a.final());
}

// Versión 2: Usando métodos privados de clase, usando punters
int Abin::compta_nodes(node *p){
    int cont = 0;
    if (p != NULL){
        cont++;
        cont+=compta_nodes(p->f_esq);
        cont+=compta_nodes(p->f_dret);
    }
    return cont;
}

int Abin::compta_nodes(){
    return compta_nodes(_arrel);
}
