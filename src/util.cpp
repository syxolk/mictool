#include <iostream>
#include "util.h"
using namespace std;

int parseHexDigit(char c) {
  if(c >= '0' && c <= '9') {
    return c - '0';
  } else if(c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  } else if(c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  } else {
    cout << "Unexpected char: " << c << endl;
    return 0;
  }
}
