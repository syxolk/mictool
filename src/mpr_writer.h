#ifndef _MICTOOL_MPR_WRITER_H
#define _MICTOOL_MPR_WRITER_H

#include <fstream>
#include "mpr.h"

class MPRWriter {
	public:
		MPRWriter() {};
		virtual bool writeMPR(std::ofstream& stream, MPRFile& title) =0;
};

#endif
