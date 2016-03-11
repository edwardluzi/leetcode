#include "stdafx.h"
#include <vector>

using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL)
	{
	}
};

class Solution
{
public:
	static vector<int> preorderTraversal(TreeNode* root)
	{
		vector<int> orders;
		visit(root, orders);
		return orders;
	}

	static void visit(TreeNode* node, vector<int>& order)
	{
		if (node != NULL)
		{
			order.push_back(node->val);
			visit(node->left, order);
			visit(node->right, order);
		}
	}

	static void print(string name, vector<int>& vectors)
	{
		bool firstNumber = true;

		printf("%s: ", name.c_str());

		for (vector<int>::iterator it = vectors.begin(); it != vectors.end(); it++)
		{
			if (firstNumber)
			{
				printf("%d", *it);
				firstNumber = false;
			}
			else
			{
				printf(", %d", *it);
			}
		}

		printf("\n");
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	TreeNode* root = new TreeNode(1);
	root->right = new TreeNode(2);
	root->right->left = new TreeNode(3);

	vector<int> result = Solution::preorderTraversal(root);

	Solution::print("", result);

	return 0;
}

