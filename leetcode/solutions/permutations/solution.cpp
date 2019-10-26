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
	void permute_recursive(vector<vector<int>>& res, vector<int>& a, ssize_t pos, size_t size) {
		if (pos == (ssize_t)size - 1) {
			res.push_back(a);
		} else {
			for (ssize_t i = pos; i < (ssize_t)size; i++) {
				swap(a[i], a[pos]);
				permute_recursive(res, a, pos+1, size);
				swap(a[i], a[pos]);
			}
		}
	}

	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> res;
		permute_recursive(res, nums, 0, nums.size());
		return res;
	}
};

int main()
{
	vector<int> input[] = {
		{ },
		{1},
		{1,2},
		{1,2,3},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.permute(nums) << endl;
	}
	return 0;
}
