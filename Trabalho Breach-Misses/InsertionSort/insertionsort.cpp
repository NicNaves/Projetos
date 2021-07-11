#include <bits/stdc++.h>
using namespace std;
#define VMAX 1000000
 
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
 
int main()
{
    srand(time(NULL));
    int arr[VMAX];
    for (int i = 0; i<VMAX; i++){
        arr[i] = rand() %VMAX; 
    }
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int n = sizeof(arr) / sizeof(arr[0]);
 
    insertionSort(arr, n);
    printArray(arr, n);
 
    return 0;
}
 

