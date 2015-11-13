#ifndef __IO_HANDLER
#define __IO_HANDLER


#include <tree_node.h>
#include <binary_io.h>
#include <iostream>
#include <fstream>
#include <forward_list>
#include <map>







/**
	Defines the behavior of the << operator when 
	a forward_list<std::pair<char, unsigned int>>
	is passed to it
	@param os output stream - usually cout
	@param list list to be put into the out-stream

*/
std::ostream& operator<<(std::ostream& os, std::forward_list<TreeNode<char, unsigned int>>& list);

/**
	Counts the chars of a file, and stores their
	frequencies in a map referred by the corresponding
	char as the key
	@param fileName Path of the file to be read
	@param map Map to which the results of the count 
		are going to be stored
	@return Total number of chars read
*/
unsigned int countChars(std::string& fileName, std::map<char, unsigned int>& charMap);

/**
Prints the elements of the Huffman Tree
@param *root Pointer to the root of the tree
*/
void printTreeElements(TreeNode<char, unsigned int> *root);


// TODO DOCUMENT
void writeByte(std::string *s, unsigned int &currentBit, std::ofstream &out, bits_in_byte &bitContainer);


#endif