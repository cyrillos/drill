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
	//
	// Simply use prefix sums
	long long maximumSumScore(vector<int>& nums) {
		long long sum = 0;
		for (int v: nums)
			sum += v;

		long long sum_prev = 0;
		long long res = -1000000;
		for (size_t i = 0; i < nums.size(); i++) {
			sum_prev += nums[i];
			long long left = sum_prev;
			long long right = sum - sum_prev + nums[i];
			res = max(res, max(left, right));
		}

		return res;
	}
};

int main()
{
	vector<int> input[] = {
		{4,3,-2,5},	// 10
		{-3,-5},	// -3
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.maximumSumScore(nums) << endl;
	}
	return 0;
}
