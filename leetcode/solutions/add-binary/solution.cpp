#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	string addBinary(string shorter, string longer) {
		string res = {};

		if (shorter.length() > longer.length())
			return addBinary(longer, shorter);

		res.resize(longer.length() + 1);
		int pos = 0;
		int carry = 0;
		int pos_a = shorter.length()-1;
		int pos_b = longer.length()-1;

		//
		// Direct walking over chars are way
		// more faster than converting to numbers
		// and evaluate s sum.
		while (pos_a >= 0) {
			if (shorter[pos_a] != longer[pos_b]) {
				if (carry) {
					res[pos++] = '0';
				} else {
					res[pos++] = '1';
				}
			} else {
				if (shorter[pos_a] == '1') {
					if (carry) {
						res[pos++] = '1';
					} else {
						carry = 1;
						res[pos++] = '0';
					}
				} else {
					if (carry) {
						carry = 0;
						res[pos++] = '1';
					} else {
						res[pos++] = '0';
					}
				}
			}
			pos_a--;
			pos_b--;
		}

		while (pos_b >= 0) {
			if (longer[pos_b] == '1') {
				if (carry) {
					res[pos++] = '0';
				} else {
					res[pos++] = '1';
					carry = 0;
				}
			} else {
				if (carry) {
					res[pos++] = '1';
					carry = 0;
				} else {
					res[pos++] = '0';
				}
			}
			pos_b--;
		}

		if (carry)
			res[pos++] = '1';

		res.resize(pos);
		reverse(res.begin(), res.end());
		return res;
	}
};

int main(void)
{
	string a = "110010";
	string b =  "10111";

	Solution s;

	cout << "res " << s.addBinary(a, b) << endl;

	return 0;
}
