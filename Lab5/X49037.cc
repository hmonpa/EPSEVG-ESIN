 #include <iostream>
 #include <iostream>
 #include <cstdlib>
 using namespace std;
 typedef unsigned int nat;

 // --------------
 // Especificació
 // --------------

 template <typename T>
 class Abin {
   public:
     Abin(): _arrel(NULL) {};
     // Pre: cert
     // Post: el resultat és un arbre sense cap element
     Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
     // Pre: cert
     // Post: el resultat és un arbre amb un element i dos subarbres
 
     // Les tres grans
     Abin(const Abin<T> &a);
     ~Abin();
     Abin<T>& operator=(const Abin<T>& a);
 
     // Escriu una línia amb els elements del nivell i-èssim, d’esquerra 
     // a dreta. Cada element ha de sortir precedit d’un espai.
     void nivell(nat i) const;
 
   private:
     struct node {
       node* f_esq;
       node* f_dret;
       T info;
     };
     node* _arrel;
     static node* copia_nodes(node* m);
     static void esborra_nodes(node* m);
 
     // Aquí va l’especificació dels mètodes privats addicionals
     static void nivell(nat i, node* n, nat niv);
 };
 
// --------------
// Implementació
// --------------


// Aquí va la implementació del mètode nivell
 template <typename T>	
 void Abin<T>::nivell(nat i) const{
   int niv = 0;
   nivell(i, _arrel, niv);
 }

 template <typename T>	
 void Abin<T>::nivell(nat i, node* n, nat niv){
   if (n != NULL){
     if (i == niv){
       cout << " " << n->info;
     }
     else{
       niv++;
       nivell(i, n->f_esq, niv);
       nivell(i, n->f_dret, niv);
     }
   }
 }

// --------------
// Programa
// --------------
/*
// Llegeix un arbre binari des de cin i el retorna.
Abin<int> llegir_arbre() {
  Abin<int> a;
  int valor;
  cin >> valor;
  if (valor != -1) {
    Abin<int> ae = llegir_arbre();
    Abin<int> ad = llegir_arbre();
    a = Abin<int>(ae, valor, ad);
  }
  return a;
}

int main() {
  Abin<int> a(llegir_arbre());
  nat n;
  while (cin >> n) {
    a.nivell(n);
    cout << endl;
  }
  return 0;
}*/
