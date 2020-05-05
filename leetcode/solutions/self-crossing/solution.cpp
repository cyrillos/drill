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
	bool isSelfCrossing(vector<int>& x) {
		size_t i = 2;

		//
		// At least it should be 4 edges
		// to make a square.
		if (x.size() < 4)
			return false;

		//
		// An increasing spirale.
		while (i < x.size() && x[i] > x[i-2])
			i++;

		//
		// Transition point(s)
		if (i < x.size()) {
			if (i == 3 && x[3] == x[1]) {
				//
				//     x1
				// +--------+
				// |        | x0
				// |        +
				// | x2
				// |    +---+
				// |        | x4
				// +--------+
				//     x3
				//
				// Just sub x[0] from x[3] dropping
				// the top part (i.e. x0, x1 segment),
				// then the valid spiral gonna be
				// decreasing.
				//
				x[2] -= x[0];
			} else if (i >= 4 && x[i] >= x[i-2] - x[i-4]) {
				//          x5
				//   +------------+
				//   |    x1      |
				//   |  +----+    |
				//   |  |    | x0 | x4   (A)
				//   |  |x2       |
				//   |  +---------+
				//   |    x3
				//   |
				// x6|    x9
				//   |  +---------+
				//   |  |         |
				//   |  |x10 | x12|
				//   |  +----+    | x8   (B)
				//   |    x11     |
				//   +------------+
				//          x7
				//
				//
				// The transition point is x6, thus to make sure
				// the upcoming spiral doesn't cross we need to
				// be sure the x7 is greater or equal than x5
				// (x[i] >= x[i-2] - x[i-4]) and substract x4 from
				// x6 dropping the part A off.
				//
				// The similar situation when the spiral is
				// reflected in mirror (ie increasing first
				// and decreasing then).
				//
				x[i-1] -= x[i-3];
			}
			//
			// Make sure we're going to next step since the
			// transition point will be considered in next
			// cycle.
			i++;
		}

		//
		// A decreasing spirale.
		while (i < x.size() && x[i] < x[i-2])
			i++;

		return i == x.size() ? false : true;
	}
};

int main()
{
	vector<int> input[] = {
		{},		// false
		{1},		// false
		{1,1},		// false
		{1,1,1},	// false
		{2,1,1,2},	// true
		{1,2,3,4},	// false
		{1,1,1,1},	// true
		{1,2,3,4},	// false
		{3,3,3,2,1,1},	// false
	};
	Solution solution;
	for (auto nums: input) {
		cout << nums << " => " << solution.isSelfCrossing(nums) << endl;
	}
	return 0;
}
