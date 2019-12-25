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
	vector<int> findDisappearedNumbers(vector<int>& a) {
		vector<int> res;
		int i = 0;

		// Simple count sorting
		while (i < (int)a.size()) {
			if (a[i] != i+1 && (a[i]-1) < (int)a.size() &&
			    a[i] != a[a[i]-1]) {
				swap(a[i], a[a[i]-1]);
			} else
				i++;
		}

		for (i = 0; i < (int)a.size(); i++) {
			if (a[i] != i+1)
				res.push_back(i+1);
		}

		return res;
	}
};

int main()
{
	vector<int> input[] = {
		{1,2,3},
		{1},
		{},
		{4,3,2,7,8,2,3,1}, // {5,6}
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.findDisappearedNumbers(nums) << " => " << nums << endl;
	}
	return 0;
}
