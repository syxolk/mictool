#ifndef _MICTOOL_LATEX_H_
#define _MICTOOL_LATEX_H_

#include <string>
#include <iostream>
#include "mpr.h"
#include "mpr_writer.h"

/**
 * @brief Implementation of MPRWriter that outputs MPR files as LaTeX.
 *
 * Note: Latex source will be outputted not an already rendered
 * PDF. You need to call pdflatex (or something similar) on the
 * output file.
 *
 * Special Latex characters will be escaped in the output.
 *
 * @author Hans Kirchner
 */
class MPRWriterLaTeX : public MPRWriter {
	public:
		/**
		 * @brief Empty constructor
		 */
		MPRWriterLaTeX() {};

		/**
		 * @brief Write the given MPR file to the output stream as a Latex document.
		 *
		 * @param stream the method will write into this stream
		 * @param mprFile this MPRFile instance will be written
		 * @return always true
		 */
		bool writeMPR(std::ostream& stream, const MPRFile& mprFile);
	private:
		// internal helper functions for writing Latex
		void writeMulticolumn(std::ostream& file, const std::string& value, int colspan);
		void writeRotatedMulticolumn(std::ostream& file, const std::string& value, int colspan);
		void writeMulticolumnWithAmp(std::ostream& file, const std::string& value, int colspan);
		void writeMulticolumnWithAmp(std::ostream& file, const std::string& value);

		// escaping and encoding functions
		std::string escapeLatex(const std::string& data);
		std::string replaceLatexCommands(const std::string& data);

		struct ColumnDescriptor {
			const char* name;
			const int colspan;
		};
};

#endif /* _MICTOOL_LATEX_H_ */

