/****************************************************************
/*            heap.cpp
/*            by Gara Pruesse
/*            Oct 30, 2014
/*
/*            reads a heap in from a file
/*            builds heap, provides heap access routines
/*            
/*********************************************************************/

#include <climits>
#include "maxheap.h"


maxheap::maxheap()
{
	n=0;
}


// argument x is the maximum size for the heap
maxheap::maxheap(int x)
{
	arraysize=x;
   n=0;
   key = new int[arraysize]; 
   heapArray = new int[arraysize]; 
   heapIndex= new int[arraysize]; 
}


maxheap::~maxheap()
{
   delete key;
   delete heapArray;
   delete heapIndex;
} 

bool maxheap::empty()
{
   return (n<=0);
}

void maxheap::setsize(int x)
// For the time being, we are using static arrays
{
	n=0;
	arraysize=x;
   key = new int[arraysize]; 
   heapArray = new int[arraysize]; 
   heapIndex= new int[arraysize]; 
}

      

void maxheap::increaseKey(int v, int k)
// v is the vertex number
{    
      int temp, i;

      if (v>= arraysize) {
         cerr<< "element "<<v<<" out of range of 0--"<< arraysize<<".\n";
         return;
      }

   	if (key[v]>= k)  // That's not a key increase!
         return;

      key[v]=k;
      i = heapIndex[v];

      int p=parent(i); 
      int vertexparent = heapArray[p];

      // bubble up till parent has greater key
      while (i!=0 && key[vertexparent]<k) {
        heapArray[p]=v;
        heapArray[i]=vertexparent;
        heapIndex[vertexparent]=i;
        heapIndex[v]=p;
        i=p;
        p = parent(i);
        vertexparent = heapArray[p];
      }
}

int maxheap::insert(int k, int v)
{
   heapArray[n]=v;
   key[v]=k;
   heapIndex[v]=n;
   int i=n;

   n++;


   int p=parent(i);
   int vertexparent = heapArray[p];

   while (i!=0 && key[vertexparent]<k) {
      heapArray[p]=v;
      heapArray[i]=vertexparent;
      heapIndex[vertexparent]=i;
      heapIndex[v]=p;
      i=p;
      p = parent(i);
      vertexparent = heapArray[p];
   }


}

int maxheap::deleteMax()
{
   if (n<1) {
      cerr<< "removing from empty heap.\n";
      return(-1);
   }
   int element = heapArray[0];

   int xv, xi, pv, pi;
   xv=heapArray[n-1];
   xi=0;
   heapArray[xi]=xv;
   heapIndex[xv]=xi;
   
   n--;

   // bubble down
   int childi = largerChild(xi);
   while  (childi>xi){
      swap(xi,childi);
      xi = childi;
      childi = largerChild(xi);
   }

   return (element);
}

int maxheap::largerChild(int i) 
// determines if either of index i's children have a larger key
// than i's key; if not, returns 0; if so, returns the index of the 
// largest-keyed of the two children
{
   int lefti =  2*i+1;
   int righti = 2*i+2;
   
   // if righti is not in the heap, then check if left is in heap
   //if so make comparison and return 0 or lefti
   if (righti >= n) {
      if (lefti >= n) {
         return(0);
      }
      else  {
         if (key[heapArray[lefti]]>key[heapArray[i]])
            return (lefti);
         else return (0);
      }

   }


   else {// righti and lefti are true heap nodes
   
      if (key[heapArray[lefti]]>=key[heapArray[righti]]) {
         if (key[heapArray[i]]<key[heapArray[lefti]]) 
            return(lefti);
         else return (0);
         }
      else  // righti is the larger-keyed child -- is it smaller than i?
         if (key[heapArray[i]]<key[heapArray[righti]]) {
            return(righti);
         }
   }
   return(0);
}
      

void maxheap::swap(int i1, int i2)
{
   int tempv1=heapArray[i1];
   int tempv2=heapArray[i2];
   heapArray[i1] = tempv2;
   heapArray[i2] = tempv1;

   heapIndex[tempv1]=i2;
   heapIndex[tempv2]=i1;

}

int maxheap::parent(int i)
{
   if (i<3) return 0;
   return((int) ((i-1)/2));
}

int maxheap::size()
{
 	return n;		
}

int maxheap::maxVertex()
{
	
	return heapArray[0];
}
int maxheap::maxKey()
{
	
	return key[heapArray[0]];
}


// call print_node on each node in the heap
void maxheap::print_heap()
{
   for (int i=0; i<n; i++)
   {
        cout << "heap["<<i<<"]= "<<heapArray[i] <<" key is "<< key[heapArray[i]]<<endl;
   }
}

void maxheap::debug_print()
{
   for (int i=0; i<n; i++)
   {
        cout << "heap["<<i<<"]= "<<heapArray[i] <<" key is "<< key[heapArray[i]]<<endl;
   }
   for (int i=0; i<arraysize; i++)
   {
        cout << i<<":"<<key[i]<< "  " ;
   }
}

