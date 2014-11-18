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
	int getLineNumber();
	std::string getName();
	std::bitset<80> getBits();
	static bool isDefaultValue(std::string value);
	std::string getInterruptFlag();
	std::string getInterrupt();
	std::string getKMux();
	int getConstant();
	std::string getSource();
	std::string getFunction();
	std::string getDestination();
	int getRAAddr();
	std::string getRAAddrContext();
	int getRBAddr();
	std::string getRBAddrContext();
	std::string getYMuxAB();
	std::string getYMuxDB();
	std::string getCINMux();
	std::string getShifts();
	std::string getCEMicro();
	std::string getCEMachine();
	std::string getStatusRegisterTestContext();
	std::string getStatusRegisterTest();
	std::string getConditionCodeEnable();
	std::string getJump();
	int getBAR();
	std::string getBZ_LD();
	std::string getBZ_ED();
	std::string getBZ_INC();
	std::string getBZ_EA();
	std::string getIR_LD();
	std::string getMWE();
protected:
	int getInt(int fromBit, int toBit);
};

class RamCell {
private:
	std::string data;
public:
	RamCell(const std::string& data) :
			data(data) {
	}
	std::string getData() {
		return data;
	}
	bool couldHaveAnOpcode();
	int getOpCode();
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
	std::vector<MicroLine>& getMicroLines() {
		return micLines;
	}
	std::vector<RamCell>& getRamCells() {
		return ramCells;
	}
	std::string getName() {
		return name;
	}
	std::string getMicroLineByLineNumber(int lineNumber);
};

#endif /* _MICTOOL_MPR_H_ */
