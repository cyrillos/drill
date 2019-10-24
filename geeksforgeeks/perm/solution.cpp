#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <queue>
#include <stack>

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

//
// First lets consider a set @A = {1,2,3} and produce
// all permutations (not matter how exactly yet). We
// know that the number of permutations is P(n) = n!.
//
// Thus permutations are:
//
// 	{1,2,3}
// 	{1,3,2}
// 	{2,1,3}
// 	{2,3,1}
// 	{3,2,1}
// 	{3,1,2}
//
// Due definition of the 'permutation' we know that each
// number from the set should appear on each set position
// (n-1)! times. Thus we can consider groups of permutations.
// For the set @A the power is 3, thus we will have 3 groups
// of permutations:
//
// 	{1, ... }
// 	{2, ... }
// 	{3, ... }
//
// The rest of members '...' can be considered as subgroups
// of permutations with power |@A| - 1 = 2, which are
//
// 	{1, 2}
// 	{1, 3}
// 	{2, 1}
// 	{2, 3}
// 	{3, 1}
// 	{3, 2}
//
// Thus we can generate all permutations recursively:
// - choose a member for the first position from the set
// - generate all subgroups
// - choose another members and generate all subgroups
//   for it, and etc
//
// Note that permutations are NOT in lexicographic order!
//
static void generate(vector<int> a, int pos, int size)
{
	if (pos == size-1) {
		// this is the last entry in the current
		// group of permutation (lets reuse pos
		// variable as a counter)
		cout << "{";
		for (pos = 0; pos < size-1; pos++)
			cout << a[pos] << ",";
		if (pos < size)
			cout << a[pos];
		cout << "}" << endl;
	} else {
		// For each group of permutation
		for (int i = pos; i < size; i++) {
			// Iterate over all entries in the group
			// and set every rest to first position
			// of [sub]group.
			swap(a[i], a[pos]);
			// Generate permutations for subgroups
			generate(a, pos+1, size);
			// Restore back the original order so
			// we could choose another member for
			// the [sub]group.
			swap(a[i], a[pos]);
		}
	}
}

int main()
{
	vector<int> a = {1,2,3,4};
	vector<vector<int>> res;
	generate(a, 0, static_cast<int>(a.size()));

	return 0;
}
