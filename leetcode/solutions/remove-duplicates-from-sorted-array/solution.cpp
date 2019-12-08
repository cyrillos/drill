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
	    size_t i, pos = 0;

	    if (nums.size() < 2)
		    return nums.size();

	    for (i = 1; i < nums.size(); i++) {
		    if (nums[i] == nums[pos])
			    continue;
		    nums[pos+1] = nums[i];
		    pos++;
	    }

	    return pos+1;
    }
};

int main()
{
	vector<int> input[] = {
		{1,1,2},		// {1,2} -> 2
		{0,0,1,1,1,2,2,3,3,4},	// {0,1,2,3,4} -> 5
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.removeDuplicates(nums) << " " <<
			nums << endl;
	}
	return 0;
}
