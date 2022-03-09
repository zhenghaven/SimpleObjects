// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.



#include <gtest/gtest.h>

#include <algorithm>

#include <SimpleObjects/ConstSequence.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
} // namespace SimpleObjects_Test

GTEST_TEST(TestConstSequence, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

GTEST_TEST(TestConstSequence, ArrayLen)
{
	using namespace Internal;
	static_assert(ArrayLen("TEST") == 5,
		"Implementation Error");
	static_assert(ArrayLen("TEST_STRING") == 12,
		"Implementation Error");

	static_assert(ArrayLen({0, 1, 2, 3, 4}) == 5,
		"Implementation Error");
	static_assert(ArrayLen({0, 1, 2, 3, 4, 5, 6, 7}) == 8,
		"Implementation Error");
}

template<
	typename KDataType,
	typename ExpKDataType,
	typename ExpDataType,
	size_t ExpDataSize>
void TestDataArray(const ExpDataType (&expData)[ExpDataSize])
{
	static_assert(std::is_same<KDataType, ExpKDataType >::value,
		"Implementation Error");
	static_assert(
		KDataType::sk_size == ExpDataSize,
		"Implementation Error");

	static constexpr auto testArray2_a = KDataType::sk_data();
	EXPECT_EQ(testArray2_a.size(), ExpDataSize);
	EXPECT_TRUE(std::equal(
		testArray2_a.begin(), testArray2_a.end(),
		std::begin(expData)));

	static const auto& testArray2_c = KDataType::sk_cData();
	EXPECT_EQ(ExpDataSize,
		static_cast<size_t>(std::distance(
			std::begin(testArray2_c),
			std::end(testArray2_c))));
	EXPECT_TRUE(std::equal(
		std::begin(testArray2_c), std::end(testArray2_c),
		std::begin(expData)));
}

GTEST_TEST(TestConstSequence, DataArray)
{
	static constexpr int testArray1[] = {0, 1, 2, 3, 4, 5};

	using KArrayType1 = SIMOBJ_KARRAY(testArray1);
	TestDataArray<
		KArrayType1,
		DataSeq<int, 0, 1, 2, 3, 4, 5>
	>(testArray1);

	static constexpr long testArray2[] = {7, 6, 5, 4, 3, 2, 1, 0};
	using KArrayType2 = SIMOBJ_KARRAY(testArray2);
	TestDataArray<
		KArrayType2,
		DataSeq<long, 7, 6, 5, 4, 3, 2, 1, 0>
	>(testArray2);
}

template<typename KStrType, typename ExpKStrType, size_t ExpStrLen>
void TestStringArray(const char (&expStr)[ExpStrLen])
{
	static_assert(std::is_same<KStrType, ExpKStrType>::value,
		"Implementation Error");
	static_assert(KStrType::sk_size ==
		(ExpStrLen - 1),
		"Implementation Error");

	static constexpr auto testArray1_a = KStrType::sk_data();
	EXPECT_EQ(
		testArray1_a.size(),
		static_cast<size_t>(std::distance(
			std::begin(expStr),
			std::end(expStr))) - 1);
	EXPECT_TRUE(std::equal(
		testArray1_a.begin(), testArray1_a.end(),
		std::begin(expStr)));

	static const auto& testArray1_c = KStrType::sk_cData();
	EXPECT_EQ(
		(ExpStrLen - 1),
		static_cast<size_t>(std::distance(
			std::begin(testArray1_c),
			std::end(testArray1_c))));
	EXPECT_TRUE(std::equal(
		std::begin(testArray1_c), std::end(testArray1_c),
		std::begin(expStr)));

	static const auto& testStr1_c = KStrType::sk_cstr();
	EXPECT_EQ(
		(ExpStrLen),
		static_cast<size_t>(std::distance(
			std::begin(testStr1_c),
			std::end(testStr1_c))));
	EXPECT_TRUE(std::equal(
		std::begin(testStr1_c), std::end(testStr1_c),
		std::begin(expStr)));

	static const auto& testStr1_s = KStrType::sk_str();
	EXPECT_EQ((ExpStrLen - 1), testStr1_s.size());
	EXPECT_EQ(testStr1_s, std::string(expStr));
}

GTEST_TEST(TestConstSequence, StringArray)
{
	TestStringArray<
		SIMOBJ_KSTR("test"),
		StrSeq<'t', 'e', 's', 't'>
	>("test");

	TestStringArray<
		SIMOBJ_KSTR("test string"),
		StrSeq<'t', 'e', 's', 't', ' ',
			's', 't', 'r', 'i', 'n', 'g'>
	>("test string");
}

GTEST_TEST(TestConstSequence, Misc)
{
	static constexpr int testArray[] = {0, 1, 2, 3, 4, 5};
	static_assert(testArray[1] == 1,
		"Implementation Error");
	static_assert(testArray[3] == 3,
		"Implementation Error");
	static_assert(testArray[5] == 5,
		"Implementation Error");
}
