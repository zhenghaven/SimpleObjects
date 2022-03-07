// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <memory>

#include <cstring>

#include <SimpleObjects/SimpleObjects.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
} // namespace SimpleObjects_Test

GTEST_TEST(TestDict, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

GTEST_TEST(TestDict, Construction)
{
	// Default
	EXPECT_NO_THROW({
		Dict().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Dict());
		base.reset();
	});

	// Copy & Move
	const Dict testDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};
	Dict cpDc(testDc);
	EXPECT_EQ(cpDc, testDc);
	Dict mvDc(std::move(cpDc));
	EXPECT_EQ(mvDc, testDc);
}

GTEST_TEST(TestDict, Assignment)
{
	const Dict testDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};

	Dict cpDc;
	EXPECT_EQ(cpDc.size(), 0);
	cpDc = testDc;
	EXPECT_EQ(cpDc, testDc);
	cpDc = cpDc;
	EXPECT_EQ(cpDc, testDc);

	Dict mvDc;
	EXPECT_EQ(mvDc.size(), 0);
	mvDc = std::move(cpDc);
	EXPECT_EQ(mvDc, testDc);
	mvDc = std::move(mvDc);
	EXPECT_EQ(mvDc, testDc);
}

GTEST_TEST(TestDict, Category)
{
	static_assert(Dict::sk_cat() == ObjCategory::Dict, "Category failed.");
	EXPECT_EQ(Dict::sk_cat(), ObjCategory::Dict);

	Dict val;
	EXPECT_EQ(val.GetCategory(), ObjCategory::Dict);
}

GTEST_TEST(TestDict, CategoryName)
{
	EXPECT_EQ(Dict().GetCategoryName(), std::string("Dict"));
}

GTEST_TEST(TestDict, Compare)
{
	const Dict testDc_001122 = Dict({
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	});
	const Dict testDc_001122_cp = Dict({
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	});
	const Dict testDc_0011 = Dict({
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
	});
	const Dict testDc_001121 = Dict({
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 1") },
	});
	// ==
	EXPECT_TRUE(testDc_001122 != testDc_0011);
	EXPECT_TRUE(testDc_001122 != testDc_001121);
	EXPECT_FALSE(testDc_001122 != testDc_001122_cp);
	EXPECT_TRUE(testDc_001122 !=
		static_cast<const DictBaseObj&>(testDc_0011));
	EXPECT_TRUE(testDc_001122 !=
		static_cast<const DictBaseObj&>(testDc_001121));
	EXPECT_FALSE(testDc_001122 !=
		static_cast<const DictBaseObj&>(testDc_001122_cp));

	// == diff obj
	EXPECT_TRUE(Dict() != Null());
	EXPECT_TRUE(Dict() != String());

	// <
	EXPECT_THROW((void)(Dict() <  static_cast<const BaseObj&>(Dict())), UnsupportedOperation);
	EXPECT_THROW((void)(Dict() >  static_cast<const BaseObj&>(Dict())), UnsupportedOperation);
	EXPECT_THROW((void)(Dict() <= static_cast<const BaseObj&>(Dict())), UnsupportedOperation);
	EXPECT_THROW((void)(Dict() >= static_cast<const BaseObj&>(Dict())), UnsupportedOperation);

	// < diff obj
	EXPECT_THROW((void)(Dict() < String()), UnsupportedOperation);

	// > diff obj
	EXPECT_THROW((void)(Dict() < String()), UnsupportedOperation);
}

GTEST_TEST(TestDict, Len)
{
	EXPECT_EQ(
		Dict({
			{ Null(), String("test val 0") },
			{ Int64(1), String("test val 1") },
			{ String("2"), String("test val 2") },
		}).size(), 3);
}

GTEST_TEST(TestDict, Iterator)
{
	const std::unordered_map<HashableObject, Object> testDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};
	std::unordered_map<HashableObject, size_t> testCount = {
		{ Null(), 0 },
		{ Int64(1), 0 },
		{ String("2"), 0 },
	};
	Dict cpDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};
	const Dict kCpDc = cpDc;

	// const it
	for(auto it = cpDc.cbegin(); it != cpDc.cend(); it++)
	{
		EXPECT_TRUE((testDc.find(it->first) != testDc.end()) &&
			(testDc.find(it->first)->second == it->second));
		++testCount[it->first];
	}
	for(auto& count: testCount)
	{
		EXPECT_EQ(count.second, 1);
		count.second = 0;
	}

	// const obj begin & end
	for(auto it = kCpDc.begin(); it != kCpDc.end(); ++it)
	{
		EXPECT_TRUE((testDc.find(it->first) != testDc.end()) &&
			(testDc.find(it->first)->second == it->second));
		++testCount[it->first];
	}
	for(auto& count: testCount)
	{
		EXPECT_EQ(count.second, 1);
		count.second = 0;
	}

	// it
	for(auto it = cpDc.begin(); it != cpDc.end(); it++)
	{
		EXPECT_TRUE((testDc.find(it->first) != testDc.end()) &&
			(testDc.find(it->first)->second == it->second));
		++testCount[it->first];
	}
	for(auto& count: testCount)
	{
		EXPECT_EQ(count.second, 1);
		count.second = 0;
	}
}

GTEST_TEST(TestDict, At)
{
	const std::unordered_map<HashableObject, Object> testDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};
	Dict cpDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};
	const Dict kCpDc = cpDc;

	EXPECT_EQ(cpDc.at(Null()), testDc.at(Null()));
	EXPECT_EQ(cpDc.at(Int64(1)), testDc.at(Int64(1)));

	EXPECT_EQ(kCpDc.at(Int64(1)), testDc.at(Int64(1)));
	EXPECT_EQ(kCpDc.at(String("2")), testDc.at(String("2")));

	EXPECT_THROW(cpDc.at(String("3")), std::out_of_range);
	EXPECT_THROW(kCpDc.at(String("3")), std::out_of_range);

	EXPECT_TRUE(cpDc[String("3")].IsNull());
}

GTEST_TEST(TestDict, FindKey)
{
	Dict cpDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};

	EXPECT_EQ(&cpDc.find(String("2"))->second, &cpDc.at(String("2")));
	EXPECT_EQ(cpDc.find(String("3")), cpDc.end());
	[cpDc](){
		EXPECT_EQ(&cpDc.find(String("2"))->second, &cpDc.at(String("2")));
		EXPECT_EQ(cpDc.find(String("3")), cpDc.end());
	}();

	EXPECT_TRUE(cpDc.HasKey(String("2")));
	EXPECT_FALSE(cpDc.HasKey(String("3")));
}

GTEST_TEST(TestDict, Insert)
{
	Dict testDc = {
		{ Null(), String("test val 0") },
	};

	// InsertOnly
	//    Successful insert
	EXPECT_THROW(testDc.at(Int64(1)), std::out_of_range);
	EXPECT_NO_THROW(
		auto res = testDc.InsertOnly(Int64(1), String("test val 1"));
		EXPECT_EQ(res.first->first, Int64(1));
		EXPECT_EQ(res.first->second, String("test val 1"));
		EXPECT_EQ(&*res.first, &*testDc.find(Int64(1)));
		EXPECT_EQ(res.second, true);
	);
	EXPECT_EQ(testDc.at(Int64(1)), String("test val 1"));
	//    Unsuccessful insert
	EXPECT_NO_THROW(
		auto res = testDc.InsertOnly(Int64(1), String("test val 1_1"));
		EXPECT_EQ(res.first->first, Int64(1));
		EXPECT_EQ(res.first->second, String("test val 1"));
		EXPECT_EQ(&*res.first, &*testDc.find(Int64(1)));
		EXPECT_EQ(res.second, false);
	);

	// InsertOrAssign
	//    Insert
	EXPECT_THROW(testDc.at(String("2")), std::out_of_range);
	EXPECT_NO_THROW(
		testDc.InsertOrAssign(String("2"), String("test val 2")));
	EXPECT_EQ(testDc.at(String("2")), String("test val 2"));

	//    Assign
	EXPECT_NO_THROW(
		testDc.InsertOrAssign(String("2"), String("test val 2_1")));
	EXPECT_EQ(testDc.at(String("2")), String("test val 2_1"));
}

GTEST_TEST(TestDict, Remove)
{
	Dict testDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};

	EXPECT_EQ(testDc.at(String("2")), String("test val 2"));
	EXPECT_NO_THROW(
		testDc.Remove(String("2")));
	EXPECT_THROW(testDc.at(String("2")), std::out_of_range);
}

GTEST_TEST(TestDict, Miscs)
{
	// Is null
	EXPECT_FALSE(Dict().IsNull());

	// Cast
	const auto kDict = Dict();
	EXPECT_NO_THROW(kDict.AsDict());
	EXPECT_THROW(kDict.AsNull(), TypeError);
	EXPECT_THROW(kDict.AsNumeric(), TypeError);
	EXPECT_THROW(kDict.AsString(), TypeError);
	EXPECT_THROW(kDict.AsList(), TypeError);

	EXPECT_NO_THROW(Dict().AsDict());
	EXPECT_THROW(Dict().AsNull(), TypeError);
	EXPECT_THROW(Dict().AsNumeric(), TypeError);
	EXPECT_THROW(Dict().AsString(), TypeError);
	EXPECT_THROW(Dict().AsList(), TypeError);

	// Copy
	static_assert(std::is_same<
		decltype(*Dict().Copy(Dict::Base::sk_null)),
		DictBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(
		*Dict({{ Null(), String("test val 0") }}).Copy(Dict::Base::sk_null),
		Dict({{ Null(), String("test val 0") }}));

	static_assert(std::is_same<
		decltype(*Dict().Copy(Dict::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(
		*Dict({{ Null(), String("test val 0") }}).Copy(Dict::Base::Base::sk_null),
		Dict({{ Null(), String("test val 0") }}));

	// Move
	auto mDict = Dict({{ Null(), String("test val 0") }});

	static_assert(std::is_same<
		decltype(*Dict().Move(Dict::Base::sk_null)),
		DictBaseObj&>::value, "Failed to test Move virtual func");
	mDict = Dict({{ Null(), String("test val 0") }});
	EXPECT_EQ(
		*mDict.Move(Dict::Base::sk_null),
		Dict({{ Null(), String("test val 0") }}));
	EXPECT_EQ(mDict.size(), 0);

	static_assert(std::is_same<
		decltype(*Dict().Move(Dict::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Move virtual func");
	mDict = Dict({{ Null(), String("test val 0") }});
	EXPECT_EQ(
		*mDict.Move(Dict::Base::Base::sk_null),
		Dict({{ Null(), String("test val 0") }}));
	EXPECT_EQ(mDict.size(), 0);
}

GTEST_TEST(TestDict, ToString)
{
	std::string expRes1 = "{ null : \"val1\", 123 : [ \"val2\" ] }";
	std::string expRes2 = "{ 123 : [ \"val2\" ], null : \"val1\" }";
	std::string expSRes1 = "{null:\"val1\",123:[\"val2\"]}";
	std::string expSRes2 = "{123:[\"val2\"],null:\"val1\"}";

	auto testDc = Dict({
		{ Null(), String("val1") },
		{ Int64(123), List({String("val2")}) },
	});

	// DebugString
	{
		EXPECT_TRUE(
			testDc.DebugString() == expRes1 ||
			testDc.DebugString() == expRes2);
		EXPECT_TRUE(
			testDc.ShortDebugString() == expSRes1 ||
			testDc.ShortDebugString() == expSRes2);
	}

	// ToString
	{
		EXPECT_TRUE(
			testDc.ToString() == expRes1 ||
			testDc.ToString() == expRes2);
	}

	// DumpString
	{
		std::string res;
		EXPECT_NO_THROW(
			testDc.DumpString(ToOutIt<char>(std::back_inserter(res))));
		EXPECT_TRUE(
			res == expRes1 ||
			res == expRes2);
	}
}
