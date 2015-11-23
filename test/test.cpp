#include <iostream>
//#include <binary_io.h>
#include <string>

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

bool isDirectory(const char *fileName){
	struct stat filestat;
	stat(fileName, &filestat);
	return S_ISDIR(filestat.st_mode);
}
/*
void processDirectory(const char *dirPath){
	DIR *directory = opendir(dirPath);
	dirent *dirEntity;
	while(dirEntity = readdir(directory)){
		std::cout << dirEntity->d_name << std::endl;
	}
}
*/

int main(int argc, char const *argv[])
{
	/* code */


//	if(argc < 2)
//		return 1;

	//mkdir(argv[1], 511);

	char a = 5;
	char b = 2;
	char c = a / b;

	std::cout << (int) c << std::endl;



	return 0;
}