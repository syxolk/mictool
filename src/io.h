#ifndef _MICTOOL_IO_H_
#define _MICTOOL_IO_H_

#include<bitset>
#include<vector>

struct micro_line {
  int number;
  std::string name;
  std::bitset<80> bits;
};

struct ram_cell {
  char data[5];
};

void readFile(const char* path, std::vector<micro_line>& lines, std::vector<ram_cell>& ram_cells);

#endif /* _MICTOOL_IO_H_ */
