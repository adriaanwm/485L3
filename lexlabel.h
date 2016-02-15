#ifndef LEXLABEL_H_
#define LEXLABEL_H_

#include <vector>
#include <iostream>
#include <queue>

#include "element.h"

using namespace std;

void lexLabel(vector<element> *elements);

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

#endif /* LEXLABEL_H_ */
