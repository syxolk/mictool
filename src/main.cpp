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

	static option long_options[] = { { "help", no_argument, 0, 'h' }, {
			"version", no_argument, 0, 'v' }, { "output-debug", required_argument, 0, 3 },
			{ "output", required_argument, 0, 'o' },
			{ "output-html", required_argument, 0, 1 },
			{ "output-latex", required_argument, 0, 2 },
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
			} else {
				std::cout << "Cannot detect file type by extension: " << extension << "\n";
				return EXIT_FAILURE;
			}
			opts.outputFile = optarg;
			break;
		case 1 :
			opts.outputFile = optarg;
			opts.outputType = HTML;
			break;
		case 2 :
			opts.outputFile = optarg;
			opts.outputType = LATEX;
			break;
		case 3:
			opts.outputFile = optarg;
			opts.outputType = DEBUG;
			break;
		case '?':
			break;
		default:
			printError(argv[0]);
			return EXIT_FAILURE;
		}
	}

	std::unique_ptr<MPRWriter> writer(nullptr);

	// input file is now the last string in argv
	if (optind == argc - 1) {
		opts.inputFile = argv[optind];

		// read and parse input file
		MPRFile mprFile(extractFilename(std::string(opts.inputFile)));
		if (!readFile(opts.inputFile, mprFile)) {
			return EXIT_FAILURE;
		}

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
		}

		std::ofstream file(opts.outputFile);

		if(! file.is_open()) {
			return EXIT_FAILURE;
		}

		if(! writer->writeMPR(file, mprFile)) {
			return EXIT_FAILURE;
		}
	} else {
		printError(argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

// print help and usage (should be equals to README and man file)
void printHelp() {
	std::cout << "Usage: mictool <inputfile> option [outputfile]\n"
			<< "Options:\n"
			<< "-o, --output      OUTPUTFILE Writes a formatted HTML or LaTeX file of the micro program depending on file name extension\n"
			<< "--output-html       HTMLFILE Writes a formatted HTML file of the micro program\n"
			<< "--output-latex     LATEXFILE Writes a formatted LaTeX file of the micro program\n"
			<< "-d, --debug                  Writes the micro program to stdout (for debugging purposes)\n"
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
	std::cout << "Wrong parameters.\n" << "Type " << arg0
			<< " --help for help.\n" << std::endl;
}
