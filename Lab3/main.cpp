#include <iostream>
#include <locale.h>
#include "conjunt_2enters.hpp"
#include <vector>
using namespace std;

void nuevoconjunto(vector <cj_2enters> &v) {
	cj_2enters C;
	v.push_back(C);
}

void insertarelemento(vector<cj_2enters> &v) {
	int id;
    pair<int,int> elem;
	cout << "Introduce el numero del conjunto: " << endl;
	cin >> id;
	cout << "Introduce el elemento a introducir: " << endl;
	cin >> elem.first >> elem.second;
	v[id].insereix(elem);
}

void unio(vector<cj_2enters> &v) {
    cout << "Union de los dos conjuntos que eligas: " << endl;
    int c1, c2;
    cout << "Introduce el primer conjunto: " << endl;
    cin >> c1;
    cout << "Introduce el segundo conjunto: " << endl;
    cin >> c2;
    v[c1].unir(v[c2]);
}

void interseccio(vector<cj_2enters> &v) {
    cout << "Interseccion de los dos conjuntos que eligas: " << endl;
    int c1, c2;
    cout << "Introduce el primer conjunto: " << endl;
    cin >> c1;
    cout << "Introduce el segundo conjunto: " << endl;
    cin >> c2;
    v[c1].intersectar(v[c2]);
}

void resta(vector<cj_2enters> &v) {
    cout << "Resta de los dos conjuntos que eligas: " << endl;
    int c1, c2;
    cout << "Introduce el primer conjunto: " << endl;
    cin >> c1;
    cout << "Introduce el segundo conjunto: " << endl;
    cin >> c2;
    v[c1].restar(v[c2]);
}

void suma(vector<cj_2enters> &v) {
    cout << "Suma de conjuntos A + B" << endl;
    int c1, c2;
	cout << "Introduce el primer conjunto:" << endl;
	cin >> c1;
	cout << "Introduce el segundo conjunto:" << endl;
	cin >> c2;
	cj_2enters csum = v[c1] + v[c2];
    cout << endl << "Conjunto resultante: " << endl;
    csum.print(cout);
    cout << endl << endl;
}

void producto(vector<cj_2enters> &v) {
    cout << "Intersección de conjuntos A * B" << endl;
    int c1, c2;
	cout << "Introduce el primer conjunto:" << endl;
	cin >> c1;
	cout << "Introduce el segundo conjunto:" << endl;
	cin >> c2;
	cj_2enters cpro = v[c1] * v[c2];
    cout << endl << "Conjunto resultante: " << endl;
    cpro.print(cout);
    cout << endl << endl;
}

void restap(vector<cj_2enters> &v) {
    cout << "Resta de conjuntos A - B" << endl;
    int c1, c2;
	cout << "Introduce el primer conjunto:" << endl;
	cin >> c1;
	cout << "Introduce el segundo conjunto:" << endl;
	cin >> c2;
	cj_2enters cres = v[c1] - v[c2];
    cout << endl << "Conjunto resultante: " << endl;
    cres.print(cout);
    cout << endl << endl;
}

int main() {
    vector<cj_2enters> v;
    char mode = 8;
    cout << "Programa LAB3" << endl << endl;
    while (mode != 0){
        unsigned int i = 0;
        cout << "Conjuntos actuales: " << endl << endl;
        while (i < v.size()){
            cout << "Conjunto " << i << endl;
            v[i].print(cout);
            cout << endl;
            i++;
        }
        cout << "----------- Opciones -----------" << endl;
        cout << "1- Crear un nuevo conjunto" << endl;
        cout << "2- Insertar un elemento en un conjunto" << endl;
        cout << "3- Union de dos conjuntos" << endl;
        cout << "4- Interseccion de dos conjuntos" << endl;
        cout << "5- Resta de dos conjuntos" << endl;
        cout << "6- Suma de conjuntos mediante el operador +" << endl;
        cout << "7- Interseccion de conjuntos mediante el operador *" << endl;
        cout << "8- Resta de conjuntos mediante el operador -" << endl;
        cout << "0- Salir del programa" << endl;
        cin >> mode;
        if (mode == '1') {
            if (i <= 1) nuevoconjunto(v);
            else cout << "Como maximo puedes crear dos conjuntos, elige otra operacion:" << endl;
        }
        if (mode == '2') insertarelemento(v);
        if (mode == '3') unio(v);
        if (mode == '4') interseccio(v);
        if (mode == '5') resta(v);
        if (mode == '6') suma(v);
        if (mode == '7') producto(v);
        if (mode == '8') restap(v);
        if (mode == '0') break;
    }
    cout << "Hasta pronto!";
}