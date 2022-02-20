#include <gtest/gtest.h>

#include <memory>

#include <SimpleObjects/Utils.hpp>

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