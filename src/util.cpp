#include <iostream>
#include <sstream>
#include "util.h"

// parses a single hexadecimal digit
// and returns the corresponding value
int parseHexDigit(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	} else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	} else {
		std::cout << "Unexpected char: " << c << std::endl;
		return 0;
	}
}

// extracts the filename out of a relative or absolute path
// file extension is stripped as well
// example: ~/file.cpp -> file
const std::string extractFilename(const std::string& path) {
	int slashIndex = path.find_last_of("/\\") + 1;
	// if the slash character is not found the function will return -1
	// -> slashIndex + 1 will be zero -> it takes the string from the beginning

	int dotIndex = path.find_first_of('.', slashIndex);

	// if there is no dot in the filename then just take everything
	if (dotIndex == -1) {
		dotIndex = path.length();
	}

	return path.substr(slashIndex, dotIndex - slashIndex);
}

const std::string extractFileExtension(const std::string& path) {
	int dotIndex = path.find_last_of(".");

	if (dotIndex == -1) {
		return "";
	}

	return path.substr(dotIndex + 1);
}

// Replaces all occurences of a string in a string with another string
// http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
void replaceAll(std::string& str, const std::string& needle, const std::string& replacement) {
	if(needle.empty()) return;

	size_t startPos = 0;
	while((startPos = str.find(needle, startPos)) != std::string::npos) {
		str.replace(startPos, needle.length(), replacement);
		startPos += replacement.length();
	}
}

std::string intToString(int value) {
	std::ostringstream ss;
	ss << value;
	return ss.str();
}
