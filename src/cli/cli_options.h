#ifndef _MICTOOL_CLI_OPTIONS_H_
#define _MICTOOL_CLI_OPTIONS_H_

#include <boost/program_options.hpp>

/**
 * @brief CLIOptions is parsing command line arguments,
 * saves them in private members and allows read/write access
 * via public methods.
 *
 * @see CLI
 * @author Hans Kirchner
 */
class CLIOptions {
public:
    /**
     * @brief Create a default options object.
     *
     * It is recommended to call parse() in order
     * to fill the member.
     *
     * @see CLIOptions::parse
     */
    CLIOptions() {}

    /**
     * @brief Create a default options object and immediatly
     * parse the given command line arguments.
     *
     * @param argc number of command line arguments
     * @param argv list of string arguments
     */
    CLIOptions(int argc, const char *argv[]) {
        parse(argc, argv);
    }

    /**
     * @brief Start parsing the command line arguments.
     *
     * @return false if anything failed otherwise true
     */
    bool parse(int argc, const char *argv[]);

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
    CLIOptions& input(const std::string& file) {
        inputFile = file;
        return *this;
    }

    /**
     * @brief Set this CLI to read from stdin,
     * not a file.
     *
     * @return this
     */
    CLIOptions& readFromStdIn() {
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
    CLIOptions& output(const std::string& file) {
        outputFile = file;
        return *this;
    }

    /**
     * @brief Set the CLI to write of stdout
     * and not a file.
     *
     * @return this
     */
    CLIOptions& writeToStdOut() {
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
    CLIOptions& title(const std::string& title) {
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

    /**
     * @brief Output format that is currently set. Defaults to UNKNOWN.
     *
     * @return output format or UNKNOWN if not known/given
     */
    OutputType format() const {
        return outputType;
    }

    /**
     * @brief Set the output format.
     *
     * @param outputType output format
     * @return this
     */
    CLIOptions& format(OutputType outputType) {
        this->outputType = outputType;
        return *this;
    }

    /**
     * @brief Return the program name. This will be set
     * by parse() to argv[0].
     * @return program name, usually something like "mictool"
     */
    std::string programName() const {
        return program;
    }

    /**
     * @brief Set the program name
     * @param program program name
     * @return this
     */
    CLIOptions& programName(const std::string& program) {
        this->program = program;
        return *this;
    }

    /**
     * @brief Description text that will be written if
     * the user requests help information.
     *
     * This will be set by parse()
     *
     * @return description/help text
     */
    std::string description() {
        return descriptionText;
    }

    /**
     * @brief Set the desciption text.
     *
     * @param descriptionText description text
     * @return this
     */
    CLIOptions& description(const std::string& descriptionText) {
        this->descriptionText = descriptionText;
        return *this;
    }

    /**
     * @brief If "--help" was given as an argument.
     *
     * @return true if help information should be printed
     */
    bool requestedHelp() {
        return requestHelp;
    }

    /**
     * @brief Set the help flag
     *
     * @param requestHelp true if help information should be printed
     * @return this
     */
    CLIOptions& requestedHelp(bool requestHelp) {
        this->requestHelp = requestHelp;
        return *this;
    }

    /**
     * @brief If "--version" was given as an argument.
     *
     * @return true if version information should be printed
     */
    bool requestedVersion() {
        return requestVersion;
    }

    /**
     * @brief Set the version flag
     *
     * @param requestVersion true if version information should be printed
     * @return this
     */
    CLIOptions& requestedVersion(bool requestVersion) {
        this->requestVersion = requestVersion;
        return *this;
    }

    /**
     * @brief Check if there was an error during parsing.
     *
     * @return true there was an error
     */
    bool hasError() {
        return ! errorMessage.empty();
    }

    /**
     * @brief Returns the error message if there was an error
     *
     * @return error message or empty string if there was no error
     */
    std::string error() {
        return errorMessage;
    }

    /**
     * @brief Set the error message.
     * @param errorMessage error message to set
     * @return this
     */
    CLIOptions& error(const std::string& errorMessage) {
        this->errorMessage = errorMessage;
        return *this;
    }

private:
    // name of the program being executed
    // argv[0], usually "mictool"
    std::string program;

    // special options
    bool requestHelp = false;
    bool requestVersion = false;
    std::string descriptionText;
    std::string errorMessage;

    // CLI options
    std::string inputFile;
    std::string outputFile;
    OutputType outputType = OutputType::UNKNOWN;
    std::string docTitle = "";

    // set to true if the program should print no error messages
    bool beQuiet = false;
};

#endif /* _MICTOOL_CLI_OPTIONS_H_ */
