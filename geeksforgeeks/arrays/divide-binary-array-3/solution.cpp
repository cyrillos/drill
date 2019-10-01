#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <queue>
#include <stack>

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
	vector<int> ThreeEqualParts(const vector<int>& v) {
		size_t sum, nr_in_range;
		vector<int> res;
		size_t accum;
		size_t i;

		//
		// Find number of 1s since they
		// must be multiple by 3.
		sum = accumulate(v.begin(), v.end(), 0);
		if (sum < 3 || sum % 3)
			return  { -1, -1 };

		//
		// Each range must have same number of 1s.
		nr_in_range = sum / 3;

		//
		// The whole range is filled by 1s
		if (sum == v.size())
			return {(int)nr_in_range - 1, (int)v.size() - (int)nr_in_range};

		for (accum = 0, i = 0; i < v.size(); i++) {
			if (v[i] == 1) {
				accum++;
				if (accum == 1) {
					// 1s series start
					res.push_back(i);
				}
				if (accum == nr_in_range) {
					// 1s series end
					res.push_back(i);
					accum = 0;
				}
			}
		}

		//
		// 1, 0, 1, 0, 1 => source
		// 0     2     4 => res values
		//
		// 0, 1, 0, 0, 1, 0, 0, 1, 0
		//    1        4        7
		//
		// 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0
		//    1  2        5  6        9  10
		//    a  b        c  d        e  f
		//
		// {0   ... i  } first
		// {i+1 ... j-1} second
		// {j   ... n  } third

		size_t a = res[0];
		size_t b = res[1];
		size_t c = res[2];
		size_t d = res[3];
		size_t e = res[4];
		size_t f = res[5];

		// test zeros inbetween
		if ((c-b) != (e-d))
			return {-1,-1};

		// trailing zeros after f should
		// be propagated to previous intervals
		if (f < v.size()-1) {
			size_t off = v.size()-1 - f;
			b += off;
			d += off;

			// and should not overlap
			if (b >= c || d >= e)
				return {-1, -1};
		}

		// we're requested to return +1 for d
		return {(int)b, (int)d + 1};
	}
};

int main()
{
	vector<vector<int>> input = {
		{1, 0, 1, 0, 1},		// => {0, 3}
		{1, 0, 0, 1, 0, 0, 1, 0, 0},
		{1, 1, 0, 1, 1},		// => {-1,-1}
		{1, 1, 1, 1, 1, 1},		// => {1, 4}
		{1, 0, 0, 1, 0, 0, 1},		// => {0, 4}
		{0, 1, 0, 0, 1, 0, 0, 1, 0},	// => {2, 6}
		{0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0},	// => [3,8] 
	};

	Solution solution;
	for (const auto &values: input) {
		cout << values << " => " << solution.ThreeEqualParts(values) << endl;
	}
	return 0;
}
