#include <iostream>

using namespace std;

int main(void)
{
	int v = 0;
	cin >> v;
	if (v > 2 && (v % 2) == 0)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}
