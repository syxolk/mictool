#include <iostream>
#include <fstream>
#include "io.h"
using namespace std;

void readFile(const char* path) {
  string line;
  ifstream file(path, ios::in);

  if(file.is_open()) {
    if( getline(file, line) ) {
      if(line.compare("version4") != 0) {
        errorUnexpected("version4", line.c_str());
        return;
      }
    } else {
      errorEOF("version4");
      return;
    }

    if( getline(file, line) ) {
      if(line.compare("mikroprogramm:") != 0) {
        errorUnexpected("mikroprogramm:", line.c_str());
        return;
      }
    } else {
      errorEOF("mikroprogramm:");
      return;
    }

    /*string mic_line;
    string mic_name;
    string mic_program;*/
    size_t line_length;

    while( getline(file, line) ) {
      if( line.compare("maschinenprogramm:") == 0 || line.compare("register:") == 0 ) {
        break;
      }

      line_length = line.length();
      
      if(line_length < 34) {
        cout << "Can't parse line: too short: " << line << endl;
        continue;
      }

      string mic_line = line.substr(0, 3);
      string mic_name = line.substr(4, line_length - 34);
      string mic_program = line.substr(line_length - 30, 30);
      bitset<80> mic_bits;
      parseMicroBitset(mic_program, mic_bits);

      cout << "Line: " << mic_line << " Name: " << mic_name << " Program: " << mic_program << endl;
      cout << "Bits: " << mic_bits << endl;
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
