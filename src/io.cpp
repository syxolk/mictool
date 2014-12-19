#include <iostream>
#include <fstream>
#include <cstring>
#include "io.h"
#include "util.h"
#include "mpr.h"

// Helper function that removes '\r' from lines when
// reading Windows files on Linux.
std::istream& MPRReaderV4::safe_getline(std::istream& is, std::string& str) {
  getline(is, str);
  if(!str.empty() && str.back() == '\r') {
    str.resize(str.length() - 1);
  }
  return is;
}

bool MPRReaderV4::readMPR(std::istream& file, MPRFile& mprFile) {
  std::string line;

    // check file identifier
    if( safe_getline(file, line) ) {
      if(line.compare("version4") != 0) {
        errorUnexpected("version4", line.c_str());
        return false;
      }
    } else {
      errorEOF("version4");
      return false;
    }

    // start parsing
    ParsingMode mode = UNKNOWN;

    while( safe_getline(file, line) ) {

      // check for special lines
      if(line == "mikroprogramm:") {
        mode = MI_PROGRAM;
      } else if(line == "maschinenprogramm:") {
        mode = MA_PROGRAM;
      } else if(line == "register:") {
        mode = REGISTER;
      } else if(line == "befehlszaehler:") {
        mode = IP;
      } else if(mode == UNKNOWN) {
        errorDontKnowWhatToDo(line);
      } else if(mode == MI_PROGRAM) {
        size_t line_length = line.length();

        if(line_length < 33) {
          errorCantParseTooShort(line);
          continue;
        }

        int mlLineNumber;
        std::string mlName;
        std::bitset<80> mlBits;

        //ml.number = stoi(line.substr(0, 3), NULL, 16);
        sscanf(line.substr(0, 3).c_str(), "%x", &mlLineNumber);
        if(line_length > 34) {
          mlName = line.substr(4, line_length - 34);
        } else {
          mlName = "";
        }
        parseMicroBitset(line.substr(line_length - 30, 30), mlBits);

        MicroLine ml(mlLineNumber, mlName, mlBits);
        mprFile.getMicroLines().push_back(ml);
      } else if(mode == MA_PROGRAM) {
        size_t line_length = line.length();

        if(line_length == 4) {
          RamCell cell(line);

          mprFile.getRamCells().push_back(cell);
        }
      }
    }

    return true;
}

// outputs an unexpected value in case of an error
void MPRReaderV4::errorUnexpected(const std::string& expected, const std::string& found) {
	std::cerr << "Error: expected " << expected << " but found " << found << std::endl;
}

// outputs an "end of file" error
void MPRReaderV4::errorEOF(const std::string& expected) {
	std::cerr << "Error: expected " << expected << "but reached EOF";
}

void MPRReaderV4::errorCantParseTooShort(const std::string& line) {
	std::cerr << "Can't parse line, too short: " << line << std::endl;
}

void MPRReaderV4::errorDontKnowWhatToDo(const std::string& line) {
	std::cerr << "Don't know what to do with line: " << line << std::endl;
}

// parses the micro bitset part of the MPR files
void MPRReaderV4::parseMicroBitset(const std::string& str, std::bitset<80>& bits) {
  int i, bitPos = 0, hex;
  for(i = 1; i < 30; i+=3) {
    hex = parseHexDigit(str[i + 1]);
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1;

    hex = parseHexDigit(str[i]);
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1;
  }
}

