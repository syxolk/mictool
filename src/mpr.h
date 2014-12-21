/*
 * mpr.h
 *
 *  Created on: 19.10.2014
 *      Author: Hans Kirchner
 */

#ifndef _MICTOOL_MPR_H_
#define _MICTOOL_MPR_H_

#include <vector>
#include <bitset>

/**
 * @brief Instances of this class represent a single line in a micro program.
 *
 * The main content lays in the 80 bits long bitset. Helper methods
 * retrieve the human readable content of this bitset.
 *
 * @author Hans Kirchner
 */
class MicroLine {
private:
	int lineNumber;
	std::string name;
	std::bitset<80> bits;
public:
	/**
	 * @brief Construct a new micro line from the given parameters.
	 *
	 * @param lineNumber the line number as a decimal integer
	 * @param name the name given in JMic
	 * @param bits 80 bits long bitset, essentially the real content
	 */
	MicroLine(int lineNumber, const std::string& name, const std::bitset<80>& bits) :
			lineNumber(lineNumber), name(name), bits(bits) {
	}

	/**
	 * @brief Returns the line of this micro line.
	 *
	 * @return the line number given in the constructor
	 */
	int getLineNumber() const;

	/**
	 * @brief Returns the name of this micro line.
	 *
	 * @return the name given in the constructor
	 */
	std::string getName() const;

	/**
	 * @brief Returns the 80 bits long bitset.
	 *
	 * @return the real content of this micro line
	 */
	std::bitset<80> getBits() const;

	static bool isDefaultValue(std::string value);

	std::string getInterruptFlag() const;
	std::string getInterrupt() const;
	std::string getKMux() const;
	int getConstant() const;
	std::string getSource() const;
	std::string getFunction() const;
	std::string getDestination() const;
	int getRAAddr() const;
	std::string getRAAddrContext() const;
	int getRBAddr() const;
	std::string getRBAddrContext() const;
	std::string getYMuxAB() const;
	std::string getYMuxDB() const;
	std::string getCINMux() const;
	std::string getShifts() const;
	std::string getCEMicro() const;
	std::string getCEMachine() const;
	std::string getStatusRegisterTestContext() const;
	std::string getStatusRegisterTest() const;
	std::string getConditionCodeEnable() const;
	std::string getJump() const;
	int getBAR() const;
	std::string getBZ_LD() const;
	std::string getBZ_ED() const;
	std::string getBZ_INC() const;
	std::string getBZ_EA() const;
	std::string getIR_LD() const;
	std::string getMWE() const;
protected:
	/**
	 * Computes an integer from the given bit range
	 * in the bitset and returns the result.
	 */
	int getInt(int fromBit, int toBit) const;
};

/**
 * @brief Instances of this class represent a single line in the RAM (random access memory).
 *
 * Such a line can be a data line or an opcode.
 *
 * @author Hans Kirchner
 */
class RamCell {
private:
	std::string data;
public:
	/**
	 * @brief Create a new ram cell with the given data applied.
	 *
	 * @param data the data will be usually 4 bytes long
	 */
	RamCell(const std::string& data) :
			data(data) {
	}

	/**
	 * @brief Returns the data.
	 *
	 * @return the data given in the constructor
	 */
	std::string getData() const {
		return data;
	}

	/**
	 * @brief Check if this ram cell could have an opcode in the first two bytes.
	 *
	 * @return true if the first two bytes are both zero otherwise false
	 */
	bool couldHaveAnOpcode() const;

	/**
	 * @brief Compute and return the opcode if one is found.
	 *
	 * @return the first two bytes combined to a decimal integer
	 */
	int getOpCode() const;
};

/**
 * @brief Instances of this class represent a single MPR file with multiple micro lines and ram cells.
 *
 * The MPR file is also given a name.
 *
 * @author Hans Kirchner
 */
class MPRFile {
private:
	std::string name;
	std::vector<MicroLine> micLines;
	std::vector<RamCell> ramCells;
public:
	/**
	 * @brief Construct a new MPR file with the given name.
	 *
	 * @see MPRWriter
	 * @param name also called title, can be used by MPRWriters
	 */
	MPRFile(const std::string& name) :
			 name(name) {
	}

	/**
	 * @brief Returns a const vector of the micro lines owned by this MPR file.
	 *
	 * @return vector of MicroLines
	 */
	const std::vector<MicroLine>& getMicroLines() const {
		return micLines;
	}

	/**
	 * @brief Returns a non-const vector of the micro lines owned by this MPR file.
	 *
	 * @return vector of MicroLines
	 */
	std::vector<MicroLine>& getMicroLines() {
		return micLines;
	}

	/**
	 * @brief Returns a const vector of the ram cells owned by this MPR file.
	 *
	 * @return vector of RamCells
	 */
	const std::vector<RamCell>& getRamCells() const {
		return ramCells;
	}

	/**
	 * @brief Returns a non-const vector of the rams cells owned by this MPR file.
	 *
	 * @return vector of RamCells
	 */
	std::vector<RamCell>& getRamCells() {
		return ramCells;
	}

	/**
	 * @brief Returns the name given to this MPR file in the constructor.
	 *
	 * @return name or title of this MPRFile
	 */
	std::string getName() const {
		return name;
	}

	/**
	 * @brief Returns the micro line name associated with the given line number.
	 *
	 * @param lineNumber line number to look for
	 * @return name of the found line number
	 */
	std::string getMicroLineByLineNumber(int lineNumber) const;
};

#endif /* _MICTOOL_MPR_H_ */

