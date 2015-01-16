#ifndef _MICTOOL_HTML_H_
#define _MICTOOL_HTML_H_

#include <iostream>
#include <mpr/mpr.h>
#include <writer/mpr_writer.h>

/**
 * @brief Implementation of MPRWriter that outputs MPR files as HTML.
 *
 * The output is a full HTML document wrapped in html tags.
 * Special HTML characters will be escaped in the output.
 *
 * @author Hans Kirchner
 */
class MPRWriterHTML : public MPRWriter {
	public:
		/**
		 * @brief Constucts a new HTML writer.
		 */
		MPRWriterHTML() {};

		/**
		 * @brief Write the given MPR file as a HTML document to the given output stream.
		 *
		 * @param stream the method will write into this stream
		 * @param mprFile this MPR file will be written
		 * @return always true
		 */
		bool writeMPR(std::ostream& stream, const MPRFile& mprFile);
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

