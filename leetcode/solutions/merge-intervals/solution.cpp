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
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		vector<vector<int>> res;

		if (intervals.size() == 0) {
			return { };
		} else if (intervals.size() == 1) {
			return intervals;
		}
		// Just sort an merge.
		sort(intervals.begin(), intervals.end());
		res.push_back(intervals[0]);
		for (int i = 1; i < intervals.size(); i++) {
			auto& last = res.back();
			if (last[1] >= intervals[i][0]) {
				if (intervals[i][1] > last[1])
					last[1] = intervals[i][1];
			} else {
				res.push_back(intervals[i]);
			}
		}
		return res;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
			{1,3}, {2,6}, {8,10}, {15,18}, // => [1,6],[8,10],[15,18]
		}, {
			{1,4},{4,5}, // => [1,5]
		}, {
			{1,4},{2,3}, // => [1,4]
		}
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " << solution.merge(nums) << endl;
	}
	return 0;
}
