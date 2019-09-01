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
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> res;

		sort(nums.begin(), nums.end());

		//
		// This is gonna be O(n^2) algo
		//
		for (ssize_t pos = 0; pos < (ssize_t)nums.size() - 2;) {
			ssize_t j = nums.size() - 1;
			ssize_t i = pos + 1;

			while (i < j) {
				int sum = nums[pos] + nums[i] + nums[j];
				if (sum == 0) {
					vector<int> v({nums[pos], nums[i], nums[j]});
					res.push_back(move(v));
				}

				if (sum <= 0) {
					do {
						i++;
					} while (i < j && nums[i] == nums[i-1]);
				} else if (sum >= 0) {
					do {
						j--;
					} while (i < j && nums[j] == nums[j+1]);
				}
			}
			do {
				pos++;
			} while (pos < (ssize_t)nums.size() && nums[pos] == nums[pos-1]);
		}

		return res;
	}
};

int main()
{
	vector<int> input[] = {
		{ -4,-1,-1,0,1,2, },		// [[-1,-1,2],[-1,0,1]]
		{0, 0, 0, 0},
	};
	Solution solution;
	for (auto& nums: input) {
		for (auto& v: solution.threeSum(nums)) {
			cout << "v " << v << endl;
		}
		cout << "---" << endl;
	}
	return 0;
}
