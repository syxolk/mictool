#ifndef _MICTOOL_MPR_WRITER_H
#define _MICTOOL_MPR_WRITER_H

#include <fstream>
#include "mpr.h"

class MPRWriter {
	public:
		MPRWriter() {};
		virtual bool writeMPR(std::ofstream& stream, const MPRFile& file) =0;
};

#endif
