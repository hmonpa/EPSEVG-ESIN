#ifndef _MCJ_ENTERS_H
#define _MCJ_ENTERS_H
#include <iostream>
#include <vector>
using namespace std;
// Especificació
// Un objecte de la classe mcj_enters representa a un multiconjunt de com a máxim MAXSIZE enters
// Clase
class mcj_enters {

public:
  // - Parte pública: Aquí van los métodos que queremos llamar desde el main.

  // - Método 1
  // Constructora per defecte. Crea un multiconjunt buit.
  mcj_enters();

  // - Métodos 2, 3 y 4
  // Les tres grans: Constructora per còpia, destructora, operador d'assignació
  mcj_enters(const mcj_enters &cj);
  ~mcj_enters();
  mcj_enters& operator=(const mcj_enters &cj);

  // - Más métodos
  // Insereix l’enter e en el multiconjunt.
  void insereix(int e);

  // Unió, intersecció i diferència de multiconjunts. Operen modificant el multiconjunt sobre el que s’aplica
  // el mètode, usant el segon multiconjunt com argument. P.e.: a.restar(b) fa que el nou valor d’a sigui
  // A - B, on A i B són els valors originals dels objectes a i b.
  void unir(const mcj_enters& B);
  void intersectar(const mcj_enters& B);
  void restar(const mcj_enters& B);

  // Unió, intersecció i diferència de multiconjunts. Operen creant un nou multiconjunt sense modificar el con-
  // junt sobre el que s’aplica el mètode. La suma de multiconjunts correspon a la unió, la resta a la
  // diferència i el producte a la intersecció.
  mcj_enters operator+(const mcj_enters& B) const;
  mcj_enters operator*(const mcj_enters& B) const;
  mcj_enters operator-(const mcj_enters& B) const;

  // Retorna cert si i només si e pertany al multiconjunt.
  bool conte(int e) const;

  // Retornen els elements màxim i mínim del multiconjunt, respectivament.
  // El seu comportament no està definit si el multiconjunt és buit.
  int max() const;
  int min() const;

  // Retorna el nombre d’elements (la cardinalitat) del multiconjunt.
  int card() const;

  // Operadors relacionals. == retorna cert si i només si els
  // dos multiconjunts (el paràmetre implícit i B) contenen els
  // mateixos elements; != retorna cert si i només si els
  // multiconjunts són diferents.
  bool operator==(const mcj_enters& B) const;
  bool operator!=(const mcj_enters& B) const;

  // Imprimeix el multiconjunt d’enters, ordenats en ordre ascendent, sobre
  // el canal de sortida os; el format és [e1 e2 ... en], és a dir, amb
  // espais entre els elements i tancant la seqüència amb corxets.
  void print(ostream& os) const;

private:
  // - Parte privada: Aquí van los atributos (variables) y métodos que queremos que queden ocultos (sólo pueden ser llamados dentro de la clase)
	const static unsigned int MAX_SIZE = 20000;   // Máximo valor que puede tener un multiconjunto
	vector<int> v;                                // Declaración del vector v 
	unsigned int t=0;                             // t = Tamaño del vector v
  //void clean();
};
#endif
