class Solution {
public:
	int deleteAndEarn(vector<int>& nums) {
		vector<int> bucket(10001, 0);

		//
		// [2,2,3,3,3,4] => {[2] = 4, [3] = 9, [4] = 4}
		//
		// note that buckets are sorted
		for (auto v: nums)
			bucket[v] += v;

		vector<int> dp(10001, 0);
		dp[0] = bucket[0];
		dp[1] = bucket[1];

		//
		// The key moment here is simila to
		// house robbing: we either take value
		// or not take. If we take we should skip
		// previous, thus i-2, if we're not taking
		// then we skip current and take previous.
		//
		// Same time we propagate max value even for
		// buckets which are not present in nums, thus
		// we always know which best value was the last.
		for (int i = 2; i < bucket.size(); i++)
			dp[i] = max(bucket[i] + dp[i - 2], dp[i - 1]);

		return dp[10000];
	}
};
