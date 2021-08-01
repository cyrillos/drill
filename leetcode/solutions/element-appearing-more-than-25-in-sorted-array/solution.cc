class Solution {
public:
	int findSpecialInteger(vector<int>& arr) {
		int n = arr.size() / 4 + 1;
		int nr = 1, prev = arr[0];

		if (arr.size() < 2)
			return arr[0];

		//
		// Just use simply linear scan,
		// it has "easy" tag as implies.
		//
		// Another approach could be to
		// use binary seacrh: split the
		// range down to 4 subranges and
		// one element should appear twice
		// at subrange bounds.
		for (auto i = 1; i < arr.size(); i++) {
			if (prev == arr[i]) {
				nr++;
				if (nr >= n)
					return arr[i];
			} else {
				prev = arr[i];
				nr = 1;
			}
		}

		return -1;
	}
};
