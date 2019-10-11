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
	int maxArea(const vector<int>& a) {
		ssize_t i = 0, j = a.size()-1;
		int res = 0, left, right;

		if (j <= i)
			return 0;

		while (i < j) {
			left = a[i];
			right = a[j];

			int accum = min(left, right) * (j-i);
			res = max(res, accum);
			if (left < right)
				i++;
			else
				j--;
		}

		return res;
	}
};

int main()
{
	vector<int> input[] = {
		{1},
		{},
		{1,8,6,2,5,4,8,3,7},	// => 49
	};

	Solution solution;

	for (const auto &height: input) {
		cout << height << " => " << solution.maxArea(height) << endl;
	}
	return 0;
}
