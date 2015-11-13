#ifndef __TREE_LEAF
#define __TREE_LEAF

template<class A, class B>
struct TreeNode{
	A a;
	B b;
	TreeNode<A,B>* left;
	TreeNode<A,B>* right;
};

#endif