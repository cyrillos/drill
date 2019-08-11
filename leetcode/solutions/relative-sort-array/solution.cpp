#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

ostream& operator<<(ostream& out, const vector<int>& v)
{
       out << '[';
       for (auto it = v.begin(); it != v.end(); ++it) {
               if (it != v.begin())
                       out << ", ";
               out << *it;
       }
       out << ']';
       return out;
}

ostream& operator<<(ostream& out, map<int,size_t> v)
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
	vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
		vector<int> res(arr1.size());
		map<int,size_t> d;

		for (auto it: arr1) {
			if (d[it])
				d[it]++;
			else
				d[it] = 1;
		}

		size_t pos = 0;
		for (auto it: arr2) {
			if (d[it]) {
				while (d[it]) {
					res[pos++] = it;
					d[it]--;
				}
			}
		}

		for (auto it: d) {
			while (it.second) {
				res[pos++] = it.first;
				it.second--;
			}
		}

		return res;
	}
};

int main()
{
	vector<int> arr1 = { 2,3,1,3,2,4,6,7,9,2,19 };
	vector<int> arr2 = { 2,1,4,3,9,6 };

	Solution solution;
	cout << solution.relativeSortArray(arr1, arr2) << endl;
	return 0;
}
