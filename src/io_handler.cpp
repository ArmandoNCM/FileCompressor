#include <io_handler.h>




bool isDirectory(char *fileName){
	struct stat filestat;
	stat(fileName, &filestat);
	return S_ISDIR(filestat.st_mode);
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
  	//delete in;
  	return 0;


}

std::ostream& operator<<(std::ostream& os, std::vector<TreeNode>& list){
	for(auto item : list){
		os << "(" << item.character << "," << item.frequency << ")";
	}
	return os;
}


void storeTree(FILE *out, TreeNode *root){
	if(root != NULL){
		if(root->character != 0)
			fputc(root->character, out);
		else
			fputc('*', out);
		storeTree(out, root->left);
		storeTree(out, root->right);

	} else
		fputc('.', out);

}


void printTreeElements(TreeNode *root){
	// Print all the items in the tree to which root points.
	// The item in the root is printed first, followed by the
	// items in the left subtree and then the items in the
	// right subtree.
	if(root != NULL){
		if(root->character != 0)
			std::cout << root->character << root->frequency << std::endl;	// Print the root item.
		printTreeElements(root->left);	// Print items in left subtree.
		printTreeElements(root->right);	// Print items in right subtree.
	}
}



/*

void writeByte(std::string *s, byte &currentBit, FILE *out, bits_in_byte &bitContainer){
	byte strLength(s->length());
	char overflow = strLength - currentBit - 1;
	if(overflow > 0){
		// we got ourselves a problem
//		std::cout << "There was Overflow" << std::endl;

		unsigned int threshold(strLength-overflow);
		writeByte(new std::string(s->substr(0,threshold)), currentBit, out, bitContainer);
//		std::cout << "Flushing Complete byte: " << bitContainer << std::endl;
		fputc(byte(bitContainer.to_ulong()), out);
		bitContainer.reset();
		currentBit=7; // Reset current bit position
		writeByte(new std::string(s->substr(threshold)), currentBit, out, bitContainer);
	}
	else{

		for(auto const &bit : *s){
			if(bit == '1'){
				bitContainer[currentBit] = 1;// XXX insert zero at currentBit in bitSet
//				std::cout << "Set bit\t->" << (currentBit+1) << " to: 1\t->"  << bitContainer << std::endl;
			}
//			else std::cout << "Set bit\t->" << (currentBit+1) << " to: 0\t->"  << bitContainer << std::endl; 
//				

			//else don't insert anything (leave with default 0)
			currentBit--;
		}	
	}
}
*/

void writeBytes(std::string &encodedString, FILE *out){
	std::string bitSequence;
	bits_in_byte bitarray;
	long long int strLength(encodedString.length());
	long long int max(strLength - BITS_PER_BYTE + 1);
	long long int i = 0;
	long long int j;
	while(i < max){
		j = i + 8;
		bitSequence = encodedString.substr(i, j);
		bitarray = bits_in_byte(bitSequence);
		fputc((byte) bitarray.to_ulong(), out);
		i=j;
	}
	//if(i < strLength)
	//	writePaddedByte(encodedString.substr(strLength));
}

//void writePaddedByte(std::string lastBitSequence)