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
	vector<vector<int>> permuteUnique(vector<int>& a) {
		vector<vector<int>> res;
		ssize_t last_idx;

		if (a.size() < 2)
			return {a};

		//
		// The key moment is just use lexicographic
		// permutations. So sort the entries first
		// and permutations will be unique.
		//
		// We could use next_permutation from std
		// library but it is much interesting to
		// implement it by self to refresh memory.
		//

		sort(a.begin(), a.end());

		auto next_permutation = [&](vector<int>& a, ssize_t last_idx) {
			ssize_t i, j;

			i = last_idx;
			while (i > 0 && a[i-1] >= a[i])
				i--;
			if (i == 0)
				return false;

			j = last_idx;
			while (a[i-1] >= a[j])
				j--;

			swap(a[i-1], a[j]);

			j = last_idx;
			while (i < j)
				swap(a[i++],a[j--]);
			return true;
		};

		last_idx = a.size()-1;
		do {
			res.push_back(a);
		} while (next_permutation(a, last_idx));

		return res;
	}
};

int main()
{
	vector<int> input[] = {
		{ },
		{ 1 },
		{1,1,2},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.permuteUnique(nums) << endl;
	}
	return 0;
}
