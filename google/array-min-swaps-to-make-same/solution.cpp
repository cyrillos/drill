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

	template<typename T>

ostream& operator<<(ostream& out, unordered_map<int,size_t> v)
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
	int MakeSwaps(vector <int>& a, vector <int>& b) {

		// All numbers are [1..6], thus simply
		// use counting sort approach: count
		// frequency of numbers in both arrays,
		// then find the number which seen most
		// time and count sum from two freq to
		// see if we can make an array with same
		// numbers.

		int freq_a[7] = { }; // to index from 1
		int freq_b[7] = { };

		// 1, 2, 2, 3, 3, 6
		// 1, 2, 2, 2, 2, 4

		for (size_t i = 0; i < a.size(); i++) {
			if (a[i] == b[i]) {
				int v = a[i];
				// Make frequency inequal,
				// to minimize number of swaps,
				// later we will return the minimal
				// value.
				if (freq_a[v] < freq_b[v])
					freq_b[v]++;
				else
					freq_a[v]++;
			} else {
				freq_a[a[i]]++;
				freq_b[b[i]]++;
			}
		}

		for (size_t i = 1; i < 7; i++) {
			if (freq_a[i] + freq_b[i] == (int)a.size()) {
				return min(freq_a[i], freq_b[i]);
		}

		return -1;
	}
};

int main()
{
	vector<vector <int>> arr1 = {
		{1, 2, 3, 6, 3, 2},
		{1, 2, 1, 2},
		{1, 1, 1, 2, 2, 2},
	};
	vector<vector <int>> arr2 = {
		{2, 1, 2, 2, 2, 4},		// => 2 (swap idx 1 and 5)
		{2, 6, 1, 2},			// => -1
		{2, 2, 2, 1, 2, 2},		// => 1
	};
	Solution solution;

	for (size_t i = 0; i < arr1.size(); i++) {
		auto res = solution.MakeSwaps(arr1[i], arr2[i]);
		cout << arr1[i] << " | " << arr2[i] << " => " << res << endl;
	}
	return 0;
}
