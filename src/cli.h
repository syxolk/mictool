#ifndef _MICTOOL_CLI_H_
#define _MICTOOL_CLI_H_

#include <string>
#include <getopt.h>

/**
 * @brief The command line interface implementation is used to parse command line arguments.
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
		/**
		 * @brief Constructs a new CLI object with the parameters usually given to a main(...) function.
		 *
		 * The constructor returns immediately.
		 * The next method call must be parse().
		 *
		 * @see parse()
		 * @param argc number of command line arguments
		 * @param argv command line arguments
		 */
		CLI(int argc, char **argv) : argc(argc), argv(argv) {};

		/**
		 * @brief Empty deconstructor
		 */
		~CLI() {};

		/**
		 * @brief Start parsing the command line arguments.
		 *
		 * This method must be called first after the constructor.
		 *
		 * @see work()
		 * @return false if anything failed otherwise true
		 */
		bool parse();

		/**
		 * @brief Read the input source and write a formatted MPR file.
		 *
		 * This method must be called after parse() and only
		 * if parsed() returned with true.
		 *
		 * @see parse()
		 * @return false if anything failed otherwise true
		 */
		bool work();
	private:
		// different output types
		// UNKNOWN means there was no output type specified
		enum OutputType {
			UNKNOWN, HTML, DEBUG, LATEX
		};

		// available command line options
		static const option *long_options;

		// CLI arguments
		int argc;
		char **argv;

		// CLI options
		char *inputFile = nullptr;
		char *outputFile = nullptr;
		OutputType outputType = UNKNOWN;
		std::string title = "Formatted MPR file";
		bool autoDetectOutputType = true;
		bool fixedTitle = false;

		// helper methods for error and help messages
		void printHelp();
		void printVersion();
		void printError(char* arg0);
		void printUnknownOutputType(char* arg0);
		void printUnableToOpenFile(std::string inputFile);
};

#endif /* _MICTOOL_CLI_H_ */

