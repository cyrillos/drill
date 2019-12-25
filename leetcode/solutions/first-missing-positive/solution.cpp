#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int firstMissingPositive(vector<int>& a) {
		int i = 0;

		//
		// Just use a count sort, don't use
		// for() cycle since we'are adjusting
		while (i < a.size()) {
			if (a[i] > 0 && a[i] <= a.size() &&
			    a[i] != a[a[i]-1]) {
				swap(a[i], a[a[i]-1]);
			} else
				i++;
		}
		for (i = 0; i < a.size(); i++) {
			if (a[i] != i+1)
				return i+1;
		}
		return a.size()+1;
	}
};

int main()
{
	vector<int> input[] = {
		{1,2,0},		// 3
		{3,4,-1,1},		// 2
		{7,8,9,11,12},		// 1
		{-1,4,2,1,9,10},	// 3
		{4,1,2,3},		// 5
	};

	Solution solution;

	for (auto &nums: input) {
		cout << nums << " => " << solution.firstMissingPositive(nums) << endl;
	}

	return 0;
}
