#include <iostream>
#include <stdio.h>
#include <string.h>


void method(int **ptrptrInt){
	int lol = 5;
	*ptrptrInt = &lol;
}


int main(int argc, char const *argv[])
{
	/* code */

	int an = 10;
	int *ptrAn = &an;
	method(&ptrAn);

	std::cout << *ptrAn << std::endl;

	return 0;
}