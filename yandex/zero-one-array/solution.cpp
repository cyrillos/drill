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
	int maxOnes(vector<int> a) {
		vector<pair<int,int>> range;
		int nr = a.size();
		int max_len = 0;

		//
		// Either it is empty array or
		// one element which we can change.
		if (nr == 0)
			return 0;
		else if (nr == 1)
			return 1;

		//
		// Start a range
		range.push_back(make_pair(a[0], 1));
		int rlast = 0;

		for (auto i = 1; i < nr; i++) {
			if (a[i] == range[rlast].first) {
				//
				// Increas a subsequence length
				range[rlast].second++;
				continue;
			}

			//
			// Starting a new 0 subsequence, lets
			// count previous 1's
			if (a[i] == 0) {
				if (range[rlast-1].second == 1 && rlast > 1) {
					//
					// Try to merge with previous
					max_len = max(max_len, range[rlast].second + range[rlast-2].second + 1);
				} else {
					// Always can extend with 1
					max_len = max(max_len, range[rlast].second + 1);
				}
			}

			//
			// It is a new subsequence
			range.push_back(make_pair(a[i], 1));
			rlast++;
		}

		//
		// Ending 0's, always can add ending 1
		if (range[rlast].first == 0)
			return max(max_len, range[rlast-1].second + 1);

		//
		// Last subsequence is 1's
		if (range[rlast-1].second == 1 && rlast > 1) {
			//
			// Try to merge with previous
			max_len = max(max_len, range[rlast].second + range[rlast-2].second + 1);
		} else {
			//
			// Always can add 1
			max_len = max(max_len, range[rlast].second + 1);
		}

		return max_len;
	}
};

int main()
{
	vector<int> input[] = {
		{},			// 0
		{0},			// 1
		{0,0},			// 1
		{0,1,0},		// 2
		{0,1,0,0,1},		// 2
		{1,1,0},		// 3
		{1,1,1,0,1,1,0,0},	// 6
		{1,1,1,1,1,1,0,0},	// 7
		{1,1,1,1,1,1,1,0},	// 8
	};
	Solution solution;
	for (auto& a: input) {
		cout << a << " => " << solution.maxOnes(a) << endl;
	}
	return 0;
}
