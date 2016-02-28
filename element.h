#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <vector>
#include <iostream>

using namespace std;

struct element {
	element() : touched(false), lowerCounts(0) {}
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

#endif /* ELEMENT_H_ */


