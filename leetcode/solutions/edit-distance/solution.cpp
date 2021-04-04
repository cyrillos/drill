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
	int minDistance(string src, string dst) {
		size_t nr_src = src.size();
		size_t nr_dst = dst.size();

		// Corner cases.
		if (!nr_src)
			return nr_dst;
		else if (!nr_dst)
			return nr_src;

		//
		// Well known Levinstein distance
		//
		//    i n t e n t i o n
		//  0 1 2 3 4 5 6 7 8 9
		//  -------------------
		//e 1 1 2 3 4 5 6 7 8 9 
		//x 2 2 2 3 4 5 6 7 8 9
		//e 3 3 3 3 4 5 6 7 8 9
		//c 4 4 4 4 4 5 6 7 8 9
		//u 5 5 5 5 5 5 6 7 8 9
		//t 6 6 6 5 6 6 5 6 7 8
		//i 7 6 7 6 6 7 6 5 6 7 
		//o 8 7 7 7 7 7 7 6 5 6
		//n 9 8 7 8 8 7 8 7 6 5
		//
		size_t rows = nr_src+1;
		size_t cols = nr_dst+1;
		vector<vector<size_t>> d(rows, vector<size_t>(cols));


		for (size_t r = 0; r < rows; r++)
			d[r][0] = r;
		for (size_t c = 0; c < cols; c++)
			d[0][c] = c;

		for (size_t r = 1; r < rows; r++) {
			for (size_t c = 1; c < cols; c++) {
				if (src[r-1] == dst[c-1]) {
					d[r][c] = d[r-1][c-1];
				} else {
					d[r][c] =
						min(d[r-1][c],
						    min(d[r][c-1],
							d[r-1][c-1])) + 1;
				}
			}
		}
		return d[rows-1][cols-1];
	}
};

int main()
{
	struct {
		string w1;
		string w2;
	} input[] = {
		{	// 3
			.w1 = "horse",
			.w2 = "ros",
		}, {	// 5
			.w1 = "intention",
			.w2 = "execution",
		},
	};
	Solution solution;
	for (auto& d: input) {
		cout << d.w1 << ", " << d.w2 << " => " <<
			solution.minDistance(d.w1, d.w2) << endl;
	}
	return 0;
}
