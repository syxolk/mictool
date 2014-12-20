#ifndef _MICTOOL_HTML_H_
#define _MICTOOL_HTML_H_

#include <iostream>
#include "mpr.h"
#include "mpr_writer.h"

/*
 * MPRWriter implementation that outputs MPRFile's content
 * as a full HTML document wrapped in <html> ... </html>.
 *
 * Special HTML characters will be escaped in the output.
 *
 * @author Hans Kirchner
 */
class MPRWriterHTML : public MPRWriter {
	public:
		/*
		 * Constucts a new HTML writer.
		 */
		MPRWriterHTML() {};

		/*
		 * Write the given MPR file as a HTML document
		 * to the given output stream.
		 *
		 * @return always true
		 */
		bool writeMPR(std::ostream& stream, const MPRFile& mpr);
	private:
		// internal helper functions for writing HTML
		void writeTD(std::ostream& file, const std::string& value, int colspan, bool checkDefault);
		void writeTDWithCheckDefault(std::ostream& file, const std::string& value);
		void writeTD(std::ostream& file, const std::string& value, int colspan);
		void writeTD(std::ostream& file, const std::string& value);

		// escape and encoding functions
		std::string htmlspecialchars(const std::string& data);
		std::string replaceHtmlCommands(const std::string& data);

		struct ColumnDescriptor {
			const char* name;
			const int colspan;
		};
};

#endif /* _MICTOOL_HTML_H_ */

