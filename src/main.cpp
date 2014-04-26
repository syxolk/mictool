#include <iostream>
#include <vector>
#include <cstring>
#include "io.h"
#include "html.h"

using namespace std;

void printHelp();
void printVersion();
void printError();

int main(int argc, char* argv[]) {
  if(argc == 2) {
    if(strcmp(argv[1], "--version") == 0) {
      printVersion();
    } else if(strcmp(argv[1], "--help") == 0) {
      printHelp();
    } else {
      printError();
      return 1;
    }
  } else if(argc == 4 || argc == 3) {
    vector<micro_line> lines;
    readFile(argv[1], lines);
    
    if(argc == 4 && strcmp(argv[2], "--output-html") == 0) {
      writeHTML(argv[3], lines);
    } else if(argc == 3 && strcmp(argv[2], "--show") == 0) {
      for(auto& line : lines) {
        cout << line.number << " : " << line.name  << endl;
        cout << " " << line.bits << endl;
      }
    } else {
      printError();
      return 1;
    }
  } else {
    printError();
    return 1;
  }

  return 0;
}

void printHelp() {
  cout << "Usage: mictool inputfile option [outputfile]" << endl;
  cout << "Options:" << endl;
  cout << "--output-html outputfile Writes a formatted HTML file of the micro program" << endl;
  cout << "--show                   Writes the micro program to stdout (for debug only)" << endl;
  cout << "--version                Display mictool version" << endl;
  cout << "--help                   Display this information" << endl;
}

void printVersion() {
  cout << "mictool 1.0" << endl;
  cout << "This is open source software." << endl;
}

void printError() {
  cout << "Wrong parameters." << endl;
  cout << "Type mictool --help for help." << endl;
}
