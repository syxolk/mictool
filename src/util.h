#ifndef _MICTOOL_UTIL_H_
#define _MICTOOL_UTIL_H_

int parseHexDigit(char c);

const std::string extractFilename(const std::string& path);

const std::string htmlspecialchars(const std::string& data);

std::string intToString(int value);

#endif /* _MICTOOL_UTIL_H_ */
