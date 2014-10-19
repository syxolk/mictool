#include <fstream>
#include <iostream>
#include "latex.h"

bool writeLaTeX(const char* path, MPRFile& mprFile) {
	std::ofstream file(path);
	if(file.is_open()) {
		
		file << mprFile.getName();
		
		file.close();
		return true;
	} else {
		std::cout << "Cannot write file: " << path << std::endl;
		return false;
	}
}
