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
	int uniquePaths(int m, int n) {
		int v[n][m];

		for (int i = 0; i < m; i++)
			v[0][i] = 1;
		for (int i = 0; i < n; i++)
			v[i][0] = 1;

		for (int i = 1; i < n; i++) {
			for (int j = 1; j < m; j++)
				v[i][j] = v[i-1][j] + v[i][j-1];
		}
                return v[n-1][m-1];
        }
};

int main()
{
	vector<int> input[] = {
		{3, 2},	//  3
		{3, 3}, //  4
		{7, 3},	// 28
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " << endl << solution.uniquePaths(nums[0], nums[1]) << endl;
	}
	return 0;
}
