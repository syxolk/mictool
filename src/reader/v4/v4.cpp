#include <iostream>
#include <fstream>
#include <cstring>
#include <reader/v4/v4.h>
#include <util/util.h>
#include <mpr/mpr.h>

bool MPRReaderV4::readMPR(std::istream& file, MPRFile& mprFile, std::ostream& err) {
  std::string line;

    // check file identifier
    if( Utils::safeGetline(file, line) ) {
      if(line.compare("version4") != 0) {
        errorUnexpected(err, "version4", line.c_str());
        return false;
      }
    } else {
      errorEOF(err, "version4");
      return false;
    }

    // start parsing
    ParsingMode mode = UNKNOWN;

    while( Utils::safeGetline(file, line) ) {

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
        errorDontKnowWhatToDo(err, line);
      } else if(mode == MI_PROGRAM) {
        size_t line_length = line.length();

        if(line_length < 33) {
          errorCantParseTooShort(err, line);
          continue;
        }

        int mlLineNumber;
        std::string mlName;
        std::bitset<80> mlBits;

        //ml.number = stoi(line.substr(0, 3), NULL, 16);
        //sscanf(line.substr(0, 3).c_str(), "%x", &mlLineNumber);
        mlLineNumber = Utils::hexToInt(line.substr(0, 3));
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
void MPRReaderV4::errorUnexpected(std::ostream& err, const std::string& expected, const std::string& found) {
	err << "Error: expected " << expected << " but found " << found << std::endl;
}

// outputs an "end of file" error
void MPRReaderV4::errorEOF(std::ostream& err, const std::string& expected) {
	err << "Error: expected " << expected << "but reached EOF" << std::endl;
}

void MPRReaderV4::errorCantParseTooShort(std::ostream& err, const std::string& line) {
	err << "Can't parse line, too short: " << line << std::endl;
}

void MPRReaderV4::errorDontKnowWhatToDo(std::ostream& err, const std::string& line) {
	err << "Don't know what to do with line: " << line << std::endl;
}

// parses the micro bitset part of the MPR files
void MPRReaderV4::parseMicroBitset(const std::string& str, std::bitset<80>& bits) {
  int i, bitPos = 0, hex;
  for(i = 1; i < 30; i+=3) {
    hex = Utils::parseHexDigit(str[i + 1]);
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1;

    hex = Utils::parseHexDigit(str[i]);
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1; hex >>= 1;
    bits[bitPos++] = hex & 1;
  }
}

