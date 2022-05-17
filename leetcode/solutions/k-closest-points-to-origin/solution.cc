class Solution {
public:
	//
	// Trivial geometry: simply calculate squared hypotenuse and sort
	// the results, closest points are having smaller hypotenuse.
	vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
		int nr = points.size();
		sort(points.begin(), points.end(),
		     [](const vector<int>& a, const vector<int>& b) {
			return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
		     });
		vector<vector<int>> res(k, {0, 0});

		for (int i = 0; i < k; i++)
			res[i] = points[i];

		return res;
	}
};
