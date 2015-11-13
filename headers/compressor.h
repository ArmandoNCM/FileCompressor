#ifndef __COMPRESSOR
#define __COMPRESSOR

#include <io_handler.h>
#include <tree_node.h>
#include <iostream>
#include <map>
#include <forward_list>
#include <string>

bool compare(const TreeNode<char,unsigned int>& leafA, const TreeNode<char,unsigned int>& leafB);


unsigned int createLinkedList(std::map<char, unsigned int>& charMap, std::forward_list<TreeNode<char, unsigned int>>& list);


TreeNode<char, unsigned int> generateTree(std::forward_list<TreeNode<char, unsigned int>>& list, unsigned int itemCount);


std::map<char, std::string> getMap(TreeNode<char, unsigned int> *root);


unsigned int compressFile(std::ifstream &in, std::map<char, std::string> &map, std::ofstream &out);


#endif
