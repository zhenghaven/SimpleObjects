#include <gtest/gtest.h>

namespace SimpleObjects_Test
{
	size_t g_numOfTestFile = 0;
}

int main(int argc, char** argv)
{
	constexpr size_t EXPECTED_NUM_OF_TEST_FILE = 12;

	std::cout << "===== SimpleObjects test program =====" << std::endl;
	std::cout << std::endl;

	std::cout << "EXPECTED_NUM_OF_TEST_FILE = " << EXPECTED_NUM_OF_TEST_FILE << std::endl;
	std::cout << "__cplusplus = " << __cplusplus << std::endl;

	std::cout << std::endl;
	std::cout << "===== SimpleObjects test start   =====" << std::endl;

	testing::InitGoogleTest(&argc, argv);
	int testRet = RUN_ALL_TESTS();

	if (SimpleObjects_Test::g_numOfTestFile != EXPECTED_NUM_OF_TEST_FILE)
	{
		std::cout << "********************************************************************************" << std::endl;
		std::cout << "***** WARNING: Expecting " << EXPECTED_NUM_OF_TEST_FILE;
		std::cout << " testing source files, but only ";
		std::cout << SimpleObjects_Test::g_numOfTestFile << " were ran. *****" << std::endl;
		std::cout << "********************************************************************************" << std::endl;

		return -1;
	}

	return testRet;
}
