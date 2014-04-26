#include <iostream>
#include "io.h"

using namespace std;

int main(int argc, char* argv[]) {
  if(argc != 2) {
    cout << "Wrong usage. Please use a filename as the first and only parameter." << endl;
  } else {
    readFile(argv[1]);
  }

  return 0;
}
