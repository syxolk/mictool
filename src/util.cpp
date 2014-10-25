#include <iostream>
#include <sstream>
#include "util.h"

// parses a single hexadecimal digit
// and returns the corresponding value
int parseHexDigit(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	} else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	} else {
		std::cout << "Unexpected char: " << c << std::endl;
		return 0;
	}
}

// extracts the filename out of a relative or absolute path
// file extension is stripped as well
// example: ~/file.cpp -> file
const std::string extractFilename(const std::string& path) {
	int slashIndex = path.find_last_of("/\\") + 1;
	// if the slash character is not found the function will return -1
	// -> slashIndex + 1 will be zero -> it takes the string from the beginning

	int dotIndex = path.find_first_of('.', slashIndex);

	// if there is no dot in the filename then just take everything
	if (dotIndex == -1) {
		dotIndex = path.length();
	}

	return path.substr(slashIndex, dotIndex - slashIndex);
}

const std::string extractFileExtension(const std::string& path) {
	int dotIndex = path.find_last_of(".");

	if (dotIndex == -1) {
		return "";
	}

	return path.substr(dotIndex + 1);
}

// works like PHP htmlspecialchars
// -> http://de1.php.net/manual/en/function.htmlspecialchars.php
// implementation is from stackoverflow
// -> http://stackoverflow.com/questions/5665231/most-efficient-way-to-escape-xml-html-in-c-string
const std::string htmlspecialchars(const std::string& data) {
	std::string buffer;
	buffer.reserve(data.size());
	for (size_t pos = 0; pos != data.size(); ++pos) {
		switch (data[pos]) {
		case '&':
			buffer.append("&amp;");
			break;
		case '\"':
			buffer.append("&quot;");
			break;
		case '\'':
			buffer.append("&apos;");
			break;
		case '<':
			buffer.append("&lt;");
			break;
		case '>':
			buffer.append("&gt;");
			break;
		default:
			buffer.append(&data[pos], 1);
			break;
		}
	}
	return buffer;
}

const std::string replaceHtmlCommands(const std::string& data) {
	std::string buffer(data);

	replaceAll(buffer, "<ge>", "&ge;");
	replaceAll(buffer, "<gt>", "&gt;");
	replaceAll(buffer, "<le>", "&le;");
	replaceAll(buffer, "<lt>", "&lt;");
	replaceAll(buffer, "<ne>", "&ne;");
	replaceAll(buffer, "<not>", "&not;");
	replaceAll(buffer, "<or>", "&or;");
	replaceAll(buffer, "<micro>", "&micro;");

	return buffer;
}

// http://tex.stackexchange.com/questions/34580/escape-character-in-latex
const std::string escapeLatex(const std::string& data) {
	std::string buffer;
	buffer.reserve(data.size());
	for (size_t pos = 0; pos != data.size(); pos++) {
		switch (data[pos]) {
		case '&':
		case '%':
		case '$':
		case '#':
		case '_':
		case '{':
		case '}':
			buffer.append("\\").append(&data[pos], 1);
			break;
		case '~':
			buffer.append("\\textasciitilde{}");
			break;
		case '^':
			buffer.append("\\textasciicircum{}");
			break;
		case '\\':
			buffer.append("\\textbackslash{}");
			break;
		default:
			buffer.append(&data[pos], 1);
			break;
		}
	}
	return buffer;
}

const std::string replaceLatexCommands(const std::string& data) {
	std::string buffer(data);

	replaceAll(buffer, "<ge>", "$\\geq$");
	replaceAll(buffer, "<gt>", "$>$");
	replaceAll(buffer, "<le>", "$\\leq$");
	replaceAll(buffer, "<lt>", "$<$");
	replaceAll(buffer, "<ne>", "$\\neg$");
	replaceAll(buffer, "<not>", "$\\ne$");
	replaceAll(buffer, "<or>", "$\\lor$");
	replaceAll(buffer, "<micro>", "$\\mu$");

	return buffer;
}

// Replaces all occurences of a string in a string with another string
// http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
void replaceAll(std::string& str, const std::string& needle, const std::string& replacement) {
	if(needle.empty()) return;

	size_t startPos = 0;
	while((startPos = str.find(needle, startPos)) != std::string::npos) {
		str.replace(startPos, needle.length(), replacement);
		startPos += replacement.length();
	}
}

std::string intToString(int value) {
	std::ostringstream ss;
	ss << value;
	return ss.str();
}
