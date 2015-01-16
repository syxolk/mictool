#include <gtest/gtest.h>
#include <bitset>
#include <mpr/mpr.h>

TEST(MicroLine, allMethods) {
	std::bitset<80> bits;
	bits[0] = 1;
	bits[1] = 1; bits[3] = 1; bits[4] = 1; bits[5] = 1;
	bits[19] = 1; bits[20] = 1; bits[21] = 1; bits[22] = 1;
	bits[29] = 1; bits[30] = 1;
	bits[37] = 1; bits[38] = 1; bits[39] = 1; bits[40] = 1;
	bits[49] = 1;
	bits[55] = 1;
	bits[74] = 1;
	bits[79] = 1;
	
	MicroLine mic(0, "IFETCH", bits);
	
	// check simple members
	EXPECT_EQ(0, mic.getLineNumber());
	EXPECT_EQ("IFETCH", mic.getName());
	
	// check contents of bitset
	EXPECT_EQ("R", mic.getMWE());
	EXPECT_EQ("H", mic.getIR_LD());
	EXPECT_EQ("E", mic.getBZ_EA());
	EXPECT_EQ("H", mic.getBZ_INC());
	EXPECT_EQ("H", mic.getBZ_ED());
	EXPECT_EQ("H", mic.getBZ_LD());
	
	EXPECT_EQ(0, mic.getBAR());
	EXPECT_EQ("CONT", mic.getJump());
	EXPECT_EQ("PS", mic.getConditionCodeEnable());
	
	EXPECT_EQ("signed <gt>", mic.getStatusRegisterTest());
	EXPECT_EQ("-", mic.getStatusRegisterTestContext());
	
	EXPECT_EQ("H", mic.getCEMachine());
	EXPECT_EQ("H", mic.getCEMicro());
	
	EXPECT_EQ("RSL", mic.getShifts());
	EXPECT_EQ("CI0", mic.getCINMux());
	
	EXPECT_EQ("H", mic.getYMuxDB());
	EXPECT_EQ("H", mic.getYMuxAB());
	EXPECT_EQ("MR", mic.getRBAddrContext());
	EXPECT_EQ(1, mic.getRBAddr());
	EXPECT_EQ("IR", mic.getRAAddrContext());
	EXPECT_EQ(0, mic.getRAAddr());
	
	EXPECT_EQ("NOP", mic.getDestination());
	EXPECT_EQ("ADD", mic.getFunction());
	EXPECT_EQ("AB", mic.getSource());
	
	EXPECT_EQ(0, mic.getConstant());
	EXPECT_EQ("D", mic.getKMux());
	EXPECT_EQ("LDM", mic.getInterrupt());
	EXPECT_EQ("Dis", mic.getInterruptFlag());
}

