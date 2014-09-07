#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <getopt.h>
#include "io.h"
#include "html.h"

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

    std::vector<micro_line> lines;
    std::vector<ram_cell> ram_cells;
    readFile(opts.inputFile, lines, ram_cells);

    if(opts.outputType == DEBUG) {
      for(auto& line : lines) {
        std::cout << line.number << " : " << line.name  << std::endl;
        std::cout << " " << line.bits << std::endl;
      }

      for(auto& cell : ram_cells) {
        std::cout << cell.data << std::endl;
      }
    } else if(opts.outputType == HTML) {
      writeHTML(opts.outputFile, lines, ram_cells);
    }
  } else {
    printError(argv[0]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void printHelp() {
  std::cout << "Usage: mictool inputfile option [outputfile]\n"
            << "Options:\n"
            << "-o, --output-html outputfile Writes a formatted HTML file of the micro program\n"
            << "-d, --debug                  Writes the micro program to stdout (for debugging purposes)\n"
            << "-v, --version                Display mictool version\n"
            << "-h, --help                   Display this information\n"
            << std::endl;
}

void printVersion() {
  std::cout << "mictool 1.0\n"
            << "This program is compatible with JMIC 1.4 and MPR-Files v4.\n"
            << "This is open source software: https://github.com/syxolk/mictool\n"
            << std::endl;
}

void printError(char* arg0) {
  std::cout << "Wrong parameters.\n"
            << "Type " << arg0 << " --help for help.\n"
            << std::endl;
}
