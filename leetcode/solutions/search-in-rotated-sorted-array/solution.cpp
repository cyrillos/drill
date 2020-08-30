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
	int search(vector<int>& n, int t) {
		if (n.size() < 1)
			return -1;

		int nr = n.size();
		int r = n.size() - 1;

		//
		// find a pivot point, ie the smallest
		// value, since we know it must be there
		int lo = 0, hi = r;
		auto pivot = [&](int lo, int hi) {
			while (lo < hi) {
				int pos = (lo + hi) / 2;
				if (n[pos] > n[hi])
					lo = pos + 1;
				else
					hi = pos;
			}
			return lo;
		};

		//
		// Once we're a pivot point we can search for
		// the value needed.
		int pivot_pos = pivot(0, r);
		lo = 0, hi = r;
		while (lo <= hi) {
			int pos = (lo + hi) / 2;
			int rot_pos = (pos + pivot_pos) % nr;
			if(n[rot_pos] == t)
				return rot_pos;
			else if(n[rot_pos] < t)
				lo = pos + 1;
			else
				hi = pos - 1;
		}
		return -1;
	}
};

int main()
{
	struct {
		vector<int> nums;
		int target;
	} input[] = {
		{
			// 4
			.nums = {4,5,6,7,0,1,2},
			.target = 0,
		}, {
			// -1
			.nums = {4,5,6,7,0,1,2},
			.target = 3,
		}, {
			// -1
			.nums = {1},
			.target = 0,
		}, {
			// 2
			.nums = {1,2,3,4},
			.target = 3,
		},
	};
	Solution solution;
	for (auto& n: input) {
		cout << n.nums << "," << n.target << " => " <<
			solution.search(n.nums, n.target) << endl;
	}
	return 0;
}
