#include <iostream>
#include <vector>
#include <list>

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

static void __insertion_sort(vector<size_t>& a, size_t lo, size_t hi)
{
	for (auto i = lo+1; i <= hi; i++) {
		auto key = a[i];
		ssize_t j = i-1;
		while (j >= 0 && a[j] > key) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = key;
	}
}

static void insertion_sort(vector<size_t>& a)
{
	__insertion_sort(a, 0, a.size()-1);
}

int main(void)
{
	vector<size_t> array = {45, 6, 5, 15, 4, 3, 3, 3};
	cout << "array " << array << endl;

	insertion_sort(array);
	cout << "array " << array << endl;
	return 0;
}
