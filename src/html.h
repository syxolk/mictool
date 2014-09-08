#ifndef _MICTOOL_HTML_H_
#define _MICTOOL_HTML_H_

#include <vector>
#include "io.h"

bool writeHTML(const char* path, const std::string& title, std::vector<micro_line>& lines, std::vector<ram_cell>& ram_cells);

#endif /* _MICTOOL_HTML_H_ */
