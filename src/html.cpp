#include <fstream>
#include <vector>
#include <iostream>
#include "html.h"
#include "io.h"
using namespace std;

void writeHTML(const char* path, vector<micro_line>& lines) {
  ofstream file(path);
  if(file.is_open()) {
    
    for(auto& line : lines) {
      file << line.name << ": " << line.bits << endl;
    }
    
    file.close();
  } else {
    cout << "Cannot write file: " << path << endl;
  }
}
