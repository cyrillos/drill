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

template<typename K, typename V>
ostream& operator<<(ostream& out, unordered_map<K,V> v)
{
       out << '{';
       for (auto it = v.begin(); it != v.end(); ++it) {
               if (it != v.begin())
                       out << ", ";
               out << '[' << it->first << "]: " << it->second;
       }
       out << '}';
       return out;
}

class Solution {
public:
	int maxSubArray(const vector<int>& a) {
		int best, sums;

		if (a.size() < 1)
			return 0;

		//
		// Either current position is
		// a start of a new subarray,
		// either we're continue accumulating
		// increasing length of subarray.

		best = a[0];
		sums = 0;

		for (size_t i = 0; i < a.size(); i++) {
			sums = max(a[i], sums + a[i]);
			best = max(sums, best);
		}

		return best;
	}
};

int main()
{
	vector<int> input[] = {
		{ -1 },
		{ -1, -2, -3 },				// -1
		{ -2, 1, -3, 4, -1, 2, 1, -5, 4 },	// 6
		{ 0, 1, 2, -4 },
	};
	Solution solution;
	for (const auto& nums: input) {
		cout << nums << " => " <<
			solution.maxSubArray(nums) << endl;
	}
	return 0;
}
