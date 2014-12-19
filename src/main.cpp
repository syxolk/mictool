#include <cstdlib>
#include "cli.h"

int main(int argc, char* argv[]) {
	CLI cli(argc, argv);
	
	if(! cli.parse()) {
		return EXIT_FAILURE;
	}
	
	if(! cli.work()) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

