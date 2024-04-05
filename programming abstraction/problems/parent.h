#include <cstdio>

using namespace std;

struct TreeNode {
	int v; //You can use this field value only for debugging
	TreeNode * left;
	TreeNode * right;
};

TreeNode * getParent(TreeNode * root, TreeNode * one, TreeNode * two);

