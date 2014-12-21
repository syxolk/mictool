/*
 * mpr.cpp
 *
 *  Created on: 19.10.2014
 *      Author: Hans Kirchner
 */

#include "mpr.h"
#include "util.h"

// string constants
const char *MI_INTERRUPT[] = { "LDM", "RDM", "CLM", "STM", "BCLM", "BSTM",
		"LDST", "RDST", "ENI", "DISI", "RDVC", "CLI", "CLMR", "CLMB", "CLVC",
		"MCL" };
const char *MI_SRC[] = { "AQ", "AB", "ZQ", "ZB", "ZA", "DA", "DQ", "DZ" };
const char *MI_FUNC[] = { "ADD", "SUBR", "SUBS", "OR", "AND", "NOTRS", "EXOR",
		"EXNOR" };
const char *MI_DEST[] = { "QREG", "NOP", "RAMA", "RAMF", "RAMQD", "RAMD",
		"RAMQU", "RAMU" };
const char *MI_CIN_MUX[] = { "CI0", "CI1", "CIX", "CIC" };
const char *MI_TEST_WHAT[] = { "-", "<micro>SR", "MSR", "-" };
const char *MI_TEST[] = { "signed <gt>", "signed <le>", "signed <ge>",
		"signed <lt>", "<ne>", "=", "Not overflow", "Overflow",
		"<not> (C <or> Z)", "C <or> Z", "unsigned <lt>", "unsigned <ge>",
		"unsigned <gt>", "unsigned <le>", "not N", "N" };
const char *MI_JUMP[] = { "JZ", "CJS", "JMAP", "CJP", "PUSH", "JSRP", "CJV",
		"JRP", "RFCT", "RPCT", "CRTN", "CJPP", "LDCT", "LOOP", "CONT", "TWB" };
const char *MI_SHIFT[] = { "RSL", "RSH", "RSCONI", "RSDH", "RSDC", "RSDN",
		"RSDL", "RSDCO", "RSRCO", "RSRCIO", "RSR", "RSDIC", "RSDRCI", "RSDRCO",
		"RSDXOR", "RSDR", "LSLCO", "LSHCO", "LSL", "LSH", "LSDLCO", "LSDHCO",
		"LSDL", "LSDH", "LSCRO", "LSCRIO", "LSR", "LSLICI", "LSDCIO", "LSDRCO",
		"LSDCI", "LDSR" };

int MicroLine::getLineNumber() const {
	return lineNumber;
}

std::string MicroLine::getName() const {
	return name;
}

std::bitset<80> MicroLine::getBits() const {
	return bits;
}

/**
 * computes the integer from the bitset in them given interval
 */
int MicroLine::getInt(int fromBit, int toBit) const {
	int result = 0;

	for (int i = toBit; i >= fromBit; i--) {
		result = (result << 1) + bits[i];
	}

	return result;
}

bool MicroLine::isDefaultValue(std::string value) {
	return value == "H" || value == "R";
}

std::string MicroLine::getInterruptFlag() const {
	return bits[79] ? "Dis" : "IE";
}

std::string MicroLine::getInterrupt() const {
	return MI_INTERRUPT[getInt(75, 78)];
}

std::string MicroLine::getKMux() const {
	return bits[74] ? "D" : "K";
}

int MicroLine::getConstant() const {
	return getInt(58, 73);
}

std::string MicroLine::getSource() const {
	return MI_SRC[getInt(55, 57)];
}

std::string MicroLine::getFunction() const {
	return MI_FUNC[getInt(52, 54)];
}

std::string MicroLine::getDestination() const {
	return MI_DEST[getInt(49, 51)];
}

int MicroLine::getRAAddr() const {
	return getInt(45, 48);
}

std::string MicroLine::getRAAddrContext() const {
	return bits[44] ? "MR" : "IR";
}

int MicroLine::getRBAddr() const {
	return getInt(40, 43);
}

std::string MicroLine::getRBAddrContext() const {
	return bits[39] ? "MR" : "IR";
}

std::string MicroLine::getYMuxAB() const {
	return bits[38] ? "H" : "AB";
}

std::string MicroLine::getYMuxDB() const {
	return bits[37] ? "H" : "DB";
}

std::string MicroLine::getCINMux() const {
	return MI_CIN_MUX[getInt(35, 36)];
}

std::string MicroLine::getShifts() const {
	return MI_SHIFT[getInt(31, 34) + (bits[50] << 4)];
}

std::string MicroLine::getCEMicro() const {
	return bits[30] ? "H" : "L";
}

std::string MicroLine::getCEMachine() const {
	return bits[29] ? "H" : "L";
}

std::string MicroLine::getStatusRegisterTestContext() const {
	return MI_TEST_WHAT[getInt(27, 28)];
}

std::string MicroLine::getStatusRegisterTest() const {
	return MI_TEST[getInt(23, 26)];
}

std::string MicroLine::getConditionCodeEnable() const {
	return bits[22] ? "PS" : "C";
}

std::string MicroLine::getJump() const {
	return MI_JUMP[getInt(18, 21)];
}

int MicroLine::getBAR() const {
	return getInt(6, 17);
}

std::string MicroLine::getBZ_LD() const {
	return bits[5] ? "H" : "L";
}

std::string MicroLine::getBZ_ED() const {
	return bits[4] ? "H" : "E";
}

std::string MicroLine::getBZ_INC() const {
	return bits[3] ? "H" : "I";
}

std::string MicroLine::getBZ_EA() const {
	return bits[2] ? "H" : "E";
}

std::string MicroLine::getIR_LD() const {
	return bits[1] ? "H" : "L";
}

std::string MicroLine::getMWE() const {
	return bits[0] ? "R" : "W";
}

bool RamCell::couldHaveAnOpcode() const {
	return !(data[0] == '0' && data[1] == '0');
}

int RamCell::getOpCode() const {
	return Utils::parseHexDigit(data[0]) * 16 + Utils::parseHexDigit(data[1]);
}

/**
 * find the micro line with the given line number
 * and return its name
 * if nothing is found returns null
 */
std::string MPRFile::getMicroLineByLineNumber(int lineNumber) const {
	for (auto& line : micLines) {
		if (line.getLineNumber() == lineNumber) {
			return line.getName();
		}
	}

	return "";
}
