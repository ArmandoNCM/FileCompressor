#ifndef __DECOMPRESSOR
#define __DECOMPRESSOR

#include <io_handler.h>



TreeNode* generateTree(char *buffer, unsigned int &pos);

void decode(std::string &bitString, TreeNode* root, std::string &decodedString);

char calculateShortestDistance(TreeNode *root);


#endif