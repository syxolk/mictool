#ifndef _io_h_
#define _io_h_

using namespace std;
#include<bitset>
#include <vector>

struct micro_line {
	int number;
	string name;
	bitset<80> bits;
};

void readFile(const char* path, vector<micro_line>& lines);
void errorUnexpected(const char* expected, const char* found);
void errorEOF(const char* expected);
void parseMicroBitset(const string& str, bitset<80>& bits);

#endif /* _io_h_ */
