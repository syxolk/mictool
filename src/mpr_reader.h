#ifndef _MICTOOL_MPR_READER_H
#define _MICTOOL_MPR_READER_H

#include <iostream>
#include "mpr.h"

class MPRReader {
	public:
		MPRReader() {};
		virtual ~MPRReader() {};
		virtual bool readMPR(std::istream& stream, MPRFile& file) =0;
};

#endif

