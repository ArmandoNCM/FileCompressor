#include <decompressor.h>

int process(const char *fileName){

	// Reading file
	char *buffer;
	unsigned int fileSize = 0;

	int result = readFile(fileName, &buffer, fileSize);
	if(result != 0)
		return result; // If there was a problem, return its error code


	// First Byte must be a StartOfHeader SOH character
	if(buffer[0] != 1)
		return 2; // File is not compressed in huff format

	// Got number of padding bytes
	char paddingBits = buffer[1];

	unsigned int pos(2);
	TreeNode *root = generateTree(buffer, pos);

	// XXX TESTING
	printTreeElements(root);


	// Creating bitstring
	std::string bitString;
	for(unsigned int i = pos+2; i < fileSize; i++){
		bitString += bits_in_byte(buffer[i]).to_string();
	}


	std::string decodedString;
	decode(bitString, root, decodedString);
	
	

	char pops = (char) paddingBits / calculateShortestDistance(root);
	for(char i = 0; i < pops; i++){
		decodedString.pop_back();
	}


	std::string outputFileName(fileName);
	for(char i = 0; i < 4; i++){
		outputFileName.pop_back();
	}

	std::ofstream out(outputFileName);

	out << decodedString;

	out.close();

/*
*/
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