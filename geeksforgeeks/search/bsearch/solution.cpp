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

static ssize_t bsearch(vector<size_t> array, size_t elem)
{
	ssize_t i = 0, j = array.size() - 1;
	while (i <= j) {
		auto pos = (i+j) / 2;
		if (array[pos] == elem) {
			// leftmost in case of repetitions
			do {
				pos--;
			} while (pos >= 0 && array[pos] == elem);
			return pos+1;
		} else if (array[pos] < elem)
			i = pos + 1;
		else
			j = pos - 1;
	}
	return -1;
}

int main(void)
{
	vector<size_t> array_unique = {1, 1, 3, 5, 7, 7, 8};
	size_t elems[] = {1,5,7,8,9,0};

	for (auto i: elems) {
		cout << "array " << array_unique <<
			" lookup " << i <<
			" pos " << bsearch(array_unique, i) <<
			endl;
	}

	return 0;
}
