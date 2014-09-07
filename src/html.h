#ifndef _MICTOOL_HTML_H_
#define _MICTOOL_HTML_H_

#include <vector>
#include "io.h"

void writeHTML(const char* path, std::vector<micro_line>& lines, std::vector<ram_cell>& ram_cells);

#endif /* _MICTOOL_HTML_H_ */
