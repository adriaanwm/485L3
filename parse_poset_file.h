#ifndef PARSE_POSET_FILE_H_
#define PARSE_POSET_FILE_H_

#include <vector>
#include <iostream>
#include <fstream>

#include "element.h"

using namespace std;

bool getPosetInfo(char *fn, vector<element> *elements);

#endif /* PARSE_POSET_FILE_H_ */
