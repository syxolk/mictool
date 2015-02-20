#ifndef _MICTOOL_CLI_H_
#define _MICTOOL_CLI_H_

#include <string>
#include <boost/program_options.hpp>
#include <cli/cli_options.h>

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
         * @brief Constructs a new CLI object with an CLIOptions object.
		 *
		 * The constructor returns immediately.
         * The next method call should be work().
		 *
         * @see CLIOptions
         * @param options command line options
		 */
        CLI(const CLIOptions& options) : options(options) {}

		/**
		 * @brief Empty deconstructor
		 */
        ~CLI() {}

		/**
         * @brief Read the input source and write a formatted MPR file.
		 *
		 * @return false if anything failed otherwise true
		 */
		bool work();
    private:
        // command line options
        CLIOptions options;

		// helper methods for error and help messages
        void printHelp();
		void printVersion();
        void printError();
        void printUnknownOutputType();
        void printUnableToOpenFile(const std::string& file);
};

#endif /* _MICTOOL_CLI_H_ */

