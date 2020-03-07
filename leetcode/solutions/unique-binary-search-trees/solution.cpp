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
	int numTrees(int n) {
		int dp[n+1] = { 0 };

		/*
		 * Strictly speakin this is Catalan number.
		 * But the idea behind is the following:
		 * let consider bst with n nodes, say root
		 * at position i, thus we have nodes [1...i-1]
		 * as a left subtree and [i+1...n] as a right
		 * subtree. denote c(n) as a number of all
		 * bst with n nodes, if we choose i as a root
		 * then c(i) = c(i-1) * c(n-i) because each
		 * subtree should be considered independently.
		 *
		 * Thus c(n) = \sum(i=1...n) t(i-1)t(n-i)
		 *
		 * c(2) = c(0)c(1) + c(1)c(0) = 2
		 * c(3) = c(0)c(2) + c(1)c(1) + c(2)c(0) = 2 + 1 + 2 = 5
		 * c(4) = c(0)c(3) + c(1)c(2) + c(2)c(1) + c(3)c(0) = 5 + 2 + 2 + 5 = 14
		 *
		 * Another more obvious approach is to look into
		 * recurrence which appears one we generate trees
		 * by hands:
		 *
		 * 0 and 1 node: one tree possible
		 *
		 * 2 nodes:
		 *      1	2
		 *       \     /
		 *        2   1
                 *
                 *        two trees lengh of 2 nodes
                 *
                 * 3 nodes:
                 *
                 *      take each node as a root
                 *
                 *      1       1
                 *       \       \
                 *        2       3
                 *         \     /
                 *          3   2
                 *
                 *      2
                 *     / \
                 *    1   3
                 *
                 *       3      3
                 *      /      /
                 *     2      1
                 *    /        \
                 *   1          2
                 *
                 *   we have two trees with length of 3 (2 node subtree)
                 *   and one tree with length of 2 (1 node subtree)
                 *
                 * This allows us to reuse previously accounted values
                 * in a recurrent way: consider dp[n] as a number of
                 * subtrees with length of n, thus if we take a particular
                 * node i the number of subtrees gonna be a product of
                 * all left subtrees and right subtrees (remember
                 * a multiplication rule from combinatorics).
                 */

		dp[0] = 1;
		dp[1] = 1;

		// Consider each tree of length i
		for (int i = 2; i <= n; i++) {
			// Now reccurently account subtrees
			// for tree of i elements, where
			// each element is considered as
			// root
			for (int j = 1; j <= i; j++)
				dp[i] += dp[j-1] * dp[i-j];
		}

		return dp[n];
	}
};

int main()
{
	int input[] = {
		3, // 5
	};
	Solution solution;
	for (auto& n: input) {
		cout << n << " => " << solution.numTrees(n) << endl;
	}
	return 0;
}
