#include "element.h"


void dump(vector<int> v) {
	for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i)
		cout << *i << " " ;
}

void dump(element e) {
	cout << "key: " << e.key << endl;
	cout << "lex: " << e.lex << endl;
	cout << "upperCover: "; dump(e.upperCover); cout << endl;
	cout << "lowerCover: "; dump(e.lowerCover); cout  << endl;
	cout << "lowerCounts: "<< e.lowerCounts  << endl;
	cout << "upperLex: "; dump(e.upperLex); cout  << endl << endl;
}

void dump(vector<element> elements) {
	for (std::vector<element>::const_iterator i = elements.begin(); i != elements.end(); ++i)
		dump(*i);
}
