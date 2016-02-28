#include "lexlabel.h"

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
					 it != e->lowerCover.end(); ++ it) {
				element *e2 = &(*elements)[*it];
				e2->upperLex.insert(e2->upperLex.begin(), e->lex);
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
			e2->upperLex.insert(e2->upperLex.begin(), e->lex);
			if (!e2->touched) {
				e2->touched = true;
				count --;
			}
			if (e2->upperLex.size() == e2->upperCover.size()) ready.push(e2);
		}

	}

	// dump(*elements);

}	
