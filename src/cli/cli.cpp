#include <fstream>
#include <algorithm>
#include <memory>
#include <string>
#include <boost/program_options.hpp>
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

bool CLI::parse() {
	// create namespace alias (shortcut)
	namespace po = boost::program_options;

	// initialize description object
	po::options_description desc("Options");
	desc.add_options()
		("help,h", "Print help messages")
		("version,v", "Print version info")
		("output,o", po::value<std::string>(), "Specify output file")
		("html", "Set output type to HTML")
		("latex", "Set output type to LaTeX")
		("debug", "Set output type to Debug")
		("title", po::value<std::string>(), "Set title for document");

	po::options_description hiddenDesc("Hidden");
	hiddenDesc.add_options()
		("input", po::value<std::string>(), "Specify input file");

	po::options_description allOptions("All Options");
	allOptions.add(desc).add(hiddenDesc);

	po::positional_options_description poDesc;
	poDesc.add("input", -1);

	// parse command line
	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).
          options(allOptions).positional(poDesc).run(), vm);
	po::notify(vm);

	if(vm.count("help")) {
		printHelp(desc);
		return EXIT_SUCCESS; // TODO better exit
	}

	if(vm.count("version")) {
		printVersion();
		return EXIT_SUCCESS; // TODO better exit
	}

	if(vm.count("output")) {
		writeToStdOut = false;
		outputFile = vm["count"].as<std::string>();
	}

	if(vm.count("input")) {
		readFromStdIn = false;
		inputFile = vm["input"].as<std::string>();
	}

	// check for title option
	// if there is no title option then extract the title from the input
	// or output file
	if(vm.count("title")) {
		title = vm["title"].as<std::string>();
	} else if(! readFromStdIn) {
		title = Utils::extractFilename(inputFile);
	} else if(! writeToStdOut) {
		title = Utils::extractFilename(outputFile);
	}

	if(vm.count("html")) {
		outputType = HTML;
	} else if(vm.count("latex")) {
		outputType = LATEX;
	} else if(vm.count("debug")) {
		outputType = DEBUG;
	} else if(! writeToStdOut) { // if no output type option is given but an output file
		std::string extension = Utils::extractFileExtension(outputFile);
		std::transform(extension.begin(), extension.end(), extension.begin(), tolower);

		if(extension == "html" || extension == "htm") {
			outputType = HTML;
		} else if(extension == "tex") {
			outputType = LATEX;
		} else if(extension == "dbg" || extension == "debug") {
			outputType = DEBUG;
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
	if(readFromStdIn) {
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
	if(writeToStdOut) {
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
void CLI::printHelp(const boost::program_options::options_description& desc) {
	std::cout << "Usage: mictool [inputfile] [format options] -o [outputfile]\n"
			<< "\n"
			<< "You can give no inputfile in order to read from standard input.\n"
			<< "You can give no outputfile in order to write to standard output.\n"
			<< "The -o parameter auto detects the output format depending on file\n"
			<< "name extension if no other output format parameter is given.\n"
			<< "\n"
			<< desc
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

