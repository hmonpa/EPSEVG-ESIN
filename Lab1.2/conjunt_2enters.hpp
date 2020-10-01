#include <iostream>
using namespace std;

// Especificación
// Un objeto de la clase cj_2enters representa a un conjunto de como máximo MAXSIZE enteros

class cj_2enters {
// Conjunt de parelles d'enters.
// Dins del conjunt no importa l'ordre de les parelles i no poden haver-hi parelles repetides
// Dins de cada parella d'enters importa l'ordre dels dos enters i es poden repetir els dos enters
// Per exemple (els elements del conjunt estan separats amb espais i la parella d'enters amb una coma):
//   [1,1 3,1 1,2] i [3,1 1,2 1,1] són el mateix conjunt
//   [1,2] i [2,1] són conjunts diferents

public:
  // - Parte pública: Aquí van los métodos que queremos llamar desde fuera de la clase (desde el main).

  // Constructora per defecte. Crea un conjunt buit.
  cj_2enters();

  // Les tres grans: Constructora per còpia, destructora, operador d'assignació
  cj_2enters(const cj_2enters &cj);
  ~cj_2enters();
  cj_2enters& operator=(const cj_2enters &cj);

  // Insereix la parella d'enters pe en el conjunt. No fa res si pe ja pertanyia al conjunt.
  void insereix(pair<int, int> pe);

  // Unió, intersecció i diferència de conjunts. Operen modificant el conjunt sobre el que
  // s'aplica el mètode, usant el segon conjunt com argument. P.e.: a.restar(b) fa que el
  // nou valor d'a sigui A - B, on A i B són els valors originals dels objectes a i b.
  void unir(const cj_2enters& B);
  void intersectar(const cj_2enters& B);
  void restar(const cj_2enters& B);

  // Unió, intersecció i diferència de conjunts. Operen creant un nou conjunt sense 
  // modificar el conjunt sobre el que s'aplica el mètode. La suma de conjunts correspon
  // a la unió, la resta a la diferència i el producte a la intersecció.
  cj_2enters operator+(const cj_2enters& B) const;
  cj_2enters operator*(const cj_2enters& B) const;
  cj_2enters operator-(const cj_2enters& B) const;

  // Retorna cert si i només si pe pertany al conjunt.
  bool conte(pair<int, int> pe) const;

  // Retornen els elements màxim i mínim del conjunt, respectivament.
  // El seu comportament no està definit si el conjunt és buit.
  // pe1 és major que pe2 si el 1er enter de pe1 és major que el 1er enter de pe2. En cas
  // que siguin iguals, si el 2on enter de pe1 és major que el 2on enter de pe2. 
  pair<int, int> max() const;
  pair<int, int> min() const;

  // Retorna el nombre d'elements (la cardinalitat) del conjunt.
  int card() const;

  // Operadors relacionals. == retorna cert si i només si els dos conjunts
  // (el paràmetre implícit i B) contenen els mateixos elements;
  // != retorna cert si i només si els conjunts són diferents.
  bool operator==(const cj_2enters& B) const;
  bool operator!=(const cj_2enters& B) const;

  // Imprimeix el conjunt de parelles d'enters, ordenats en ordre ascendent, sobre
  // el canal de sortida os; el format és [pe1 pe2 ... pen], és a dir, amb
  // espais entre els elements i tancant la seqüència amb claudàtors.
  // Els dos enters de la parella d'enters estan separats amb una coma.
  void print(ostream& os) const;

private:
    // Los definiremos dentro del fichero .rep
    #include "conjunt_2enters.rep"
};
