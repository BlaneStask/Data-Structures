#include <iostream>
using namespace std;

class Heap{
    int *a;
    int size;
    public:
    Heap(int *b, int n){
        a = new int[100];
        if (n > 100) cout << "too many elements !" << endl;
        else {
          for (int i = 0; i < n ; i++) a[i] = b[i];        
          size = n;
        } 
     }

    void insert(int x){
      if (size == 100) cout << "heap is full !" << endl;
      else {
        int k = size;
        a[k] = x;
        size ++;

        int temp;

        while ( k > 0 && a[(k-1)/2] > a[k])  {
          //swap a[(k-1)/2] and a[k]
          temp = a[k];
          a[k] = a[(k-1)/2];
          a[(k-1)/2] = temp;
          k = (k-1)/2;
        }
      }       
    }
    
    int min(){
        return a[0];
    }
    
    void deletemin(){
      if (size == 0) cout << "heap is empty!" << endl;
      else {
        a[0] = a[size-1];
        size--;
        heapify(0);
      }
    }
    
    void heapify(int k){   
      int left = 2*k + 1;
      int right = 2*k + 2;
      int smallest = k;
      int temp;

      if (left < size && a[left] < a[k]) smallest = left;
      if (right < size && a[right] < a[smallest]) smallest = right;
      if (smallest != k) {
        //swap a[k] and a[smallest]
        temp = a[k];
        a[k] = a[smallest];
        a[smallest] = temp;

        heapify(smallest);
      }
    }
    
    void buildheap(){             
      for (int i = size/2 - 1; i >= 0; i--) heapify(i);
    }
    
    void printHeap(int index, int indent){
      int left = 2*index + 1;
      int right = 2*index + 2;
      
      if (right < size) printHeap(right, indent + 1);

      for (int i = 0; i < indent; i++ ) cout << "\t";
      cout << a[index] << endl;
  
      if (left < size) printHeap(left, indent + 1);
    }
};

int main()
{
    int b[] = {20, 18, 10, 30, 25, 13, 12, 15, 4 , 7, 9, 22, 28};
    int n = 13;
    Heap *h = new Heap(b, n);

    h->printHeap(0,0);
    cout << "---------" << endl;

    h->buildheap();
    h->printHeap(0,0);

    cout << "---------" << endl;
    cout<< "Min: " << h->min() << endl;

    cout << "---------" << endl;
    h->deletemin();
    h->printHeap(0,0);
    
    cout << "---------" << endl;
    h->insert(3);
    h->printHeap(0,0);

    return 0;
}
