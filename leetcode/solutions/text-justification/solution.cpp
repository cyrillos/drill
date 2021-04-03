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
	vector<string> fullJustify(vector<string>& w, int maxWidth) {
		vector<string> res;

		size_t nr = w.size();
		size_t pos = 0, start = 0;
		int acc, sum;

		//
		// Just accumullate in a greedy way
		// as much words as we can, then
		// simply distribute them in a string.
		// This is obviously not a "hard" task
		// simply time consuming to code out.

		while (pos < nr) {
			start = pos;
			acc = maxWidth;
			sum = 0;
			while (pos < nr) {
				if (acc != maxWidth)
					acc--;
				acc -= w[pos].size();
				sum += w[pos].size();
				if (acc <= 0) {
					if (acc == 0)
						break;
					acc += w[pos].size();
					sum -= w[pos].size();
					pos--;
					break;
				}
				pos++;
			}
			auto i = start, j = min(pos, nr-1) + 1;
			pos++;

			string s(maxWidth, ' ');
			if (j == nr) {
				// Last ones simply copy as is.
				auto t = 0;
				for (i = start ; i < j; i++) {
					for (auto ii = 0; ii < w[i].size(); ii++)
						s[t++] = w[i][ii];
					t++;
				}
				res.push_back(s);
			} else {
				auto nr_gaps = j - start - 1;
				if (sum == maxWidth || nr_gaps == 0) {
					// Exactly one word
					auto t = 0;
					for (auto ii = 0; ii < w[start].size(); ii++)
						s[t++] = w[start][ii];
				} else {
					auto pad = (maxWidth - sum) / nr_gaps;
					auto extra = maxWidth - nr_gaps * pad - sum;
					auto t = 0;
					for (i = start ; i < j; i++) {
						for (auto ii = 0; ii < w[i].size(); ii++)
							s[t++] = w[i][ii];
						while (extra > 0) {
							// Add extra spaces if
							// needed.
							t++, extra--;
							break;
						}
						auto p = i < j ? pad : 0;
						while (p > 0)
							t++, p--;
					}
				}
				res.push_back(s);
			}
		}
		return res;
	}
};

int main()
{
	std::cout.setf(std::ios::unitbuf);
	struct {
		vector<string> words;
		int maxWidth;
	} input[] = {
		{
			.words = {
				"This", "is", "an",
				"example", "of", "text",
				"justification.",
			},
			.maxWidth = 16,
		}, {
			.words = {
				"1234",
				"5678",
				"90", "10",
			},
			.maxWidth = 4,
		}, {
			.words = {
				"What", "must", "be",
				"acknowledgment",
				"shall", "be",
			},
			.maxWidth = 16,
		}, {
			.words = {
				"Science", "is", "what", "we",
				"understand", "well", "enough",
				"to", "explain", "to", "a",
				"computer.", "Art", "is",
				"everything", "else", "we", "do",
			},
			.maxWidth = 20,
		}
	};
	Solution solution;
	for (auto& d: input) {
		auto r = solution.fullJustify(d.words, d.maxWidth);
		cout << "---" << endl;
		cout << r << endl;
//		cout << d.words << ", " << d.maxWidth << " => " <<
//			solution.fullJustify(d.words, d.maxWidth) << endl;
	}
	return 0;
}
