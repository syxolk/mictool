#include <iostream>
#include <vector>
#include "io.h"

using namespace std;

int main(int argc, char* argv[]) {
  if(argc != 2) {
    cout << "Wrong usage. Please use a filename as the first and only parameter." << endl;
  } else {
    vector<micro_line> lines;
    readFile(argv[1], lines);
    
    for(auto& line : lines) {
      cout << line.number << " : " << line.name  << endl;
      cout << " " << line.bits << endl;
    }
  }

  return 0;
}
