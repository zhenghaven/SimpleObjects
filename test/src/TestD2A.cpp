// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER
#include <SimpleObjects/Internal/rj_dtoa.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestD2A, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestD2A, Zeros) {
	static constexpr double testInput01 = -0.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput01, 10), "-0.0");
	static constexpr double testInput02 =  0.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput02, 10), "0.0");
}

GTEST_TEST(TestD2A, Grisu2Focus) {
	static constexpr double testInput01 =  1.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput01, 10), "1.0");
	static constexpr double testInput05 =  -1.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput05, 10), "-1.0");
	static constexpr double testInput06 =  -12.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput06, 10), "-12.0");
	static constexpr double testInput07 =  -123.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput07, 10), "-123.0");
	static constexpr double testInput08 =  -1234.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput08, 10), "-1234.0");
	static constexpr double testInput09 =  -12345.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput09, 10), "-12345.0");
	static constexpr double testInput10 =  -123456.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput10, 10), "-123456.0");
	static constexpr double testInput11 =  -1234567.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput11, 10), "-1234567.0");
	static constexpr double testInput12 =  -12345678.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput12, 10), "-12345678.0");
	static constexpr double testInput13 =  -123456789.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput13, 10), "-123456789.0");
	static constexpr double testInput14 =  -1234567891.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput14, 10), "-1234567891.0");
	static constexpr double testInput15 =  -12345678912.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput15, 10), "-12345678912.0");
	static constexpr double testInput16 =  -123456789123.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput16, 10), "-123456789123.0");
	static constexpr double testInput17 =  -1234567891234.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput17, 10), "-1234567891234.0");
}

GTEST_TEST(TestD2A, PrettifyFocus) {
	// case1: 12345e6 -> 12345000000
	static constexpr double testInput01_1 =  12345000000.0;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput01_1, 10), "12345000000.0");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput01_1, 10), "-12345000000.0");

	// case2.1: 1234567e-4 -> 123.4567
	static constexpr double testInput02_1 = 123.4567;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput02_1, 10), "123.4567");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput02_1, 10), "-123.4567");
	// case2.2: 1234567e-4 -> 123.4567 -> 123.45
	static constexpr double testInput02_2 = 123.4567;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput02_2, 2), "123.45");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput02_2, 2), "-123.45");
	// case2.3: 12345008e-5 -> 123.45008 -> 123.45
	static constexpr double testInput02_3 = 123.45008;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput02_3, 4), "123.45");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput02_3, 4), "-123.45");
	// case2.4: 1230007e-5 -> 123.0007 -> 123.0
	static constexpr double testInput02_4 = 123.0007;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput02_4, 3), "123.0");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput02_4, 3), "-123.0");
	// case2.5: 1234567e-4 -> 123.4567 -> 123.4
	static constexpr double testInput02_5 = 123.4567;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput02_5, 0), "123.4");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput02_5, 0), "-123.4");

	// case3.1: 1234e-4 -> 0.1234
	static constexpr double testInput03_1 = 0.1234;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput03_1, 10), "0.1234");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput03_1, 10), "-0.1234");
	// case3.2: 1234e-6 -> 0.001234
	static constexpr double testInput03_2 = 0.001234;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput03_2, 10), "0.001234");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput03_2, 10), "-0.001234");
	// case3.3: 1234e-6 -> 0.001234 -> 0.001
	static constexpr double testInput03_3 = 0.001234;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput03_3, 3), "0.001");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput03_3, 3), "-0.001");
	// case3.4: 1004e-6 -> 0.001004 -> 0.001
	static constexpr double testInput03_4 = 0.001004;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput03_4, 5), "0.001");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput03_4, 5), "-0.001");
	// case3.5: 1234e-4 -> 0.1234 -> 0.1
	static constexpr double testInput03_5 = 0.1234;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput03_5, 0), "0.1");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput03_5, 0), "-0.1");
	// case3.6: 123456789123456789123456789e-29 -> 0.001234567891234568
	static constexpr double testInput03_6 = 0.00123456789123456789123456789;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput03_6, 50), "0.001234567891234568");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput03_6, 50), "-0.001234567891234568");

	// Case 4 is removed since the maximum decimal place should not affect the eX format
	// // case4.1: 1234e-20 -> 1234e-20 -> 0.0
	// static constexpr double testInput04_1 = 1234e-20;
	// EXPECT_EQ(Internal::dtoa<std::string>(testInput04_1, 10), "0.0");
	// EXPECT_EQ(Internal::dtoa<std::string>(-testInput04_1, 10), "-0.0");
	// // case4.2: 1234e-20 -> 1234e-20 -> 0.0
	// static constexpr double testInput04_2 = 1234e-20;
	// EXPECT_EQ(Internal::dtoa<std::string>(testInput04_2, 0), "0.0");
	// EXPECT_EQ(Internal::dtoa<std::string>(-testInput04_2, 0), "-0.0");

	// case5.1: 1e-20 -> 1e-20
	static constexpr double testInput05_1 = 1e-20;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput05_1, 50), "1e-20");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput05_1, 50), "-1e-20");
	// case5.1: 1e20 -> 1e20
	static constexpr double testInput05_2 = 1e120;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput05_2, 50), "1e120");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput05_2, 50), "-1e120");
	// case5.1: 1e-9 -> 1e-9
	static constexpr double testInput05_3 = 1e-9;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput05_3, 50), "1e-9");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput05_3, 50), "-1e-9");

	// case6.1: 1e-20 -> 1e-20
	static constexpr double testInput06_1 = 1.12345e-20;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput06_1, 50), "1.12345e-20");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput06_1, 50), "-1.12345e-20");
	// case6.1: 1e20 -> 1e20
	static constexpr double testInput06_2 = 1.12345e120;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput06_2, 50), "1.12345e120");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput06_2, 50), "-1.12345e120");
	// case6.1: 1e-9 -> 1e-9
	static constexpr double testInput06_3 = 1.12345e-9;
	EXPECT_EQ(Internal::dtoa<std::string>(testInput06_3, 50), "1.12345e-9");
	EXPECT_EQ(Internal::dtoa<std::string>(-testInput06_3, 50), "-1.12345e-9");
}

GTEST_TEST(TestD2A, BackInserter) {
	static constexpr double testInput06_3 = 1.12345e-9;

	std::string outputStr;
	Internal::dtoa(std::back_inserter(outputStr), testInput06_3, 50);
	EXPECT_EQ(outputStr, "1.12345e-9");

	outputStr = "";
	Internal::dtoa(std::back_inserter(outputStr), -testInput06_3, 50);
	EXPECT_EQ(outputStr, "-1.12345e-9");
}
