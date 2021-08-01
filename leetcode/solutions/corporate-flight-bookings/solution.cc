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
	vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
#if 0
		// correct but time limit overstepped
		vector<int> r(n, 0);
		for (auto i = 0; i < bookings.size(); i++) {
			vector<int>& b = bookings[i];
			for (auto j = b[0]-1; j <= b[1]-1; j++) {
				r[j] += b[2];
			}
		}
		return r;
#endif

		//
		// A faster way is to accumulate the differences
		// with previous flight. Here is an original sums
		//
		//  1  2  3  4  5
		// 10 10
		//    20 20
		//    25 25 25 25
		//
		// 10 55 45 35 35
		//
		// It oversteps time limit. The ranges are continious
		// so we can accumulate total reservations and mark
		// the moment when particular reservation ends.
		//
		//  1   2   3   4   5
		// 10     -10               (1)
		//     20     -20           (2)
		//     45            | -25  (3)
		//
		// 10  55  45  25  25
		//
		vector<int> r(n, 0);

		for (auto i = 0; i < bookings.size(); i++) {
			vector<int>& b = bookings[i];
			auto start = b[0]-1;
			auto end = b[1];

			r[start] += b[2];
			if (end < n)
				r[end] -= b[2];
		}

		for (auto i = 1; i < n; i++)
			r[i] = r[i-1] + r[i];

		return r;
	}
};

int main()
{
	struct {
		vector<vector<int>> b;
		int n;
	} d[] = {
		{
			.b = {
				{1,2,10},
				{2,3,20},
				{2,5,25},
			},
			.n = 5,
		},
	};
	Solution solution;
	for (auto& v: d) {
		cout << v.b << ", " << v.n << " => " <<
			solution.corpFlightBookings(v.b, v.n) << endl;
	}
	return 0;
}
