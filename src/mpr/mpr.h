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
 * @see http://www.lrr.in.tum.de/~eti/Praktikum/DasBuch.pdf
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

	/**
	 * @brief Check if the micro line value is a default (unchanged).
	 *
	 * @return true if equals 'H' or 'R'
	 */
	static bool isDefaultValue(std::string value);

	/**
	 * @brief Status of the interrupt flag, either Dis or IE
	 */
	std::string getInterruptFlag() const;

	/**
	 * @brief Type of interrupt
	 */
	std::string getInterrupt() const;

	/**
	 * @brief Status of K-multiplexer, either D or K
	 */
	std::string getKMux() const;

	/**
	 * @brief 16 bit constant value
	 */
	int getConstant() const;

	/**
	 * @brief Source of the operation, e.g. AB, ZB
	 */
	std::string getSource() const;

	/**
	 * @brief Function to execute, e.g. ADD, SUBR
	 */
	std::string getFunction() const;

	/**
	 * @brief Destination of the function result, e.g. RAMA, RAMF
	 */
	std::string getDestination() const;

	/**
	 * @brief Register for RA
	 */
	int getRAAddr() const;

	/**
	 * @brief Context of getRAAddr(), either MR or IR
	 */
	std::string getRAAddrContext() const;

	/**
	 * @brief Register for RB
	 */
	int getRBAddr() const;

	/**
	 * @brief Context of getRBAddr(), either MR or IR
	 */
	std::string getRBAddrContext() const;

	/**
	 * @brief Enable address bus Y multiplexer, either H or AB
	 */
	std::string getYMuxAB() const;

	/**
	 * @brief Enable data bus Y multiplexer, either H or DB
	 */
	std::string getYMuxDB() const;

	/**
	 * @brief Special information for function execution, e.g. CI0, CI1
	 */
	std::string getCINMux() const;

	/**
	 * @brief Bit shift operations
	 */
	std::string getShifts() const;

	/**
	 * @brief Enable setting of micro status flags
	 */
	std::string getCEMicro() const;

	/**
	 * @brief Enable setting of machine status flags
	 */
	std::string getCEMachine() const;

	/**
	 * @brief Test machine or micro status flags
	 */
	std::string getStatusRegisterTestContext() const;

	/**
	 * @brief Test function, e.g. signed lower than
	 */
	std::string getStatusRegisterTest() const;

	/**
	 * @brief Enable condition code flag, either PS or C
	 */
	std::string getConditionCodeEnable() const;

	/**
	 * @brief Jump or continue function
	 */
	std::string getJump() const;

	/**
	 * @brief Jump destination or additional jump information
	 */
	int getBAR() const;

	/**
	 * @brief Load program counter from data bus
	 */
	std::string getBZ_LD() const;

	/**
	 * @brief Write program counter to data bus
	 */
	std::string getBZ_ED() const;

	/**
	 * @brief Increment program counter by 1
	 */
	std::string getBZ_INC() const;

	/**
	 * @brief Write program counter on address bus
	 */
	std::string getBZ_EA() const;

	/**
	 * @brief Load data from data bus into instruction register
	 */
	std::string getIR_LD() const;

	/**
	 * @brief Memory write enable, can be W or R
	 */
	std::string getMWE() const;
protected:
	/**
	 * @brief Computes an integer from the given bit range
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

