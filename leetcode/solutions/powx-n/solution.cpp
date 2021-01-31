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
	double myPow(double x, int n) {
		if (n == 0)
			return 1;
		else if (x == 1)
			return 1;
		else if (n == 1 || n == -1)
			return n == 1 ? x : 1/x;
		else if (n == 2 || n == -2)
			return n == 2 ? x * x : 1/(x * x);

		bool invert = false;
		bool onemore = false;
		if (n < 0) {
			invert = true;
			if (n == INT_MIN) {
				n = INT_MAX;
				onemore = true;
			} else {
				n = -n;
			}
		}

		// Just use addition property
		// of power function, then calculate
		// the remainder.

		double r = x;
		long long i = 2;
		while (i <= n) {
			r *= r;
			if (i * 2 < n)
				i *= 2;
			else
				break;
		}
		r *= myPow(x, n - i);
		if (onemore)
			r *= x;
		return invert ? 1 / r : r;
	}
};

int main()
{
	struct {
		double x;
		int n;
	} data[] = {
		{2, 10},
		{2.1, 3},
		{2, -2},
		{2, -2147483648},
		{8.95371, -1},
	};
	Solution solution;
	for (auto& d: data) {
		cout << d.x << ", " << d.n << " => " << endl <<
			solution.myPow(d.x, d.n) << endl;
	}
	return 0;
}
