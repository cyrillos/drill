#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <map>
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

template<typename K, typename V>
ostream& operator<<(ostream& out, map<K,V> v)
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
	bool isPossibleDivide(vector<int>& nums, int k) {
		int n = (int)nums.size();
		int cnt = 0;

		//
		// Splitting to sets equal in size, requires
		// the size of array being divisible by k
		if (n % k != 0)
			return false;

		//
		// Count entries (make sure to use ordered map
		// othervise we will have to sort array first
		// and find out bounds of sequences!)
		map<int, int> map;

		for (int i = 0; i < n; i++)
			map[nums[i]]++;

		//
		// Walk over sorted map, find if particular number
		// can start a set and find the sequence length
		// of k.
		auto it = map.begin();
		while (it != map.end()) {
			int pos = it->first;
			if (map[pos] > 0) {
				for (int i = 0; i < k; i++) {
					int where = pos + i;
					if (!map.count(where) ||
					    --map[where] < 0)
						return false;
				}
				cnt++;
			} else
				it++;
		}

		return cnt > 1 ? true : false;
	}
};

int main()
{
	struct {
		vector<int> nums;
		int k;
	} input[] = {
		{
			// True
			// 1,2,3,4 | 3,4,5,6
			.nums = {1,2,3,3,4,4,5,6},
			.k = 4,
		}, {
			// True
			// 1,2,3 | 2,3,4 | 3,4,5 | 9,10,11
			.nums = {3,2,1,2,3,4,3,4,5,9,10,11},
			.k = 3,
		}, {
			// True
			// 3,2,1 | 3,2,1
			.nums = {3,3,2,2,1,1},
			.k = 3,
		}, {
			// False
			.nums = {1,2,3,4},
			.k = 4,
		}, {
			// False
			.nums = {2,4,6},
			.k = 3,
		},
	};

	Solution solution;
	for (auto &v: input) {
		cout << v.nums << " by " << v.k << " => " <<
			solution.isPossibleDivide(v.nums, v.k) << endl;
	}
	return 0;
}
