#include <iostream>
#include <vector>
using namespace std;
typedef unsigned int nat;

void swap(int &a, int &b)  
{  
    int aux = a;  
    a = b;  
    b = aux;  
}  


void enfonsa(int t[], int mida, int i){
    int mida_act = i;
    int izq = i*2 + 1;
    int der = i*2 + 2;

    if (izq < mida and t[izq] > t[mida_act]){
        mida_act = izq;
    }
    if (der < mida and t[der] > t[mida_act]){
        mida_act = der;
    }
    if (mida_act != i){
        swap(t[i], t[mida_act]);
        enfonsa(t, mida, mida_act);
    }
}

void heapsort(int t[], int mida){             // Sense usar CuaPrio
    for (int i=mida/2-1; i>=0; i--){          // Crea el Heap
        enfonsa(t, mida, i);
    }
    for (int i=mida-1; i>0; i--){
        swap(t[0], t[i]);
        enfonsa(t, i, 0);
    }
}


void mostra(int t[], int mida)  
{  
    int i;  
    cout << "MIN-HEAP: " << endl;
    for (i = 0; i < mida; i++){
        cout << t[i] << " "; 
    } 
    cout << endl << endl;
    cout << "MAX-HEAP: " << endl;
    for (i = mida-1; i >= 0; i--){
        cout << t[i] << " ";
    }  
    cout << endl;
}  
  
int main()  
{  
    int n;
    cin >> n;
    int t[n];
    int valor;
    for (int i=0;i<n;i++)
    {
        cin >> valor;
        t[i]=valor;
    } 
    heapsort(t, n);  
    mostra(t, n);   
}  