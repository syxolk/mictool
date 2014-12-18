#ifndef _MICTOOL_LATEX_H_
#define _MICTOOL_LATEX_H_

#include <fstream>
#include "mpr.h"
#include "mpr_writer.h"

class MPRWriterLaTeX : public MPRWriter {
	public:
		MPRWriterLaTeX() {};
		bool writeMPR(std::ofstream& stream, const MPRFile& mprFile);
};

#endif /* _MICTOOL_LATEX_H_ */
