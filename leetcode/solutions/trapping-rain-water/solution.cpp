#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<int>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int trap(vector<int>& a) {
		if (a.size() == 0)
			return 0;
		size_t max_right = 0;
		size_t max_left = 0;
		size_t accum = 0;

		for (size_t l = 0, r = a.size() - 1; l < r;) {
			size_t left_val = a[l];
			size_t right_val = a[r];

			max_right = max(max_right, right_val);
			max_left = max(max_left, left_val);

			if (left_val <= right_val) {
				accum += max_left - left_val;
				l++;
			} else {
				accum += max_right - right_val;
				r--;
			}
		}
		return accum;
	}
};

int main()
{
	vector<int> input[] = {
		{ },
		{ 0 },
		{ 1, 1 },
		{ 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 },
	};
	Solution solution;
	for (auto& v: input)
		cout << v << " => " << solution.trap(v) << endl;
	return 0;
}
