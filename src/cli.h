#ifndef _MICTOOL_CLI_H_
#define _MICTOOL_CLI_H_

#include <string>
#include <getopt.h>

class CLI {
	public:
		CLI(int argc, char **argv) : argc(argc), argv(argv) {};
		~CLI() {};
		bool parse();
		bool work();
	private:
		// different output types
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
