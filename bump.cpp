/**
 * course: CSCI 485
 * date: January 28, 2016
 * student name: Adriaan Mulder
 * student number: 575148838
 */

#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "maxheap.h"

using namespace std;

struct element {
	element() : touched(false) {}
	vector<int> upperLex;
	vector<int> upperCover;
	vector<int> lowerCover;
	int lowerCounts;
	bool touched;
	int key;
	int lex;
};

void dump(vector<element> elements);
void dump(element e);
void dump(vector<int> v);

struct comparator {
	bool operator()(element *le, element *re) {
		bool lhsLarger = true;
		bool rhsLarger = false;
		bool eq = true;
		int lhsLex;
		int rhsLex;

		cout << "left: " << endl;
		dump(*le);
		cout << "right: " << endl;
		dump(*re);

		for (int i = 0; i < le->upperLex.size(); i++) {
			lhsLex = le->upperLex[i];
			if (re->upperLex.size() < i) return lhsLarger;
			rhsLex = re->upperLex[i];

			if (lhsLex > rhsLex) return lhsLarger;
			if (lhsLex < rhsLex) return rhsLarger;
		}

		if (re->upperLex.empty()) return eq;

		return rhsLarger;


		// while (true) {
    //
		// 	// if any are empty
		// 	if (le.upperLex.empty() && re.upperLex.empty()) return eq;
		// 	if (le.upperLex.empty()) return rhsLarger;
		// 	if (re.upperLex.empty()) return lhsLarger;
    //
		// 	// if none are empty
		// 	lhsLex = le.upperLex.back(); le.upperLex.pop_back();	
		// 	rhsLex = re.upperLex.back(); re.upperLex.pop_back();
		// 	if (lhsLex > rhsLex) return lhsLarger;
		// 	if (lhsLex < rhsLex) return rhsLarger;
		// 	
		// }	
	}
};

void lexLabel(int n, vector<element> *elements); 

/** 
 * generates a random integer from 0-range that has not already been 
 * given by the function (as kept track by usedPriorities array,
 * if usedPriorities[i] = 0 then i might be returned, else i will not
 * be returned)
 */
int randInt(int range, vector<int> usedPriorities);


// see specification at http://csciun1.mala.bc.ca:8080/~gpruesse/teaching/485/labs/2.posetCoverHeap.html
int bump(char *fn);

int main(int argc, char *argv[]) {

  if (argc != 2) {
		cout << "bump requires a file name as argument" << endl;
		return 0;
	}

  bump(argv[1]); 	

  return 0;
}

int bump(char *fn) {
	ifstream f;
	int v;
	int u;
	int n = 0;
   
	f.open(fn);

	if (!f) {
		cerr<<"File not openable. "<<endl; 
		return 0;
	}
      
   f >> n;   
	 
	// keep track of how many elements are in the lower cover of each element
	// int lowerCounts[n] = {0};
	
	// TODO check this...
	// vector<int> lowerCounts (n, 0);
	// vector<int> *upperCover = new vector<int>[n];  
	vector<element> elements;
	for (int i = 0; i < n; i++) {
		element e;
		e.key = i;
		elements.push_back(e);
	}


	maxheap maxHeap(n);

	int list[n][2];

	if (n>100000) { cerr<<"n too large: "<<n<<endl; return 0;} // arbitrary

	f >> u;

	while (u<n && f) {
		f >> v; 
		element *e = &elements[u];
		while (v < n && f) {
			e->upperCover.push_back(v);
			elements[v].lowerCover.push_back(u);
			e->lowerCounts ++;
			
			f >> v;
		}
		f >> u;
	}
	

	lexLabel(n, &elements);

	dump(elements);

	// int remainingNodes = n;
	// // int usedPriorities[2*n] = {0};
	// vector<int> usedPriorities (2*n, 0);
	// // int *usedPriorities = new array(0)[2*n];
	// int upperNode;
	// int vertex;
	// int key;

	/** 
	* any elements with no elements in their lower covers are eligible to be
	* put into the linear extension next (depending on priority). So put
	* these elements in a max heap to find which element should be added
	* next (first).
	*/
	// for (int i=0; i<n; i++) {
	// 	if (lowerCounts[i] == 0) 
	// 		maxHeap.insert(randInt(2*n, usedPriorities), i);
	// }

	/** 
	* All eligible elements to be added to the linear extension are now in
	* the maxHeap, so:
	*	- remove the one with the heighest priority and put it in the linear extension
	*	- decrement the number of elements in the lower cover count of each element in 
	*	  the upper cover of the element that was just removed from the heap.
	*	- if any of these elements now have 0 elements in their lower cover, add
	*	  them to the max heap as well
	*	- repeat this until all the nodes are in the linear extension
	*/
	// while (remainingNodes > 0) {
	// 	vertex = maxHeap.maxVertex();
	// 	key = maxHeap.maxKey();
	// 	list[n-remainingNodes][0] = vertex;
	// 	list[n-remainingNodes][1] = key;
	// 	maxHeap.deleteMax();
	// 	remainingNodes --;
	// 	while (upperCover[vertex].size() > 0) {
	// 		upperNode = upperCover[vertex].back();
	// 		upperCover[vertex].pop_back();
	// 		if (lowerCounts[upperNode] != 1) {
	// 			 lowerCounts[upperNode] = lowerCounts[upperNode] - 1;
	// 		} else {
	// 			 maxHeap.insert(randInt(2*n, usedPriorities), upperNode);
	// 		}
	// 	 }
	// };
  //
	// // print the linear extension
	// cout << "linear extension (top first)" << endl;
	// for (int i = 0; i < n; i ++) 
	// 	cout << "value " << list[i][0] << " priority " << list[i][1] << endl;

	f.close();	

	return 0;
}

int randInt(int range, vector<int> usedPriorities) {
	int num;
	
	// initalize random number
	srand(time(NULL));

	do {
		num = rand() % range;
	} while (usedPriorities[num] == 1);

	usedPriorities[num] = 1;
	return num;
}

void lexLabel(int n, vector<element> *elements) {
	// priority_queue<std::vector<int>, std::vector<std::vector<int> > , comparator> ready;
	priority_queue<element*, std::vector<element*>, comparator> ready;

	int count = n;
	int last = -1;
	int lex = 0;

	for (int i = 0; i < n; i++) {
		element *e = &(*elements)[i];
		if (e->upperCover.size() == 0) {
			e->lex = lex;
			count --;

			// cycle through lower cover
			for (std::vector<int>::iterator it = e->lowerCover.begin(); 
					 it != e->lowerCover.end(); ++it) {
				element *e2 = &(*elements)[*it];
				e2->upperLex.insert(e2->upperLex.begin(), e->key);
				if (!e2->touched) {
					e2->touched = true;
					count --;
				}
				if (e2->upperLex.size() == e2->upperCover.size()) ready.push(e2);
			}
			if (count == 0) break;
		}
	}

	while (ready.size() > 0) {
		element *e = ready.top(); ready.pop();

		// custom equals?
		if (last >= 0 && (*elements)[last].upperLex == e->upperLex)
			e->lex = lex;
		else
			e->lex = ++lex;
		last = e->key;

		// cycle through lower cover
		for (std::vector<int>::iterator it = e->lowerCover.begin(); 
				 it != e->lowerCover.end(); ++it) {
			element *e2 = &(*elements)[*it];
			e2->upperLex.insert(e2->upperLex.begin(), e->key);
			if (!e2->touched) {
				e2->touched = true;
				count --;
			}
			if (e2->upperLex.size() == e2->upperCover.size()) ready.push(e2);
		}

	}

}	

void dump(vector<int> v) {
	for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i)
		cout << *i << " " ;
}

void dump(element e) {
	cout << "key: " << e.key << endl;
	cout << "lex: " << e.lex << endl;
	cout << "upperCover: "; dump(e.upperCover); cout << endl;
	cout << "lowerCover: "; dump(e.lowerCover); cout  << endl;
	cout << "upperLex: "; dump(e.upperLex); cout  << endl << endl;
}

void dump(vector<element> elements) {
	for (std::vector<element>::const_iterator i = elements.begin(); i != elements.end(); ++i)
		dump(*i);
}




