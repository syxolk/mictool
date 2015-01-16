#include <gtest/gtest.h>
#include <mpr/mpr.h>

TEST(RamCell, getData) {
	const RamCell cell("1e34");
	EXPECT_EQ("1e34", cell.getData());
}

TEST(RamCell, couldHaveAnOpcode) {
	const RamCell cellYes("1e34");
	EXPECT_TRUE(cellYes.couldHaveAnOpcode());
	
	const RamCell cellYes2("1034");
	EXPECT_TRUE(cellYes2.couldHaveAnOpcode());
	
	const RamCell cellYes3("0134");
	EXPECT_TRUE(cellYes3.couldHaveAnOpcode());
	
	const RamCell cellNo("0034");
	EXPECT_FALSE(cellNo.couldHaveAnOpcode());
}

TEST(RamCell, getOpCode) {
	const RamCell cell("a121");
	EXPECT_EQ(161, cell.getOpCode());
}

