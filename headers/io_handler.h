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
//XXX #include <forward_list> 
#include <vector>
#include <unordered_map>





int readFile(char const *fileName, char **buffer, long &fileSize);

/**
	Defines the behavior of the << operator when 
	a forward_list<std::pair<char, unsigned int>>
	is passed to it
	@param os output stream - usually cout
	@param list list to be put into the out-stream

*/
std::ostream& operator<<(std::ostream& os, std::vector<TreeNode>& list);

void storeTree(FILE *out, TreeNode *root);



/**
Prints the elements of the Huffman Tree
@param *root Pointer to the root of the tree
*/
void printTreeElements(TreeNode *root);


//void writeByte(std::string *s, byte &currentBit, FILE *out, bits_in_byte &bitContainer);

void writeBytes(std::string &encodedString, FILE *out);




#endif