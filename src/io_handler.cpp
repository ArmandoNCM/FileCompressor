#include <io_handler.h>




int checkPath(char *fileName){

	stat(fileName, &filestat);
	if(S_ISDIR(filestat.st_mode))
		return 0;
	else
		return 1;
}

int readFile(char const *fileName, char **buffer, long &fileSize){
	FILE *in = fopen(fileName, "rb");
	if(in == NULL)
		return 2;

	// obtain file size
	fseek(in, 0, SEEK_END);
	fileSize = ftell(in);
	rewind(in);

	// allocate memory to contain the whole file:
  	*buffer = (char*) malloc (sizeof(char)*fileSize);
  	if(buffer == NULL)
  		return 3;

  	if(fread(*buffer, 1, fileSize, in) != fileSize)
  		return 4;

  	fclose(in);
  	return 0;


}

std::ostream& operator<<(std::ostream& os, std::forward_list<TreeNode<char, unsigned int>>& list){
	for(auto item : list){
		os << "(" << item.a << "," << item.b << ")";
	}
	return os;
}


void storeTree(FILE *out, TreeNode<char, unsigned int> *root){
	if(root != NULL){
		if(root->a != 0)
			fputc(root->a, out);
		else
			fputc('*', out);
		storeTree(out, root->left);
		storeTree(out, root->right);

	} else
		fputc('.', out);

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





void writeByte(std::string *s, unsigned int &currentBit, FILE *out, bits_in_byte &bitContainer){
	int strLength(s->length());
	int overflow = strLength - currentBit - 1;
	if(overflow > 0){
		// we got ourselves a problem
//		std::cout << "There was Overflow" << std::endl;

		unsigned int threshold(strLength-overflow);
		writeByte(new std::string(s->substr(0,threshold)), currentBit, out, bitContainer);
//		std::cout << "Flushing Complete byte: " << bitContainer << std::endl;
		fputc(byte(bitContainer.to_ulong()), out);
//		fflush(out);
		bitContainer = bits_in_byte("00000000"); // Reset bits_in_byte to zeros
		currentBit=7; // Reset current bit position
		writeByte(new std::string(s->substr(threshold)), currentBit, out, bitContainer);
	}
	else{

		for(auto const &bit : *s){
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