#include <iostream>
#include "debug.h"

bool MPRWriterDebug::writeMPR(std::ostream& stream, const MPRFile& mprFile) {
	stream << mprFile.getName() << "\n\n";

	for (auto& line : mprFile.getMicroLines()) {
		stream << line.getLineNumber() << " : " << line.getName()
				<< std::endl;
		stream << " " << line.getBits() << std::endl;
	}

	for (auto& cell : mprFile.getRamCells()) {
		stream << cell.getData() << std::endl;
	}
	
	return true;
}

