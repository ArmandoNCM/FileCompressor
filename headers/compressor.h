#ifndef __COMPRESSOR
#define __COMPRESSOR

// Headers
#include <io_handler.h>
#include <tree_node.h>

// C++ Libraries
#include <string>
#include <algorithm>
#include <utility>

const unsigned char maxAscii = 255;

bool compare(const TreeNode &leafA, const TreeNode &leafB);

void countChars(unsigned int *freqCount, char *buffer, unsigned int &fileSize);


unsigned char createLinkedList(unsigned int *freqCount, std::vector<TreeNode>& list);

TreeNode generateTree(std::vector<TreeNode>& list, unsigned char itemCount);

void setCharIndex(TreeNode *root, std::pair<char, std::string*> *charIndex);

void encode(char *buffer, std::pair<char, std::string*> *charIndex, std::string &encodedString, unsigned char &itemCount, unsigned int &length);

#endif
