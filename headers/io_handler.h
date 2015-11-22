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
#include <vector>

bool isDirectory(const char *fileName)

int readFile(char const *fileName, char **buffer, unsigned int &fileSize);

std::ostream& operator<<(std::ostream& os, std::vector<TreeNode>& list);

void storeTree(FILE *out, TreeNode *root);

void printTreeElements(TreeNode *root);

void writeBytes(std::string &encodedString, FILE *out);

#endif