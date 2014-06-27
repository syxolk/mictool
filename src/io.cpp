#include <iostream>
#include <fstream>
#include <vector>
#include "io.h"
using namespace std;

void errorUnexpected(const char* expected, const char* found);
void errorEOF(const char* expected);
void parseMicroBitset(const string& str, bitset<80>& bits);

// Helper function that removes \r when from lines when
// reading Windows files on Linux.
istream& safe_getline(istream& is, string& str) {
  getline(is, str);
  if(str.length() > 0 && str.back() == '\r') {
    str.resize(str.length() - 1);
  }
  return is;
}

enum ParsingMode {
  UNKNOWN, MI_PROGRAM, MA_PROGRAM, REGISTER, IP
};

void readFile(const char* path, vector<micro_line>& lines) {
  string line;
  
  // open the file
  ifstream file(path, ios::in);

  if(file.is_open()) {
    
    // check file identifier
    if( safe_getline(file, line) ) {
      if(line.compare("version4") != 0) {
        errorUnexpected("version4", line.c_str());
        return;
      }
    } else {
      errorEOF("version4");
      return;
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
        cout << "Don't know what to do with line: " << line << endl;
      } else if(mode == MI_PROGRAM) {
        size_t line_length = line.length();
        
        if(line_length < 33) {
          cout << "Can't parse line, too short: " << line << endl;
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
      }
    }

    file.close();
  } else {
    cout << "Unable to open file: " << path  << endl;
  }
}

void errorUnexpected(const char* expected, const char* found) {
  cout << "Error: expected " << expected << " but found " << found << endl;
}

void errorEOF(const char* expected) {
  cout << "Error: expected " << expected << "but reached EOF"; 
}

int parseHexDigit(char c) {
  if(c >= '0' && c <= '9') {
    return c - '0';
  } else if(c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  } else if(c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  } else {
    cout << "Unexpected char: " << c << endl;
    return 0;
  }
}

void parseMicroBitset(const string& str, bitset<80>& bits) {
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
