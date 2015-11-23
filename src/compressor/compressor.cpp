#include <compressor.h>

bool compare(const TreeNode &leafA, const TreeNode &leafB){

	return leafA.frequency > leafB.frequency;

}

void countChars(unsigned int *freqCount, char *buffer, unsigned int &fileSize){
	for(unsigned int i = 0; i < fileSize; i++){
		freqCount[buffer[i]]++;
	}
}

unsigned char createLinkedList(unsigned int *freqCount, std::vector<TreeNode>& list){
	unsigned char itemCount = 0;

	for(unsigned char i = 0; i < maxAscii; i++){
		if(freqCount[i] != 0){
			TreeNode *leaf = new TreeNode;
			leaf->character = i;
			leaf->frequency = freqCount[i];
			leaf->left = NULL;
			leaf->right = NULL;
			list.push_back(*leaf);	
			itemCount++;
		}
	}
	return itemCount;
}

TreeNode generateTree(std::vector<TreeNode>& list, unsigned char itemCount){
	TreeNode *leafA, *leafB;

	while(itemCount > 1){
		// XXX list.sort(compare);
		std::sort(list.begin(), list.end(), compare);
		leafA = new TreeNode(list.back());
		list.pop_back();
		leafB = new TreeNode(list.back());
		list.pop_back();
		TreeNode leafC;
		leafC.character = 0;
		leafC.frequency = leafA->frequency + leafB->frequency;
		leafC.right = leafA;
		leafC.left = leafB;
		list.push_back(leafC);
		itemCount--;
	}
	return list.front();
}

void traceTreeLeafs(TreeNode *root, std::string &s, std::pair<char, std::string*> *charIndex, unsigned int &pos){

	if(root != NULL && root->character == 0){
		s.push_back('0');
		traceTreeLeafs(root->left, s, charIndex, pos);
		s.push_back('1');
		traceTreeLeafs(root->right, s, charIndex, pos);
	} else {
		charIndex[pos] = std::pair<char, std::string*>(root->character, new std::string(s));
		pos++;
	}
		s.pop_back();

}

void setCharIndex(TreeNode *root, std::pair<char, std::string*> *charIndex){
	if(root->left == NULL){
		charIndex[0] = std::pair<char, std::string*>(root->character, new std::string("0"));
		return;
	}

	unsigned int pos = 0;

	std::string s("0");
	traceTreeLeafs(root->left, s, charIndex, pos);	// Start with left branch
	s = "1";
	traceTreeLeafs(root->right, s, charIndex, pos);	// and now right branch
	
}

std::string getEncodedChar(char &character, std::pair<char, std::string*> *charIndex, unsigned char &itemCount){
	for(unsigned int i = 0; i < itemCount; i++){
		if(std::get<0>(charIndex[i]) == character)
			return *std::get<1>(charIndex[i]);
	}
	return NULL; // This shall never happen
}

void encode(char *buffer, std::pair<char, std::string*> *charIndex, std::string &encodedString, unsigned char &itemCount, unsigned int &length){
	for(unsigned int i = 0; i < length; i++){
		encodedString += getEncodedChar(buffer[i], charIndex, itemCount);
	}	
}