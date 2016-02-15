#include "parse_poset_file.h"

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
