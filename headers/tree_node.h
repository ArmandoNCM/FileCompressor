#ifndef __TREE_LEAF
#define __TREE_LEAF

struct TreeNode{
	char character;
	unsigned int frequency;
	TreeNode* left;
	TreeNode* right;
};

#endif