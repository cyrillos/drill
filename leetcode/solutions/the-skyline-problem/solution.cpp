#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>

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
	vector<vector<int>> getSkyline(vector<vector<int>>& b) {
		vector<vector<int>> res;
		if (b.size() == 0)
			return res;

		//
		// sp -- start point
		// ep -- end point
		//
		// Special case 1
		//
		//     sp2   ep2
		//      +----+
		//      |    |
		//      |    |
		// +----+ep1 |
		// |sp1 |    |
		// |    |    |
		// +----+----+
		//
		// Special case 2
		//
		// sp1   ep1
		// +----+
		// |    |
		// |    |
		// |    +----+ ep2
		// |    |sp2 |
		// |    |    |
		// +----+----+
		//
		// Special case 3
		//
		// sp2       ep2
		// +----------+
		// |          |
		// |          |
		// +----+ep1  |
		// |sp1 |     |
		// |    |     |
		// +----+-----+
		//
		// We create a pairs of points, the entry points
		// are saved with negative height such that more
		// tall buildings with same starts comes first.
		//
		// Same time this allows us to distinguish starts
		// and ends of buildings.
		vector<pair<int, int>> points;

		points.reserve(b.size() * 2);
		for (size_t i = 0; i < b.size(); i++) {
			points.emplace_back(b[i][0], -b[i][2]);
			points.emplace_back(b[i][1], b[i][2]);
		}

		//
		// Sort buildings by their X values so we
		// walk left to right.
		sort(points.begin(), points.end());
		//
		// Multiset keeps heights of buildings
		// in ascending order.
		multiset<int> mset{0};

		int pre = 0, cur = 0;
		for (size_t i = 0; i < points.size(); i++) {
			if (points[i].second < 0) {
				// Insert building height
				// when we meet start of it.
				mset.insert(-points[i].second);
			} else {
				// Drop building height when
				// we meet end of it.
				mset.erase(mset.find(points[i].second));
			}

			// Current maximum height value.
			cur = *mset.rbegin();
			if (cur != pre) {
				res.push_back({points[i].first, cur});
				pre = cur;
			}
		}

		return res;
	}
};

int main()
{
	vector<vector <int>> input[] = {
		{
			//l   r   h
			{ 2,  9, 10},
			{ 3,  7, 15},
			{ 5, 12, 12},
			{15, 20, 10},
			{19, 24,  8},
		}
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.getSkyline(nums) << endl;
	}
	return 0;
}
