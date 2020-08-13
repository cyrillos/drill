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
	void recursive(vector<vector<int>>& res, vector<int>& acc, int next, int k, int n) {
		if ((int)acc.size() == k && n == 0) {
			res.push_back(acc);
			return;
		}

		//
		// This is similar to generation of all permutations
		// via recursion: we just add a new digit back, and
		// call it again to apped new digits until target is
		// reached, then simply pop it and start with next
		// subgroup.
		if ((int)acc.size() < k) {
			for (int i = next; i <= 9; i++) {
				if (n - i < 0)
					break;
				acc.push_back(i);
				recursive(res, acc, i+1, k, n - i);
				acc.pop_back();
			}
		}
	}

	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>> res;
		vector<int> acc;
		recursive(res, acc, 1, k, n);
		return res;
	}
};

int main()
{
	struct {
		int k;
		int n;
	} input[] = {
		{
			.k = 3,
			.n = 7,
		}, {
			.k = 3,
			.n = 9,
		},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums.k << " , " << nums.n << " => " <<
			solution.combinationSum3(nums.k, nums.n) << endl;
	}
	return 0;
}
