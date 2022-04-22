#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

template<typename T, typename V>
ostream& operator<<(ostream& out, const pair<T,V>& v)
{
	out << '(' << v.first << "," << v.second << ')';
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
	int findMax_brute_force(vector<pair<int,int>>& date) {
		int nr = date.size();

		if (nr < 1)
			return 0;
		else if (nr < 2)
			return 1;
		//
		// Brute force: allocate range of days
		// and accumulate number of people in.
		// This require O(N) additional memory
		// and O(N^2) speed.
		auto longest =
			*max_element(date.begin(), date.end(),
				     [](const auto& l, const auto& r) {
				     return l.second < r.second; });
		int days = longest.second;

		vector<int> visitors(days+1, 0);
		for (int i = 0; i < nr; i++) {
			auto from = date[i].first;
			auto due = date[i].second;
			for (int j = from; j <= due; j++)
				visitors[j]++;
		}
		return *max_element(visitors.begin(), visitors.end());
	}

	int findMax_count(vector<pair<int,int>>& date) {
		size_t nr = date.size();
		unordered_map<int,int> in;
		unordered_map<int,int> out;

		if (nr < 1)
			return 0;
		else if (nr < 2)
			return 1;

		//
		// Move in and out into map so we could
		// find if day belongs to this sets fastly
		for (size_t i = 0; i < date.size(); i++) {
			in[date[i].first]++;
			out[date[i].second]++;
		}

		int moved_in = 0, max_moved_in = 0;
		for (size_t i = 1; i < nr; i++) {
			auto move_in = in.find(i);
			if (move_in != in.end()) {
				moved_in += move_in->second;
				//
				// Update immediately since
				// we use a sum which travels
				// left to right.
				max_moved_in = max(max_moved_in, moved_in);
			}
			auto move_out = out.find(i);
			if (move_out != out.end())
				max_moved_in -= move_out->second;
		}
		return max_moved_in;
	}

	int findMax(vector<pair<int,int>>& date) {
		//
		// This is kind of segments
		//
		// [(1, 2), (1, 3), (2, 4), (2, 3), (4,6)]
		//
		//     1 2 3 4 5 6 day
		// 1) |+|+|-
		// 2) |+|+|+|-
		// 3)   |+|+|+|-
		// 4)   |+|+|-
		// 5)       |+|+|+|-
		//
		//       ^
		//       | max = 4
		//
		// [(1,2), (2,4), (3,6)]
		//
		//     1 2 3 4 5 6
		// 1) |+|+|
		// 2)   |+|+|+|
		// 3)     |+|+|+|
		//
		//      ^  ^ ^
		//      |--|-| max = 2

		return findMax_count(date);
	}
};

int main()
{
	vector<pair<int,int>> input[] = {
		{
			// 4
			{1, 2}, {2, 4}, {1, 3}, {2, 3}, {4,6}
		}, {
			{1, 2}, {2, 4}, {2, 6},
		}
	};
	Solution solution;
	for (auto& d: input) {
		cout << d << " => " << solution.findMax(d) << endl;
	}
	return 0;
}
