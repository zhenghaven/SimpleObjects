// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <memory>

#include <cstring>

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

GTEST_TEST(TestDict, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
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
	// We want to ensure assignment self is OK,
	// meanwhile to avoid compiler warning
	Dict* cpDcPtr = nullptr;
	cpDcPtr = &cpDc;
	cpDc = *cpDcPtr;
	EXPECT_EQ(cpDc, testDc);

	Dict mvDc;
	EXPECT_EQ(mvDc.size(), 0);
	mvDc = std::move(cpDc);
	EXPECT_EQ(mvDc, testDc);
	Dict* mvDcPtr = nullptr;
	mvDcPtr = &mvDc;
	mvDc = std::move(*mvDcPtr);
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

GTEST_TEST(TestDict, Setters)
{
	Dict dc1;
	EXPECT_NO_THROW(Dict().Set(Dict()));
	EXPECT_NO_THROW(Dict().Set(dc1));

	Null null1;
	EXPECT_THROW(Dict().Set(Null()), TypeError);
	EXPECT_THROW(Dict().Set(null1), TypeError);

	EXPECT_THROW(Dict().Set(static_cast<bool >(true)), TypeError);
	EXPECT_THROW(Dict().Set(static_cast<uint8_t >(1)), TypeError);
	EXPECT_THROW(Dict().Set(static_cast< int8_t >(1)), TypeError);
	EXPECT_THROW(Dict().Set(static_cast<uint32_t>(1)), TypeError);
	EXPECT_THROW(Dict().Set(static_cast< int32_t>(1)), TypeError);
	EXPECT_THROW(Dict().Set(static_cast<uint64_t>(1)), TypeError);
	EXPECT_THROW(Dict().Set(static_cast< int64_t>(1)), TypeError);
	EXPECT_THROW(Dict().Set(static_cast<double>(1.0)), TypeError);
}

GTEST_TEST(TestDict, Getters)
{
	EXPECT_FALSE(Dict().IsTrue());
	EXPECT_TRUE( Dict({{Null(), Null()}}).IsTrue());

	EXPECT_THROW(Dict().AsCppUInt8() ,  TypeError);
	EXPECT_THROW(Dict().AsCppInt8()  ,  TypeError);
	EXPECT_THROW(Dict().AsCppUInt32(),  TypeError);
	EXPECT_THROW(Dict().AsCppInt32() ,  TypeError);
	EXPECT_THROW(Dict().AsCppUInt64(),  TypeError);
	EXPECT_THROW(Dict().AsCppInt64() ,  TypeError);
	EXPECT_THROW(Dict().AsCppDouble() , TypeError);
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

	std::cout << "TEST X 0" << std::endl;

	// ==
	EXPECT_TRUE(testDc_001122 != testDc_0011);
	EXPECT_TRUE(testDc_001122 != testDc_001121);
	EXPECT_FALSE(testDc_001122 != testDc_001122_cp);

	std::cout << "TEST X 1" << std::endl;

	using DictBaseCmp = CompareTestHelpers<DictBaseObj>;

	EXPECT_TRUE(DictBaseCmp::Neq(testDc_001122, testDc_0011));
	EXPECT_TRUE(DictBaseCmp::Neq(testDc_001122, testDc_001121));
	EXPECT_FALSE(DictBaseCmp::Neq(testDc_001122, testDc_001122_cp));

	std::cout << "TEST X 2" << std::endl;

	// == diff obj
	using BaseObjCmp = CompareTestHelpers<BaseObj>;

	EXPECT_TRUE(BaseObjCmp::Neq(Dict(), Null()));
	EXPECT_TRUE(BaseObjCmp::Neq(Dict(), String()));

	std::cout << "TEST X 3" << std::endl;

	// <
	EXPECT_THROW(BaseObjCmp::Lt(Dict(), Dict()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Gt(Dict(), Dict()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Le(Dict(), Dict()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Ge(Dict(), Dict()), UnsupportedOperation);

	std::cout << "TEST X 4" << std::endl;

	// < diff obj
	EXPECT_THROW(BaseObjCmp::Lt(Dict(), String()), UnsupportedOperation);

	std::cout << "TEST X 5" << std::endl;

	// > diff obj
	EXPECT_THROW(BaseObjCmp::Lt(Dict(), String()), UnsupportedOperation);

	std::cout << "TEST X 6" << std::endl;
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
		EXPECT_TRUE((testDc.find(it->first.GetVal()) != testDc.end()) &&
			(testDc.find(it->first.GetVal())->second == it->second));
		++testCount[it->first.GetVal()];
	}
	for(auto& count: testCount)
	{
		EXPECT_EQ(count.second, 1);
		count.second = 0;
	}

	// const obj begin & end
	for(auto it = kCpDc.begin(); it != kCpDc.end(); ++it)
	{
		EXPECT_TRUE((testDc.find(it->first.GetVal()) != testDc.end()) &&
			(testDc.find(it->first.GetVal())->second == it->second));
		++testCount[it->first.GetVal()];
	}
	for(auto& count: testCount)
	{
		EXPECT_EQ(count.second, 1);
		count.second = 0;
	}

	// it
	for(auto it = cpDc.begin(); it != cpDc.end(); it++)
	{
		EXPECT_TRUE((testDc.find(it->first.GetVal()) != testDc.end()) &&
			(testDc.find(it->first.GetVal())->second == it->second));
		++testCount[it->first.GetVal()];
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

	auto tmpNull = Null();
	EXPECT_EQ(cpDc[tmpNull], testDc.at(Null()));
	EXPECT_EQ(cpDc[Int64(1)], testDc.at(Int64(1)));

	EXPECT_EQ(kCpDc[Int64(1)], testDc.at(Int64(1)));
	EXPECT_EQ(kCpDc[String("2")], testDc.at(String("2")));

	EXPECT_THROW(kCpDc[String("3")], KeyError);
	EXPECT_TRUE(cpDc[String("3")].IsNull());
}

GTEST_TEST(TestDict, FindKey)
{
	Dict cpDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};

	[cpDc](){
		EXPECT_EQ(&cpDc.find(String("2"))->second, &cpDc[String("2")]);
		EXPECT_EQ(cpDc.find(String("3")), cpDc.end());
	}();
	EXPECT_EQ(&cpDc.find(String("2"))->second, &cpDc[String("2")]);
	EXPECT_EQ(cpDc.find(String("3")), cpDc.end());

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
	EXPECT_FALSE(testDc.HasKey(Int64(1)));
	auto subTest1 = [&]()
	{
		auto res = testDc.InsertOnly(Int64(1), String("test val 1"));
		EXPECT_TRUE(res.first->first.GetVal().AsRealNum() == Int64(1));
		EXPECT_TRUE(res.first->second.AsString() == String("test val 1"));
		EXPECT_TRUE(&*res.first == &*testDc.find(Int64(1)));
		EXPECT_TRUE(res.second == true);
	};
	EXPECT_NO_THROW(subTest1(););
	EXPECT_TRUE(testDc[Int64(1)].AsString() == String("test val 1"));

	EXPECT_FALSE(testDc.HasKey(Int64(2)));
	auto subTest2 = [&]()
	{
		const auto tmpKey = HashableObject(Int64(2));
		const auto tmpVal = Object(String("test val 2"));
		auto res = testDc.InsertOnly(tmpKey, tmpVal);
		EXPECT_TRUE(res.first->first.GetVal().AsRealNum() == Int64(2));
		EXPECT_TRUE(res.first->second.AsString() == String("test val 2"));
		EXPECT_TRUE(&*res.first == &*testDc.find(Int64(2)));
		EXPECT_TRUE(res.second == true);
	};
	EXPECT_NO_THROW(subTest2(););
	EXPECT_TRUE(testDc[Int64(2)].AsString() == String("test val 2"));


	//    Unsuccessful insert
	auto subTest3 = [&]()
	{
		auto res = testDc.InsertOnly(Int64(1), String("test val 1_1"));
		EXPECT_TRUE(res.first->first.GetVal().AsRealNum() == Int64(1));
		EXPECT_TRUE(res.first->second.AsString() == String("test val 1"));
		EXPECT_TRUE(&*res.first == &*testDc.find(Int64(1)));
		EXPECT_TRUE(res.second == false);
	};
	EXPECT_NO_THROW(subTest3(););
	EXPECT_TRUE(testDc[Int64(1)].AsString() == String("test val 1"));

	auto subTest4 = [&]()
	{
		const auto tmpKey = HashableObject(Int64(2));
		const auto tmpVal = Object(String("test val 2_2"));
		auto res = testDc.InsertOnly(tmpKey, tmpVal);
		EXPECT_TRUE(res.first->first.GetVal().AsRealNum() == Int64(2));
		EXPECT_TRUE(res.first->second.AsString() == String("test val 2"));
		EXPECT_TRUE(&*res.first == &*testDc.find(Int64(2)));
		EXPECT_TRUE(res.second == false);
	};
	EXPECT_NO_THROW(subTest4(););
	EXPECT_TRUE(testDc[Int64(2)].AsString() == String("test val 2"));

	// InsertOrAssign
	//    Insert
	{
		EXPECT_FALSE(testDc.HasKey(String("2")));
		EXPECT_NO_THROW(
			auto res = testDc.InsertOrAssign(String("2"), String("test val 2"));
			EXPECT_TRUE(res.second == true););
		EXPECT_TRUE(testDc[String("2")].AsString() == String("test val 2"));
	}

	{
		const auto tmpKey = HashableObject(String("3"));
		const auto tmpVal = Object(String("test val 3"));
		EXPECT_FALSE(testDc.HasKey(tmpKey));
		EXPECT_NO_THROW(
			auto res = testDc.InsertOrAssign(tmpKey, tmpVal);
			EXPECT_TRUE(res.second == true););
		EXPECT_TRUE(testDc[String("3")].AsString() == String("test val 3"));
	}

	//    Assign
	{
		EXPECT_NO_THROW(
			auto res = testDc.InsertOrAssign(String("2"), String("test val 2_1"));
			EXPECT_TRUE(res.second == false););
		EXPECT_TRUE(testDc[String("2")].AsString() == String("test val 2_1"));
	}

	{
		const auto tmpKey = HashableObject(String("3"));
		const auto tmpVal = Object(String("test val 3_1"));
		EXPECT_NO_THROW(
			auto res = testDc.InsertOrAssign(tmpKey, tmpVal);
			EXPECT_TRUE(res.second == false););
		EXPECT_TRUE(testDc[String("3")].AsString() == String("test val 3_1"));
	}
}

GTEST_TEST(TestDict, Remove)
{
	Dict testDc = {
		{ Null(), String("test val 0") },
		{ Int64(1), String("test val 1") },
		{ String("2"), String("test val 2") },
	};

	EXPECT_TRUE(testDc[String("2")].AsString() == String("test val 2"));
	EXPECT_NO_THROW(
		testDc.Remove(String("2")));
	EXPECT_FALSE(testDc.HasKey(String("2")));
}

GTEST_TEST(TestDict, Miscs)
{
	// Is null
	EXPECT_FALSE(Dict().IsNull());

	// Cast
	const auto kDict = Dict();
	EXPECT_NO_THROW(kDict.AsDict());
	EXPECT_THROW(kDict.AsNull(),       TypeError);
	EXPECT_THROW(kDict.AsRealNum(),    TypeError);
	EXPECT_THROW(kDict.AsString(),     TypeError);
	EXPECT_THROW(kDict.AsList(),       TypeError);
	EXPECT_THROW(kDict.AsStaticDict(), TypeError);
	EXPECT_THROW(kDict.AsBytes(),      TypeError);

	EXPECT_NO_THROW(Dict().AsDict());
	EXPECT_THROW(Dict().AsNull(),       TypeError);
	EXPECT_THROW(Dict().AsRealNum(),    TypeError);
	EXPECT_THROW(Dict().AsString(),     TypeError);
	EXPECT_THROW(Dict().AsList(),       TypeError);
	EXPECT_THROW(Dict().AsStaticDict(), TypeError);
	EXPECT_THROW(Dict().AsBytes(),      TypeError);

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

GTEST_TEST(TestDict, BaseDictIterator)
{
	// const
	{
		auto testDc = Dict({
			{ Null(),         Bool(false) },
			{ Int64(123),     Int64(321) },
			{ String("key3"), String("val3") },
		});
		auto testKeys = List({ Null(), Int64(123), String("key3") });
		auto testNKeys = List({ Bool(true), Int64(321), String("key3X") });

		auto testVals = List({ Bool(false), Int64(321), String("val3") });
		auto testNVals = List({ Bool(true), Int64(123), String("val3X") });

		const DictBaseObj& testDcB = testDc;

		{
			auto it = testDcB.KeysBegin();
			auto ite = testDcB.KeysEnd();
			size_t i = 0;

			for (; it != ite; ++it, ++i)
			{
				EXPECT_TRUE(testKeys.Contains(*it));
				EXPECT_FALSE(testNKeys.Contains(*it));
			}

			EXPECT_TRUE(i == 3);
			EXPECT_TRUE(it == testDcB.KeysEnd());
		}
		{
			auto it = testDcB.ValsBegin();
			auto ite = testDcB.ValsEnd();
			size_t i = 0;

			for (; it != ite; ++it, ++i)
			{
				EXPECT_TRUE(testVals.Contains(*it));
				EXPECT_FALSE(testNVals.Contains(*it));
			}

			EXPECT_TRUE(i == 3);
			EXPECT_TRUE(it == testDcB.ValsEnd());
		}
	}

	// non-const
	{
		auto testDc = Dict({
			{ Null(),         Bool(false) },
			{ Int64(123),     Int64(321) },
			{ String("key3"), String("val3") },
		});

		auto testVals = List({ Bool(true), Int64(123), String("val3Y") });
		auto testNVals = List({ Bool(false), Int64(321), String("val3") });

		DictBaseObj& testDcB = testDc;

		{
			auto it = testDcB.ValsBegin();
			auto ite = testDcB.ValsEnd();
			size_t i = 0;

			for (; it != ite; ++it, ++i)
			{
				if ((*it) == Bool(false))
				{
					(*it).Set(Bool(true));
				}
				else if ((*it) == Int64(321))
				{
					(*it).Set(Int64(123));
				}
				else if ((*it) == String("val3"))
				{
					(*it).Set(String("val3Y"));
				}
			}

			EXPECT_TRUE(i == 3);
			EXPECT_TRUE(it == testDcB.ValsEnd());
		}
		{
			auto it = testDcB.ValsBegin();
			auto ite = testDcB.ValsEnd();
			size_t i = 0;

			for (; it != ite; ++it, ++i)
			{
				EXPECT_TRUE(testVals.Contains(*it));
				EXPECT_FALSE(testNVals.Contains(*it));
			}

			EXPECT_TRUE(i == 3);
			EXPECT_TRUE(it == testDcB.ValsEnd());
		}
	}

	// const zipped iterators
	{
		auto testDc = Dict({
			{ Null(),         Bool(false) },
			{ Int64(123),     Int64(321) },
			{ String("key3"), String("val3") },
		});
		auto testKeys = List({ Null(), Int64(123), String("key3") });
		auto testNKeys = List({ Bool(true), Int64(321), String("key3X") });

		auto testVals = List({ Bool(false), Int64(321), String("val3") });
		auto testNVals = List({ Bool(true), Int64(123), String("val3X") });

		const DictBaseObj& testDcB = testDc;

		{
			auto it = testDcB.begin();
			auto ite = testDcB.end();
			size_t i = 0;

			for (; it != ite; ++it, ++i)
			{
				// Keys
				EXPECT_TRUE(testKeys.Contains(*std::get<0>(*it)));
				EXPECT_FALSE(testNKeys.Contains(*std::get<0>(*it)));

				// Vals
				EXPECT_TRUE(testVals.Contains(*std::get<1>(*it)));
				EXPECT_FALSE(testNVals.Contains(*std::get<1>(*it)));
			}

			EXPECT_TRUE(i == 3);
			EXPECT_TRUE(it == testDcB.end());
		}
	}

	// non-const zipped iterators
	{
		auto testDc = Dict({
			{ Null(),         Bool(false) },
			{ Int64(123),     Int64(321) },
			{ String("key3"), String("val3") },
		});
		auto testKeys = List({ Null(), Int64(123), String("key3") });
		auto testNKeys = List({ Bool(true), Int64(321), String("key3X") });

		auto testVals = List({ Bool(false), Int64(321), String("val3") });
		auto testNVals = List({ Bool(true), Int64(123), String("val3X") });

		DictBaseObj& testDcB = testDc;

		{
			auto it = testDcB.begin();
			auto ite = testDcB.end();
			size_t i = 0;

			for (; it != ite; ++it, ++i)
			{
				// Keys
				EXPECT_TRUE(testKeys.Contains(*std::get<0>(*it)));
				EXPECT_FALSE(testNKeys.Contains(*std::get<0>(*it)));

				// Vals
				EXPECT_TRUE(testVals.Contains(*std::get<1>(*it)));
				EXPECT_FALSE(testNVals.Contains(*std::get<1>(*it)));

				// check mutation APIs
				if ((*std::get<1>(*it)) == String("val3"))
				{
					(*std::get<1>(*it)).AsString().push_back('X');
					(*std::get<1>(*it)).AsString().pop_back();
				}
			}

			EXPECT_TRUE(i == 3);
			EXPECT_TRUE(it == testDcB.end());
		}
	}
}

GTEST_TEST(TestDict, BaseDictFindVal)
{
	{
		auto testDc = Dict({
			{ Null(),         Bool(false) },
			{ Int64(123),     Int64(321) },
			{ String("key3"), String("val3") },
		});
		DictBaseObj& testDcB = testDc;
		const DictBaseObj& testKDcB = testDc;

		auto it = testDcB.FindVal(HashableObject(Int64(123)));
		EXPECT_TRUE(it != testDcB.ValsEnd());
		EXPECT_TRUE((*it) == testDc[Int64(123)]);
		EXPECT_TRUE(testDcB[HashableObject(Int64(123))] == testDc[Int64(123)]);

		it = testDcB.FindVal(HashableObject(String("keyX")));
		EXPECT_TRUE(it == testDcB.ValsEnd());

		auto kit = testKDcB.FindVal(HashableObject(Int64(123)));
		EXPECT_TRUE(kit != testKDcB.ValsEnd());
		EXPECT_TRUE((*kit) == testDc[Int64(123)]);
		EXPECT_TRUE(testKDcB[HashableObject(Int64(123))] == testDc[Int64(123)]);

		kit = testKDcB.FindVal(HashableObject(String("keyX")));
		EXPECT_TRUE(kit == testKDcB.ValsEnd());
		EXPECT_THROW(testKDcB[HashableObject(String("keyX"))], KeyError);

		EXPECT_FALSE(testKDcB.HasKey(HashableObject(String("keyX"))));

		EXPECT_TRUE(testDcB[HashableObject(String("keyXX"))] == Null());
	}
}

GTEST_TEST(TestDict, BaseDictInsert)
{
	// Insert-only
	{
		auto testDc = Dict({
			{ Null(),         Bool(false) },
			{ Int64(123),     Int64(321) },
			{ String("key3"), String("val3") },
		});
		DictBaseObj& testDcB = testDc;

		// Successful
		//     l-reference
		EXPECT_NO_THROW(
			auto res = testDcB.InsertOnly(
				HashableObject(String("key4")), Object(String("val4")));
			EXPECT_TRUE(res);
			EXPECT_TRUE(
				testDcB[HashableObject(String("key4"))] == String("val4"));
		);

		//     r-reference
		const auto key5 = HashableObject(String("key5"));
		const auto val5 = Object(String("val5"));
		EXPECT_NO_THROW(
			auto res = testDcB.InsertOnly(key5, val5);
			EXPECT_TRUE(res);
			EXPECT_TRUE(testDcB[key5] == val5);
		);

		// Failed
		//     l-reference
		EXPECT_NO_THROW(
			auto res = testDcB.InsertOnly(
				HashableObject(String("key3")), Object(String("valx")));
			EXPECT_FALSE(res);
			EXPECT_TRUE(
				testDcB[HashableObject(String("key3"))] == String("val3"));
		);

		//     r-reference
		const auto key3 = HashableObject(String("key3"));
		const auto val3 = Object(String("valx"));
		EXPECT_NO_THROW(
			auto res = testDcB.InsertOnly(key3, val3);
			EXPECT_FALSE(res);
			EXPECT_TRUE(testDcB[key3] == String("val3"));
		);
	}

	// Insert-or-assign
	{
		auto testDc = Dict({
			{ Null(),         Bool(false) },
			{ Int64(123),     Int64(321) },
			{ String("key3"), String("val3") },
		});
		DictBaseObj& testDcB = testDc;

		// Insert
		//     l-reference
		EXPECT_NO_THROW(
			auto res = testDcB.InsertOrAssign(
				HashableObject(String("key4")), Object(String("val4")));
			EXPECT_TRUE(res);
			EXPECT_TRUE(
				testDcB[HashableObject(String("key4"))] == String("val4"));
		);

		//     r-reference
		const auto key5 = HashableObject(String("key5"));
		const auto val5 = Object(String("val5"));
		EXPECT_NO_THROW(
			auto res = testDcB.InsertOrAssign(key5, val5);
			EXPECT_TRUE(res);
			EXPECT_TRUE(testDcB[key5] == val5);
		);

		// Assign
		//     l-reference
		EXPECT_NO_THROW(
			auto res = testDcB.InsertOrAssign(
				HashableObject(String("key3")), Object(String("valx")));
			EXPECT_FALSE(res);
			EXPECT_TRUE(
				testDcB[HashableObject(String("key3"))] == String("valx"));
		);

		//     r-reference
		const auto key3 = HashableObject(String("key3"));
		const auto val3 = Object(String("valy"));
		EXPECT_NO_THROW(
			auto res = testDcB.InsertOrAssign(key3, val3);
			EXPECT_FALSE(res);
			EXPECT_TRUE(testDcB[key3] == val3);
		);
	}

	// cast fails
	{
		auto testDc = Dict({
			{ Null(),         Bool(false) },
			{ Int64(123),     Int64(321) },
			{ String("key3"), String("val3") },
		});
		DictBaseObj& testDcB = testDc;

		EXPECT_THROW(
			testDcB.InsertOrAssign(
				HashableObject(String("key4")), String("val4")), TypeError);
		EXPECT_THROW(
			testDcB.InsertOnly(
				HashableObject(String("key4")), String("val4")), TypeError);
		EXPECT_THROW(
			testDcB.InsertOrAssign(
				String("key4"), Object(String("val4"))), TypeError);
		EXPECT_THROW(
			testDcB.InsertOnly(
				String("key4"), Object(String("val4"))), TypeError);

		const auto key5 = HashableObject(String("key5"));
		const auto val5 = Object(String("val5"));
		const auto keyx = String("keyx");
		const auto valx = String("valx");

		EXPECT_THROW(
			testDcB.InsertOrAssign(key5, valx), TypeError);
		EXPECT_THROW(
			testDcB.InsertOnly(key5, valx), TypeError);
		EXPECT_THROW(
			testDcB.InsertOrAssign(keyx, val5), TypeError);
		EXPECT_THROW(
			testDcB.InsertOnly(keyx, val5), TypeError);
	}
}

GTEST_TEST(TestDict, BaseDictRemove)
{
	{
		auto testDc = Dict({
			{ Null(),         Bool(false) },
			{ Int64(123),     Int64(321) },
			{ String("key3"), String("val3") },
		});
		DictBaseObj& testDcB = testDc;

		EXPECT_TRUE(testDcB.HasKey(HashableObject(String("key3"))));

		testDcB.Remove(HashableObject(String("key3")));

		EXPECT_FALSE(testDcB.HasKey(HashableObject(String("key3"))));
	}
}
