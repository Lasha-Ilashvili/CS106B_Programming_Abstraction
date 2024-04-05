#include "parent.h"
#include "strlib.h"

bool getChild(TreeNode* root, TreeNode* child1, TreeNode* child2) {
	if(root == NULL) {
		return false;
	}

	if(root == child1 || root == child2) {
		return true;
	}
	
	return getChild(root->left, child1, child2) || getChild(root->right, child1, child2);
}

TreeNode * getParent(TreeNode * root, TreeNode * one, TreeNode * two) {

	while(true) {
		if(root == NULL) {
			break;
		}

		if(root == one || root == two) {
			return root;
		}

		bool leftPath  = getChild(root->left, one, two);
		bool rightPath = getChild(root->right, one, two);

		if(leftPath && rightPath) {
			return root;
		}
		
		if(!leftPath) {
			root = root->right;
		} else {
			root = root->left;
		}

	} 
 
	return NULL;
}