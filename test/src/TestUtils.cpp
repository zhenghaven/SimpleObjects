// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <memory>

#include <SimpleObjects/Utils.hpp>
#include <SimpleObjects/ToString.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestUtils, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestUtils, BoolToInt)
{
	// "This" is not bool
	std::unique_ptr<int> testIn1 = std::unique_ptr<int>(new int);
	EXPECT_TRUE(testIn1 != nullptr);
	bool testResBool = Internal::BoolToInt<std::unique_ptr<int>, int>::Convert(testIn1).get() != nullptr;
	int* testResPtr = Internal::BoolToInt<std::unique_ptr<int>, int>::Convert(testIn1).get();
	EXPECT_TRUE(testResBool);
	EXPECT_EQ(testResPtr, testIn1.get());

	// "This" is bool
	auto trConvert = Internal::BoolToInt<bool, int>::Convert(true);
	auto trType = std::is_same<decltype(trConvert), int>::value;
	auto faConvert = Internal::BoolToInt<bool, int>::Convert(false);
	auto faType = std::is_same<decltype(faConvert), int>::value;

	EXPECT_EQ(trConvert, 1);
	EXPECT_TRUE(trType);
	EXPECT_EQ(faConvert, 0);
	EXPECT_TRUE(faType);
}

GTEST_TEST(TestUtils, IfConstexpr)
{
	Internal::IfConstexpr<true>::Eval(
		[]() { EXPECT_TRUE(true); }, // This one should always run
		[]() { EXPECT_TRUE(false); }
	);

	Internal::IfConstexpr<false>::Eval(
		[]() { EXPECT_TRUE(false); },
		[]() { EXPECT_TRUE(true); } // This one should always run
	);
}

GTEST_TEST(TestUtils, ByteToHEX)
{
	{
		std::string expOut = "\\x7F";
		std::string testOut;

		Internal::ByteToHEX<true, char>(std::back_inserter(testOut), 0x7FU);

		EXPECT_EQ(testOut, expOut);
	}

	{
		std::string expOut = "F5";
		std::string testOut;

		Internal::ByteToHEX<false, char>(std::back_inserter(testOut), 0xF5U);

		EXPECT_EQ(testOut, expOut);
	}
}

GTEST_TEST(TestUtils, BytesToHEX)
{
	{
		std::vector<uint8_t> testIn =
			{ 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, };
		std::string expOut = "0x000102030405";
		std::string testOut;

		Internal::BytesToHEX<true, char>(
			std::back_inserter(testOut),
			testIn.begin(),
			testIn.end()
		);

		EXPECT_EQ(testOut, expOut);
	}

	{
		std::vector<uint8_t> testIn =
			{ 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU, };
		std::string expOut = "456789ABCDEF";
		std::string testOut;

		Internal::BytesToHEX<false, char>(
			std::back_inserter(testOut),
			testIn.begin(),
			testIn.end()
		);

		EXPECT_EQ(testOut, expOut);
	}
}
