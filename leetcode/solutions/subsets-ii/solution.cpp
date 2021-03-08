#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>

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
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		size_t nr = nums.size();
		if (nr <= 0)
			return {};
		else if (nr == 1)
			return {{}, nums};

		struct classcomp {
			bool operator() (const vector<int>& lhs, const vector<int>& rhs) const
			{
				size_t l = lhs.size();
				size_t r = rhs.size();

				if (l != r)
					return false;

				for (size_t i = 0; i < l; i++) {
					if (lhs[i] != rhs[i])
						return false;
				}
				return true;
			}
		};
		set<vector<int>> set;

		size_t pow = 2;
		for (size_t n = 1; n < nr; n++)
			pow *= 2;
		pow -= 1; // since we add empty set manually

		//
		// Number of subsets if 2^N, where N
		// is initial set cardinality. Thus
		// we can use binary mask to enumerate
		// all possible subsets.
		//
		// Since no duplicates are allowed use
		// set to track already inserted entries.

		vector<vector<int>> r;
		r.push_back({});

		while (pow > 0) {
			vector<int> e;
			for (size_t i = 0; i < 32; i++) {
				if (pow & (1 << i)) {
					e.push_back(nums[i]);
				}
			}
			sort(e.begin(), e.end());
			if (set.find(e) == set.end()) {
				set.insert(e);
				r.push_back(e);
			}
			pow--;
		}

		return r;
	}
};

int main()
{
	vector<int> input[] = {
		{1,2,3},
		{1,2,3,4},
		{1,2},
		{},
		{0},
	};

	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.subsetsWithDup(nums) << endl;
	}
	return 0;
}
