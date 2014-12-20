#ifndef _MICTOOL_CLI_H_
#define _MICTOOL_CLI_H_

#include <string>
#include <getopt.h>

/*
 * CLI (command line interface) is used to parse
 * command line arguments.
 *
 * Usually a file will be parsed from a file or standard input.
 * Then it will be written out to a file again or the standard ouput.
 *
 * Help and version information will be given here as well.
 *
 * @author Hans Kirchner
 */
class CLI {
	public:
		/*
		 * Constructs a new CLI object with the parameters usually
		 * given to a main(...) function.
		 *
		 * The constructor returns immediately.
		 */
		CLI(int argc, char **argv) : argc(argc), argv(argv) {};

		/*
		 * Empty deconstructor
		 */
		~CLI() {};

		/*
		 * Start parsing the command line arguments.
		 * This method must be called first after the constructor.
		 *
		 * @return false if anything failed
		 */
		bool parse();

		/*
		 * Read the input source and write a formatted MPR file.
		 * This method must be called after parse() and only
		 * if parsed() returned with true.
		 *
		 * @return false if anything failed
		 */
		bool work();
	private:
		// different output types
		// UNKNOWN means there was no output type specified
		enum OutputType {
			UNKNOWN, HTML, DEBUG, LATEX
		};

		// CLI arguments
		int argc;
		char **argv;

		// CLI options
		char *inputFile = nullptr;
		char *outputFile = nullptr;
		OutputType outputType = UNKNOWN;
		std::string title = "Formatted MPR file";
		bool autoDetectOutputType = true;

		// helper methods for error and help messages
		void printHelp();
		void printVersion();
		void printError(char* arg0);
		void printUnknownOutputType(char* arg0);
		void printUnableToOpenFile(std::string inputFile);
};

#endif /* _MICTOOL_CLI_H_ */

