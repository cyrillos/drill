#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T> v)
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

static void heapify(vector<size_t>& a, ssize_t root, ssize_t hi)
{
	ssize_t pos = root;
	while (true) {
		ssize_t l = pos * 2;
		ssize_t r = pos * 2 + 1;

		if (l <= hi && a[l] > a[pos])
			pos = l;
		if (r <= hi && a[r] > a[pos])
			pos = r;
		if (root == pos)
			break;
		swap(a[pos], a[root]);
		root = pos;
	}
}

static void __heapsort(vector<size_t>& a, ssize_t lo, ssize_t hi)
{
	for (ssize_t i = hi / 2; i >= lo; i--)
		heapify(a, i, hi);

	for (ssize_t i = hi; i > lo; i--) {
		swap(a[lo], a[i]);
		heapify(a, lo, i-1);
	}
}

static void heapsort(vector<size_t>& a)
{
	__heapsort(a, 0, a.size()-1);
}

int main(void)
{
	vector<size_t> array = {45, 4, 3, 2, 1, 6, 5, 15, 4, 3, 3, 3};
	cout << "array " << array << endl;

	heapsort(array);
	cout << "array " << array << endl;
	return 0;
}
