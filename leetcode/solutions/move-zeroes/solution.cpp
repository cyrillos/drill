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
	void moveZeroes(vector<int>& a) {
		size_t i, j;

		for (i = 0; i < a.size(); i++) {
			if (a[i] != 0)
				continue;
			for (j = i + 1; j < a.size(); j++) {
				if (a[j] != 0)
					break;
			}
			if (j == a.size())
				break;
			swap(a[i], a[j]);
		}

		// If I would not have to keep relative order
		// then it would be close to quicksort
#if 0
		while (i < j) {
			while (a[i] != 0 && i <= j) i++;
			while (a[j] == 0 && j >= i) j--;
			if (i < j) {
				swap(a[i], a[j]);
				i++, j--;
			}
		}
#endif
	}
};

int main()
{
	vector<int> input[] = {
		{ },			// { }
		{ 1 },			// { 1 }
		{ 1, 2 },
		{ 1, 0, 2},		// { 1, 2, 0 }
		{ 1, 2, 0, 3 },		// { 1, 1, 1, 0 },
		{ 0, 0, 0, 1 },		// { 1, 0, 0, 0 }
		{ 0, 1, 0, 3, 0, 12 },	// { 1, 3, 12, 0, 0, 0}
		{ 0, 0, 0, 1 },
		{ 0, 1, 1, 0 },
		{ 1, 0, 0, 1 },
		{ 0, 0, 0 },
		{ 0, 1, 0, 1, 1 },
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums ;
		solution.moveZeroes(nums);
		cout << " => " << nums << endl;
	}
	return 0;
}
