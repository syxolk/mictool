#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <getopt.h>
#include "io.h"
#include "html.h"

using namespace std;

enum OutputType {
  HTML, DEBUG, LATEX
};

// CLI options
// struct is using c++11 default values
struct options {
  char *inputFile;
  char *outputFile;
  OutputType outputType;
};

void printHelp();
void printVersion();
void printError(char* arg0);

int main(int argc, char* argv[]) {
  
  int c;
  options opts;
  opts.inputFile = opts.outputFile = NULL;
  opts.outputType = DEBUG;
  
  static option long_options[] = {
    {"help",        no_argument,       0, 'h'},
    {"version",     no_argument,       0, 'v'},
    {"debug",       no_argument,       0, 'd'},
    {"output-html", required_argument, 0, 'o'},
    {0,             0,                 0,  0 }
  };
  
  while ( (c = getopt_long(argc, argv, "hvo:d", long_options, NULL)) != -1) {
    switch(c) {
    case 'h':
      printHelp();
      return EXIT_SUCCESS;
    case 'v':
      printVersion();
      return EXIT_SUCCESS;
    case 'o':
      opts.outputFile = optarg;
      opts.outputType = HTML;
      break;
    case 'd':
      opts.outputType = DEBUG;
      break;
    case '?':
      break;
    default:
      printError(argv[0]);
      return EXIT_FAILURE;
    }
  }
  
  if (optind == argc - 1) {
    opts.inputFile = argv[optind];
    
    vector<micro_line> lines;
    readFile(opts.inputFile, lines);
    
    if(opts.outputType == DEBUG) {
      for(auto& line : lines) {
        cout << line.number << " : " << line.name  << endl;
        cout << " " << line.bits << endl;
      }
    } else if(opts.outputType == HTML) {
      writeHTML(opts.outputFile, lines);
    }
  } else {
    printError(argv[0]);
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}

void printHelp() {
  cout << "Usage: mictool inputfile option [outputfile]" << endl;
  cout << "Options:" << endl;
  cout << "-o, --output-html outputfile Writes a formatted HTML file of the micro program" << endl;
  cout << "-d, --debug                  Writes the micro program to stdout (for debugging purposes)" << endl;
  cout << "-v, --version                Display mictool version" << endl;
  cout << "-h, --help                   Display this information" << endl;
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
