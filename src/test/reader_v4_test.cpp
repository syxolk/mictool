#include <sstream>
#include <bitset>
#include <iostream>
#include <gtest/gtest.h>
#include <reader/v4/v4.h>
#include <mpr/mpr.h>

TEST(MPRReaderV4, readMPR) {
	std::istringstream text (
		"version4\n"
		"mikroprogramm:\n"
		"000 IFETCH 3b 00 78 60 60 00 82 00 00 84\n"
		"001 3d 00 78 60 60 00 82 00 00 84\n"
		"maschinenprogramm:\n"
		"0000-03ff\n"
		"0104\n"
		"0115"
	);

	std::ostream cerr(0);

	MPRReaderV4 reader;
	MPRFile mpr("test file 1");
	
	reader.readMPR(text, mpr, cerr);

	// check size of vectors
	ASSERT_EQ(2, mpr.getMicroLines().size());
	ASSERT_EQ(2, mpr.getRamCells().size());
	
	// check file name
	EXPECT_EQ("test file 1", mpr.getName());
	
	// check first micro line
	std::bitset<80> bits;
	bits[0] = 1;
	bits[1] = 1; bits[3] = 1; bits[4] = 1; bits[5] = 1;
	bits[19] = 1; bits[20] = 1; bits[21] = 1; bits[22] = 1;
	bits[29] = 1; bits[30] = 1;
	bits[37] = 1; bits[38] = 1;
	bits[49] = 1;
	bits[55] = 1;
	bits[74] = 1;
	bits[79] = 1;
	
	EXPECT_EQ(bits, mpr.getMicroLines()[0].getBits());
	
	// check micro line line numbers
	EXPECT_EQ(0, mpr.getMicroLines()[0].getLineNumber());
	EXPECT_EQ(1, mpr.getMicroLines()[1].getLineNumber());
	
	// check ram cells
	EXPECT_EQ("0104", mpr.getRamCells()[0].getData());
	EXPECT_EQ("0115", mpr.getRamCells()[1].getData());
}

