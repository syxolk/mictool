#ifndef _MICTOOL_DEBUG_H_
#define _MICTOOL_DEBUG_H_

#include <fstream>
#include "mpr.h"
#include "mpr_writer.h"

class MPRWriterDebug : public MPRWriter {
	public:
		MPRWriterDebug() {};
		bool writeMPR(std::ofstream& stream, const MPRFile& mpr);
};

#endif /* _MICTOOL_DEBUG_H_ */

