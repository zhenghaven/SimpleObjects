// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <memory>

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER
#include <SimpleObjects/SimpleObjects.hpp>

#include "CompareHelpers.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestNull, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestNull, Construction)
{
	Null val1;
	Null val2 = Null();
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Null());
		base.reset();
	});
}

GTEST_TEST(TestNull, Category)
{
	static_assert(Null::sk_cat() == ObjCategory::Null, "Category failed.");
	EXPECT_EQ(Null::sk_cat(), ObjCategory::Null);

	Null val;
	EXPECT_EQ(val.GetCategory(), ObjCategory::Null);
}


GTEST_TEST(TestNull, CategoryName)
{
	EXPECT_EQ(Null().GetCategoryName(), std::string("Null"));
}

GTEST_TEST(TestNull, Hash)
{
	EXPECT_EQ(Null().Hash(), 0);
}

GTEST_TEST(TestNull, Miscs)
{
	// Is Null
	EXPECT_TRUE(Null().IsNull());

	// Cast
	const auto kNull = Null();
	EXPECT_NO_THROW(kNull.AsNull());
	EXPECT_THROW(kNull.AsRealNum(),    TypeError);
	EXPECT_THROW(kNull.AsString(),     TypeError);
	EXPECT_THROW(kNull.AsList(),       TypeError);
	EXPECT_THROW(kNull.AsDict(),       TypeError);
	EXPECT_THROW(kNull.AsStaticDict(), TypeError);
	EXPECT_THROW(kNull.AsBytes(),      TypeError);
	EXPECT_NO_THROW(kNull.AsHashable());

	EXPECT_NO_THROW(Null().AsNull());
	EXPECT_THROW(Null().AsRealNum(),    TypeError);
	EXPECT_THROW(Null().AsString(),     TypeError);
	EXPECT_THROW(Null().AsList(),       TypeError);
	EXPECT_THROW(Null().AsDict(),       TypeError);
	EXPECT_THROW(Null().AsStaticDict(), TypeError);
	EXPECT_THROW(Null().AsBytes(),      TypeError);
	EXPECT_NO_THROW(Null().AsHashable());

	// Copy
	static_assert(std::is_same<
		decltype(*Null().Copy(Null::Base::sk_null)),
		HashableBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Null().Copy(Null::Base::sk_null), Null());

	static_assert(std::is_same<
		decltype(*Null().Copy(Null::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Null().Copy(Null::Base::Base::sk_null), Null());

	// Move
	static_assert(std::is_same<
		decltype(*Null().Move(Null::Base::sk_null)),
		HashableBaseObj&>::value, "Failed to test Move virtual func");
	EXPECT_EQ(*Null().Move(Null::Base::sk_null), Null());

	static_assert(std::is_same<
		decltype(*Null().Move(Null::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Move virtual func");
	EXPECT_EQ(*Null().Move(Null::Base::Base::sk_null), Null());
}

GTEST_TEST(TestNull, Compare)
{
	// Self
	EXPECT_TRUE(Null() == Null());
	EXPECT_FALSE(Null() != Null());

	// Base
	using BaseObjCmp = CompareTestHelpers<BaseObj>;

	EXPECT_EQ(BaseObjCmp::Neq(Null(), Null()), nullptr != nullptr);

	EXPECT_THROW(BaseObjCmp::Ge(Null(), Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Le(Null(), Null()), UnsupportedOperation);
}

GTEST_TEST(TestNull, ToString)
{
	const std::string expRes = "null";
	// DebugString
	{
		EXPECT_EQ(Null().DebugString(), expRes);
		EXPECT_EQ(Null().ShortDebugString(), expRes);
		EXPECT_EQ(testing::PrintToString(Null()), "<" + expRes + ">");
	}

	// ToString
	{
		EXPECT_EQ(Null().ToString(), expRes);
	}

	// DumpString
	{
		std::string res;
		EXPECT_NO_THROW(
			Null().DumpString(ToOutIt<char>(std::back_inserter(res))));
		EXPECT_EQ(res, expRes);
	}
}

GTEST_TEST(TestNull, Setters)
{
	Null null1;
	EXPECT_NO_THROW(Null().Set(Null()));
	EXPECT_NO_THROW(Null().Set(null1));

	String str1;
	EXPECT_THROW(Null().Set(String()), TypeError);
	EXPECT_THROW(Null().Set(str1), TypeError);

	EXPECT_THROW(Null().Set(static_cast<bool >(true)), TypeError);
	EXPECT_THROW(Null().Set(static_cast<uint8_t >(1)), TypeError);
	EXPECT_THROW(Null().Set(static_cast< int8_t >(1)), TypeError);
	EXPECT_THROW(Null().Set(static_cast<uint32_t>(1)), TypeError);
	EXPECT_THROW(Null().Set(static_cast< int32_t>(1)), TypeError);
	EXPECT_THROW(Null().Set(static_cast<uint64_t>(1)), TypeError);
	EXPECT_THROW(Null().Set(static_cast< int64_t>(1)), TypeError);
	EXPECT_THROW(Null().Set(static_cast<double>(1.0)), TypeError);
}

GTEST_TEST(TestNull, Getters)
{
	EXPECT_FALSE(Null().IsTrue());

	EXPECT_THROW(Null().AsCppUInt8() ,  TypeError);
	EXPECT_THROW(Null().AsCppInt8()  ,  TypeError);
	EXPECT_THROW(Null().AsCppUInt32(),  TypeError);
	EXPECT_THROW(Null().AsCppInt32() ,  TypeError);
	EXPECT_THROW(Null().AsCppUInt64(),  TypeError);
	EXPECT_THROW(Null().AsCppInt64() ,  TypeError);
	EXPECT_THROW(Null().AsCppDouble() , TypeError);
}
