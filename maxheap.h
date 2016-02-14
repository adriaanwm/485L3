/****************************************************************
*            heap.h
*            by Gara Pruesse
*            Nov 26, 2015
*            Altered Jan 20, 2016 to be a Max-Heap
*            (for 485 poset application)
*
*            class for heap
*            
*********************************************************************/
#include <string>
#include <iostream>
// #include <values.h>

// heap items are vertex name (int) and key value (int)
// heap is a max-heap, array based implementation

using namespace std;


class maxheap{
   private:
      int arraysize;
      int n;              // n is number of elements in heap
                          // so valid indices into heapArray and
                          // heapIndex are [0..n-1].
      int *key;           // key[v] is key for vertex v
      int *heapArray;     // the heap.  Max-keyed element is heapArray[0]
      int *heapIndex;     //if heapArray[i]=v then heapIndex[v]=i
      int parent(int i);  // calculates index of parent of an index
      int largerChild(int i); // calculates the index of children
                               // and checks; for those children 
                               // whose key is <n, which has smallest
                               // key; returns that index if 
                               // key is larger than key of vertex 
                               // at heapIndex i; returns 0 if neither key
                               // is greater.
      void swap(int i1, int i2);  // swaps elements at heapArray indices
                              // i1 and i2, and updates heapIndex

   public: 
      maxheap();
      maxheap(int max);
			~maxheap();
			int size(); 
			bool empty(); 
			void setsize(int x); 
			void increaseKey(int v, int k); 
			int insert(int v, int k);
			int deleteMax();
			int maxVertex();
			int maxKey();
			void print_heap();
			void debug_print();
};


	
