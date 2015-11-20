//#include <io_handler.h>
//#include <tree_node.h>
#include <compressor.h>

//std::ostream& operator<<(std::ostream &out, char)





int process(const char *fileName){
	// Checking the number of arguments
	//if(argc < 2)
	//	return 1;
	// Getting file pointer
	//XXX FILE *in = fopen(argv[1], "r");

	//char

	// Reading file
	char *buffer;
	unsigned int fileSize = 0;

	int result = readFile(fileName, &buffer, fileSize);
	if(result != 0)
		return result; // If there was a problem, return its error code


	// Creating the char map
	std::unordered_map<char, unsigned int> charMap;
	// Count Chars
	countChars(buffer, charMap, fileSize); 


	// Creating a forward linked list
	std::vector<TreeNode> list;
	unsigned int itemCount = createLinkedList(charMap, list);
	// Getting Tree root
	TreeNode root = generateTree(list, itemCount);

//	std::cout << "Tree Elements:" << std::endl;
//	printTreeElements(&root);
//	std::cout << std::endl;

	std::pair<char, std::string*> *charIndex;// = new std::pair<char, std::string*>()[];
	charIndex = (std::pair<char, std::string*>*) malloc((sizeof(std::pair<char, std::string*>)) * itemCount);

	// Generate character index with short representations of each character
	setCharIndex(&root, charIndex);

	std::string encodedString;
	encode(buffer, charIndex, encodedString, itemCount, fileSize);
	
	free(buffer);
	//delete buffer;


	char fPath[strlen(fileName) + 4]; // = {0};
	memset(fPath, 0, strlen(fileName) + 4); // Set Array to Zero
	strcat(fPath, fileName);
	strcat(fPath, ".huff");
	FILE *out = fopen(fPath , "wb");
	writeBytes(encodedString, out);

/*


	fputc((char) 1, out); // SOH
	fputs(argv[1], out); // fileName
	fputc((char) 25, out); // EM
	int pos = ftell(out);
	fputc((char) 21, out); // NAK
	fputc((char) 6, out); // ACK
	storeTree(out, &root); // Tree 
	fputc((char) 2, out); // STX

	*/


//	char paddingBits = compressFile(buffer, map, out, fileSize);
//	fseek(out, pos, SEEK_SET);
//	fputc(paddingBits, out);
//	fseek(out, 0, SEEK_END);
//	std::cout << "Number of padding tail bits: " << (int) paddingBits << std::endl;
//	std::cout << "Total chars read: " << fileSize << std::endl;
//	fflush(out);

	return 0;
}



int main(int argc, char const *argv[])
{
	/* code */

	if(argc < 2)
		return 1;


	process(argv[1]);

	return 0;
}