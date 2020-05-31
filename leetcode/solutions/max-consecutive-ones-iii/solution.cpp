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
	int longestOnes(vector<int>& a, int k) {
		int i = 0, j = 0, n = k, best = 0;

		//
		// Traditional sliding window, where
		// i - right bound and j -- left
		while (i < (int)a.size()) {
			if (a[i] == 0) {
				if (n <= 0) {
					while (a[j] == 1)
						j++;
					j++, n++;
					continue;
				} else
					n--;
			}
			best = max(best, i - j + 1);
			i++;
		}

		return best;
	}
};

int main()
{
	struct {
		vector<int> a;
		int k;
	} input[] = {
		{
			.a = {1,0,1,0,1,1,0,1,1,},
			.k = 2,	// 6
		}, {
			.a = {1,1,1,0,0,0,1,1,1,1,0},
			.k = 2,	// 6
		}, {
			.a = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1},
			.k = 3, // 10
		}
	};
	Solution solution;
	for (auto& in: input) {
		cout << "a = " << in.a << " k = " << in.k << " => " <<
			solution.longestOnes1(in.a, in.k) << endl;
	}
	return 0;
}
