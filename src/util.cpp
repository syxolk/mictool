#include <iostream>
#include "util.h"

// parses a single hexadecimal digit
// and returns the corresponding value
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

// extracts the filename out of a relative or absolute path
// file extension is stripped as well
// example: ~/file.cpp -> file
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

// works like PHP htmlspecialchars
// -> http://de1.php.net/manual/en/function.htmlspecialchars.php
// implementation is from stackoverflow
// -> http://stackoverflow.com/questions/5665231/most-efficient-way-to-escape-xml-html-in-c-string
const std::string htmlspecialchars(const std::string& data) {
  std::string buffer;
  buffer.reserve(data.size());
  for(size_t pos = 0; pos != data.size(); ++pos) {
    switch(data[pos]) {
      case '&':  buffer.append("&amp;");       break;
      case '\"': buffer.append("&quot;");      break;
      case '\'': buffer.append("&apos;");      break;
      case '<':  buffer.append("&lt;");        break;
      case '>':  buffer.append("&gt;");        break;
      default:   buffer.append(&data[pos], 1); break;
    }
  }
  return buffer;
}
