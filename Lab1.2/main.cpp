#include "conjunt_2enters.hpp"
#include <sstream>

int main() {
  string linea, comanda;
  char cjt, cjt1, cjt2;
  pair<int, int> pe;
  while (getline(cin, linea)) {
    cj_2enters c[2];

    // Obtenim elements 1er conjunt
    istringstream ss1(linea);
    while (ss1 >> pe.first >> pe.second){
      c[0].insereix(pe);
    }
    c[0].print(cout); cout << endl;

    // Obtenim elements 2on conjunt
    getline(cin, linea);
    istringstream ss2(linea);
    while (ss2 >> pe.first >> pe.second){
      c[1].insereix(pe);
    }
    c[1].print(cout); cout << endl;

    // Processem comandes
    while (getline(cin, linea) and linea != "----------") {
      cout << linea << ": ";
      istringstream ss(linea);
      ss >> comanda;
      if (comanda == "insereix") {
        ss >> cjt >> pe.first >> pe.second;
        c[cjt-'A'].insereix(pe);
        c[cjt-'A'].print(cout);

      } else if (comanda == "conte") {
        ss >> cjt >> pe.first >> pe.second;
        cout << c[cjt-'A'].conte(pe);

      } else if (comanda == "max") {
        ss >> cjt;
        pe = c[cjt-'A'].max();
        cout << pe.first << "," << pe.second;

      } else if (comanda == "min") {
        ss >> cjt;
        pe = c[cjt-'A'].min();
        cout << pe.first << "," << pe.second;

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
        cj_2enters cj = c[cjt1-'A'] + c[cjt2-'A'];
        cj.print(cout);

      } else if (comanda == "*") {
        ss >> cjt1 >> cjt2;
        cj_2enters cj = c[cjt1-'A'] * c[cjt2-'A'];
        cj.print(cout);

      } else if (comanda == "-") {
        ss >> cjt1 >> cjt2;
        cj_2enters cj = c[cjt1-'A'] - c[cjt2-'A'];
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
  return 0;
}
