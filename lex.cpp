// int count = n;
// int lex = 0;
// int last = 0;
// int lexNumbers[n];
// bool touched[n] = {false};
// vector<int> * upperLex = new vector<int>[n];
//
// for (int i = 0; i < n; i++) {
// 	if (i.uc.length == 0) {
// 		lexNumbers[i] = lex;
// 		count --;
//
// 		// cycle through lower cover
// 		for (std::vector<int>::iterator it = lowerCover[i].begin(); 
// 				 it != lowerCover[i].end(); ++it) {
// 			upperLex[*it].push(i);
// 			if (!touched[*it]) {
// 				touched[*it] = true;
// 				count --;
// 			}
// 			if (upperLex[*it].size() == upperCover[*it].size())	{
// 				ready.insert();
// 			}
// 		}
// 		if (count == 0) break;
// 	}
// }
//
// while (ready.size() > 0) {
// 	
// }


/**
 * v2
 */

struct element {
	vector<int> upperLex = new vector<int>;
	vector<int> upperCover = new vector<int>;
	vector<int> lowerCover = new vector<int>;
	bool touched = false;
	int key;
	int lex;
}

void lexLabel(int n, element elements[]) {
	int count = n;
	int last = -1;
	int lex = 0;

	for (int i = 0; i < n; i++) {
		element e = elements[i];
		if (e.upperCover.size() == 0) {
			e.lex = lex;
			count --;

			// cycle through lower cover
			for (std::vector<int>::iterator it = e.lowerCover.begin(); 
					 it != e.lowerCover.end(); ++it) {
				element e2 = elements[*it];
				e2.upperLex.push(e.key);
				if (!e2.touched) {
					e2.touched = true;
					count --;
				}
				if (e2.upperLex.size() == e2.size()) ready.insert(e2);
			}
			if (count == 0) break;
		}
	}

	while (ready.size() > 0) {
		element e = ready.removeMin();
		
		// custom equals?
		if (last >= 0 && elements[last].upperLex == e.upperLex)
			e.lex = lex;
		else
			e.lex = ++lex;
		last = e.key;
	}

}	




