#include <fstream>
#include <algorithm>
#include <memory>
#include <string>
#include <reader/v4/v4.h>
#include <writer/html/html.h>
#include <writer/latex/latex.h>
#include <writer/debug/debug.h>
#include <util/util.h>
#include <mpr/mpr.h>
#include <writer/mpr_writer.h>
#include <reader/mpr_reader.h>
#include "cli.h"
#include <MictoolConfig.h>

// avaliable command line options
// this array of structs is needed for getopt_long
static const option CLI_long_options_data[] = {
	{ "help", no_argument, 0, 'h' },
	{ "version", no_argument, 0, 'v' },
	{ "output", required_argument, 0, 'o' },
	{ "html", no_argument, 0, 1 },
	{ "latex", no_argument, 0, 2 },
	{ "debug", no_argument, 0, 3 },
	{ "title", required_argument, 0, 4 },
	{ 0, 0, 0, 0 }
};
const option* CLI::long_options = CLI_long_options_data;

bool CLI::parse() {
	int c;
	std::string extension;

	// parse command line options
	while ((c = getopt_long(argc, argv, "hvo:", long_options, NULL)) != -1) {
		switch (c) {
		case 'h': /* --help, -h */
			printHelp();
			return EXIT_SUCCESS;
		case 'v': /* --version, -v */
			printVersion();
			return EXIT_SUCCESS;
		case 'o': /* --output, -o */
			if(autoDetectOutputType) {
				// try to detect output type by file name extension
				extension = Utils::extractFileExtension(optarg);
				std::transform(extension.begin(), extension.end(), extension.begin(), tolower);
				if(extension == "html" || extension == "htm") {
					outputType = HTML;
				} else if(extension == "tex") {
					outputType = LATEX;
				} else if(extension == "dbg" || extension == "debug") {
					outputType = DEBUG;
				}
			}

			outputFile = optarg;
			break;
		case 1 : /* --html */
			outputType = HTML;
			autoDetectOutputType = false;
			break;
		case 2 : /* --latex */
			outputType = LATEX;
			autoDetectOutputType = false;
			break;
		case 3: /* --debug */
			outputType = DEBUG;
			autoDetectOutputType = false;
			break;
		case 4: /* --title */
			title = optarg;
			fixedTitle = true;
			break;
		case '?':
			break;
		default:
			printError(argv[0]);
			return false;
		}
	}

	// input file is now the last string in argv
	if (optind == argc - 1) {
		inputFile = argv[optind];
	}
	
	// if --title was not given
	if(! fixedTitle) {
		// try to get the MPR file title from input or output file name
		if(inputFile != nullptr) {
			title = Utils::extractFilename(std::string(inputFile));
		} else if(outputFile != nullptr) {
			title = Utils::extractFilename(std::string(outputFile));
		}
	}
	
	return true;
}

bool CLI::work() {
	MPRFile mprFile(title);

	std::unique_ptr<MPRReader> reader(new MPRReaderV4());

	std::unique_ptr<MPRWriter> writer(nullptr);

	// check different output formats
	switch (outputType) {
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
		return false;
	}

	// check different input sources
	if(inputFile == nullptr) {
		// read from standard input
		if(! reader->readMPR(std::cin, mprFile)) {
			return false;
		}
	} else {
		 // open the file
  		std::ifstream file(inputFile, std::ios::in);
  		
  		if(! file.is_open()) {
  			printUnableToOpenFile(inputFile);
  			return false;
    	}
    	
    	// read and parse from input file
		if (! reader->readMPR(file, mprFile)) {
			return false;
		}
		
		file.close();
	}

	// check for output file
	if(outputFile == nullptr) {
		// write to standard output
		if(! writer->writeMPR(std::cout, mprFile)) {
			return false;
		}
	} else {
		// open file for writing
		std::ofstream file(outputFile);

		if(! file.is_open()) {
			printUnableToOpenFile(outputFile);
			return false;
		}
		
		// write to file
		if(! writer->writeMPR(file, mprFile)) {
			return false;
		}
	
		file.close();
	}
	
	return true;
}

// print help and usage (should be equals to README and man file)
void CLI::printHelp() {
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
			<< "--title                TITLE Set the title to be used for output document\n"
			<< "-v, --version                Display mictool version\n"
			<< "-h, --help                   Display this information\n"
			<< std::endl;
}

// print version and license information
void CLI::printVersion() {
	std::cout << "mictool " << Mictool_VERSION_MAJOR << "." << Mictool_VERSION_MINOR <<"\n"
			<< "This program is compatible with JMIC 1.4 and MPR-Files v4.\n"
			<< "This is open source software: https://github.com/syxolk/mictool\n"
			<< std::endl;
}

// print error in case of wrong command line usage
void CLI::printError(char* arg0) {
	std::cerr << "Wrong parameters.\n" << "Type " << arg0
			<< " --help for help.\n" << std::endl;
}

void CLI::printUnknownOutputType(char* arg0) {
	std::cerr << "Unknown output type.\n" << "Type " << arg0
			<< " --help for help.\n" << std::endl;
}

void CLI::printUnableToOpenFile(std::string inputFile) {
	std::cerr << "Unable to open file: " << inputFile
			<< "\n" << "Check file existance and permissions.\n" << std::endl;
}

