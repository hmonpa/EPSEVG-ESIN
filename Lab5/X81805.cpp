#include "arbreBin.hpp"
#include <sstream>
using namespace std;


arbreBin <int> suma_arbre (arbreBin<int> a){
  arbreBin<int> suma;
  int sum;
  if (not a.es_buit()) {
    if (not(a.fe().es_buit() and a.fd().es_buit()) ) {        // CR: Hijos no vacíos
      //cout << "Arrel: " << a.arrel() << endl;
      arbreBin<int> fill_esq = suma_arbre(a.fe());
      arbreBin<int> fill_dret = suma_arbre(a.fd());
      //cout << "Arrel: " << a.arrel() << endl;
      if (not fill_esq.es_buit() and not fill_dret.es_buit())        sum = a.arrel() + fill_esq.arrel() + fill_dret.arrel();  // Ningún hijo vacío
      else if (not fill_esq.es_buit() and fill_dret.es_buit())       sum = a.arrel() + fill_esq.arrel() + 0;                  // Hijo der vacío
      else if (fill_esq.es_buit() and not fill_dret.es_buit())       sum = a.arrel() + 0 + fill_dret.arrel();                 // Hijo izq vacío
      suma = arbreBin<int>(sum, fill_esq, fill_dret);
      //cout << "Arbre fins al moment: " << endl << suma << endl;
    }
    else {                                                      // CD: Hijos vacíos
      arbreBin<int> fill_esq;
      arbreBin<int> fill_dret;
      suma = arbreBin<int>(a.arrel(), fill_esq, fill_dret);
    }
  }
  return suma;
}

int main() {
  arbreBin<int> a;
  cin >> a;
  //cout << a << endl;
  arbreBin<int> res;
  res = suma_arbre(a);
  cout << res << endl;
}
