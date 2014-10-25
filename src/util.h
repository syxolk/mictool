#ifndef _MICTOOL_UTIL_H_
#define _MICTOOL_UTIL_H_

int parseHexDigit(char c);

const std::string extractFilename(const std::string& path);

const std::string extractFileExtension(const std::string& path);

const std::string htmlspecialchars(const std::string& data);
const std::string replaceHtmlCommands(const std::string& data);

const std::string escapeLatex(const std::string& data);
const std::string replaceLatexCommands(const std::string& data);

void replaceAll(std::string& str, const std::string& needle, const std::string& replacement);

std::string intToString(int value);

#endif /* _MICTOOL_UTIL_H_ */
