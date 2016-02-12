#include <queue>
#include <iostream>
#include <vector>
  
using namespace std;
  
struct comparator {
	bool operator()(std::vector<int> lhs, std::vector<int> rhs) {
		bool lhsLarger = true;
		bool rhsLarger = false;
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
};

void dump(std::vector<int> v) {
  while (!v.empty()) {
    cout << v.back() << " ";
    v.pop_back();
  }
  cout << endl;
  return;
}
  
int main(int argc, char const *argv[])
{
	priority_queue<std::vector<int>, std::vector<std::vector<int> > , comparator> minHeap;

	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> v3;

	v1.push_back(0);
	v1.push_back(4);
	v1.push_back(6);
	v2.push_back(0);
	v2.push_back(0);
	v2.push_back(4);
	v2.push_back(6);
	v3.push_back(7);
	v3.push_back(7);
	v3.push_back(7);

	minHeap.push(v1);
	minHeap.push(v2);
	minHeap.push(v3);

	while (!minHeap.empty()) {
    std::vector<int> vec = minHeap.top();
    dump(vec);
		minHeap.pop();
	}
	return 0;
}
