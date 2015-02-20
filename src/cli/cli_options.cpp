#include <sstream>
#include <cli/cli_options.h>
#include <util/util.h>

bool CLIOptions::parse(int argc, const char *argv[]) {
    if(argc >= 1) {
        program = argv[0];
    }

    // create namespace alias (shortcut)
    namespace po = boost::program_options;

    // initialize description object
    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "Print help messages")
        ("version,v", "Print version info")
        ("quiet,q", "Do not print any error messages")
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

    std::ostringstream ossDesc;
    ossDesc << desc;
    descriptionText = ossDesc.str();

    // parse command line
    po::variables_map vm;

    try {
        po::store(po::command_line_parser(argc, argv).
              options(allOptions).positional(poDesc).run(), vm);

        if(vm.count("help")) {
           requestHelp = true;
            return true;
        }

        po::notify(vm);
    } catch(boost::program_options::error& e) {
        std::ostringstream ossError;
        ossError << "ERROR: " << e.what();
        errorMessage = ossError.str();
        return false;
    }

    if(vm.count("version")) {
        requestVersion = true;
        return true;
    }

    if(vm.count("quiet")) {
        beQuiet = true;
    }

    if(vm.count("output")) {
        outputFile = vm["output"].as<std::string>();
    }

    if(vm.count("input")) {
        inputFile = vm["input"].as<std::string>();
    }

    // check for title option
    // if there is no title option then extract the title from the input
    // or output file
    if(vm.count("title")) {
        docTitle = vm["title"].as<std::string>();
    } else if(! isReadFromStdIn()) {
        docTitle = Utils::extractFilename(inputFile);
    } else if(! isWriteToStdOut()) {
        docTitle = Utils::extractFilename(outputFile);
    }

    if(vm.count("html")) {
        outputType = OutputType::HTML;
    } else if(vm.count("latex")) {
        outputType = OutputType::LATEX;
    } else if(vm.count("debug")) {
        outputType = OutputType::DEBUG;
    } else if(! isWriteToStdOut()) { // if no output type option is given but an output file
        std::string extension = Utils::extractFileExtension(outputFile);
        std::transform(extension.begin(), extension.end(), extension.begin(), tolower);

        if(extension == "html" || extension == "htm") {
            outputType = OutputType::HTML;
        } else if(extension == "tex") {
            outputType = OutputType::LATEX;
        } else if(extension == "dbg" || extension == "debug") {
            outputType = OutputType::DEBUG;
        }
    }

    return true;
}
