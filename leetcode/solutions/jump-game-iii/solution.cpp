#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

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
	bool canReach(vector<int>& arr, int start) {
		vector<bool> visited(arr.size(), false);
		queue<ssize_t> q;

		// Just a regular BFS
		q.push(start);
		while (!q.empty()) {
			auto pos = q.front();
			q.pop();

			visited[pos] = true;
			if (arr[pos] == 0)
				return true;

			auto l = pos - arr[pos];
			auto r = pos + arr[pos];
			if (l >= 0 && !visited[l])
				q.push(l);
			if (r <= arr.size()-1 && !visited[r])
				q.push(r);
		}

		return false;
	}
};

int main()
{
	struct {
		vector<int> arr;
		int start;
	} input[] = {
		{
			.arr	= {4,2,3,0,3,1,2},
			.start	= 5,	// true
		}, {
			.arr	= {4,2,3,0,3,1,2},
			.start	= 0,	// true
		}, {
			.arr	= {3,0,2,1,2},
			.start	= 2,	// false
		}
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums.arr << " : " << nums.start << " => " <<
			solution.canReach(nums.arr, nums.start) << endl;
	}
	return 0;
}
