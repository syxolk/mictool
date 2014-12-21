#ifndef _MICTOOL_UTIL_H_
#define _MICTOOL_UTIL_H_

#include <string>

/**
 * Utility class with static functions that are used by more
 * than one class.
 *
 * @author Hans Kirchner
 */
class Utils {
	public:
		/**
		 * @brief Parses a single hexadecimal digit an return its decimal value.
		 *
		 * @param c hexadecimal character
		 * @retrun -1 in case of an error otherwise the value of the hexadecimal value
		 */
		static int parseHexDigit(char c);

		/**
		 * @brief Extracts the filename out of a relative or absolute path.
		 *
		 * The file extension is stripped as well.
		 * Example: ~/file.cpp -> file
		 * @param path the path where the file name should be extracted
		 * @return extracted file name
		 */
		static std::string extractFilename(const std::string& path);

		/**
		 * @brief Extracts the file extension out of a relative or absolute path.
		 *
		 * Example: ~/file.cpp -> cpp
		 * @param path the path where the file extension should be extracted
		 * @return extracted file extension
		 */
		static std::string extractFileExtension(const std::string& path);

		/**
		 * @brief Replaces all occurences of a string in a string with another string.
		 *
		 * http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
		 * @param str the string to change
		 * @param needle the string to look for
		 * @param replacement the string to replace for the found needle
		 */
		static void replaceAll(std::string& str, const std::string& needle, const std::string& replacement);

		/**
		 * @brief Convert an integer into its decimal representation.
		 *
		 * @param value the integer to convert
		 * @return the converted decimal representation
		 */
		static std::string intToString(int value);
};

#endif /* _MICTOOL_UTIL_H_ */

