#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

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
	int jump(vector<int>& nums) {
		ssize_t n = nums.size();
		size_t best = 1;

		if (n < 2)
			return 0;

		size_t i = 0;
		//
		// Just walk left to right and choose
		// a maximal distance
		while (i + nums[i] < n-1) {
			size_t next = i+1; // minimal step
			for (size_t j = i; j <= i + nums[i]; j++) {
				if (j + nums[j] > next + nums[next])
					next = j;
			}
			i = next;
			best++;
		}

		return best;
	}
};

int main()
{
	vector<int> input[] = {
		{0},		// 0
		{2,3,0,1,4},	// 2
		{2,0,0},	// 1
		{2,1,1,1,3,1},	// 4
		{2,3,1,1,4},	// 2
		{1,2,3},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " << solution.jump(nums) << endl;
	}
	return 0;
}
