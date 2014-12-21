#include <iostream>
#include <sstream>
#include "util.h"

int Utils::parseHexDigit(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	} else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	} else {
		return -1;
	}
}

std::string Utils::extractFilename(const std::string& path) {
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

std::string Utils::extractFileExtension(const std::string& path) {
	int dotIndex = path.find_last_of(".");

	if (dotIndex == -1) {
		return "";
	}

	return path.substr(dotIndex + 1);
}

void Utils::replaceAll(std::string& str, const std::string& needle, const std::string& replacement) {
	if(needle.empty()) return;

	size_t startPos = 0;
	while((startPos = str.find(needle, startPos)) != std::string::npos) {
		str.replace(startPos, needle.length(), replacement);
		startPos += replacement.length();
	}
}

std::string Utils::intToString(int value) {
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

