#ifndef __COMPRESSOR
#define __COMPRESSOR

// Headers
#include <io_handler.h>
#include <tree_node.h>

// C++ Libraries
#include <iostream>
#include <map>
#include <forward_list>
#include <string>

bool compare(const TreeNode<char,unsigned int>& leafA, const TreeNode<char,unsigned int>& leafB);




/**
	Counts the chars of a file, and stores their
	frequencies in a map referred by the corresponding
	char as the key
	@param fileName Path of the file to be read
	@param map Map to which the results of the count 
		are going to be stored
	@return Total number of chars read
*/
void countChars(char *buffer, std::map<char, unsigned int>& charMap, long &length);


unsigned int createLinkedList(std::map<char, unsigned int>& charMap, std::forward_list<TreeNode<char, unsigned int>>& list);


TreeNode<char, unsigned int> generateTree(std::forward_list<TreeNode<char, unsigned int>>& list, unsigned int itemCount);


std::map<char, std::string> getMap(TreeNode<char, unsigned int> *root);


unsigned char compressFile(char *buffer, std::map<char, std::string> &map, FILE *out, long &length);


#endif
