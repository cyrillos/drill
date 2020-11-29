#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include<bits/stdc++.h>

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
	void nextPermutation(vector<int>& a) {
		if (a.size() < 2)
			return;

		//
		// The idea is similar to generating
		// all permutations of the sequence in
		// lexicographic order. One of the key moment
		// is the order itself.
		//
		// The permutation is "greater" if a[i] < b[i]
		// for some position. For example
		//
		//    0 1 2 3
		// a) 1 2 3 4
		// b) 1 2 4 3
		//
		// The b) is greater from position 2. The
		// prefix 1 2 is common for both but suffix
		// 4 3 is "greater".
		//
		// Another understanding comes from a sorted
		// sequence, where the first permutation is
		// numbers sorted in an ascending way and the last
		// permutation gonna be where all numbers are
		// sorted in a descending way.
		//
		// The number of permutations is n! (easy to prove
		// as well as lexicographic permuts are really fit
		// partial order axioms).
		//
		// Say we have an initial array a = [1,2,3,4,5]
		// Thus the first and last permutations are
		//
		//   1) [1,2,3,4,5]
		//      ...
		// 120) [5,4,3,2,1]
		//
		//  - We start looking for a pivot point from last
		//    position, ie the point where *ascending* order
		//    violated. If there is no such point it means
		//    it is the last permutation. We walk from the
		//    end of the permutation.
		//
		//    For example
		//
		//    1,3,5,4,2 <== start from here
		//        ^
		//        pivot
		//
		//     The pivot point separates subgroups of
		//     permutations with same prefix. Moving the pivot
		//     point right to left at every position gives
		//     us a guarantee that all possible subgroups
		//     will be considered.
		//
		//     In example above the first permutation ends
		//     with number 5, which is the pivot point. We
		//     can consider its moving from right to left
		//     as subgroup generations. Here is an example
		//     in nonlexicographic order
		//
		//     {1,2},a,b,5
		//     {1,2},b,a,5
		//     {1,2},a,5,b
		//     {1,2},b,5,a
		//     {1,2},5,a,b
		//     {1,2},5,b,a
		//
		//     Now if we apply lexicographic order we will have
		//
		//     {1,2},a,b,5
		//     {1,2},a,5,b
		//     {1,2},b,a,5
		//     {1,2},b,5,a
		//     {1,2},5,a,b
		//     {1,2},5,b,a
		//
		//     Where we move the biggest element from the end to
		//     a new position which makes next perm "greater",
		//     see the subgroups starting from {a}, {b} and {5}.
		//
		// - Once pivot point is found
		//
		//    1,3,5,4,2 <== start from here
		//        ^
		//        pivot
		//
		//   we know that subgroup started from {3} is finished
		//   and we need to start a new subgroup starting from
		//   next "greater" element.
		//
		//   For this sake we lookup for first element from the
		//   right which is next to {3} and this is element {4}
		//
		//   We swap it with {3}
		//
		//   {1,4},{5,3,2}
		//
		//   Now we need to sort the tail {5,3,2} to get "lowest"
		//   lexicographic order. And here is a trick: since elements
		//   are generated in lexicographic order the tail is already
		//   in "greater" state so we simply need to swap all elements
		//   around {3}
		//
		//   {1,4},{2,3,5}
		//
		// - Finally repeat the procedure again until all elements
		//   are in lexicographic order.
		//

		int last_idx = a.size()-1;
		int i, j;

		// Lookup for pivot point
		i = last_idx;
		while (i > 0 && a[i-1] >= a[i])
			i--;
		if (i == 0) {
			// Already sorted, lets rerun, this
			// is requirement from the task.
			sort(a.begin(), a.end());
			return;
		}

		// Lookup for new subgroup start element
		j = last_idx;
		while (a[i-1] >= a[j])
			j--;

		// Start new subgroup
		swap(a[i-1], a[j]);

		// Resort subgroup tail in ascending order
		j = last_idx;
		while (i < j)
			swap(a[i++], a[j--]);
	}
};

int main()
{
	vector<int> input[] = {
		{1,3,5,4,2},	// 1,4,2,3,5
		{1,2,3},	// 1,3,2
		{3,2,1},	// 1,2,3
		{1,1,5},	// 1,5,1
	};
	Solution solution;

	for (auto& nums: input) {
		cout << nums << " => ";
		solution.nextPermutation(nums);
		cout << nums << endl;
	}
	return 0;
}
