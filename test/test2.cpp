#include <stdio.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	/* code */

	if(argc < 2)
		return 1;

	FILE *file = fopen(argv[1], "w");

	char c = '@';

	fputc(c, file);

	fflush(file);
	fclose(file);

	file = fopen(argv[1], "r");

	

	char ch = fgetc(file);

	std::cout << (int)ch << std::endl;

	return 0;
}
