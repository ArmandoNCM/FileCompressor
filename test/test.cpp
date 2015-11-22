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

void processDirectory(const char *dirPath){
	DIR *directory = opendir(dirPath);
	dirent *dirEntity;
	while(dirEntity = readdir(directory)){
		std::cout << dirEntity->d_name << std::endl;
	}
}

int main(int argc, char const *argv[])
{
	/* code */

	if(argc < 3)
		return 1;

	mkdir(argv[2], 0777);
	
	if(isDirectory(argv[1])){
		std::cout << "Is directory" << std::endl;
//		processDirectory(argv[1]);
	}
	else
		std::cout << "Is file" << std::endl;





	return 0;
}