class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		int count = 0, sum = 0;
		int nr = nums.size();

		//
		// We can use a cummulative sum, (for k=7)
		// ie
		//
		//  3  4  7  2 -3  1  4  2 nums[i]
		//  3  7 14 16 13 14 18 20 sum[i] = sum[i-1] + num[i]
		// -4  0  7  9  6  7 11 13 sum[i] - k
		// ----				(1)
		//      --			(2)
		//      ------------		(3)
		//                --------	(4)
		//
		// then if we take some indices i and j
		// and sum[j] - sum[i] == k, then we've
		// found a subsequence.
		//
		// Next lest put cummulative sum[i] for each
		// element into a map
		//
		// 	map[sum[i]] = number of occurences
		//
		// when several subsequences are summing up to
		// k it means the cummulative sum is multiplier of k,
		// so we found a subsequence. Same time every sum[i]
		// might be a start of a new required subsequence thus
		// we lookup for sum[i]-k as well.
		//
		unordered_map<int, int> map;
		map[0] = 1;

		for (auto i = 0; i < nr; i++) {
			sum += nums[i];
			auto d = sum - k;
			if (map.find(d) != map.end())
				count += map[d];
			if (map.find(sum) != map.end())
				map[sum]++;
			else
				map[sum] = 1;
		}

		return count;
	}
};
