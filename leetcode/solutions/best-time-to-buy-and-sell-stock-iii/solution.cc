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
	int maxProfit(vector<int>& prices) {
		int nr = prices.size();
		int min_val = INT_MAX;
		int best = 0;

		//
		// At first iteration lets make an O^2
		// solution (plain bruteforce).
		//

		auto next_best = [](vector<int>& prices, int j, int nr) {
			int min_val = INT_MAX;
			int best = 0;
			for (size_t i = j; i < nr; i++) {
				if (prices[i] < min_val) {
					min_val = prices[i];
				} else {
					best = max(best, prices[i] - min_val);
				}
			}
			return best;
		};

		for (size_t i = 0; i < nr; i++) {
			if (prices[i] < min_val) {
				min_val = prices[i];
			} else {
				int v1 = prices[i] - min_val;
				int v2 = next_best(prices, i+1, nr);
				best = max(best, v1 + v2);
			}
		}

		return best;
	}
};

int main()
{
	vector<int> data[] = {
		{3,3,5,0,0,3,1,4},	// 6
		{1,2,3,4,5},		// 4
		{7,6,4,3,1},		// 0
		{},			// 0
		{1},			// 0
		{1, 2},			// 1
		{1, 3, 2},		// 2
		{1, 3, 2, 4},		// 4
		{1, 2, 3, 4, 5},	// 4
		{5, 2, 4, 7, 1, 9, 3},	// 13
		{3, 3, 5, 0, 0, 3, 1, 4},// 6
	};
	Solution solution;
	for (auto& d: data) {
		cout << d << " => " <<
			solution.maxProfit(d) << endl;
	}
	return 0;
}
