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
		int profit = 0;

		//
		// The idea is close to easy case
		// where we need to find minimum
		// followed by maximum value, except
		// we can hold one share at a time.
		// This exception is a key: we can buy
		// stock and sell it then if only price
		// is ascending.
		for (size_t i = 1; i < nr; i++) {
			if (prices[i] > prices[i-1])
				profit += prices[i] - prices[i-1];
		}
		return profit;
	}
};

int main()
{
	vector<int> data[] = {
		{7,1,5,3,6,4},	// 7
		{1,2,3,4,5},	// 4
		{7,6,4,3,1},	// 0
	};
	Solution solution;
	for (auto& d: data) {
		cout << d << " => " <<
			solution.maxProfit(d) << endl;
	}
	return 0;
}
