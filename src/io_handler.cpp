#include <io_handler.h>


std::ostream& operator<<(std::ostream& os, std::forward_list<TreeNode<char, unsigned int>>& list){
	for(auto item : list){
		os << "(" << item.a << "," << item.b << ")";
	}
	return os;
}

unsigned int countChars(std::string& fileName, std::map<char, unsigned int>& charMap){
	std::ifstream in(fileName);
	// Reading characters
	unsigned int totalChars = 0;
	char ch;
	while(in.get(ch)){
		charMap[ch]++;
		totalChars++;
	}
	return totalChars;
}



void printTreeElements(TreeNode<char, unsigned int> *root){
	// Print all the items in the tree to which root points.
	// The item in the root is printed first, followed by the
	// items in the left subtree and then the items in the
	// right subtree.
	if(root != NULL){
		if(root->a != 0)
			std::cout << root->a << root->b << std::endl;	// Print the root item.
		printTreeElements(root->left);	// Print items in left subtree.
		printTreeElements(root->right);	// Print items in right subtree.
	}
}


void writeByte(std::string *s, unsigned int &currentBit, std::ofstream &out, bits_in_byte &bitContainer){
	int strLength(s->length());
	int overflow = strLength - currentBit - 1;
	if(overflow > 0){
		// we got ourselves a problem
//		std::cout << "There was Overflow" << std::endl;

		unsigned int threshold(strLength-overflow);
		writeByte(new std::string(s->substr(0,threshold)), currentBit, out, bitContainer);
//		std::cout << "Flushing Complete byte: " << bitContainer << std::endl;
		out.put(byte(bitContainer.to_ulong())); // XXX KEEP THIS IN MIND, HERE IS THE FLUSH OF THE BYTE TO THE OUTPUT STREAM
//		out.flush();
		bitContainer = bits_in_byte("00000000");
		currentBit=7; // XXX
		writeByte(new std::string(s->substr(threshold)), currentBit, out, bitContainer);
	} // TODO CHECK IF THE FOLLOWING CYCLE SHOULD BE IN THE ELSE CLAUSE OF THE THE PREVIOUS IF BLOCK
	else{
		for(auto bit : *s){
			if(bit == '1'){
				bitContainer[currentBit] = 1;// XXX insert zero at currentBit in bitSet
//				std::cout << "Set bit\t->" << (currentBit+1) << " to: 1\t->"  << bitContainer << std::endl;
			}
//			else // XXX
//				std::cout << "Set bit\t->" << (currentBit+1) << " to: 0\t->"  << bitContainer << std::endl;

			//else don't insert anything (leave with default 0)
			currentBit--;
		}	
	}
}