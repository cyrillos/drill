#include <algorithm>
#include <iostream>
#include <string>
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

class Solution {
public:
	// 1 -> "1"
	// 2 -> say(1) -> one 1 -> "11"
	// 3 -> say(2) -> two 1 -> "21"
	// 4 -> say(3) -> "21" -> one 2 + one 1 -> "1211"

	string count(string &r) {
		string s;

		char *last = &r[0], nr = 0;
		for (int i = 0; i < (int)r.length(); i++) {
			if (r[i] == *last) {
				nr++;
				continue;
			}
			s.append(to_string(nr));
			s.append(last, 1);

			nr = 1;
			last = &r[i];
		}

		if (nr) {
			s.append(std::to_string(nr));
			s.append(last, 1);
		}
		return s;
	};

	string countAndSay(int n) {
		if (n < 1)
			return "";
		string r = "1";
		for (int i = 1; i < n; i++)
			r = count(r);
		return r;
	}
};

int main()
{
	int nums[] = {1,2,3,4,5,6,7,8,9,10};
	Solution solution;
	for (auto& n: nums) {
		cout << n << " => " << solution.countAndSay(n) << endl;
	}
	return 0;
}
