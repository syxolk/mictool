#ifndef _MICTOOL_HTML_H_
#define _MICTOOL_HTML_H_

#include <fstream>
#include "mpr.h"
#include "mpr_writer.h"

class MPRWriterHTML : public MPRWriter {
	public:
		MPRWriterHTML() {};
		bool writeMPR(std::ofstream& stream, MPRFile& mpr);
};

#endif /* _MICTOOL_HTML_H_ */
