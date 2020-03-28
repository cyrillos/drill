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
	int findDuplicate(vector<int>& nums) {
		if (nums.size() < 2)
			return 0;
		//
		// We can use sorting or sets,
		// but this is not interesting.
		//
		// Lets rather use two pointers
		// where one comes with step 1
		// and second one with step 2,
		// if there is a loop we will
		// detect a cycle. Then simply
		// spin the hare with step 1
		// and restart tortoise.
		//
		// See tortoise and hare algo.
		int tortoise = nums[0];
		int hare = nums[nums[0]];

		while (tortoise != hare) {
			tortoise = nums[tortoise];
			hare = nums[nums[hare]];
		}

		tortoise = 0;
		while (tortoise != hare) {
			tortoise = nums[tortoise];
			hare = nums[hare];
		}

		return tortoise;
	}
};

int main()
{
	vector<int> input[] = {
		{2,5,9,6,9,3,8,9,7,1}, // 9
		{1,3,4,2,2},	// 2
		{1,3,4,4,4,2},	// 2
		{3,1,3,4,2},	// 3
		{1,1,1,2},	// 1
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.findDuplicate(nums) << endl;
	}
	return 0;
}
