#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	int nr = 0;
	cin >> nr;

	for (auto i = 0; i < nr; i++) {
		string s;
		cin >> s;

		if (s.size() > 10) {
			cout << s[0] << s.size()-2 << s[s.size()-1] << endl;
		} else
			cout << s << endl;
	}

	return 0;
}
