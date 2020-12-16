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
  
int partir (int t[], int u, int v)  
{  
    int pivot = t[v];  
    int i = (u - 1); 
  
    for (int j = u; j <= v - 1; j++)  
    {  
        if (t[j] < pivot)  
        {  
            i++; 
            swap(t[i], t[j]);  
        }  
    }  
    swap(t[i + 1], t[v]);  
    return (i + 1);  
}  
  
void quicksort(int t[], int u, int v)  
{  
    if (u < v)  
    {  
        int pivot = partir(t, u, v);  
  
        quicksort(t, u, pivot - 1);  
        quicksort(t, pivot + 1, v);  
    }  
}  
  

void mostra(int t[], int size)  
{  
    int i;  
    cout << "Tabla ordenada: " << endl;
    for (i = 0; i < size; i++)  
        cout << t[i] << " ";  
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
    quicksort(t, 0, n-1);  
    mostra(t, n);   
}  