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
	void recursive(vector<vector<int>>& acc, vector<int>& comb,
		       int comb_len, int cur_n, int n, int k) {
		if (comb_len == k) {
			acc.push_back(comb);
			return;
		} else if (cur_n > n) {
			return;
		}

		//
		// Just pick next number and try to append
		// it into current subgroup.
		int next_n = cur_n + 1;
		comb.push_back(cur_n);
		recursive(acc, comb, comb_len + 1, next_n, n, k);
		comb.pop_back();
		recursive(acc, comb, comb_len, next_n, n, k);
	}

	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> acc;
		vector<int> comb;

		recursive(acc, comb, 0, 1, n, k);
		return acc;
	}
};

int main()
{
	int input[][2] = {
		{4, 3},
		{4, 2},
		{1, 1},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums[0] << ", " << nums[1] << " => " <<
			solution.combine(nums[0], nums[1]) << endl;
	}
	return 0;
}
