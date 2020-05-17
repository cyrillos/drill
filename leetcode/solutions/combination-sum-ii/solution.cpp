#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

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

class Solution {
public:
	void backtrace(const vector<int> &n, int target, size_t pos,
		       vector<bool> &set, vector<vector<int>> &res)
	{
		if (target == 0) {
			vector<int> t;
			for (size_t i = 0; i < n.size(); i++) {
				if (set[i])
					t.push_back(n[i]);
			}
			res.push_back(t);
			return;
		}

		if (pos >= n.size())
			return;

		for (size_t i = pos; i < n.size(); i++) {
			if (n[i] > target)
				break;
			//
			// Eliminate duplications.
			if (i > pos && n[i-1] == n[i])
				continue;
			set[i] = true;
			backtrace(n, target - n[i], i+1, set, res);
			set[i] = false;
		}
	}

	vector<vector<int>> combinationSum2_backtrace(const vector<int>& n, int target)
	{
		vector<bool> set(n.size(), false);
		vector<vector<int>> res;

		//
		// Need to sort the data to be able
		// to detect duplicates since we're
		// asked to generate unique sets.
		auto nn = n;
		sort(nn.begin(), nn.end());

		// [1,1,2,5,6,7,10], 8
		// [10,1,2,7,6,1,5], 8
		//
		//     ^ ^       ^
		//       ^   ^
		//     ^   ^
		//     ^     ^ ^
		//
		// [1, 7], [1, 2, 5], [2, 6], [1, 1, 6]
		backtrace(nn, target, 0, set, res);
		return res;
	}

	vector<vector<int>> combinationSum2(const vector<int>& n, int target)
	{
		return combinationSum2_backtrace(n, target);
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{ {}, 1 },
		{ {1}, 2 },
		{ {5}, 5 },
		{ {4, 2}, 6 },
		{ {10, 1, 2, 7, 6, 1, 5}, 8 },
		{ {2,5,2,1,2}, 5 },
	};

	Solution solution;
	for (auto& p: input) {
		auto& n = p.first;
		auto target = p.second;
		cout << "in: " << n << " target: " << target << endl <<
			solution.combinationSum2(n, target) << endl;
	}
	return 0;
}
