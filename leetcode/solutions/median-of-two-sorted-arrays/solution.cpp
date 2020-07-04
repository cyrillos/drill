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

#include <cassert>

class Solution {
public:
	double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
		ssize_t nr_a = a.size(), nr_b = b.size();
		// +1 to cover odd length
		ssize_t half = (nr_a + nr_b + 1) / 2;

		//
		// Walk via smaller array for convenience.
		if (nr_a > nr_b)
			return findMedianSortedArrays(b, a);

		//
		// Both are zero size.
		if (nr_b == 0)
			return 0;

		// Inclue upper bound to handle the case
		// where they are not intersecting.
		ssize_t i = 0, j = nr_a;

		//
		// What we're doing is finding a pivot
		// point where all elements on left side
		// are smaller(or equal) than elements on
		// right side of both arrays.
		//
		// If arrays are intersecting then such pivot
		// is guaranteed to present: merged set will have
		// a half of elements on the left of median and
		// a half on the right. Thus our function has and
		// range and domain from math pov.
		//
		// One of the best explanation I found (if there
		// is no interest in math) is here
		// https://medium.com/@hazemu/finding-the-median-of-2-sorted-arrays-in-logarithmic-time-1d3f2ecbeb46
		while (i <= j) {
			ssize_t pos_a = (i + j) / 2;
			ssize_t pos_b = half - pos_a;

			if (pos_a < nr_a && a[pos_a] < b[pos_b-1]) {
				// need to go right, since
				// we're not big enough and
				// there are elems in b yet
				// which are bigger
				i = pos_a + 1;
			} else if (pos_a > 0 && b[pos_b] < a[pos_a-1]) {
				// need to go left, since
				// we're too big and
				// there are elems in b yet
				// which are less
				j = pos_a - 1;
			} else {
				//
				// The matching position.
				double max_left, min_right;

				if (pos_a == 0)
					max_left = b[pos_b-1];
				else if (pos_b == 0)
					max_left = a[pos_a-1];
				else
					max_left = max(a[pos_a-1], b[pos_b-1]);

				if ((nr_a + nr_b) % 2 == 1)
					return max_left;

				if (pos_a == nr_a)
					min_right = b[pos_b];
				else if (pos_b == nr_b)
					min_right = a[pos_a];
				else
					min_right = min(a[pos_a], b[pos_b]);

				return (max_left + min_right) / 2.;
			}
		}

		assert(false);
		return -1;
	}
};

int main()
{
	struct {
		vector<int> nums1;
		vector<int> nums2;
	} input[] = {
		{
#if 1
			.nums1 = {2},		// 2.0
			.nums2 = {1, 3},
		}, {
			.nums1 = {},
			.nums2 = {3, 4},	// 3.5
		}, {
			.nums1 = {},
			.nums2 = {2, 3, 4},	// 3
		}, {
			.nums1 = {1, 2},
			.nums2 = {3, 4},	// 2.5
		}, {
			.nums1 = {1, 2, 5, 6},
			.nums2 = {3, 4, 7, 8},
		}, {
			.nums1 = {1, 2, 3, 4},
			.nums2 = {5, 6, 7, 8},
		}, {
#endif
#if 1
			.nums1 = {1, 2, 4},
			.nums2 = {3, 7, 8},
#endif
#if 1
		}, {
			.nums1 = {1, 3, 8, 9, 15, 16},
			.nums2 = {7, 11, 18, 19, 21, 25},
			//
			// 1,3,7,8,9,11,|15,16,18,19,21,25 -> 12 elems, 6
			//           ^^  ^^
			//           (11+15) / 2.0 = 13.
		}, {
			.nums1 = {4,6,8,10,11,18},	// ?
			.nums2 = {3,7,9,15,18,21,25},
		}, {
			.nums1 = {4,6,8,15},		// ?
			.nums2 = {3,5,9,10,11,16},
		}, {
			.nums1 = {1,2},
			.nums2 = {3,4,5,6},
#endif
		},
	};
	Solution solution;
	for (auto n: input) {
		cout << n.nums1 << " , " << n.nums2 << " => \n" <<
			solution.findMedianSortedArrays(n.nums1, n.nums2) <<
			"\n===" << endl;
	}
	return 0;
}
