// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <SimpleObjects/SimpleObjects.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

#include "CompareHelpers.hpp"

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestBytes, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestBytes, HashBytes)
{
	std::vector<uint8_t> val1 = { 0x00U, 0x00U, 0x00U, };
	std::vector<uint8_t> val2 = { 0x01U, 0x02U, 0x03U, };

	size_t h1 = Internal::hash_range(val1.cbegin(), val1.cend());
	size_t h2 = Internal::hash_range(val2.cbegin(), val2.cend());

	EXPECT_NE(h1, h2);
}

GTEST_TEST(TestBytes, Construction)
{
	// Default
	EXPECT_NO_THROW({
		Bytes().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Bytes());
		base.reset();
	});

	// std::vector, initializer_list
	std::vector<uint8_t> testInput_01 = { 0x00U, 0x01U, 0x02U, 0x03U, };
	std::vector<uint8_t> expValues_01 = { 0x00U, 0x01U, 0x02U, 0x03U, };
	EXPECT_EQ(Bytes(testInput_01.cbegin(), testInput_01.cend()).GetVal(),
		expValues_01);
	EXPECT_EQ(Bytes(testInput_01).GetVal(), expValues_01);
	EXPECT_EQ(Bytes(std::move(testInput_01)).GetVal(), expValues_01);
	EXPECT_EQ(Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, }).GetVal(), expValues_01);

	// Copy and Move
	Bytes cpSrc = { 0x00U, 0x01U, 0x02U, 0x03U, };
	EXPECT_EQ(Bytes(Bytes(cpSrc)).GetVal(), expValues_01);
}

GTEST_TEST(TestBytes, Assignment)
{
	Bytes testInput_01 = { 0x00U, 0x01U, 0x02U, 0x03U, };

	Bytes cpBytes;
	EXPECT_EQ(cpBytes.size(), 0);
	cpBytes = testInput_01;
	EXPECT_EQ(cpBytes, testInput_01);
	// We want to ensure assignment self is OK,
	// meanwhile to avoid compiler warning
	Bytes* cpBytesPtr = nullptr;
	cpBytesPtr = &cpBytes;
	cpBytes = *cpBytesPtr;
	EXPECT_EQ(cpBytes, testInput_01);

	Bytes mvBytes;
	EXPECT_EQ(mvBytes.size(), 0);
	mvBytes = std::move(cpBytes);
	EXPECT_EQ(mvBytes, testInput_01);
	Bytes* mvBytesPtr = nullptr;
	mvBytesPtr = &mvBytes;
	mvBytes = std::move(*mvBytesPtr);
	EXPECT_EQ(mvBytes, testInput_01);
}

GTEST_TEST(TestBytes, Category)
{
	static_assert(Bytes::sk_cat() == ObjCategory::Bytes, "Category failed.");
	EXPECT_EQ(Bytes::sk_cat(), ObjCategory::Bytes);

	Bytes val;
	EXPECT_EQ(val.GetCategory(), ObjCategory::Bytes);
}

GTEST_TEST(TestBytes, CategoryName)
{
	EXPECT_EQ(Bytes().GetCategoryName(), std::string("Bytes"));
}

GTEST_TEST(TestBytes, Miscs)
{
	// Is null
	EXPECT_FALSE(Bytes().IsNull());

	// Cast
	const auto kBytes = Bytes();
	EXPECT_NO_THROW(kBytes.AsBytes());
	EXPECT_THROW(kBytes.AsNull(),       TypeError);
	EXPECT_THROW(kBytes.AsRealNum(),    TypeError);
	EXPECT_THROW(kBytes.AsString(),     TypeError);
	EXPECT_THROW(kBytes.AsList(),       TypeError);
	EXPECT_THROW(kBytes.AsDict(),       TypeError);
	EXPECT_THROW(kBytes.AsStaticDict(), TypeError);
	EXPECT_NO_THROW(kBytes.AsHashable());

	EXPECT_NO_THROW(Bytes().AsBytes());
	EXPECT_THROW(Bytes().AsNull(),       TypeError);
	EXPECT_THROW(Bytes().AsRealNum(),    TypeError);
	EXPECT_THROW(Bytes().AsString(),     TypeError);
	EXPECT_THROW(Bytes().AsList(),       TypeError);
	EXPECT_THROW(Bytes().AsDict(),       TypeError);
	EXPECT_THROW(Bytes().AsStaticDict(), TypeError);
	EXPECT_NO_THROW(Bytes().AsHashable());

	// Copy
	static_assert(std::is_same<
		decltype(*Bytes().Copy(Bytes::Base::sk_null)),
		BytesBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Bytes({0, 12,}).Copy(Bytes::Base::sk_null), Bytes({0, 12,}));

	static_assert(std::is_same<
		decltype(*Bytes().Copy(Bytes::Base::Base::sk_null)),
		HashableBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Bytes({0, 12,}).Copy(Bytes::Base::Base::sk_null), Bytes({0, 12,}));

	static_assert(std::is_same<
		decltype(*Bytes().Copy(Bytes::Base::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Bytes({0, 12,}).Copy(Bytes::Base::Base::Base::sk_null), Bytes({0, 12,}));

	// Move
	auto mBytes = Bytes({0, 12,});

	static_assert(std::is_same<
		decltype(*Bytes().Move(Bytes::Base::sk_null)),
		BytesBaseObj&>::value, "Failed to test Move virtual func");
	mBytes = Bytes({0, 12,});
	EXPECT_EQ(*mBytes.Move(Bytes::Base::sk_null), Bytes({0, 12,}));
	EXPECT_EQ(mBytes.size(), 0);

	static_assert(std::is_same<
		decltype(*Bytes().Move(Bytes::Base::Base::sk_null)),
		HashableBaseObj&>::value, "Failed to test Move virtual func");
	mBytes = Bytes({0, 12,});
	EXPECT_EQ(*mBytes.Move(Bytes::Base::Base::sk_null), Bytes({0, 12,}));
	EXPECT_EQ(mBytes.size(), 0);

	static_assert(std::is_same<
		decltype(*Bytes().Move(Bytes::Base::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Move virtual func");
	mBytes = Bytes({0, 12,});
	EXPECT_EQ(*mBytes.Move(Bytes::Base::Base::Base::sk_null), Bytes({0, 12,}));
	EXPECT_EQ(mBytes.size(), 0);
}

GTEST_TEST(TestBytes, Setters)
{
	Bytes bytes1;
	EXPECT_NO_THROW(Bytes().Set(Bytes()));
	EXPECT_NO_THROW(Bytes().Set(bytes1));

	Null null1;
	EXPECT_THROW(Bytes().Set(Null()), TypeError);
	EXPECT_THROW(Bytes().Set(null1),  TypeError);

	EXPECT_THROW(Bytes().Set(static_cast<bool >(true)), TypeError);
	EXPECT_THROW(Bytes().Set(static_cast<uint8_t >(1)), TypeError);
	EXPECT_THROW(Bytes().Set(static_cast< int8_t >(1)), TypeError);
	EXPECT_THROW(Bytes().Set(static_cast<uint32_t>(1)), TypeError);
	EXPECT_THROW(Bytes().Set(static_cast< int32_t>(1)), TypeError);
	EXPECT_THROW(Bytes().Set(static_cast<uint64_t>(1)), TypeError);
	EXPECT_THROW(Bytes().Set(static_cast< int64_t>(1)), TypeError);
	EXPECT_THROW(Bytes().Set(static_cast<double>(1.0)), TypeError);
}

GTEST_TEST(TestBytes, Getters)
{
	EXPECT_FALSE(Bytes().IsTrue());
	EXPECT_TRUE( Bytes({ 0x00U, 0x12U, }).IsTrue());

	EXPECT_THROW(Bytes().AsCppUInt8() ,  TypeError);
	EXPECT_THROW(Bytes().AsCppInt8()  ,  TypeError);
	EXPECT_THROW(Bytes().AsCppUInt32(),  TypeError);
	EXPECT_THROW(Bytes().AsCppInt32() ,  TypeError);
	EXPECT_THROW(Bytes().AsCppUInt64(),  TypeError);
	EXPECT_THROW(Bytes().AsCppInt64() ,  TypeError);
	EXPECT_THROW(Bytes().AsCppDouble() , TypeError);
}

GTEST_TEST(TestBytes, Hash)
{
	std::vector<uint8_t> val1 = { 0x00U, 0x01U, 0x02U, 0x03U, };
	std::vector<uint8_t> val2 = { 0x00U, 0x01U, 0x02U, 0x06U, };

	size_t h1 = Internal::hash_range(val1.cbegin(), val1.cend());
	size_t h2 = Internal::hash_range(val2.cbegin(), val2.cend());

	EXPECT_EQ(Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, }).Hash(), h1);
	EXPECT_EQ(Bytes({ 0x00U, 0x01U, 0x02U, 0x06U, }).Hash(), h2);
	EXPECT_NE(Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, }).Hash(), h2);

	EXPECT_EQ(Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, }).Hash(),
		std::hash<Bytes>()(Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, })));
	EXPECT_EQ(Bytes({ 0x00U, 0x01U, 0x02U, 0x06U, }).Hash(),
		std::hash<Bytes>()(Bytes({ 0x00U, 0x01U, 0x02U, 0x06U, })));
	EXPECT_NE(Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, }).Hash(),
		std::hash<Bytes>()(Bytes({ 0x00U, 0x01U, 0x02U, 0x06U, })));
}

GTEST_TEST(TestBytes, At)
{
	const auto testBytes1 = Bytes({ 0x00U, 0x01U, 0x02U, });
	EXPECT_EQ(&testBytes1[1], &testBytes1[1]);
	EXPECT_EQ(&testBytes1[2], &testBytes1[1] + 1);
	EXPECT_EQ(testBytes1[2], testBytes1[1] + 1);
	EXPECT_EQ(testBytes1[2], 0x02U);

	EXPECT_THROW(testBytes1[testBytes1.size()], IndexError);

	auto testBytes2 = Bytes({ 0x00U, 0x01U, 0x02U, });
	EXPECT_EQ(&testBytes2[1], &testBytes2[1]);
	EXPECT_EQ(&testBytes2[2], &testBytes2[1] + 1);
	EXPECT_EQ(testBytes2[2], testBytes2[1] + 1);
	EXPECT_EQ(testBytes2[2], 0x02U);

	testBytes2[2] = 0x0AU;
	EXPECT_EQ(testBytes2[2], 0x0AU);

	EXPECT_THROW(testBytes2[testBytes2.size()] = 0xAAU, IndexError);
}

GTEST_TEST(TestBytes, PushPopBack)
{
	auto testBytes1 = Bytes({ 0x00U, 0x01U, });
	EXPECT_EQ(testBytes1, Bytes({ 0x00U, 0x01U, }));

	testBytes1.push_back(0x02U);
	EXPECT_EQ(testBytes1, Bytes({ 0x00U, 0x01U, 0x02U, }));

	testBytes1.pop_back();
	EXPECT_EQ(testBytes1, Bytes({ 0x00U, 0x01U, }));
}

GTEST_TEST(TestBytes, Append)
{
	auto testBytes1 = Bytes({ 0x00U, 0x01U, });
	auto testBytes2 = Bytes({ 0x02U, 0x03U, });
	EXPECT_EQ(testBytes1, Bytes({ 0x00U, 0x01U, }));

	testBytes1 += testBytes2;
	EXPECT_EQ(testBytes1, Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, }));
}

GTEST_TEST(TestBytes, Data)
{
	auto testBytes1 = Bytes({ 0x00U, 0x01U, });
	EXPECT_EQ(testBytes1.data(), &testBytes1[0]);
}

GTEST_TEST(TestBytes, Capacity)
{
	auto testBytes1 = Bytes({ 0x00U, 0x01U, });
	auto testBytes2 = Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, });

	EXPECT_EQ(testBytes1.size(), 2);
	EXPECT_EQ(testBytes2.size(), 4);

	testBytes1.reserve(20);
	EXPECT_EQ(testBytes1.size(), 2);

	testBytes1.resize(5);
	EXPECT_EQ(testBytes1, Bytes({ 0x00U, 0x01U, 0x00U, 0x00U, 0x00U, }));

	testBytes1.resize(3);
	EXPECT_EQ(testBytes1, Bytes({ 0x00U, 0x01U, 0x00U, }));
}

GTEST_TEST(TestBytes, Compare)
{
	EXPECT_TRUE(Bytes({ 0x00U, 0x01U, }) == Bytes({ 0x00U, 0x01U, }));
	EXPECT_TRUE(Bytes({ 0x00U, 0x01U, }) != Bytes({ 0x00U, 0x02U, }));
	EXPECT_TRUE(Bytes({ 0x00U, 0x01U, }) <  Bytes({ 0x00U, 0x02U, }));
	EXPECT_TRUE(Bytes({ 0x00U, 0x02U, }) >  Bytes({ 0x00U, 0x01U, }));
	EXPECT_TRUE(Bytes({ 0x00U, 0x01U, }) <= Bytes({ 0x00U, 0x02U, }));
	EXPECT_TRUE(Bytes({ 0x00U, 0x02U, }) >= Bytes({ 0x00U, 0x01U, }));
}

GTEST_TEST(TestBytes, BaseIsEqual)
{
	// Base object
	using BaseObjCmp = CompareTestHelpers<BaseObj>;

	EXPECT_TRUE(BaseObjCmp::Neq(Bytes(), Bool(true)));
	EXPECT_TRUE(BaseObjCmp::Neq(Bytes(), Null()));

	EXPECT_TRUE(BaseObjCmp::Neq(
		Bytes({ 0x01U, 0x02U, }), Bytes({ 0x01U, 0x03U, })));
	EXPECT_FALSE(BaseObjCmp::Neq(
		Bytes({ 0x01U, 0x02U, }), Bytes({ 0x01U, 0x02U, })));

	// Bytes base object
	using BytesBaseCmp = CompareTestHelpers<BytesBaseObj>;

	EXPECT_TRUE(BytesBaseCmp::Neq(
		Bytes({ 0x01U, 0x02U, }), Bytes({ 0x01U, 0x03U, })));
	EXPECT_FALSE(BytesBaseCmp::Neq(
		Bytes({ 0x01U, 0x02U, }), Bytes({ 0x01U, 0x02U, })));
}

GTEST_TEST(TestBytes, BaseCompare)
{
	// Base object
	using BaseObjCmp = CompareTestHelpers<BaseObj>;

	EXPECT_THROW(BaseObjCmp::Le(Bytes(), Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Ge(Bytes(), Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Le(Bytes(), Int32()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Ge(Bytes(), Int32()), UnsupportedOperation);

	EXPECT_TRUE(BaseObjCmp::Le(
		Bytes({ 0x01U, 0x02U, }), Bytes({ 0x01U, 0x03U, })));
	EXPECT_TRUE(BaseObjCmp::Ge(
		Bytes({ 0x01U, 0x03U, }), Bytes({ 0x01U, 0x02U, })));

	// Bytes base object
	using BytesBaseCmp = CompareTestHelpers<BytesBaseObj>;

	// less or equal to, true
	EXPECT_TRUE(BytesBaseCmp::Le(
		Bytes({ 0x01U, 0x02U, }), Bytes({ 0x01U, 0x02U, 0x03U, })));
	EXPECT_TRUE(BytesBaseCmp::Le(
		Bytes({ 0x01U, 0x02U, }), Bytes({ 0x01U, 0x02U, })));

	// less or equal to, false
	EXPECT_FALSE(BytesBaseCmp::Le(
		Bytes({ 0x01U, 0x02U, 0x03U, }), Bytes({ 0x01U, 0x02U, })));

	// greater or equal to, true
	EXPECT_TRUE(BytesBaseCmp::Ge(
		Bytes({ 0x01U, 0x02U, 0x03U, }), Bytes({ 0x01U, 0x02U, })));
	EXPECT_TRUE(BytesBaseCmp::Ge(
		Bytes({ 0x01U, 0x02U, }), Bytes({ 0x01U, 0x02U, })));

	// greater or equal to, false
	EXPECT_FALSE(BytesBaseCmp::Ge(
		Bytes({ 0x01U, 0x02U, }), Bytes({ 0x01U, 0x02U, 0x03U, })));
}

GTEST_TEST(TestBytes, Iterator)
{
	auto testBytes1 = Bytes({ 0x00U, 0x12U, 0xABU, 0xCDU, });
	auto expBytes1 = std::vector<uint8_t>({ 0x00U, 0x12U, 0xABU, 0xCDU, });

	{
		auto ita = testBytes1.begin();
		auto itb = expBytes1.begin();
		for(; ita != testBytes1.end() && itb != expBytes1.end(); ++ita, ++itb)
		{
			EXPECT_EQ(*ita, *itb);
			*ita = *itb;
		}
	}

	{
		auto ita = testBytes1.rbegin();
		auto itb = expBytes1.rbegin();
		for(; ita != testBytes1.rend() && itb != expBytes1.rend(); ++ita, ++itb)
		{
			EXPECT_EQ(*ita, *itb);
			*ita = *itb;
		}
	}

	auto testProg1 = [testBytes1, expBytes1]()
	{
		auto ita = testBytes1.begin();
		auto itb = expBytes1.begin();
		for(; ita != testBytes1.end() && itb != expBytes1.end(); ++ita, ++itb)
		{
			EXPECT_EQ(*ita, *itb);
		}
	};
	testProg1();

	auto testProg2 = [testBytes1, expBytes1]()
	{
		auto ita = testBytes1.crbegin();
		auto itb = expBytes1.crbegin();
		for(; ita != testBytes1.crend() && itb != expBytes1.crend(); ++ita, ++itb)
		{
			EXPECT_EQ(*ita, *itb);
		}
	};
	testProg2();
}

GTEST_TEST(TestBytes, ToString)
{
	auto testBytes1 = Bytes({ 0x00U, 0x12U, 0xABU, 0xCDU, });
	std::string expRes = "\"\\x00\\x12\\xAB\\xCD\"";

	// DebugString
	{
		EXPECT_EQ(testBytes1.DebugString(), expRes);
		EXPECT_EQ(testBytes1.ShortDebugString(), expRes);
	}

	// ToString
	{
		EXPECT_EQ(testBytes1.ToString(), expRes);
	}

	// DumpString
	{
		std::string res;
		EXPECT_NO_THROW(
			testBytes1.DumpString(ToOutIt<char>(std::back_inserter(res))));
		EXPECT_EQ(res, expRes);
	}
}
