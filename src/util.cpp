#include <iostream>
#include "util.h"

int parseHexDigit(char c) {
  if(c >= '0' && c <= '9') {
    return c - '0';
  } else if(c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  } else if(c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  } else {
    std::cout << "Unexpected char: " << c << std::endl;
    return 0;
  }
}

const std::string extractFilename(const std::string& path) {
  int slashIndex = path.find_last_of("/\\") + 1;
  // if the slash character is not found the function will return -1
  // -> slashIndex + 1 will be zero -> it takes the string from the beginning

  int dotIndex = path.find_first_of('.', slashIndex);

  // if there is no dot in the filename then just take everything
  if(dotIndex == -1) {
    dotIndex = path.length();
  }

  return path.substr(slashIndex, dotIndex - slashIndex);
}
