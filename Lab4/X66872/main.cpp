#include <iostream>
#include <sstream>
#include "llista.hpp"

int main() {
  string linea;
  while (getline(cin, linea)) {
    vector<int> v;
    istringstream ss(linea);
    int n;
    while (ss >> n) {
      v.push_back(n);
    }
    Llista l(v);
    Llista l2;
    l.separa(l2);
    cout << l.longitud() << " ";
    l.mostra();
    cout << " " << l2.longitud() << " ";
    l2.mostra();
    cout << endl;
  }
}
