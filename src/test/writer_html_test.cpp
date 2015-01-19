#include <sstream>
#include <gtest/gtest.h>
#include <writer/html/html.h>
#include <mpr/mpr.h>
#include <util/util.h>

TEST(MPRWriterHTML, writeMPR) {
	MPRFile mpr("test file");
	std::stringstream out;
	
	MPRWriterHTML writer;
	bool returnCode = writer.writeMPR(out, mpr);
	
	EXPECT_TRUE(returnCode) << "Will never return false";
	
	std::string line;
	
	if(Utils::safeGetline(out, line)) {
		EXPECT_EQ("<!doctype html>", line) << "First line should be HTML 5 Doctype";
	} else {
		FAIL() << "Nothing was written.";
	}
	
	// TODO check with HTML validator
}

