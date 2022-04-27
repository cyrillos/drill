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
	vector<int> twoSum(vector<int>& numbers, int target) {
		int l = 0, r = numbers.size()-1;
		while (l < r) {
			auto v = numbers[l] + numbers[r];
			if (v == target)
				return {l+1,r+1};
			if (v < target)
				l++;
			else
				r--;
		}
		return {};
	}
};

int main()
{
	struct {
		vector<int> numbers;
		int target;
	} data[] = {
		{
			// [1,2]
			.numbers = {2,7,11,15},
			.target = 9,
		}, {
			// [1,3]
			.numbers = {2,3,4},
			.target = 6,
		}, {
			// [1,2]
			.numbers = {-1,0},
			.target = -1,
		}
	};
	
	Solution solution;
	for (auto& d: data) {
		cout << d.numbers << ", " << d.target << " => " <<
			solution.twoSum(d.numbers, d.target) << endl;
	}
	return 0;
}
