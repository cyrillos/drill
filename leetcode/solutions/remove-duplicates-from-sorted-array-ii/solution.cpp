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
	int removeDuplicates(vector<int>& nums) {
		size_t pos = 0, cnt = 1, i;

		if (nums.size() < 2)
			return nums.size();

		for (i = 1; i < nums.size(); i++) {
			if (nums[i] == nums[pos]) {
				if (cnt >= 2)
					continue;
			} else
				cnt = 0;

			nums[pos+1] = nums[i];
			pos++;
			cnt++;
		}
		return pos+1;
	}
};

int main()
{
	vector<int> input[] = {
		{1,1,1,2,2,3}, // {1, 1, 2, 2, 3} -> 5
		{0,0,1,1,1,1,2,3,3}, // {0, 0, 1, 1, 2, 3,3} -> 7
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.removeDuplicates(nums) << "" <<
			nums << endl;
	}
	return 0;
}
