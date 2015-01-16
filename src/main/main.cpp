#include <cstdlib>
#include <cli/cli.h>

// entrypoint to mictool
int main(int argc, char* argv[]) {
	// create new command line parser
	CLI cli(argc, argv);

	// parse command line arguments
	if(! cli.parse()) {
		return EXIT_FAILURE;
	}

	// work on the input and print the results to the output
	if(! cli.work()) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

