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
	int pivotIndex(vector<int>& nums) {
		//
		// An idea is pretty simple.
		// Consider a sequence where the
		// pivot exists
		//
		//    a + b + c + d = sum
		//            ^
		//          pivot
		//
		// Thus a + b == d, so a + b = sum - d - c
		//
		// So we use a rolling sum_prev = a + b, we
		// have for pivot element
		//
		// sum - (a+b) - c == (a+b)
		//
		int sum = 0;
		for (auto v: nums)
			sum += v;

		int sum_prev = 0;
		for (size_t i = 0; i < nums.size(); i++) {
			auto v = sum - sum_prev - nums[i];
			if (v == sum_prev)
				return i;
			sum_prev += nums[i];
		}
		return -1;
	}
};

int main()
{
	vector<int> input[] = {
		{1,7,3,6,5,6},	// 3
		{1,2,3},	// -1
		{2,1,-1},	// 0
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.pivotIndex(nums) << endl;
	}
	return 0;
}
