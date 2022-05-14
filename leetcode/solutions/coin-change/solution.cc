#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

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
	/*
	 * Bottom up DP. Consider a simple case: one coin X = [1]
	 * and target is 6. To consider all possible combinations
	 * (we're can use same coin infinite number of times) lets
	 * rather walk over every target [1..6] and collect the number
	 * of coins we need to reach this target.
	 *
	 * Initially we have the DP
	 *
	 * 	target     0 1 2 3 4 5 6
	 * 	dp[i]      0 0 0 0 0 0 0
	 *
	 * Then we take coin 1 and try to add it to the
	 * previous collected number
	 *
	 * 	target     0 1 2 3 4 5 6
	 * 	dp[1]      0 1 ? ? ? ? ?
	 *
	 * For dp[2] we can reuse dp[1] + 1, because previous
	 * amount 1 plus 1 coin gives 2.
	 *
	 * 	target     0 1 2 3 4 5 6
	 * 	dp[2]      0 1 2 ? ? ? ?
	 *
	 * and so on. Thus dp[i] = dp[i-coin] + 1. Finally
	 * we will have
	 *
	 * 	target     0 1 2 3 4 5 6
	 * 	dp[2]      0 1 2 3 4 5 6
	 *
	 * This can be propagated to another set of coins, for
	 * example coins [1,2] but we need to choose a minimum
	 * number of coins on each iteration.
	 *
	 * For example when we use only 1 coin we have
	 *
	 * 	target     0 1 2 3 4 5 6
	 * 	dp[i]      0 1 2 3 4 5 6
	 *
	 * And if we consider only coin 2 we have
	 *
	 * 	target     0 1 2 3 4 5 6
	 * 	dp[i]      0 0 1 1 2 2 3
	 *
	 * Combining these two tasks together we choose
	 * answer 3 as a minumum number of coins.
	 *
	 * _Note_ that we should conside every step in amount
	 * since they are working like coin multipliers.
	 */
	int coinChange(vector<int>& coins, int amount) {
                if (amount == 0)
                        return 0;
		vector<int> dp(amount+1, amount+1);
		dp[0] = 0;

		for (int i = 1; i <= amount; i++) {
			for (auto c: coins) {
				//
				// Can't reach amount @i with
				// this coin it is too big.
				if (c > i)
					continue;
				//
				// How many other coins collected
				// adding up with current coin gives
				// us amount = @i.
				auto prev_nr_coins = dp[i - c];
				//
				// Either we initialize with new
				// number of coins or minimize the
				// sum using coin with bigger value.
				dp[i] = min(dp[i], prev_nr_coins + 1);
			}
		}
		return dp[amount] > amount ? -1 : dp[amount];
        }
#if 0
	/*
	 * Recusrion with memoization. Consider example [1,2,5] and
	 * amount 11. We take every case in recursion and reuse already
	 * calculated results.
         *
         *      target 11 (reduce the sum by tree node value on every step)
         *
	 *             [1,2,5]
         *             /  |  \
         *           10   9   6------[1,2,5]
         *           /     \         /  |  \
         *        [1,2,5] [1,2,5]   5   4   1
         *         /       /       /   ...   \
         *        9       8      [1,2,5]    [1,2,5]
         *       /       /        ...       /
         *    [1,2,5] [1,2,5]              0 - answer
         *      ...     ...
         */
	int helper(vector<int>& coins, vector<int>& memo, int idx, int amount) {
		int res = INT_MAX;
		if (memo[amount] != INT_MAX)
			return memo[amount];

		for (int i = 0; i < (int)coins.size(); i++) {
			auto v = amount - coins[i];
			if (v < 0)
				continue;
			else if (v == 0)
				return 1;
			auto n = helper(coins, memo, i, v);
			if (n >= 0)
				res = min(res, n+1);
		}

		if (res == INT_MAX)
			res = -1;

		memo[amount] = res;
		return res;
	}
	int coinChange(vector<int>& coins, int amount) {
		if (amount == 0)
			return 0;
		vector<int> memo(amount+1, INT_MAX);
		return helper(coins, memo, 0, amount);
	}
#endif
};

int main()
{
	struct {
		vector<int> coins;
		int amount;
	} data[] = {
		{
			// 3
			.coins = {1,2,5},
			.amount = 11,
		}, {
			// -1
			.coins = {2},
			.amount = 3,
		}, {
			// 0
			.coins = {1},
			.amount = 0,
		}, {
			.coins = {2,3,5},
			.amount = {9},
		}, {
			// 20
			.coins = {1,2,5},
			.amount = 100,
		}
	};
	Solution solution;
	for (auto& d: data) {
		cout << d.coins << ", " << d.amount << " => " <<
			solution.coinChange(d.coins, d.amount) << endl;
	}
	return 0;
}
