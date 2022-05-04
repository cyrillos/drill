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
	//
	// An idea is pretty simple: consider the function
	// where we need to find a minimal point and maximal
	// point prisent *after* minimal.
	int maxProfit(vector<int>& prices) {
		int profit = 0;
		int min_point = INT_MAX;
		for (size_t i = 0; i < prices.size(); i++) {
			if (prices[i] < min_point)
				min_point = prices[i];
			else
				profit = max(profit, prices[i] - min_point);
		}
		return profit;
	}
};

int main()
{
	vector<int> data[] = {
		{7,1,5,3,6,4},	// 5
		{7,6,4,3,1},	// 0
	};
	Solution solution;
	for (auto& d: data) {
		cout << d << " => " <<
			solution.maxProfit(d) << endl;
	}
	return 0;
}
