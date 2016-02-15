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
#include "element.h"

using namespace std;

struct comparator {
	bool operator()(element *le, element *re) {
		bool lhsLarger = true;
		bool rhsLarger = false;
		bool eq = true;
		int lhsLex;
		int rhsLex;

		for (int i = 0; i < le->upperLex.size(); i++) {
			lhsLex = le->upperLex[i];
			if (re->upperLex.size() < i) return lhsLarger;
			rhsLex = re->upperLex[i];

			if (lhsLex > rhsLex) return lhsLarger;
			if (lhsLex < rhsLex) return rhsLarger;
		}

		if (re->upperLex.empty()) return eq;

		return rhsLarger;
	}
};

void lexLabel(vector<element> *elements); 

bool getPosetInfo(char *fn, vector<element> *elements);

// see specification at http://csciun1.mala.bc.ca:8080/~gpruesse/teaching/485/labs/2.posetCoverHeap.html
int bump(vector<element> *elements);

int main(int argc, char *argv[]) {

  if (argc != 2) {
		cout << "bump requires a file name as argument" << endl;
		return 0;
	}

	vector<element> elements;
	
	if (!getPosetInfo(argv[1], &elements)) { return 0; }
	lexLabel(&elements);
  bump(&elements); 	


  return 0;
}

int bump(vector<element> *els) {
	vector<element> elements = *els;
	int n = elements.size();

	int remainingNodes = n;
	int upperNode;
	int vertex;
	int key;
	vector<int> buf;

	/** 
	* any elements with no elements in their lower covers are eligible to be
	* put into the linear extension next (depending on priority). So put
	* these elements in a max heap to find which element should be added
	* next (first).
	*/
	maxheap maxHeap(n);
	for (int i=0; i<n; i++) {
		if (elements[i].lowerCounts == 0) 
			maxHeap.insert(elements[i].lex, i);
	}


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
	int list[n][2];
	int bumps = 0;
	while (remainingNodes > 0) {
		if (maxHeap.empty()) {
			bumps ++;
			cout << "--";
			while (!buf.empty()) {
				maxHeap.insert(elements[buf.back()].lex, buf.back());
				buf.pop_back();
			}
		} else {
			cout << " ";
		}

		vertex = maxHeap.maxVertex();
		key = maxHeap.maxKey();
		cout << vertex << " (" << key << ")";
		list[n-remainingNodes][0] = vertex;
		list[n-remainingNodes][1] = key;
		maxHeap.deleteMax();
		remainingNodes --;
		while (!buf.empty()) {
			maxHeap.insert(elements[buf.back()].lex, buf.back());
			buf.pop_back();
		}
		while (elements[vertex].upperCover.size() > 0) {
			upperNode = elements[vertex].upperCover.back();
			elements[vertex].upperCover.pop_back();
			if (elements[upperNode].lowerCounts == 1)
				buf.push_back(upperNode);
			else 
				elements[upperNode].lowerCounts --;
		}
	};

	cout << " [" << bumps << " bump(s)]" << endl;
  //
	// // print the linear extension
	// cout << "linear extension (top first)" << endl;
	// for (int i = 0; i < n; i ++) 
	// 	cout << list[i][0] << "(" << list[i][1] << ")" << endl;
		// cout << "value " << list[i][0] << " priority " << list[i][1] << endl;


	return 0;
}

void lexLabel(vector<element> *elements) {
	int n = elements->size();
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

bool getPosetInfo(char *fn, vector<element> *elements) {
	ifstream f;
	int v;
	int u;
	int n = 0;

	f.open(fn);

	if (!f) {
		cout << "File not openable. \n";
		return false;
	}

  f >> n;   

	// TODO look for a quicker way
	for (int i = 0; i < n; i++) {
		element e;
		e.key = i;
		(*elements).push_back(e);
	}


	if (n>100000) {
		cout << "n too large" << endl;
		return false;
	}

	f >> u;

	while (u<n && f) {
		f >> v; 
		element *e = &(*elements)[u];
		while (v < n && f) {
			e->upperCover.push_back(v);
			(*elements)[v].lowerCover.push_back(u);
			(*elements)[v].lowerCounts ++;

			f >> v;
		}
		f >> u;
	}

	f.close();	
	return true;
}
