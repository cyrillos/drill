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
	string& permute(string& g, int off, int fact, int n, int k) {
		if (n <= 0)
			return g;

		//
		// Since there is N number and each number generates
		// up to (N-1)! permutaions we can figure out from which
		// number Kth permutation starts.
		//
		// N! = N * (N-1) * ... => (N-1)! = N! / N,
		// iow number of subgroups with first
		// number fixed position is (N-1)!
		//
		// For example n = 4 and k = 8,
		// 
		// n = {1,2,3,4} => 4! => 24 permutations,
		// 24 / 6 => 4 subgroups with first fixed
		// positions, each subgroup will have 6
		// permutations (3!)
		//
		//	{{1}, 2, 3, 4}  (1)
		//	{{1}, 2, 4, 3}  (2)
		//	{{1}, 3, 2, 4}  (3)
		//	{{1}, 3, 4, 2}  (4)
		//	{{1}, 4, 2, 3}  (5)
		//	{{1}, 4, 3, 2}  (6)
		//
		//	{{2}, 1, 3, 4}  (7)
		//	{{2}, 1, 4, 3}  (8)
		//	{{2}, 3, 1, 4}  (9)
		//	{{2}, 3, 4, 1}  (10)
		//	{{2}, 4, 1, 3}  (11)
		//	{{2}, 4, 3, 1}  (12)
		//
		int nr_sub = fact / n; // 24/6 => 4

		//
		// Lets find the position which gonna
		// be first in our permutation. IOW, the
		// first in {x} in example above. K-1
		// because indexing is from 0 and we
		// start from first group.
		int pos = (k - 1) / nr_sub; // 8 / 4 = 2

		//
		// Move this element left, shifting
		// all to right.
		for (int i = pos; i > 0; i--)
			swap(g[off+i], g[off+i-1]);

		//
		// Lets walk into next subgroup (or same
		// subgroup but different offset inside
		// subgroup).
		return permute(g, off + 1, nr_sub, n - 1, k - pos * nr_sub);
	}

	string getPermutation(int n, int k) {
		const char a[] = "123456789";
		string group = string(a, n);

		if (k == 1)
			return group;
		else if (n == 1)
			return string("1");

		//
		// As we know the number of permitations
		// is n!, thus calc it here and pass to
		// the helper, where we explain the details.
		int fact = 1;
		for (int i = 1; i <= n; i++)
			fact *= i;

		return permute(group, 0, fact, n, k);
	}
};

int main()
{
	struct {
		int n;
		int k;
	} input[] = {
		{ .n = 1, .k = 4, },	// "1"
		{ .n = 3, .k = 3, },	// "213"
		{ .n = 3, .k = 5, },	// "312"
		{ .n = 3, .k = 6, },	// "321"
		{ .n = 4, .k = 9, },	// "2314"
		{ .n = 3, .k = 1, },	// "123"
		{ .n = 4, .k = 2, },	// "1243"
		{ .n = 5, .k = 120, },	// "54321"
	};
	Solution solution;
	for (auto& v: input) {
		cout << v.n << ", " << v.k  << " => " <<
			solution.getPermutation(v.n, v.k) << endl;
	}
	return 0;
}
