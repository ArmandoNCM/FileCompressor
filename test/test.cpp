#include <iostream>
#include <stdio.h>
#include <string.h>

using byte = unsigned char;

int main(int argc, char const *argv[])
{
	/* code */

	std::cout << "EOF: " << EOF << "( " << ((int) EOF) << " )" << std::endl;

	FILE *in = fopen(argv[1], "r");

	char ch;

	while((ch = fgetc(in)) != EOF){
		std::cout << ch << ",";
	}
	std::cout << std::endl;

	return 0;
}