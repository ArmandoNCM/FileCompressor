#include <io_handler.h>
#include <tree_node.h>
#include <compressor.h>
#include <utility>

// Returns true if the a is less than b
/*
void test(TreeNode<char, unsigned int> *root){
	if(root != NULL){
		std::cout << root->a << root->b << std::endl;
		test(root->left);
		test(root->right);
	}
}
*/

int main(int argc, char* argv[]){
	// Checking the number of arguments
	if(argc < 2)
		return 1;
	// Getting filename
	std::string fileName(argv[1]);

	// Creating the char map
	std::map<char, unsigned int> charMap;
	// Count Chars
	unsigned int totalChars = countChars(fileName, charMap);


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

	std::ifstream in(fileName, std::ios::in);
	std::ofstream out(fileName += ".huf", std::ios::out | std::ios::binary);
	std::cout << "Number of padding tail bits: " << compressFile(in, map, out) << std::endl;


	//std::cout << root.right->left->right->a << root.right->left->right->b << std::endl;


/*
	std::cout << "Items in list: " << itemCount << std::endl;
	std::cout << "Unsorted List: " << list << std::endl;
	list.sort(compare);
	std::cout << "Sorted List: " << list << std::endl;
*/
	std::cout << "Total chars read: " << totalChars << std::endl;
	return 0;
}
