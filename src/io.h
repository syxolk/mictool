#ifndef _MICTOOL_IO_H_
#define _MICTOOL_IO_H_

#include <iostream>
#include <bitset>
#include <string>
#include "mpr.h"
#include "mpr_reader.h"

/**
 * Currently the only implementation of MPRReader.
 * Reads and parses MPR files of version 4.
 *
 * @author Hans Kirchner
 */
class MPRReaderV4 : public MPRReader {
	public:
		/**
		 * Empty constructor
		 */
		MPRReaderV4() {};

		/**
		 * Read a version 4 MPR file from the stream and set
		 * the attributes of the given mprFile accordingly.
		 *
		 * @return false if parsing failed
		 */
		bool readMPR(std::istream& stream, MPRFile& mprFile);
	private:
		// functions to print errors
		void errorUnexpected(const std::string& expected, const std::string& found);
		void errorEOF(const std::string& expected);
		void errorCantParseTooShort(const std::string& line);
		void errorDontKnowWhatToDo(const std::string& line);

		// parse a single set of 80 bit as a micro line
		void parseMicroBitset(const std::string& str, std::bitset<80>& bits);

		// reads a single safely (and more portable) from the input stream
		std::istream& safe_getline(std::istream& is, std::string& str);

		// each parsing mode corresponds to a sector in the MPR file
		enum ParsingMode {
			UNKNOWN, MI_PROGRAM, MA_PROGRAM, REGISTER, IP
		};
};

#endif /* _MICTOOL_IO_H_ */

