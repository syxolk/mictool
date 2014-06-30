#ifndef _MICTOOL_IO_H_
#define _MICTOOL_IO_H_

using namespace std;
#include<bitset>
#include <vector>

struct micro_line {
  int number;
  string name;
  bitset<80> bits;
};

struct ram_cell {
  char data[5];
};

void readFile(const char* path, vector<micro_line>& lines, vector<ram_cell>& ram_cells);

#endif /* _MICTOOL_IO_H_ */
