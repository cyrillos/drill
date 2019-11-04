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

class Solution {
public:
	vector<vector<int>> combinationSum(const vector<int>& n, int target) {
		vector<int> factor(n.size());
		vector<vector<int>> res;
		int sum = 0;

		//
		// The idea is to walk over entries and accumulate
		// the partial sums. For example lets consider the
		// set {2, 3, 6, 7} and the target 7.
		//
		// We start from 2, store it in @factor and what is
		// important we do a break and restart scanning from
		// the 2 again to count its factor into the destination
		// sum.

		do {
			for (int i = 0; i < n.size(); i++) {
				if (sum + n[i] <= target) {
					sum += n[i];
					factor[i]++;
					break;
				}
				//
				// We either already saw this
				// members and should drop them
				// from a sum or this member is
				// too big to be included.
				sum -= factor[i] * n[i];
				factor[i] = 0;
			}
			//
			// If we've found a set we need just
			// append it to result but do not clear
			// the @factor set, on next iteration
			// this will allow us to not consider
			// the low members of the set again
			// and drop it from sum and factor.
			if (sum == target) {
				vector<int> tmp;
				for (int i = 0; i < n.size(); i++) {
					if (!factor[i])
						continue;
					for (int j = 1; j <= factor[i]; j++)
						tmp.push_back(n[i]);
				}
				res.push_back(move(tmp));
			}
		} while (sum > 0);

		return res;
	}
};

int main()
{
	struct {
		vector<int>	candidates;
		int		target;
	} input[] = {
		{
			.candidates	= { },
			.target		= 1,
		}, {
			.candidates	= {2, 3, 6, 7},	// {7}, {2,2,3} 
			.target		= 7,
		}, {
			.candidates	= {2, 3, 6, 7},	// {7}, {2,2,3} 
			.target		= 10,
		}, {
			.candidates	= {2, 3, 5},	// {2,2,2,2}, {2,3,3}, {3,5}
			.target		= 8,
		},
	};
	Solution solution;
	for (auto& n: input) {
		cout << n.candidates << " " << n.target << " => " <<
			solution.combinationSum(n.candidates, n.target) << endl;
	}
	return 0;
}
