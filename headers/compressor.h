#ifndef __COMPRESSOR
#define __COMPRESSOR

// Headers
#include <io_handler.h>
#include <tree_node.h>

// C++ Libraries
#include <string>
#include <algorithm>
#include <utility>

bool compare(const TreeNode &leafA, const TreeNode &leafB);




/**
	Counts the chars of a file, and stores their
	frequencies in a map referred by the corresponding
	char as the key
	@param fileName Path of the file to be read
	@param map Map to which the results of the count 
		are going to be stored
	@return Total number of chars read
*/
void countChars(char *buffer, std::unordered_map<char, unsigned int>& charMap, long &length);


unsigned int createLinkedList(std::unordered_map<char, unsigned int>& charMap, std::vector<TreeNode>& list);


TreeNode generateTree(std::vector<TreeNode>& list, unsigned int itemCount);

void setCharIndex(TreeNode *root, std::pair<char, std::string*> *charIndex);


//std::unordered_map<char, std::string> getMap(TreeNode *root);


//unsigned char compressFile(char *buffer, std::unordered_map<char, std::string> &map, FILE *out, long &length);

void encode(char *buffer, std::unordered_map<char, std::string> &map, std::string &encodedString, long &length);

//void traceTreeLeafs(TreeNode *root, std::string &s, std::unordered_map<char, std::string> &map);


#endif
