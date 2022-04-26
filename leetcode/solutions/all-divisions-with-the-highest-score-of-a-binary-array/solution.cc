#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const pair<T,T>& v)
{
	out << '{' << v.first << ',' << v.second << '}';
	return out;
}

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
	vector<int> maxScoreIndices(vector<int>& nums) {
		int sum0 = 0, sum1 = 0;
		int nr = nums.size();
		vector<pair<int,int>> res(nr+1);

		for (int i = 0; i < nr; i++) {
			sum0 += !nums[i];
			sum1 += nums[i];
		}

		res[0] = {sum1, 0};
		res[nr]= {sum0, nr};

		//    0 0 1 0
		// 0: 1 2 2 3
		// 1: 0 0 1 1

		int left0 = 0, left1 = 0;
		for (int i = 0; i < nr-1; i++) {
			left0 += !nums[i];
			left1 += nums[i];

			res[i+1] = {left0 + (sum1 - left1), i+1};
		}
		sort(res.begin(), res.end());

		vector<int> ret;
		ret.push_back(res[nr--].second);
		for (; nr >= 0; nr--) {
			if (res[nr+1].first != res[nr].first)
				break;
			ret.push_back(res[nr].second);
		}
		return ret;
	}
};

int main()
{
	vector<int> data[] = {
		{0,0,1,0},		// [2,4]
		{0,0,0},		// [3]
		{1,1},			// [0]
		{1,0,1,0,1,1,0,1,0},	// [0,2,4]
	};
	Solution solution;
	for (auto& d: data) {
		cout << d << " => " <<
			solution.maxScoreIndices(d) << endl;
	}
	return 0;
}
