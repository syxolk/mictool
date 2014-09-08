#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "io.h"
#include "util.h"

void errorUnexpected(const char* expected, const char* found);
void errorEOF(const char* expected);
void parseMicroBitset(const std::string& str, std::bitset<80>& bits);

// Helper function that removes '\r' from lines when
// reading Windows files on Linux.
std::istream& safe_getline(std::istream& is, std::string& str) {
  getline(is, str);
  if(str.length() > 0 && str.back() == '\r') {
    str.resize(str.length() - 1);
  }
  return is;
}

enum ParsingMode {
  UNKNOWN, MI_PROGRAM, MA_PROGRAM, REGISTER, IP
};

bool readFile(const char* path, std::vector<micro_line>& lines, std::vector<ram_cell>& ram_cells) {
  std::string line;

  // open the file
  std::ifstream file(path, std::ios::in);

  if(file.is_open()) {

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
      if(line.compare("mikroprogramm:") == 0) {
        mode = MI_PROGRAM;
      } else if(line.compare("maschinenprogramm:") == 0) {
        mode = MA_PROGRAM;
      } else if(line.compare("register:") == 0) {
        mode = REGISTER;
      } else if(line.compare("befehlszaehler:") == 0) {
        mode = IP;
      } else if(mode == UNKNOWN) {
        std::cout << "Don't know what to do with line: " << line << std::endl;
      } else if(mode == MI_PROGRAM) {
        size_t line_length = line.length();

        if(line_length < 33) {
          std::cout << "Can't parse line, too short: " << line << std::endl;
          continue;
        }

        micro_line ml;

        //ml.number = stoi(line.substr(0, 3), NULL, 16);
        sscanf(line.substr(0, 3).c_str(), "%x", &ml.number);
        if(line_length > 34) {
          ml.name = line.substr(4, line_length - 34);
        } else {
          ml.name = "";
        }
        parseMicroBitset(line.substr(line_length - 30, 30), ml.bits);

        lines.push_back(ml);
      } else if(mode == MA_PROGRAM) {
        size_t line_length = line.length();

        if(line_length == 4) {
          ram_cell cell;
          memcpy(&cell.data, line.c_str(), 5);

          ram_cells.push_back(cell);
        }
      }
    }

    file.close();
    return true;
  } else {
    std::cout << "Unable to open file: " << path  << std::endl;
    return false;
  }
}

void errorUnexpected(const char* expected, const char* found) {
  std::cout << "Error: expected " << expected << " but found " << found << std::endl;
}

void errorEOF(const char* expected) {
  std::cout << "Error: expected " << expected << "but reached EOF";
}

void parseMicroBitset(const std::string& str, std::bitset<80>& bits) {
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
