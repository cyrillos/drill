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
	bool canJump(vector<int>& nums) {
		if (nums.size() < 2)
			return true;

		for (int i = nums.size()-1; i >= 0; i--) {
			if (nums[i] > 0)
				continue;

			// Just try to find suitable left position
			// to jump from to reach position after i
			// (or end of array).
			bool found = false;
			for (int j = i-1; j >= 0; j--) {
				if (nums[j] > (i - j)) {
					found = true;
					break;
				} else if (nums[j] == (i - j)) {
					if (i == nums.size()-1) {
						found = true;
						break;
					}
				}
			}
			if (!found)
				return false;
		}

		return true;
	}
};

int main()
{
	vector<int> input[] = {
		{0},		// false
		{2,0,0},	// true
		{2,3,1,1,4},	// true
		{3,2,1,0,4},	// false
		{3,3,1,0,4},	// true
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " << solution.canJump(nums) << endl;
	}
	return 0;
}
