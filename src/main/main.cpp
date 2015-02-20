#include <cstdlib>
#include <iostream>
#include <cli/cli_options.h>
#include <cli/cli.h>

// entrypoint to mictool
int main(int argc, char* argv[]) {
	try {
		// create new command line parser
        CLIOptions options;

        bool parseResult = options.parse(argc, (const char**) argv);

        CLI cli(options);

        bool workResult = cli.work();

        if(!parseResult || !workResult) {
            return EXIT_FAILURE;
        }
	} catch (std::exception& e) {
		std::cerr << "Unhandled Exception reached the top of main: "
			  << e.what() << ", application will now exit" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

