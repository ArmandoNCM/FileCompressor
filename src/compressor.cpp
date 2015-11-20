#include <compressor.h>

bool compare(const TreeNode &leafA, const TreeNode &leafB){

	return leafA.frequency > leafB.frequency;

}


void countChars(char *buffer, std::unordered_map<char, unsigned int>& charMap, long &length){
	// Reading characters

	for(long i = 0; i < length; i++){
		charMap[*buffer]++;
		buffer++;
	}
}


unsigned int createLinkedList(std::unordered_map<char, unsigned int>& charMap, std::vector<TreeNode>& list){
	unsigned int itemCount = 0;
	for(auto const &item : charMap){
		TreeNode* leaf = new TreeNode;
		leaf->character = std::get<0>(item);
		leaf->frequency = std::get<1>(item);
		leaf->left = NULL;
		leaf->right = NULL;
		list.push_back(*leaf);
		itemCount++;
	}
	return itemCount;
}

TreeNode generateTree(std::vector<TreeNode>& list, unsigned int itemCount){
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
/*
void traceTreeLeafs(TreeNode *root, std::string &s, std::unordered_map<char, std::string> &map){

	if(root != NULL && root->character == 0){
		s.push_back('0');
		traceTreeLeafs(root->left, s, map);
		s.push_back('1');
		traceTreeLeafs(root->right, s, map);
	} else {
		map[root->character] = s;
	}
		s.pop_back();

}
*/

void traceTreeLeafs(TreeNode *root, std::string &s, std::pair<char, std::string*> *charIndex, unsigned int &pos){

	if(root != NULL && root->character == 0){
		s.push_back('0');
		traceTreeLeafs(root->left, s, charIndex, pos);
		s.push_back('1');
		traceTreeLeafs(root->right, s, charIndex, pos);
	} else {
		//charIndex[pos] = std::make_pair<char, std::string*>(root->character, new std::string(s));
		charIndex[pos] = std::pair<char, std::string*>(root->character, new std::string(s));
		pos++;
	}
		s.pop_back();

}


//std::string* getShortRepresentation(std::vector)

void setCharIndex(TreeNode *root, std::pair<char, std::string*> *charIndex){
	if(root->left == NULL){
		charIndex[0] = std::pair<char, std::string*>(root->character, new std::string("0"));
	}

	unsigned int pos = 0;

	std::string s("0");
	traceTreeLeafs(root->left, s, charIndex, pos);	// Start with left branch
	s = "1";
	traceTreeLeafs(root->right, s, charIndex, pos);	// and now right branch
	
}
/*

std::unordered_map<char, std::string> getMap(TreeNode *root){
	
	std::unordered_map<char, std::string> map;
	std::string s("0");
	traceTreeLeafs(root->left, s, map);		// Start with left branch
	s = "1";
	traceTreeLeafs(root->right, s, map);	// and now right branch
	return map; 
	
}
*/
/*
unsigned char compressFile(char *buffer, std::unordered_map<char, std::string> &map, FILE *out, long &length){

	// Initializing runtime dependencies
	bits_in_byte bitContainer;
	byte currentBit(7); // XXX 

	for(long i = 0; i < length; i++){
//		std::cout << "Compressing character: " << *buffer << std::endl;
		writeByte(new std::string(map[*buffer]), currentBit, out, bitContainer);
		buffer++;
	}

	if(currentBit != 7){
//		std::cout << "Flushing Complete byte: " << bitContainer << std::endl;
		fputc(byte(bitContainer.to_ulong()), out);
		return  currentBit+1;
	}
	fflush(out);
	//fclose(out);
	return 0;
}
*/

void encode(char *buffer, std::unordered_map<char, std::string> &map, std::string &encodedString, long &length){
	for(long i = 0; i < length; i++){
		encodedString += map[*buffer];
		buffer++;
	}	
	//free(&buffer);
	//delete &buffer;
}

