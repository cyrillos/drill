class Solution {
public:
	//
	// Simply use simultaneous traversing
	TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
		queue<TreeNode*> q1, q2;

		q1.push(original);
		q2.push(cloned);

		while (!q1.empty()) {
			auto top1 = q1.front();
			auto top2 = q2.front();
			q1.pop();
			q2.pop();

			if (top1 == target)
				return top2;
			if (top1->left) {
				q1.push(top1->left);
				q2.push(top2->left);
			}
			if (top2->right) {
				q1.push(top1->right);
				q2.push(top2->right);
			}
		}

		return nullptr;
	}
};
