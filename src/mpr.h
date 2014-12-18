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

class MicroLine {
private:
	int lineNumber;
	std::string name;
	std::bitset<80> bits;
public:
	MicroLine(int lineNumber, const std::string& name, const std::bitset<80>& bits) :
			lineNumber(lineNumber), name(name), bits(bits) {
	}
	int getLineNumber() const;
	std::string getName() const;
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
	int getInt(int fromBit, int toBit) const;
};

class RamCell {
private:
	std::string data;
public:
	RamCell(const std::string& data) :
			data(data) {
	}
	std::string getData() const {
		return data;
	}
	bool couldHaveAnOpcode() const;
	int getOpCode() const;
};

class MPRFile {
private:
	std::string name;
	std::vector<MicroLine> micLines;
	std::vector<RamCell> ramCells;
public:
	MPRFile(const std::string& name) :
			 name(name) {
	}
	const std::vector<MicroLine>& getMicroLines() const {
		return micLines;
	}
	std::vector<MicroLine>& getMicroLines() {
		return micLines;
	}
	const std::vector<RamCell>& getRamCells() const {
		return ramCells;
	}
	std::vector<RamCell>& getRamCells() {
		return ramCells;
	}
	std::string getName() const {
		return name;
	}
	std::string getMicroLineByLineNumber(int lineNumber) const;
};

#endif /* _MICTOOL_MPR_H_ */
