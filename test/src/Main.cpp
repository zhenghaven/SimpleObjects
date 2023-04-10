// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <SimpleObjects/RealNumTraits.hpp>

namespace SimpleObjects_Test
{
	size_t g_numOfTestFile = 0;
}

template<typename _T>
static void PrintIntType(const std::string& typeName)
{
	using namespace SimpleObjects;

	static constexpr const char* const sk_isUnderlying =
		RealNumTraits<_T>::sk_isRealNumUnderlyingType ?
		"RealNumT" :
		"!RealNumT";

	auto f = std::cout.flags();
	std::cout	<< std::setw(10)  << std::left  << typeName
				<< std::setw(0)  << " - "
				<< std::setw(10) << std::right << sk_isUnderlying
				<< std::setw(0)  << " - "
				<< std::setw(15) << std::left << RealNumTraits<_T>::sk_numTypeName()
				<< std::setw(0)  << " - "
				<< std::setw(20) << std::right << RealNumTraits<_T>::sk_primitiveName()
				<< std::setw(0)  << std::endl;
	std::cout.flags(f);
}

static void PrintIntTypes()
{
	PrintIntType<char    >("char");
	PrintIntType<uint8_t >("uint8_t");
	PrintIntType< int8_t >("int8_t");
	PrintIntType<uint16_t>("uint16_t");
	PrintIntType< int16_t>("int16_t");
	PrintIntType<uint32_t>("uint32_t");
	PrintIntType< int32_t>("int32_t");
	PrintIntType<uint64_t>("uint64_t");
	PrintIntType< int64_t>("int64_t");
	PrintIntType<size_t  >("size_t");
}

int main(int argc, char** argv)
{
	constexpr size_t EXPECTED_NUM_OF_TEST_FILE = 17;

	std::cout << "===== SimpleObjects test program =====" << std::endl;
	std::cout << std::endl;

	std::cout << "EXPECTED_NUM_OF_TEST_FILE = " << EXPECTED_NUM_OF_TEST_FILE << std::endl;
	std::cout << "__cplusplus = " << __cplusplus << std::endl;

	std::cout << std::endl;
	PrintIntTypes();

	std::cout << std::endl;
	std::cout << "===== SimpleObjects test start   =====" << std::endl;

	testing::InitGoogleTest(&argc, argv);
	int testRet = RUN_ALL_TESTS();

	if (SimpleObjects_Test::g_numOfTestFile != EXPECTED_NUM_OF_TEST_FILE)
	{
		std::cout << "********************************************************************************" << std::endl;
		std::cout << "***** WARNING: Expecting " << EXPECTED_NUM_OF_TEST_FILE;
		std::cout << " testing source files, but ";
		std::cout << SimpleObjects_Test::g_numOfTestFile << " were ran. *****" << std::endl;
		std::cout << "********************************************************************************" << std::endl;

		return -1;
	}

	return testRet;
}
