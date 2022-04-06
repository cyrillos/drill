#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

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
	int findRadius(vector<int>& houses, vector<int>& heaters) {
		int nr_houses = houses.size();
		int nr_heaters = heaters.size();
		int i, j;

		sort(houses.begin(), houses.end());
		sort(heaters.begin(), heaters.end());
		vector<int> res(nr_houses, INT_MAX);

		//
		// Walk houses from *left*, and find distance to the heaters
		//
		// 1  2  3  6  7  8	houses 
		//    2        7   	heaters
		// 1  0  4  1  0  ?
		//
		// Then walk from *right* and update distances (minimize
		// the distance)
		//
		// 1  2  3  6  7  8	houses 
		//    2        7   	heaters
		// 1  0  1  1  0  1
		//
		// Then simply find max distance from minimals.

		for (i = 0, j = 0; i < nr_houses && j < nr_heaters; i++) {
			if (houses[i] <= heaters[j])
				res[i] = heaters[j] - houses[i];
			else
				i--, j++;
		}

		for (i = nr_houses-1, j = nr_heaters-1; i >= 0 && j >= 0; i--) {
			if (houses[i] >= heaters[j])
				res[i] = min(res[i], houses[i] - heaters[j]);
			else
				i++, j--;
		}

		return *max_element(res.begin(), res.end());;
	}
};

int main()
{
	struct {
		vector<int> houses;
		vector<int> heaters;
	} input[] = {
		{
			// 1
			.houses = {1,2,3},
			.heaters = {2},
		}, {
			// 1
			.houses = {1,2,3,4},
			.heaters = {1,4},
		}, {
			// 1
			.houses = {1,2,3,6,7,8},
			.heaters = {2,7},
		}, {
			// 3
			.houses = {1,5},
			.heaters = {2},
		}, {
			// 0
			.houses = {1,2,3},
			.heaters = {1,2,3},
		}
	};
	Solution solution;
	for (auto& d: input) {
		cout << d.houses << ", " << d.heaters << " => " <<
			solution.findRadius(d.houses, d.heaters) << endl;
	}
	return 0;
}
