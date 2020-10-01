#include <iostream>
#include <sstream>
#include <vector>
#include "mcj_enters.hpp"
using namespace std;

int main() {
  string linea, comanda;
  char cjt, cjt1, cjt2;
  int n;
  while (getline(cin, linea)) {
    mcj_enters c[2];

    // Obtenim elements 1er conjunt
    istringstream ss1(linea);
    while (ss1 >> n){
      c[0].insereix(n);
    }
    c[0].print(cout); cout << endl;

    // Obtenim elements 2on conjunt
    getline(cin, linea);
    istringstream ss2(linea);
    while (ss2 >> n){
      c[1].insereix(n);
    }
   
    c[1].print(cout); cout << endl;

    // Processem comandes
    while (getline(cin, linea) and linea != "----------") {
      cout << linea << ": ";
      istringstream ss(linea);
      ss >> comanda;
      if (comanda == "insereix") {
        ss >> cjt >> n;
        c[cjt-'A'].insereix(n);
        c[cjt-'A'].print(cout);

      } else if (comanda == "conte") {
        ss >> cjt >> n;
        cout << c[cjt-'A'].conte(n);

      } else if (comanda == "max") {
        ss >> cjt;
        cout << c[cjt-'A'].max();

      } else if (comanda == "min") {
        ss >> cjt;
        cout << c[cjt-'A'].min();

      } else if (comanda == "card") {
        ss >> cjt;
        cout << c[cjt-'A'].card();

      } else if (comanda == "unir") {
        ss >> cjt1 >> cjt2;
        c[cjt1-'A'].unir(c[cjt2-'A']);
        c[cjt1-'A'].print(cout);

      } else if (comanda == "intersectar") {
        ss >> cjt1 >> cjt2;
        c[cjt1-'A'].intersectar(c[cjt2-'A']);
        c[cjt1-'A'].print(cout);

      } else if (comanda == "restar") {
        ss >> cjt1 >> cjt2;
        c[cjt1-'A'].restar(c[cjt2-'A']);
        c[cjt1-'A'].print(cout);

      } else if (comanda == "+") {
        ss >> cjt1 >> cjt2;
        mcj_enters cj = c[cjt1-'A'] + c[cjt2-'A'];
        cj.print(cout);

      } else if (comanda == "*") {
        ss >> cjt1 >> cjt2;
        mcj_enters cj = c[cjt1-'A'] * c[cjt2-'A'];
        cj.print(cout);

      } else if (comanda == "-") {
        ss >> cjt1 >> cjt2;
        mcj_enters cj = c[cjt1-'A'] - c[cjt2-'A'];
        cj.print(cout);

      } else if (comanda == "==") {
        ss >> cjt1 >> cjt2;
        cout << (c[cjt1-'A'] == c[cjt2-'A']);

      } else if (comanda == "!=") {
        ss >> cjt1 >> cjt2;
        cout << (c[cjt1-'A'] != c[cjt2-'A']);

      } else if (comanda == "print") {
        ss >> cjt;
        c[cjt-'A'].print(cout);
      }
      cout<<endl;
    }
    if (linea == "----------")
      cout << linea << endl;
  }
}
