#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include "io.h"
#include "html.h"

using namespace std;

void printHelp();
void printVersion();
void printError(char* arg0);

int main(int argc, char* argv[]) {
  
  int returnCode = EXIT_SUCCESS;
  
  if(argc == 2) { // check 1 parameter
    if(strcmp(argv[1], "--version") == 0) { // check version option
      printVersion();
    } else if(strcmp(argv[1], "--help") == 0) { // check help option
      printHelp();
    } else {
      returnCode = EXIT_FAILURE;
    }
  } else if(argc == 4 || argc == 3) { // check 3/4 parameters
    vector<micro_line> lines;
    readFile(argv[1], lines);
    
    if(argc == 4 && strcmp(argv[2], "--output-html") == 0) { // check HTML option
      writeHTML(argv[3], lines);
    } else if(argc == 3 && strcmp(argv[2], "--show") == 0) { // check debug option
      for(auto& line : lines) {
        cout << line.number << " : " << line.name  << endl;
        cout << " " << line.bits << endl;
      }
    } else {
      returnCode = EXIT_FAILURE;
    }
  } else {
    returnCode = EXIT_FAILURE;
  }
  
  if(returnCode == EXIT_FAILURE) {
    printError(argv[0]);
  }
  
  return returnCode;
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
  cout << "This program is compatible with JMIC 1.4 and MPR-Files v4." << endl;
  cout << "This is open source software." << endl;
}

void printError(char* arg0) {
  cout << "Wrong parameters." << endl;
  cout << "Type " << arg0 << " --help for help." << endl;
}
