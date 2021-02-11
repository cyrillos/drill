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
	vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
		size_t nr = intervals.size();
		if (nr == 0)
			return { newInterval };

		int l = newInterval[0];
		int r = newInterval[1];
		size_t pos = 0;

		vector<vector<int>> res;
		//
		// Prepend all elems which are sitting
		// before new interval.
		while (pos < nr && intervals[pos][1] < l)
			res.push_back(intervals[pos++]);

		//
		// Find out a range which [l, r] is covering,
		// min/max to find widest interval.
		while (pos < nr && intervals[pos][0] <= r) {
			l = min(l, intervals[pos][0]);
			r = max(r, intervals[pos][1]);
			pos++;
		}
		res.push_back({l, r});

		//
		// Finally append all elements which are
		// uncovered after the new interval.
		while (pos < nr)
			res.push_back(intervals[pos++]);
		return res;
	}
};

int main()
{
	struct {
		vector<vector<int>> intervals;
		vector<int> newInterval;
	} input[] = {
		{
			.intervals = {{1,3}, {6,9}},
			.newInterval = {2,5},
			// => [[1,5],[6,9]]
		}, {
			.intervals = {{1,2},{3,5},{6,7},{8,10},{12,16}},
			.newInterval = {4,8},
			// => [[1,2],[3,10],[12,16]]
		}, {
			.intervals = {},
			.newInterval = {5,7},
			// => [[5,7]]
		}, {
			.intervals = {{1,5}},
			.newInterval = {2,3},
			// => [[1,5]]
		}, {
			.intervals = {{1,5}},
			.newInterval = {2,7},
			// => [[1,7]]
		}
	};
	Solution solution;
	for (auto& v: input) {
		cout << v.intervals << ", " << v.newInterval <<
			" => " << solution.insert(v.intervals, v.newInterval) << endl;
	}
	return 0;
}
