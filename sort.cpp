#include <iostream>
#include <vector>

// return true if lhs <= rhs
bool compare(std::vector<int> lhs, std::vector<int> rhs) {
	bool lhsLarger = false;
	bool rhsLarger = true;
	bool eq = true;
	int lhsLex;
	int rhsLex;

	while (true) {

		// if any are empty
		if (lhs.empty() && rhs.empty()) return eq;
		if (lhs.empty()) return rhsLarger;
		if (rhs.empty()) return lhsLarger;

		// if none are empty
		lhsLex = lhs.back(); lhs.pop_back();	
		rhsLex = rhs.back(); rhs.pop_back();
		if (lhsLex > rhsLex) return lhsLarger;
		if (lhsLex < rhsLex) return rhsLarger;
		
	}	
}

int main() {
	std::vector<int> v1;
	std::vector<int> v2;

	v1.push_back(0);
	v1.push_back(4);
	v1.push_back(6);
	v2.push_back(0);
	v2.push_back(0);
	v2.push_back(4);
	v2.push_back(6);

	bool result = compare(v1,v2);
	
	std::cout << result << std::endl;

	return 0;
}
