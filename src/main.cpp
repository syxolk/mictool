#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <getopt.h>
#include <algorithm>
#include <memory>
#include "io.h"
#include "html.h"
#include "latex.h"
#include "debug.h"
#include "util.h"
#include "mpr.h"
#include "mpr_writer.h"

enum OutputType {
	UNKNOWN, HTML, DEBUG, LATEX
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
void printUnknownOutputType(char* arg0);

int main(int argc, char* argv[]) {

	int c;
	options opts;
	opts.inputFile = opts.outputFile = nullptr;
	opts.outputType = UNKNOWN;

	static option long_options[] = { { "help", no_argument, 0, 'h' },
			{ "version", no_argument, 0, 'v' },
			{ "output", required_argument, 0, 'o' },
			{ "html", no_argument, 0, 1 },
			{ "latex", no_argument, 0, 2 },
			{ "debug", no_argument, 0, 3 },
			{ 0, 0, 0, 0 } };

	std::string extension;

	// parse command line options
	while ((c = getopt_long(argc, argv, "hvo:", long_options, NULL)) != -1) {
		switch (c) {
		case 'h':
			printHelp();
			return EXIT_SUCCESS;
		case 'v':
			printVersion();
			return EXIT_SUCCESS;
		case 'o':
			// try to detect output type by file name extension
			extension = extractFileExtension(optarg);
			std::transform(extension.begin(), extension.end(), extension.begin(), tolower);
			if(extension == "html") {
				opts.outputType = HTML;
			} else if(extension == "tex") {
				opts.outputType = LATEX;
			} else if(extension == "dbg" || extension == "debug") {
				opts.outputType = DEBUG;
			}
			opts.outputFile = optarg;
			break;
		case 1 :
			opts.outputType = HTML;
			break;
		case 2 :
			opts.outputType = LATEX;
			break;
		case 3:
			opts.outputType = DEBUG;
			break;
		case '?':
			break;
		default:
			printError(argv[0]);
			return EXIT_FAILURE;
		}
	}

	// input file is now the last string in argv
	if (optind == argc - 1) {
		opts.inputFile = argv[optind];
	}

	std::string title("Formatted MPR file");
	
	// try to get the MPR file title from input or output file name
	if(opts.inputFile != nullptr) {
		title = extractFilename(std::string(opts.inputFile));
	} else if(opts.outputFile != nullptr) {
		title = extractFilename(std::string(opts.outputFile));
	}

	MPRFile mprFile(title);

	// check different input sources
	if(opts.inputFile == nullptr) {
		// read from standard input
		if(! readFile(std::cin, mprFile)) {
			return EXIT_FAILURE;
		}
	} else {
		 // open the file
  		std::ifstream file(opts.inputFile, std::ios::in);
  		
  		if(! file.is_open()) {
  			std::cout << "Unable to open file: " << opts.inputFile << std::endl;
  			return EXIT_FAILURE;
    	}
    	
    	// read and parse from input file
		if (!readFile(file, mprFile)) {
			return EXIT_FAILURE;
		}
		
		file.close();
	}

	std::unique_ptr<MPRWriter> writer(nullptr);

	// check different output formats
	switch (opts.outputType) {
	case DEBUG:
		writer = std::unique_ptr<MPRWriter>(new MPRWriterDebug());
		break;
	case HTML:
		writer = std::unique_ptr<MPRWriter>(new MPRWriterHTML());
		break;
	case LATEX:
		writer = std::unique_ptr<MPRWriter>(new MPRWriterLaTeX());
		break;
	case UNKNOWN:
		printUnknownOutputType(argv[0]);
		return EXIT_FAILURE;
	}

	// check for output file
	if(opts.outputFile == nullptr) {
		// write to standard output
		if(! writer->writeMPR(std::cout, mprFile)) {
			return EXIT_FAILURE;
		}
	} else {
		// open file for writing
		std::ofstream file(opts.outputFile);

		if(! file.is_open()) {
			return EXIT_FAILURE;
		}
		
		// write to file
		if(! writer->writeMPR(file, mprFile)) {
			return EXIT_FAILURE;
		}
	
		file.close();
	}

	return EXIT_SUCCESS;
}

// print help and usage (should be equals to README and man file)
void printHelp() {
	std::cout << "Usage: mictool [inputfile] [format options] -o [outputfile]\n"
			<< "\n"
			<< "You can give no inputfile in order to read from standard input.\n"
			<< "You can give no outputfile in order to write to standard output.\n"
			<< "The -o parameter auto detects the output format depending on file\n"
			<< "name extension if no other output format parameter is given.\n"
			<< "\n"
			<< "Options:\n"
			<< "-o, --output      OUTPUTFILE Write the output to the given file\n"
			<< "--html                       Set the output format to HTML\n"
			<< "--latex                      Set the output format to LaTeX\n"
			<< "--debug                      Set the output format to debug\n"
			<< "-v, --version                Display mictool version\n"
			<< "-h, --help                   Display this information\n"
			<< std::endl;
}

// print version and license information
void printVersion() {
	std::cout << "mictool 1.0\n"
			<< "This program is compatible with JMIC 1.4 and MPR-Files v4.\n"
			<< "This is open source software: https://github.com/syxolk/mictool\n"
			<< std::endl;
}

// print error in case of wrong command line usage
void printError(char* arg0) {
	std::cerr << "Wrong parameters.\n" << "Type " << arg0
			<< " --help for help.\n" << std::endl;
}

void printUnknownOutputType(char* arg0) {
	std::cerr << "Unknown output type.\n" << "Type " << arg0
			<< " --help for help.\n" << std::endl;
}
