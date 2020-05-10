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
	void sortColors(vector<int>& n) {
		int pos1 = -1;
		int pos2 = -1;

		//
		// While counting sort is most
		// known way to solve the problem,
		// we're asked if we can do that
		// in one pass.
		//
		// Thus lets do a trick: remember
		// positions of 1 and 2. Once we
		// review the current number which
		// is out of order, we swap all 1
		// and/or 2 seen so far to keep order.
		for (int i = 0; i < n.size(); i++) {
			if (n[i] == 0) {
				if (pos1 != -1)
					swap(n[i], n[pos1++]);
				if (pos2 != -1)
					swap(n[i], n[pos2++]);
			} else if (n[i] == 1) {
				if (pos2 != -1) {
					if (pos1 == -1)
						pos1 = pos2;
					swap(n[i], n[pos2++]);
				} else if (pos1 == -1)
					pos1 = i;
			} else {
				if (pos2 == -1)
					pos2 = i;
			}
		}
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{2,0,2,1,1,0}, // 0,0,1,1,2,2
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => ";
		solution.sortColors(nums);
		cout << nums << endl;
	}
	return 0;
}
