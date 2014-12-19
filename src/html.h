#ifndef _MICTOOL_HTML_H_
#define _MICTOOL_HTML_H_

#include <iostream>
#include "mpr.h"
#include "mpr_writer.h"

class MPRWriterHTML : public MPRWriter {
	public:
		MPRWriterHTML() {};
		bool writeMPR(std::ostream& stream, const MPRFile& mpr);
	private:
		void writeTD(std::ostream& file, std::string value, int colspan, bool checkDefault);
		void writeTDWithCheckDefault(std::ostream& file, std::string value);
		void writeTD(std::ostream& file, std::string value, int colspan);
		void writeTD(std::ostream& file, std::string value);

		struct ColumnDescriptor {
			const char* name;
			const int colspan;
		};
};

#endif /* _MICTOOL_HTML_H_ */
