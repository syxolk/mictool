#include <sstream>
#include <gtest/gtest.h>
#include <util/util.h>

TEST(Utils, parseHexDigit) {
	ASSERT_EQ(-1, Utils::parseHexDigit(0));
	ASSERT_EQ(-1, Utils::parseHexDigit('-'));
	ASSERT_EQ(-1, Utils::parseHexDigit('0' - 1));
	ASSERT_EQ(-1, Utils::parseHexDigit('9' + 1));
	ASSERT_EQ(-1, Utils::parseHexDigit('a' - 1));
	ASSERT_EQ(-1, Utils::parseHexDigit('f' + 1));
	ASSERT_EQ(-1, Utils::parseHexDigit('A' - 1));
	ASSERT_EQ(-1, Utils::parseHexDigit('F' + 1));

	// test 0 - 9
	for(int i = 0; i <= 9; i++) {
		EXPECT_EQ(i, Utils::parseHexDigit(i + '0'));
	}

	// test a - z and A - Z
	for(int i = 10; i < 16; i++) {
		EXPECT_EQ(i, Utils::parseHexDigit(i - 10 + 'a')) << "Input: " << (char)(i-10+'a') << " Output: " << i;
		EXPECT_EQ(i, Utils::parseHexDigit(i - 10 + 'A')) << "Input: " << (char)(i-10+'A') << " Output: " << i;
	}
}

TEST(Utils, extractFilename) {
	EXPECT_EQ("file", Utils::extractFilename("~/path/file.cpp"));
	EXPECT_EQ("file", Utils::extractFilename("~/file.cpp"));
	EXPECT_EQ("file", Utils::extractFilename("~/file."));
	EXPECT_EQ("file", Utils::extractFilename("~/file"));
	EXPECT_EQ("file", Utils::extractFilename("/file"));
	EXPECT_EQ("file", Utils::extractFilename("file"));
	EXPECT_EQ("", Utils::extractFilename(""));
}

TEST(Utils, extractFileExtension) {
	EXPECT_EQ("cpp", Utils::extractFileExtension("~/path/file.cpp"));
	EXPECT_EQ("cpp", Utils::extractFileExtension("~/file.cpp"));
	EXPECT_EQ("", Utils::extractFileExtension("~/file."));
	EXPECT_EQ("", Utils::extractFileExtension("~/file"));
	EXPECT_EQ("", Utils::extractFileExtension("/file"));
	EXPECT_EQ("", Utils::extractFileExtension("file"));
	EXPECT_EQ("", Utils::extractFileExtension(""));
}

TEST(Utils, replaceAll) {
	std::string text("xaxax");
	Utils::replaceAll(text, "a", "b");
	ASSERT_EQ("xbxbx", text) << "simple replacement a -> b";

	Utils::replaceAll(text, "xb", "-");
	ASSERT_EQ("--x", text) << "replace with shorter string xb -> -";

	Utils::replaceAll(text, "x", "samba");
	ASSERT_EQ("--samba", text) << "replace with longer string x -> samba";

	Utils::replaceAll(text, "a", "");
	ASSERT_EQ("--smb", text) << "replace with empty string a -> \"\"";

	Utils::replaceAll(text, "", "a");
	ASSERT_EQ("--smb", text) << "replace an empty string with something \"\" -> a";
}

TEST(Utils, intToString) {
	EXPECT_EQ("-1", Utils::intToString(-1));
	EXPECT_EQ("0", Utils::intToString(0));
	EXPECT_EQ("1", Utils::intToString(1));
	EXPECT_EQ("1234", Utils::intToString(1234));
}

TEST(Utils, hexToInt) {
	EXPECT_EQ(0, Utils::hexToInt("0"));
	EXPECT_EQ(10, Utils::hexToInt("A"));
	EXPECT_EQ(11, Utils::hexToInt("b"));
	EXPECT_EQ(4660, Utils::hexToInt("1234"));
	EXPECT_EQ(43981, Utils::hexToInt("ABCD"));
	EXPECT_EQ(-43981, Utils::hexToInt("-ABCD"));
}

TEST(Utils, safeGetlineLinux) {
	std::istringstream is(
		"line1\n"
		"line2"
	);
	std::string line;

	if(Utils::safeGetline(is, line)) {
		EXPECT_EQ("line1", line);
	} else {
		FAIL() << "Could not read first line";
	}

	if(Utils::safeGetline(is, line)) {
		EXPECT_EQ("line2", line);
	} else {
		FAIL() << "Could not read second line";
	}

	if(Utils::safeGetline(is, line)) {
		FAIL() << "Can read a third line which is not there";
	} else {
		SUCCEED();
	}
}

TEST(Utils, safeGetlineWindows) {
	std::istringstream is(
		"line1\r\n"
		"line2"
	);
	std::string line;

	if(Utils::safeGetline(is, line)) {
		EXPECT_EQ("line1", line);
	} else {
		FAIL() << "Could not read first line";
	}

	if(Utils::safeGetline(is, line)) {
		EXPECT_EQ("line2", line);
	} else {
		FAIL() << "Could not read second line";
	}

	if(Utils::safeGetline(is, line)) {
		FAIL() << "Can read a third line which is not there";
	} else {
		SUCCEED();
	}
}

