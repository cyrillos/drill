class Solution {
public:
	int lastStoneWeight(vector<int>& s) {
		//
		// Simply use heap structure and
		// fetch biggest values on each step.
		while (s.size() > 1) {
			make_heap(s.begin(), s.end());
			pop_heap(s.begin(), s.end());
			auto v1 = s.back();
			s.pop_back();
			if (s.size() < 1)
				return v1;

			make_heap(s.begin(), s.end());
			pop_heap(s.begin(), s.end());
			auto v2 = s.back();
			s.pop_back();
			if (v1 == v2) {
				if (s.size() == 0)
					return 0;
				continue;
			}

			s.push_back(v1 - v2);
		}
		return s[0];
	}
};
