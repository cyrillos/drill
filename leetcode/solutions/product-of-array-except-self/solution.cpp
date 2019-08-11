#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<int>& v)
{
       out << '[';
       for (auto it = v.begin(); it != v.end(); ++it) {
               if (it != v.begin())
                       out << ", ";
               out << *it;
       }
       out << ']';
       return out;
}

class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		vector<int> a(nums.size());
		vector<int> b(nums.size());
		vector<int> r(nums.size());

		if (nums.size() < 2)
			return nums;

		a[0] = nums[0];
		b[nums.size()-1] = nums[nums.size()-1];

		for (ssize_t i = 1; i < nums.size(); i++)
			a[i] = nums[i] * a[i-1];

		for (ssize_t i = nums.size()-2; i >= 0; i--)
			b[i] = nums[i] * b[i+1];

		for (ssize_t i = 0; i < nums.size(); i++) {
			if (i == 0) {
				r[i] = b[i+1];
			} else if (i == nums.size()-1) {
				r[i] = a[i-1];
			} else {
				r[i] = a[i-1] * b[i+1];
			}
		}

		return r;
	}
};

int main()
{
       vector<int> input[] = {
	       { },
	       { 1, 2 },
               { 1, 2, 3, 4 },	// 24, 12, 8, 6
       };
       Solution solution;
       for (auto& v: input)
               cout << v << " => " << solution.productExceptSelf(v) << endl;
       return 0;
}
