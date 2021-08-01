class Solution {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> c(rowIndex + 1, 1);
		vector<int> p(rowIndex + 1, 1);
		vector<int>& cur = c;
		vector<int>& prv = p;

		for (auto i = 1; i < rowIndex + 1; i++) {
			for (auto j = 1; j <= i; j++) {
				// Numbers are too big,
				// use long type.
				long v = (long)prv[j-1] + (long)prv[j];
				cur[j] = v;
			}
			swap(cur, prv);
		}
		return cur;
	}
};
