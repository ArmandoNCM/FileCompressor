#include <compressor.h>

bool compare(const TreeNode<char,unsigned int>& leafA, const TreeNode<char,unsigned int>& leafB){

	return leafA.b < leafB.b;

}


void countChars(char *buffer, std::map<char, unsigned int>& charMap, long &length){
	// Reading characters

	for(long i = 0; i < length; i++){
		charMap[*buffer]++;
		buffer++;
	}
}


unsigned int createLinkedList(std::map<char, unsigned int>& charMap, std::forward_list<TreeNode<char, unsigned int>>& list){
	unsigned int itemCount = 0;
	for(auto item : charMap){
		TreeNode<char, unsigned int>* leaf = new TreeNode<char, unsigned int>;
		leaf->a = std::get<0>(item);
		leaf->b = std::get<1>(item);
		leaf->left = NULL;
		leaf->right = NULL;
		list.push_front(*leaf);
		itemCount++;
	}
	return itemCount;
}

TreeNode<char, unsigned int> generateTree(std::forward_list<TreeNode<char, unsigned int>>& list, unsigned int itemCount){
	TreeNode<char, unsigned int> *leafA, *leafB;

	while(itemCount > 1){
		list.sort(compare);
		leafA = new TreeNode<char, unsigned int>(list.front());
		list.pop_front();
		leafB = new TreeNode<char, unsigned int>(list.front());
		list.pop_front();
		TreeNode<char, unsigned int> leafC;
		leafC.a = 0;
		leafC.b = leafA->b + leafB->b;
		leafC.right = leafA;
		leafC.left = leafB;
		list.push_front(leafC);
		itemCount--;
	}
	return list.front();




}

void traceTreeLeafs(TreeNode<char, unsigned int> *root, std::string &s, std::map<char, std::string> &map){

	if(root != NULL && root->a == 0){
		s.push_back('0');
		traceTreeLeafs(root->left, s, map);
		s.push_back('1');
		traceTreeLeafs(root->right, s, map);
	} else {
		map[root->a] = s;
	}
		s.pop_back();

}


std::map<char, std::string> getMap(TreeNode<char, unsigned int> *root){
	
	std::string s("0");
	std::map<char, std::string> map;
	traceTreeLeafs(root->left, s, map);		// Start with left branch
	s = "1";
	traceTreeLeafs(root->right, s, map);	// and now right branch
	return map; 
	
}


unsigned char compressFile(char *buffer, std::map<char, std::string> &map, FILE *out, long &length){

	// Initializing runtime dependencies
	bits_in_byte bitContainer;
	unsigned int currentBit(7); // XXX 


	for(long i = 0; i < length; i++){
		writeByte(new std::string(map[*buffer]), currentBit, out, bitContainer);
		buffer++;
	}

	if(currentBit != 7){
		std::cout << "Flushing Complete byte: " << bitContainer << std::endl;
		fputc(byte(bitContainer.to_ulong()), out);
		return (unsigned char) currentBit+1;
	}
	fflush(out);
	//fclose(out);
	return 0;
}