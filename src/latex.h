#ifndef _MICTOOL_LATEX_H_
#define _MICTOOL_LATEX_H_

#include <string>
#include <fstream>
#include "mpr.h"
#include "mpr_writer.h"

class MPRWriterLaTeX : public MPRWriter {
	public:
		MPRWriterLaTeX() {};
		bool writeMPR(std::ostream& stream, const MPRFile& mprFile);
	private:
		void writeMulticolumn(std::ostream& file, std::string value, int colspan);
		void writeRotatedMulticolumn(std::ostream& file, std::string value, int colspan);
		void writeMulticolumnWithAmp(std::ostream& file, std::string value, int colspan);
		void writeMulticolumnWithAmp(std::ostream& file, std::string value);

		struct ColumnDescriptor {
			const char* name;
			const int colspan;
		};
};

#endif /* _MICTOOL_LATEX_H_ */
