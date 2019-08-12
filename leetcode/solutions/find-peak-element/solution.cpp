#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

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
	int findPeakElement(vector<int>& a) {
		size_t l = 0, r = a.size()-1;
		while (l < r) {
			auto pos = (l + r) / 2;
			if (a[pos] > a[pos + 1])
				r = pos;
			else
				l = pos + 1;
		}
		return l;
	}
};

int main()
{
	vector<int> input[] = {
		{1,2,3,1},		// => 2
		{1,2,1,3,5,6,4 },	// => 1 or 5
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.findPeakElement(nums) << endl;
	}
	return 0;
}
