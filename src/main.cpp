//#include <io_handler.h>
//#include <tree_node.h>
#include <compressor.h>
#include <utility>


int checkPath(){
	
}


int main(int argc, char const *argv[])
{
	/* code */

	if(argc < 2)
		return 1;

	int result = checkPath(argv[1]);

	switch(result){
		case 0:
		break;

		case 1:
		break;
	}

	return 0;
}


int process(char *fileName){
	// Checking the number of arguments
	//if(argc < 2)
	//	return 1;
	// Getting file pointer
	//XXX FILE *in = fopen(argv[1], "r");

	//char

	// Reading file
	char *buffer;
	long fileSize = 0;

	int result = readFile(fileName, &buffer, fileSize);
	if(result != 0)
		return result;


	// Creating the char map
	std::map<char, unsigned int> charMap;
	// Count Chars
	countChars(buffer, charMap, fileSize); // FIXME


	// Creating a forward linked list
	std::forward_list<TreeNode<char, unsigned int>> list;
	unsigned int itemCount = createLinkedList(charMap, list);

	TreeNode<char, unsigned int> root = generateTree(list, itemCount);

//	std::cout << "Tree Elements:" << std::endl;
//	printTreeElements(&root);
//	std::cout << std::endl;
	// Generate map with short representations of each character
	std::map<char, std::string> map = getMap(&root);




	char fPath[strlen(fileName) + 4]; // = {0};
	memset(fPath, 0, strlen(fileName) + 4); // Set Array to Zero
	strcat(fPath, fileName);
	strcat(fPath, ".huff");
	FILE *out = fopen(fPath , "wb");


	fputc((char) 1, out); // SOH
	fputs(argv[1], out); // fileName
	fputc((char) 25, out); // EM
	int pos = ftell(out);
	fputc((char) 21, out); // NAK
	fputc((char) 6, out); // ACK
	storeTree(out, &root); // Tree 
	fputc((char) 2, out); // STX

	char paddingBits = compressFile(buffer, map, out, fileSize);
	fseek(out, pos, SEEK_SET);
	fputc(paddingBits, out);
	fseek(out, 0, SEEK_END);
	std::cout << "Number of padding tail bits: " << (int) paddingBits << std::endl;
	//std::cout << "Total chars read: " << fileSize << std::endl;
	fflush(out);
	free(buffer);
	return 0;
}
