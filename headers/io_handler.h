#ifndef __IO_HANDLER
#define __IO_HANDLER

// C-Style IO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Headers
#include <tree_node.h>
#include <binary_io.h>

// C++ libraries
#include <iostream>
#include <fstream>
#include <forward_list>
#include <map>





int readFile(char const *fileName, char **buffer, long &fileSize);

/**
	Defines the behavior of the << operator when 
	a forward_list<std::pair<char, unsigned int>>
	is passed to it
	@param os output stream - usually cout
	@param list list to be put into the out-stream

*/
std::ostream& operator<<(std::ostream& os, std::forward_list<TreeNode<char, unsigned int>>& list);


/**
Prints the elements of the Huffman Tree
@param *root Pointer to the root of the tree
*/
void printTreeElements(TreeNode<char, unsigned int> *root);


// TODO DOCUMENT
void writeByte(std::string *s, unsigned int &currentBit, FILE *out, bits_in_byte &bitContainer);


void storeTree(FILE *out, TreeNode<char, unsigned int> *root);


#endif