/**
 * course: CSCI 485
 * date: February 14, 2016
 * student name: Adriaan Mulder
 * student number: 575148838
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "maxheap.h"
#include "element.h"
#include "lexlabel.h"
#include "parse_poset_file.h"

using namespace std;


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


