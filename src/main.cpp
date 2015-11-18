//#include <io_handler.h>
//#include <tree_node.h>
#include <compressor.h>
#include <utility>


int main(int argc, char* argv[]){
	// Checking the number of arguments
	if(argc < 2)
		return 1;
	// Getting file pointer
	FILE *in = fopen(argv[1], "r");

	// Creating the char map
	std::map<char, unsigned int> charMap;



	// Count Chars
	unsigned int totalChars = countChars(in, charMap);


	// Creating a forward linked list
	std::forward_list<TreeNode<char, unsigned int>> list;
	unsigned int itemCount = createLinkedList(charMap, list);

	TreeNode<char, unsigned int> root = generateTree(list, itemCount);

	std::cout << "Tree Elements:" << std::endl;
	printTreeElements(&root);
	std::cout << std::endl;

	std::map<char, std::string> map = getMap(&root);
	std::cout << "Char Values:" << std::endl;
	for(auto item : map){
		std::cout << std::get<0>(item) << "=" << std::get<1>(item) << std::endl;
	}
	std::cout << std::endl;

	char fPath[strlen(argv[1]) + 4] = {};
	strcat(fPath, argv[1]);
	strcat(fPath, ".huff");
	rewind(in);
	FILE *out = fopen(fPath , "wb");
	std::cout << "Number of padding tail bits: " << compressFile(in, map, out) << std::endl;



	std::cout << "Total chars read: " << totalChars << std::endl;
	return 0;
}
