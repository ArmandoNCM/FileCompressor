#ifndef __TREE_LEAF
#define __TREE_LEAF

struct TreeNode{
	char character;
	unsigned long frequency;
	TreeNode* left;
	TreeNode* right;
};

#endif