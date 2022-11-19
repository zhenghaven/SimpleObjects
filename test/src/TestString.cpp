// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <memory>

#include <cstring>

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
} // namespace SimpleObjects_Test

GTEST_TEST(TestString, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestString, Construction)
{
	// Default
	EXPECT_NO_THROW({
		String().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new String());
		base.reset();
	});
	EXPECT_EQ(String(std::string("test1")).GetVal(), "test1");
	std::string testStr2 = "test2";
	EXPECT_EQ(String(testStr2).GetVal(), testStr2);

	// from const char*
	EXPECT_EQ(String("test string").GetVal(), std::string("test string"));
}

GTEST_TEST(TestString, Assignment)
{
	const String testStr("Test String");

	String cpStr;
	EXPECT_EQ(cpStr.size(), 0);
	cpStr = testStr;
	EXPECT_EQ(cpStr, testStr);
	// We want to ensure assignment self is OK,
	// meanwhile to avoid compiler warning
	String* cpStrPtr = nullptr;
	cpStrPtr = &cpStr;
	cpStr = *cpStrPtr;
	EXPECT_EQ(cpStr, testStr);

	String mvStr;
	EXPECT_EQ(mvStr.size(), 0);
	mvStr = std::move(cpStr);
	EXPECT_EQ(mvStr, testStr);
	String* mvStrPtr = nullptr;
	mvStrPtr = &mvStr;
	mvStr = std::move(*mvStrPtr);
	EXPECT_EQ(mvStr, testStr);
}

GTEST_TEST(TestString, Category)
{
	static_assert(String::sk_cat() == ObjCategory::String, "Category failed.");
	EXPECT_EQ(String::sk_cat(), ObjCategory::String);

	String val;
	EXPECT_EQ(val.GetCategory(), ObjCategory::String);
}

GTEST_TEST(TestString, CategoryName)
{
	EXPECT_EQ(String().GetCategoryName(), std::string("String"));
}

GTEST_TEST(TestString, Miscs)
{
	// Is null
	EXPECT_FALSE(String().IsNull());

	// Cast
	const auto kStr = String();
	EXPECT_NO_THROW(kStr.AsString());
	EXPECT_THROW(kStr.AsNull(),       TypeError);
	EXPECT_THROW(kStr.AsRealNum(),    TypeError);
	EXPECT_THROW(kStr.AsList(),       TypeError);
	EXPECT_THROW(kStr.AsDict(),       TypeError);
	EXPECT_THROW(kStr.AsStaticDict(), TypeError);
	EXPECT_THROW(kStr.AsBytes(),      TypeError);
	EXPECT_NO_THROW(kStr.AsHashable());

	EXPECT_NO_THROW(String().AsString());
	EXPECT_THROW(String().AsNull(),       TypeError);
	EXPECT_THROW(String().AsRealNum(),    TypeError);
	EXPECT_THROW(String().AsList(),       TypeError);
	EXPECT_THROW(String().AsDict(),       TypeError);
	EXPECT_THROW(String().AsStaticDict(), TypeError);
	EXPECT_THROW(String().AsBytes(),      TypeError);
	EXPECT_NO_THROW(String().AsHashable());

	// Copy
	static_assert(std::is_same<
		decltype(*String().Copy(String::Base::sk_null)),
		StringBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*String("Test").Copy(String::Base::sk_null), String("Test"));

	static_assert(std::is_same<
		decltype(*String().Copy(String::Base::Base::sk_null)),
		HashableBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*String("Test").Copy(String::Base::Base::sk_null), String("Test"));

	static_assert(std::is_same<
		decltype(*String().Copy(String::Base::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*String("Test").Copy(String::Base::Base::Base::sk_null), String("Test"));

	// Move
	auto mStr = String("Test");

	static_assert(std::is_same<
		decltype(*String().Move(String::Base::sk_null)),
		StringBaseObj&>::value, "Failed to test Move virtual func");
	mStr = String("Test");
	EXPECT_EQ(*mStr.Move(String::Base::sk_null), String("Test"));
	EXPECT_EQ(mStr.size(), 0);

	static_assert(std::is_same<
		decltype(*String().Move(String::Base::Base::sk_null)),
		HashableBaseObj&>::value, "Failed to test Move virtual func");
	mStr = String("Test");
	EXPECT_EQ(*mStr.Move(String::Base::Base::sk_null), String("Test"));
	EXPECT_EQ(mStr.size(), 0);

	static_assert(std::is_same<
		decltype(*String().Move(String::Base::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Move virtual func");
	mStr = String("Test");
	EXPECT_EQ(*mStr.Move(String::Base::Base::Base::sk_null), String("Test"));
	EXPECT_EQ(mStr.size(), 0);
}

GTEST_TEST(TestString, Setters)
{
	String str1;
	EXPECT_NO_THROW(String().Set(String()));
	EXPECT_NO_THROW(String().Set(str1));

	Null null1;
	EXPECT_THROW(String().Set(Null()), TypeError);
	EXPECT_THROW(String().Set(null1), TypeError);

	EXPECT_THROW(String().Set(static_cast<bool >(true)), TypeError);
	EXPECT_THROW(String().Set(static_cast<uint8_t >(1)), TypeError);
	EXPECT_THROW(String().Set(static_cast< int8_t >(1)), TypeError);
	EXPECT_THROW(String().Set(static_cast<uint32_t>(1)), TypeError);
	EXPECT_THROW(String().Set(static_cast< int32_t>(1)), TypeError);
	EXPECT_THROW(String().Set(static_cast<uint64_t>(1)), TypeError);
	EXPECT_THROW(String().Set(static_cast< int64_t>(1)), TypeError);
	EXPECT_THROW(String().Set(static_cast<double>(1.0)), TypeError);
}

GTEST_TEST(TestString, Getters)
{
	EXPECT_FALSE(String().IsTrue());
	EXPECT_TRUE( String("T").IsTrue());

	EXPECT_THROW(String().AsCppUInt8() ,  TypeError);
	EXPECT_THROW(String().AsCppInt8()  ,  TypeError);
	EXPECT_THROW(String().AsCppUInt32(),  TypeError);
	EXPECT_THROW(String().AsCppInt32() ,  TypeError);
	EXPECT_THROW(String().AsCppUInt64(),  TypeError);
	EXPECT_THROW(String().AsCppInt64() ,  TypeError);
	EXPECT_THROW(String().AsCppDouble() , TypeError);
}

GTEST_TEST(TestString, Hash)
{
	EXPECT_EQ(String("test string1").Hash(),
		std::hash<std::string>()(std::string("test string1")));
	EXPECT_EQ(String("test string2").Hash(),
		std::hash<std::string>()(std::string("test string2")));
	EXPECT_NE(String("test string1").Hash(),
		std::hash<std::string>()(std::string("test string2")));

	EXPECT_EQ(String("test string1").Hash(),
		std::hash<String>()(String("test string1")));
	EXPECT_EQ(String("test string2").Hash(),
		std::hash<String>()(String("test string2")));
	EXPECT_NE(String("test string1").Hash(),
		std::hash<String>()(String("test string2")));
}

GTEST_TEST(TestString, Len)
{
	EXPECT_EQ(String("abcdef").size(), std::string("abcdef").size());
	EXPECT_EQ(String("1234567890").size(), std::string("1234567890").size());
}

GTEST_TEST(TestString, At)
{
	auto testStr1 = String("abcdef");
	auto testStr2 = String("1234567890");

	// const
	auto prog = [testStr1, testStr2]()
	{
		EXPECT_EQ(&testStr1[0], testStr1.data());
		EXPECT_EQ(testStr1[1], 'b');

		EXPECT_EQ(&testStr2[0], testStr2.data());
		EXPECT_EQ(testStr2[1], '2');

		EXPECT_THROW(testStr1[7], IndexError);
		EXPECT_THROW(testStr2[11], IndexError);
	};
	prog();

	// mutables
	EXPECT_EQ(&testStr1[0], testStr1.data());
	EXPECT_EQ(testStr1[1], 'b');
	++testStr1[1];
	EXPECT_EQ(testStr1[1], 'c');

	EXPECT_EQ(&testStr2[0], testStr2.data());
	EXPECT_EQ(testStr2[1], '2');
	++testStr2[1];
	EXPECT_EQ(testStr2[1], '3');

	EXPECT_THROW(testStr1[7], IndexError);
	EXPECT_THROW(testStr2[11], IndexError);
}

GTEST_TEST(TestString, StartsWith)
{
	EXPECT_TRUE(String("abcdef").StartsWith(String("ab")));
	EXPECT_TRUE(String("abcdef").StartsWith(String("abc")));
	EXPECT_TRUE(String("abcdef").StartsWith(String("abcdef")));

	EXPECT_FALSE(String("abcdef").StartsWith(String("bcd")));
	EXPECT_FALSE(String("abcdef").StartsWith(String("ac")));
	EXPECT_FALSE(String("abcdef").StartsWith(String("abcdefg")));

	auto longStr = String("abcdefg");
	EXPECT_FALSE(String("abcdef").StartsWith(longStr.cbegin(), longStr.cend()));
}

GTEST_TEST(TestString, EndsWith)
{
	EXPECT_TRUE(String("abcdef").EndsWith(String("def")));
	EXPECT_TRUE(String("abcdef").EndsWith(String("cdef")));
	EXPECT_TRUE(String("abcdef").EndsWith(String("abcdef")));

	EXPECT_FALSE(String("abcdef").EndsWith(String("de")));
	EXPECT_FALSE(String("abcdef").EndsWith(String("cef")));
	EXPECT_FALSE(String("abcdef").EndsWith(String("zabcdef")));

	auto longStr = String("zabcdef");
	EXPECT_FALSE(String("abcdef").EndsWith(longStr.cbegin(), longStr.cend()));
}

GTEST_TEST(TestString, Contains)
{
	auto testStr = String("abcdef");
	EXPECT_EQ(testStr.Contains(String("cdef")),   testStr.cbegin() + 2);
	EXPECT_EQ(testStr.Contains(String("bcd")),    testStr.cbegin() + 1);
	EXPECT_EQ(testStr.Contains(String("b")),      testStr.cbegin() + 1);
	EXPECT_EQ(testStr.Contains(String("abcdef")), testStr.cbegin());

	EXPECT_EQ(testStr.Contains(String("acef")),    testStr.cend());
	EXPECT_EQ(testStr.Contains(String("abcdefg")), testStr.cend());

	auto longStr = String("abcdefg");
	EXPECT_EQ(testStr.Contains(longStr.cbegin(), longStr.cend()), testStr.cend());
}

GTEST_TEST(TestString, PushPopBack)
{
	auto testStr = String("abcdef");
	EXPECT_EQ(testStr, String("abcdef"));

	testStr.push_back('g');
	EXPECT_EQ(testStr, String("abcdefg"));

	testStr.pop_back();
	EXPECT_EQ(testStr, String("abcdef"));
}

GTEST_TEST(TestString, Append)
{
	auto testStr = String("abcdef");
	EXPECT_EQ(testStr, String("abcdef"));

	testStr.Append(String("ghijk"));
	EXPECT_EQ(testStr, String("abcdefghijk"));

	testStr += String("ghijk");
	EXPECT_EQ(testStr, String("abcdefghijkghijk"));
}

GTEST_TEST(TestString, CStr)
{
	EXPECT_EQ(std::strcmp(String("abcdef").c_str(), "abcdef"), 0);
}

GTEST_TEST(TestString, Capacity)
{
	auto testStr = String("abcdef");
	EXPECT_EQ(testStr, String("abcdef"));

	testStr.reserve(20);
	EXPECT_EQ(testStr, String("abcdef"));

	testStr.resize(3);
	EXPECT_EQ(testStr, String("abc"));

	testStr.resize(6);
	auto tmp = String("abc");
	tmp.push_back('\0');tmp.push_back('\0');tmp.push_back('\0');
	EXPECT_EQ(testStr, tmp);

	testStr.resize(0);
	EXPECT_EQ(testStr, String(""));
}

GTEST_TEST(TestString, Compare)
{
	EXPECT_TRUE(String("test string1") == String("test string1"));
	EXPECT_TRUE(String("test string1") != String("test string2"));
	EXPECT_TRUE(String("test string1") <  String("test string2"));
	EXPECT_TRUE(String("test string2") >  String("test string1"));
	EXPECT_TRUE(String("test string1") <= String("test string2"));
	EXPECT_TRUE(String("test string2") >= String("test string1"));
}

GTEST_TEST(TestString, BaseIsEqual)
{
	// Base object
	using BaseObjCmp = CompareTestHelpers<BaseObj>;

	EXPECT_TRUE(BaseObjCmp::Neq(String(), Bool(true)));
	EXPECT_TRUE(BaseObjCmp::Neq(String(), Null()));

	EXPECT_TRUE(BaseObjCmp::Neq(
		String("test string1"), String("test string2")));
	EXPECT_FALSE(BaseObjCmp::Neq(
		String("test string"), String("test string")));

	// String base object
	using StrBaseCmp = CompareTestHelpers<StringBaseObj>;

	EXPECT_TRUE(StrBaseCmp::Neq(
		String("test string1"), String("test string2")));
	EXPECT_FALSE(StrBaseCmp::Neq(
		String("test string"), String("test string")));
}

GTEST_TEST(TestString, BaseCompare)
{
	// Base object
	using BaseObjCmp = CompareTestHelpers<BaseObj>;

	EXPECT_THROW(BaseObjCmp::Le(String(), Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Ge(String(), Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Le(String(), Int32()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Ge(String(), Int32()), UnsupportedOperation);

	EXPECT_FALSE(BaseObjCmp::Le(String("123466"), String("123456")));
	EXPECT_FALSE(BaseObjCmp::Ge(String("123456"), String("123466")));

	// String base object
	using StrBaseCmp = CompareTestHelpers<StringBaseObj>;

	// less or equal to, true
	EXPECT_TRUE(StrBaseCmp::Le(String("123456"), String("123466")));
	EXPECT_TRUE(StrBaseCmp::Le(String("12345"), String("12345")));

	// less or equal to, false
	EXPECT_FALSE(StrBaseCmp::Le(String("123466"), String("123456")));
	EXPECT_FALSE(StrBaseCmp::Le(String("123456"), String("12345")));

	// greater or equal to, true
	EXPECT_TRUE(StrBaseCmp::Ge(String("123466"), String("123456")));
	EXPECT_TRUE(StrBaseCmp::Ge(String("12345"), String("12345")));

	// greater or equal to, false
	EXPECT_FALSE(StrBaseCmp::Ge(String("123456"), String("123466")));
	EXPECT_FALSE(StrBaseCmp::Ge(String("12345"), String("123456")));
}

GTEST_TEST(TestString, ToString)
{
	std::string expRes = "\"test string";
	expRes.push_back('\0');
	expRes.push_back('\"');

	auto testStr = String("test string");
	testStr.push_back('\0');

	// DebugString
	{
		EXPECT_EQ(testStr.DebugString(), expRes);
		EXPECT_EQ(testStr.ShortDebugString(), expRes);
	}

	// ToString
	{
		EXPECT_EQ(testStr.ToString(), expRes);
	}

	// DumpString
	{
		std::string res;
		EXPECT_NO_THROW(
			testStr.DumpString(ToOutIt<char>(std::back_inserter(res))));
		EXPECT_EQ(res, expRes);
	}
}
