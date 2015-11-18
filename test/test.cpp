#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


#include <iostream>
#include <string>




int main(int argc, char const *argv[])
{
	/* code */

	DIR *dp;
	struct dirent *dirp;
	struct stat filestat;
	std::string filepath;

	if(argc < 2)
		return 1;

	//dp = opendir(argv[1]);

	stat(argv[1], &filestat);
	if(S_ISDIR(filestat.st_mode))
		std::cout << "Is directory" << std::endl;



/*
	if(dp == NULL)
		return 2;



	while ((dirp = readdir( dp ))){
	    filepath = dirp->d_name;
	    stat( filepath.c_str(), &filestat )

	    // Check if is directory
	    if (S_ISDIR( filestat.st_mode ))         
	    	std::cout << "Directory: " << filepath << std::endl;
	    else
	    	std::cout << "Directory: " << filepath << std::endl;

    }

*/


	return 0;
}