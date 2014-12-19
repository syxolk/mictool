#ifndef _MICTOOL_IO_H_
#define _MICTOOL_IO_H_

#include <iostream>
#include <bitset>
#include <string>
#include "mpr.h"
#include "mpr_reader.h"

class MPRReaderV4 : public MPRReader {
	public:
		bool readMPR(std::istream& stream, MPRFile& mprFile);
	private:
		void errorUnexpected(const std::string& expected, const std::string& found);
		void errorEOF(const std::string& expected);
		void errorCantParseTooShort(const std::string& line);
		void errorDontKnowWhatToDo(const std::string& line);

		void parseMicroBitset(const std::string& str, std::bitset<80>& bits);
		std::istream& safe_getline(std::istream& is, std::string& str);

		enum ParsingMode {
			UNKNOWN, MI_PROGRAM, MA_PROGRAM, REGISTER, IP
		};
};

#endif /* _MICTOOL_IO_H_ */
