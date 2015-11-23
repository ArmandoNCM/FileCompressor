#include <compressor.h>

int process(const char *fileName){

	// Reading file
	char *buffer;
	unsigned int fileSize = 0;

	int result = readFile(fileName, &buffer, fileSize);
	if(result != 0)
		return result; // If there was a problem, return its error code

	// Creating the frequency count
	unsigned int *freqCount;
	freqCount = (unsigned int*) malloc(sizeof(unsigned int) * maxAscii);
	memset(freqCount, 0, sizeof(unsigned int) * maxAscii);

	// Count Chars
	countChars(freqCount, buffer, fileSize);

	// Creating a forward linked list
	std::vector<TreeNode> list;
	unsigned char itemCount = createLinkedList(freqCount, list);
	free(freqCount);

	// Getting Tree root
	TreeNode root = generateTree(list, itemCount);

	// Generate character index with short representations of each character
	std::pair<char, std::string*> *charIndex;
	charIndex = (std::pair<char, std::string*>*) malloc((sizeof(std::pair<char, std::string*>)) * itemCount);
	setCharIndex(&root, charIndex);

	// Encoding file
	std::string encodedString;
	encode(buffer, charIndex, encodedString, itemCount, fileSize);
	free(buffer);

	// Opening file to be written
	std::string fPath(fileName);
	fPath += ".huf";
	FILE *out = fopen(fPath.c_str(), "wb");

	// Writing header of file
	fputc((char) 1, out); // SOH

	// Writing number of padding bits
	char paddingBits = (char) 8 - (encodedString.length() % 8);
	if(paddingBits == 8)
		fputc(0, out);
	else
		fputc(paddingBits, out);

	// Store tree
	storeTree(out, &root); // Tree 

	// Indicate encoded file comes
	fputc((char) 2, out); // STX

	// Writing encoded string to output fileName
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