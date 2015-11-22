#include <io_handler.h>

bool isDirectory(const char *fileName){
	struct stat filestat;
	stat(fileName, &filestat);
	return S_ISDIR(filestat.st_mode);
}

int readFile(char const *fileName, char **buffer, unsigned int &fileSize){
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

byte getPaddedByte(const char *lastBitSequence, unsigned char paddingBits){
		bits_in_byte bitContainer(lastBitSequence);
		bitContainer <<= paddingBits;
		return (byte) bitContainer.to_ulong();
}

void writeBytes(std::string &encodedString, FILE *out){
	const char *bitSequence = encodedString.c_str();
	bits_in_byte bitarray;
	unsigned long strLength(encodedString.length());
	unsigned long max(strLength - BITS_PER_BYTE + 1);
	unsigned long i = 0;
	if(strLength > 7){
		while(i < max){
			bitarray = bits_in_byte(bitSequence, 8);
			fputc((byte) bitarray.to_ulong(), out);
			bitSequence += 8;
			i += 8;
		}
		if(i < strLength)
			fputc(getPaddedByte(bitSequence, (unsigned char) 8 - (strLength - i)), out);
	} else
		fputc(getPaddedByte(bitSequence, (unsigned char) 8 - strLength), out);
}