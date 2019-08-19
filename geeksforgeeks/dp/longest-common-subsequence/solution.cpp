#include <algorithm>
#include <iostream>
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
//
// a[i,j] == b[i,j] => d[i-1][j-1] + 1
// a[i,j] != b[i,j] => max(d[i-1][j], d[i][j-1])
//
//   0 A G G T A B
// 0 0 0 0 0 0 0 0
// G 0 0 1 1 1 1 1
// X 0 0 1 1 1 1 1
// T 0 0 1 1 2 2 2
// X 0 0 1 1 2 2 2
// A 0 1 1 1 2 3 3
// Y 0 1 1 1 3 3 3
// B 0 1 1 1 3 3 4

static size_t lcs(string& a, string& b)
{
	size_t i, j;

	vector<vector<size_t>> d(a.size()+1);
	for (i = 0; i < d.size(); i++)
		d[i].resize(b.size()+1, 0);

	for (i = 0; i < a.size(); i++) {
		for (j = 0; j < b.size(); j++) {
			if (b[j] == a[i]) {
				d[i+1][j+1] = d[i][j]+1;
			} else {
				d[i+1][j+1] = max(d[i][j+1],d[i+1][j]);
			}
		}
	}

	return d[i][j];
}

int main()
{
	string a = "AGGTAB";
	string b = "GXTXAYB";
	cout << a << " " << b << " " << lcs(a,b) << endl;
	return 0;
}
