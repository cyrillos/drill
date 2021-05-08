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
	int openLock(vector<string>& deadends, string target) {
		//
		// We can think of it as a graph with 10000 nodes
		// strings '0000' to '9999' and there is an edge
		// between two nodes if they differ in one digit,
		// that digit differs by 1 (wrapping around, so '0'
		// and '9' differ by 1), and if *both* nodes are
		// not in `deadends`.
		//
		// The key moment here is that a starting point
		// and the next point(s). Since we can do one rotate
		// at once (left or right) then from start point we're
		// connected to 8 nodes
		//
		//              0000
		//  +-----------/|||
		// /             |\`---------------+
		// |             | `------,        |
		// 1000         0100    0010    0001  "next"
		// 9000         0900    0090    0009  "prev"
		//
		// So we investigate each of it and then on each
		// node we generate "next" and "prev" nodes and
		// visit them. So plain BFS.

		int dest = stoi(target);
		vector<bool> visited(10000);

		for (auto &n : deadends)
			visited[stoi(n)] = true;

		if (visited[0])
			return -1;

		queue<pair<int, int>> que({make_pair(0, 0)});
		visited[0] = true;

		while (!que.empty()) {
			auto top = que.front();
			int number = top.first;
			int hop = top.second;
			que.pop();

			if (number == dest)
				return hop;

			for (int base = 1; base < 10000; base *= 10) {
				int digit = (number / base) % 10;
				int digit_next = (digit + 11) % 10;
				int digit_prev = (digit + 9) % 10;

				int next = number + (digit_next - digit) * base;
				int prev = number + (digit_prev - digit) * base;

				if (!visited[next]) {
					que.emplace(make_pair(next, hop + 1));
					visited[next] = true;
				}

				if (!visited[prev]) {
					que.emplace(make_pair(prev, hop + 1));
					visited[prev] = true;
				}
			}
		}

		return -1;
	}
};

int main()
{
	struct {
		vector<string>	deadends;
		string		target;
	} d[] = {
		{
			// 6
			.deadends = {
				"0201",
				"0101",
				"0102",
				"1212",
				"2002",
			},
			.target = "0202",
		}, {
			// 1
			.deadends = {
				"8888",
			},
			.target = "0009",
		}, {
			// -1
			.deadends = {
				"8887",
				"8889",
				"8878",
				"8898",
				"8788",
				"8988",
				"7888",
				"9888"
			},
			.target = "8888",
		}, {
			// -1
			.deadends = {
				"0000",
			},
			.target = "8888",
		},
	};
	Solution solution;
	for (auto& v: d) {
		cout << v.deadends << ", " << v.target << " => " <<
			solution.openLock(v.deadends, v.target) << endl;
	}
	return 0;
}
