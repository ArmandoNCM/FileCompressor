#include <decompressor.h>


TreeNode* generateTree(char *buffer, unsigned int &pos){
	if(buffer[pos] == 21)
		return NULL;

	TreeNode *node = new TreeNode;
	node->character = 0;
	if(buffer[pos] == 7){
		pos++;
		node->left = generateTree(buffer, pos);
		pos++;
		node->right = generateTree(buffer, pos);
		return node;
	}

	node->character = buffer[pos];
	pos++;
	node->left = generateTree(buffer, pos);
	pos++;
	node->right = generateTree(buffer, pos);
	return node;

}

void decode(std::string &bitString, TreeNode* root, std::string &decodedString){
	TreeNode *current = root;

	for(auto const &bit : bitString){
		if(bit == '0')
			current = current->left;
		else
			current = current->right;
		if(current->character != 0){
			decodedString.push_back(current->character);
			current = root;
		}
	}
}

char calculateShortestDistance(TreeNode *root){
	char shortestDistance = 0;
	while(root != NULL && root->character == 0){
		root = root->left;
		shortestDistance++;
	}
	return shortestDistance;
}

