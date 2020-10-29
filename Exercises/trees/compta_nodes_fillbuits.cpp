// 5.3 Implementa una funció que calculi el nombre de nodes amb tots dos subarbres buits d’un arbre binari donat.

// Versión con clase Abin
// Versión 1: Función externa de la clase mediante métodos públicos (iteradores)
#include "abin.hpp"
int compta_nodes(Abin<int>::iterador it, Abin<int>::iterador fi){
    int cont = 0;
    if (it != fi){
        if (a.fesq().es_buit() and a.fdret().es_buit()) cont++;
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
        if (p->f_esq == NULL and p->f_dret == NULL) cont++;
        cont+=compta_nodes(p->f_esq);
        cont+=compta_nodes(p->f_dret);
    }
    return cont;
}

int Abin::compta_nodes(){
    return compta_nodes(_arrel);
}
