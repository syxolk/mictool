#ifndef _MICTOOL_CLI_H_
#define _MICTOOL_CLI_H_

#include <string>
#include <boost/program_options.hpp>

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
        CLI(int argc, const char *argv[]) : argc(argc), argv(argv) {}

		/**
		 * @brief Empty deconstructor
		 */
        ~CLI() {}

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
		
		/**
		 * @brief Set the quiet flag to true if all error messages
		 * shall be silent. Nothing will go out on stderr.
		 *
		 * @param beQuiet quiet flag, defaults to true
		 */
        void quiet(bool beQuiet) {
			this->beQuiet = beQuiet;
		}
		
		/**
		 * Returns the status of the quiet flag.
		 *
		 * @return true if quiet flag is set
		 */
		bool quiet() const {
			return beQuiet;
		}

        /**
         * @brief Set the arguments to parse. This values usually
         * come from the main function
         *
         * @param argc number of arguments
         * @param argv list of string arguments
         * @return this
         */
        CLI& arg(int argc, const char *argv[]) {
            this->argc = argc;
            this->argv = argv;
            return *this;
        }
		
        /**
         * @brief Return the input file.
         *
         * @return input file or empty string if read from stdin.
         */
		std::string input() const {
			return inputFile;
		}
		
        /**
         * @brief Set the input file.
         *
         * @param file path of input file
         * @return this
         */
        CLI& input(const std::string& file) {
			inputFile = file;
            return *this;
		}
		
        /**
         * @brief Set this CLI to read from stdin,
         * not a file.
         *
         * @return this
         */
        CLI& readFromStdIn() {
			inputFile = "";
            return *this;
		}
		
        /**
         * @brief Check if this CLI reads from stdin
         * and not a file.
         *
         * @return true if read from stdin
         */
		bool isReadFromStdIn() const {
			return inputFile.empty();
		}
		
        /**
         * @brief Return the output file.
         *
         * @return output file or empty string if write of stdout
         */
		std::string output() const {
			return outputFile;
		}
		
        /**
         * @brief Set the output file
         *
         * @param file path of output file
         * @return this
         */
        CLI& output(const std::string& file) {
			outputFile = file;
            return *this;
        }

        /**
         * @brief Set the CLI to write of stdout
         * and not a file.
         *
         * @return this
         */
		CLI& writeToStdOut() {
			outputFile = "";
            return *this;
		}

        /**
         * @brief Check if write to stdout and not a file.
         *
         * @return true if write to stdout
         */
		bool isWriteToStdOut() const {
			return outputFile.empty();
		}

        /**
         * @brief Set the document title for the MPR file
         * to write
         *
         * @param title title for the MPR file
         * @return this
         */
        CLI& title(const std::string& title) {
            this->docTitle = title;
            return *this;
        }

        /**
         * @brief Return the document title
         *
         * @return document title
         */
        std::string title() const {
            return docTitle;
        }

        /**
         * @brief The different output formats.
         *
         * UNKNOWN means there was no output type specified
         */
        enum class OutputType {
            UNKNOWN, HTML, DEBUG, LATEX
        };

        OutputType format() const {
            return outputType;
        }

        CLI& format(OutputType outputType) {
            this->outputType = outputType;
            return *this;
        }

	private:
		// CLI arguments
		int argc;
        const char **argv;

		// CLI options
		std::string inputFile;
		std::string outputFile;
        OutputType outputType = OutputType::UNKNOWN;
        std::string docTitle = "Formatted MPR file";
		
		// set to true if the program should print no error messages
		bool beQuiet = false;

		// helper methods for error and help messages
		void printHelp(const boost::program_options::options_description& desc);
		void printVersion();
        void printError(const char* arg0);
        void printUnknownOutputType(const char* arg0);
		void printUnableToOpenFile(std::string inputFile);
};

#endif /* _MICTOOL_CLI_H_ */

