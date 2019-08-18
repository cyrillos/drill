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

static ssize_t partition(vector<size_t>& a, size_t lo, size_t hi)
{
	size_t i = lo-1, j = hi+1;
	auto pivot = a[lo];

	while (true) {
		do { i++; } while (a[i] < pivot);
		do { j--; } while (a[j] > pivot);
		if (i >= j)
			break;
		swap(a[i], a[j]);
	}
	return j;
}

static void __qsort(vector<size_t>& a, size_t lo, size_t hi)
{
	if (lo >= hi)
		return;

	size_t mid = partition(a, lo, hi);
	__qsort(a, lo, mid);
	__qsort(a, mid+1, hi);
}

static void qsort(vector<size_t>& a)
{
	__qsort(a, 0, a.size()-1);
}

int main(void)
{
	vector<size_t> array = {45, 6, 5, 15, 4, 3, 3, 3};
	cout << "array " << array << endl;

	qsort(array);
	cout << "array " << array << endl;
	return 0;
}
