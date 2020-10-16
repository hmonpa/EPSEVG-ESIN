#include <iostream>
#include <sstream>
using namespace std;
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
    cout << l.longitud() << " ";
    l.mostra();
  }
}
