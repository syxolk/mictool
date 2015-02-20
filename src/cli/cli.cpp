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

bool CLI::work() {
    if(options.hasError()) {
        printError();
        return false;
    }

    if(options.requestedHelp()) {
        printHelp();
        return true;
    }

    if(options.requestedVersion()) {
        printVersion();
        return true;
    }

    MPRFile mprFile(options.title());

	std::unique_ptr<MPRReader> reader(new MPRReaderV4());

	std::unique_ptr<MPRWriter> writer(nullptr);

    std::ostream nirvana(0); // discard all written data
    std::ostream *errorStream = options.quiet() ? &nirvana : &std::cerr;

	// check different output formats
    switch (options.format()) {
    case CLIOptions::OutputType::DEBUG:
		writer = std::unique_ptr<MPRWriter>(new MPRWriterDebug());
		break;
    case CLIOptions::OutputType::HTML:
		writer = std::unique_ptr<MPRWriter>(new MPRWriterHTML());
		break;
    case CLIOptions::OutputType::LATEX:
		writer = std::unique_ptr<MPRWriter>(new MPRWriterLaTeX());
		break;
    case CLIOptions::OutputType::UNKNOWN:
        printUnknownOutputType();
		return false;
	}

	// check different input sources
    if(options.isReadFromStdIn()) {
		// read from standard input
        if(! reader->readMPR(std::cin, mprFile, *errorStream)) {
			return false;
		}
	} else {
		 // open the file
        std::ifstream file(options.input(), std::ios::in);

  		if(! file.is_open()) {
            printUnableToOpenFile(options.input());
  			return false;
    	}

    	// read and parse from input file
        if (! reader->readMPR(file, mprFile, *errorStream)) {
			return false;
		}

		file.close();
	}

	// check for output file
    if(options.isWriteToStdOut()) {
		// write to standard output
		if(! writer->writeMPR(std::cout, mprFile)) {
			return false;
		}
	} else {
		// open file for writing
        std::ofstream file(options.output());

		if(! file.is_open()) {
            printUnableToOpenFile(options.output());
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
            << options.description()
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
void CLI::printError() {
    if(! options.quiet()) {
        std::cerr << options.error() << std::endl << std::endl;
        std::cerr << "Wrong parameters.\n" << "Type " << options.programName()
				<< " --help for help.\n" << std::endl;
	}
}

void CLI::printUnknownOutputType() {
    if(! options.quiet()) {
        std::cerr << "Unknown output type.\n" << "Type " << options.programName()
				<< " --help for help.\n" << std::endl;
	}
}

void CLI::printUnableToOpenFile(const std::string& file) {
    if(! options.quiet()) {
        std::cerr << "Unable to open file: " << file
				<< "\n" << "Check file existance and permissions.\n" << std::endl;
	}
}

