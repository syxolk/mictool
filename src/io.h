#ifndef _io_h_
#define _io_h_

using namespace std;
#include<bitset>

void readFile(const char* path);
void errorUnexpected(const char* expected, const char* found);
void errorEOF(const char* expected);
void parseMicroBitset(const string& str, bitset<80>& bits);

#endif /* _io_h_ */
