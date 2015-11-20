#include <iostream>
//#include <binary_io.h>
#include <string>
#include <utility>


void method(std::pair<char,int*> *array){
	std::cout << std::get<0>(array[0]) << "," << *std::get<1>(array[0]) << std::endl;
	array[0] = std::pair<char,int*>('3', new int(64));
	std::cout << std::get<0>(array[0]) << "," << *std::get<1>(array[0]) << std::endl;
}

int main(int argc, char const *argv[])
{
	/* code */
	int numberOfElements = 1;
	std::pair<char, int*> *array;
	array = (std::pair<char,int*>*) malloc(sizeof(std::pair<char,int*>*) * numberOfElements);
	int ch = 'a';
	int num = 3;
	array[0] = std::pair<char,int*>(ch, &num);
	method(array);

	return 0;
}