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
	vector<string> restoreIpAddresses(string s) {
		vector<string> res;
		size_t n = s.length();

		// Check for limits
		if (n < 4 || n > 12)
			return {};

		//
		// Length of each octet is from 1 to 3,
		// thus we can simply try to iterate each
		// octets and figure out if they create
		// a proper sequence.
		//
		// This is a full enumerations algo.

		for (size_t i = 1; i <= 3; i++) {
			string s1 = s.substr(0, i);
			int a = stoi(s1);
			if (a > 255 || (s1.size() > 1 && s1[0] == '0'))
				continue;

			for (size_t j = 1; j <= 3; j++) {
				string s2 = s.substr(i, j);
				int b = stoi(s2);
				if (b > 255 || (s2.size() > 1 && s2[0] == '0'))
					continue;

				for (size_t k = 1; k <= 3; k++) {
					size_t len = n - i - j - k;
					if (len < 1 || len > 3)
						continue;

					string s3 = s.substr(i + j, k);
					int c = stoi(s3);
					if (c > 255 || (s3.size() > 1 && s3[0] == '0'))
						continue;

					string s4 = s.substr(i + j + k, len);
					int d = stoi(s4);
					if (d > 255 || (s4.size() > 1 && s4[0] == '0'))
						continue;

					string ip =
						to_string(a) + "." +
						to_string(b) + "." +
						to_string(c) + "." +
						to_string(d);
					res.push_back(ip);
				}
			}
		}
		return res;
	}
};

int main()
{
	vector<string> input = {
		// "1.2.3.4"
		"1234",

		// "0.0.0.0"
		"0000",

		// "0.10.0.10","0.100.1.0"
		"010010",

		// "255.255.11.135","255.255.111.35"
		"25525511135",


		// "1.1.1.1"
		"1111",

		// "1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"
		"101023",
	};

	Solution solution;
	for (auto& s: input) {
		cout << s << " => " <<
			solution.restoreIpAddresses(s) << endl;
	}
	return 0;
}
