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

GTEST_TEST(TestList, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestList, Construction)
{
	// Default
	EXPECT_NO_THROW({
		List().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new List());
		base.reset();
	});

	// Copy & Move
	const List testLs = {String("Test String"), Bool(true), Int64(12345)};
	List cpLs(testLs);
	EXPECT_EQ(cpLs, testLs);
	List mvLs(std::move(cpLs));
	EXPECT_EQ(mvLs, testLs);
}

GTEST_TEST(TestList, Assignment)
{
	const List testLs = {String("Test String"), Bool(true), Int64(12345)};

	List cpLs;
	EXPECT_EQ(cpLs.size(), 0);
	cpLs = testLs;
	EXPECT_EQ(cpLs, testLs);
	// We want to ensure assignment self is OK,
	// meanwhile to avoid compiler warning
	List* cpLsPtr = nullptr;
	cpLsPtr = &cpLs;
	cpLs = *cpLsPtr;
	EXPECT_EQ(cpLs, testLs);

	List mvLs;
	EXPECT_EQ(mvLs.size(), 0);
	mvLs = std::move(cpLs);
	EXPECT_EQ(mvLs, testLs);
	List* mvLsPtr = nullptr;
	mvLsPtr = &mvLs;
	mvLs = std::move(*mvLsPtr);
	EXPECT_EQ(mvLs, testLs);
}

GTEST_TEST(TestList, Category)
{
	static_assert(List::sk_cat() == ObjCategory::List, "Category failed.");
	EXPECT_EQ(List::sk_cat(), ObjCategory::List);

	List val;
	EXPECT_EQ(val.GetCategory(), ObjCategory::List);
}

GTEST_TEST(TestList, CategoryName)
{
	EXPECT_EQ(List().GetCategoryName(), std::string("List"));
}

GTEST_TEST(TestList, Setters)
{
	List ls1;
	EXPECT_NO_THROW(List().Set(List()));
	EXPECT_NO_THROW(List().Set(ls1));

	Null null1;
	EXPECT_THROW(List().Set(Null()), TypeError);
	EXPECT_THROW(List().Set(null1), TypeError);

	EXPECT_THROW(List().Set(static_cast<bool >(true)), TypeError);
	EXPECT_THROW(List().Set(static_cast<uint8_t >(1)), TypeError);
	EXPECT_THROW(List().Set(static_cast< int8_t >(1)), TypeError);
	EXPECT_THROW(List().Set(static_cast<uint32_t>(1)), TypeError);
	EXPECT_THROW(List().Set(static_cast< int32_t>(1)), TypeError);
	EXPECT_THROW(List().Set(static_cast<uint64_t>(1)), TypeError);
	EXPECT_THROW(List().Set(static_cast< int64_t>(1)), TypeError);
	EXPECT_THROW(List().Set(static_cast<double>(1.0)), TypeError);
}

GTEST_TEST(TestList, Getters)
{
	EXPECT_FALSE(List().IsTrue());
	EXPECT_TRUE( List({Null()}).IsTrue());

	EXPECT_THROW(List().AsCppUInt8() ,  TypeError);
	EXPECT_THROW(List().AsCppInt8()  ,  TypeError);
	EXPECT_THROW(List().AsCppUInt32(),  TypeError);
	EXPECT_THROW(List().AsCppInt32() ,  TypeError);
	EXPECT_THROW(List().AsCppUInt64(),  TypeError);
	EXPECT_THROW(List().AsCppInt64() ,  TypeError);
	EXPECT_THROW(List().AsCppDouble() , TypeError);
}

GTEST_TEST(TestList, Compare)
{
	const List testLs_12345 =
		List({String("Test String"), Bool(true), Int64(12345)});
	const List testLs_12345_2 =
		List({String("Test String"), Bool(true), Int64(12345)});
	const List testLs_true =
		List({String("Test String"), Bool(true)});
	const List testLs_12000 =
		List({String("Test String"), Bool(true), Int64(12000)});

	// Self
	// ==
	EXPECT_FALSE(testLs_12345 == testLs_true);
	EXPECT_FALSE(testLs_12345 == testLs_12000);
	EXPECT_TRUE(testLs_12345 == testLs_12345_2);

	// !=
	EXPECT_TRUE(testLs_12345 != testLs_true);
	EXPECT_TRUE(testLs_12345 != testLs_12000);
	EXPECT_FALSE(testLs_12345 != testLs_12345_2);

	// <
	EXPECT_TRUE(
		List({Int64(1), Int64(2), Int64(3)}) <
		List({Int64(3), Int64(2)}));
	EXPECT_TRUE(
		List({Int64(1), Int64(2)}) <
		List({Int64(1), Int64(2), Int64(3)}));
	EXPECT_THROW(
		(void)(
			List({Int64(1), Int64(2), Null()}) <
			List({Int64(1), Int64(2), Null()})),
		UnsupportedOperation);

	// >
	EXPECT_TRUE(
		List({Int64(3), Int64(2)}) >
		List({Int64(1), Int64(2), Int64(3)}));
	EXPECT_TRUE(
		List({Int64(1), Int64(2), Int64(3)}) >
		List({Int64(1), Int64(2)}));

	// <=
	EXPECT_TRUE(
		List({Int64(1), Int64(2), Int64(3)}) <=
		List({Int64(3), Int64(2)}));

	// >=
	EXPECT_TRUE(
		List({Int64(3), Int64(2)}) >=
		List({Int64(1), Int64(2), Int64(3)}));

	// Base
	using ListBaseCmp = CompareTestHelpers<ListBaseObj>;
	// ==
	EXPECT_FALSE(ListBaseCmp::Eq(testLs_12345, testLs_true));
	EXPECT_FALSE(ListBaseCmp::Eq(testLs_12345, testLs_12000));
	EXPECT_TRUE(ListBaseCmp::Eq(testLs_12345, testLs_12345_2));

	// !=
	EXPECT_TRUE(ListBaseCmp::Neq(testLs_12345, testLs_true));
	EXPECT_TRUE(ListBaseCmp::Neq(testLs_12345, testLs_12000));
	EXPECT_FALSE(ListBaseCmp::Neq(testLs_12345, testLs_12345_2));

	// <
	EXPECT_TRUE(ListBaseCmp::Lt(
		List({Int64(1), Int64(2), Int64(3)}),
		List({Int64(3), Int64(2)})));
	EXPECT_THROW(ListBaseCmp::Lt(
		List({Int64(1), Int64(2), Null()}),
		List({Int64(1), Int64(2), Null()})),
		UnsupportedOperation);

	// >
	EXPECT_TRUE(ListBaseCmp::Gt(
		List({Int64(3), Int64(2)}),
		List({Int64(1), Int64(2), Int64(3)})));
	EXPECT_THROW(ListBaseCmp::Gt(
		List({Int64(1), Int64(2), Null()}),
		List({Int64(1), Int64(2), Null()})),
		UnsupportedOperation);

	// <=
	EXPECT_TRUE(ListBaseCmp::Le(
		List({Int64(1), Int64(2), Int64(3)}),
		List({Int64(3), Int64(2)})));

	// >=
	EXPECT_TRUE(ListBaseCmp::Ge(
		List({Int64(3), Int64(2)}),
		List({Int64(1), Int64(2), Int64(3)})));


	// BaseBase => BaseObj
	using BaseObjCmp = CompareTestHelpers<BaseObj>;
	// ==
	EXPECT_FALSE(BaseObjCmp::Eq(testLs_12345, testLs_true));
	EXPECT_FALSE(BaseObjCmp::Eq(testLs_12345, testLs_12000));
	EXPECT_TRUE(BaseObjCmp::Eq(testLs_12345, testLs_12345_2));

	// !=
	EXPECT_TRUE(BaseObjCmp::Neq(testLs_12345, testLs_true));
	EXPECT_TRUE(BaseObjCmp::Neq(testLs_12345, testLs_12000));
	EXPECT_FALSE(BaseObjCmp::Neq(testLs_12345, testLs_12345_2));
	EXPECT_TRUE(BaseObjCmp::Neq(List(), Null()));
	EXPECT_TRUE(BaseObjCmp::Neq(List(), String()));

	// <
	EXPECT_TRUE(BaseObjCmp::Lt(
		List({Int64(1), Int64(2), Int64(3)}),
		List({Int64(3), Int64(2)})));
	EXPECT_TRUE(BaseObjCmp::Lt(
		List({Int64(1), Int64(2)}),
		List({Int64(1), Int64(2), Int64(3)})));
	EXPECT_THROW(BaseObjCmp::Lt(List(), String()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Lt(
		List({Int64(1), Int64(2), Null()}),
		List({Int64(1), Int64(2), Null()})),
		UnsupportedOperation);

	// >
	EXPECT_TRUE(BaseObjCmp::Gt(
		List({Int64(3), Int64(2)}),
		List({Int64(1), Int64(2), Int64(3)})));
	EXPECT_TRUE(BaseObjCmp::Gt(
		List({Int64(1), Int64(2), Int64(3)}),
		List({Int64(1), Int64(2)})));
	EXPECT_THROW(BaseObjCmp::Gt(List(), String()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Gt(
		List({Int64(1), Int64(2), Null()}),
		List({Int64(1), Int64(2), Null()})),
		UnsupportedOperation);

	// <=
	EXPECT_TRUE(BaseObjCmp::Le(
		List({Int64(1), Int64(2), Int64(3)}),
		List({Int64(3), Int64(2)})));

	// >=
	EXPECT_TRUE(BaseObjCmp::Ge(
		List({Int64(3), Int64(2)}),
		List({Int64(1), Int64(2), Int64(3)})));
}

GTEST_TEST(TestList, Len)
{
	EXPECT_EQ(List({String("Test String"), Bool(true), Int64(12345)}).size(), 3);
	EXPECT_EQ(List({String("Test String"), Bool(true)}).size(), 2);
}

GTEST_TEST(TestList, Iterator)
{
	const std::vector<Object> testLs = {String("Test String"), Bool(true), Int64(12345)};
	List cpLs = {String("Test String"), Bool(true), Int64(12345)};
	const List kCpLs = cpLs;

	// const it
	auto itac = testLs.cbegin();
	auto itbc = cpLs.cbegin();
	for(; itac != testLs.cend() && itbc != cpLs.cend(); ++itac, itbc++)
	{
		EXPECT_EQ(*itac, *itbc);
	}

	// const obj begin & end
	itac = testLs.cbegin();
	itbc = kCpLs.begin();
	for(; itac != testLs.cend() && itbc != kCpLs.end(); ++itac, itbc++)
	{
		EXPECT_EQ(*itac, *itbc);
	}

	// const rev it
	auto itacr = testLs.crbegin();
	itbc = cpLs.crbegin();
	for(; itacr != testLs.crend() && itbc != cpLs.crend(); ++itacr, ++itbc)
	{
		EXPECT_EQ(*itacr, *itbc);
	}

	// it
	itac = testLs.cbegin();
	auto itb = cpLs.begin();
	for(; itac != testLs.cend() && itb != cpLs.end(); ++itac, itb++)
	{
		EXPECT_EQ(*itac, *itb);
	}

	// rev it
	itacr = testLs.crbegin();
	itb = cpLs.rbegin();
	for(; itacr != testLs.crend() && itb != cpLs.rend(); ++itacr, ++itb)
	{
		EXPECT_EQ(*itacr, *itb);
	}
}

GTEST_TEST(TestList, At)
{
	const std::vector<Object> testLs = {String("Test String"), Bool(true), Int64(12345)};
	List cpLs = {String("Test String"), Bool(true), Int64(12345)};
	const List kCpLs = cpLs;

	EXPECT_EQ(cpLs[0], testLs[0]);
	EXPECT_EQ(cpLs[2], testLs[2]);

	EXPECT_EQ(kCpLs[0], testLs[0]);
	EXPECT_EQ(kCpLs[1], testLs[1]);
}

GTEST_TEST(TestList, Contains)
{
	List nkLs = {String("Test String"), Bool(true), Int64(12345)};
	EXPECT_TRUE(nkLs.Contains(Int64(12345)) == true);
	EXPECT_TRUE(nkLs.Contains(Int64(12000)) == false);
}

GTEST_TEST(TestList, PushPopBack)
{
	//pushback
	List nkLs{String("Test String"),};
	EXPECT_EQ(nkLs, List({String("Test String"),}));
	EXPECT_NO_THROW(nkLs.push_back(Int64(12345)));
	EXPECT_EQ(nkLs, List({String("Test String"),Int64(12345)}));
	const auto tmpVal = Object(Double(123.0));
	EXPECT_NO_THROW(nkLs.push_back(tmpVal));
	EXPECT_EQ(nkLs, List({String("Test String"),Int64(12345), Double(123.0)}));

	//popback
	EXPECT_NO_THROW(nkLs.pop_back());
	EXPECT_NO_THROW(nkLs.pop_back());
	EXPECT_EQ(nkLs, List({String("Test String"),}));
}

GTEST_TEST(TestList, Append)
{
	//Append
	List nkLs{String("Test String"),};
	EXPECT_NO_THROW(
		nkLs.Append(List({Int64(12345), Bool(true)}))
	);
	EXPECT_EQ(
		nkLs,
		List({String("Test String"), Int64(12345), Bool(true)})
	);
}

GTEST_TEST(TestList, Capacity)
{
	List nkLs;
	EXPECT_EQ(nkLs.size(), 0);

	//Reserve
	EXPECT_NO_THROW(nkLs.reserve(3));

	//Resize
	EXPECT_NO_THROW(nkLs.resize(3));
	EXPECT_EQ(nkLs,
		List({Null(), Null(), Null()}));
}

GTEST_TEST(TestList, Data)
{
	//Data
	List nkLs{String("Test String"),};
	EXPECT_EQ(nkLs.data(), &nkLs[0]);
}

GTEST_TEST(TestList, InsertRemove)
{
	List nkLs = {String("Test String"), Bool(true)};

	//Insert
	EXPECT_NO_THROW(nkLs.Insert(1, Int64(12345)));
	EXPECT_EQ(nkLs,
		List({String("Test String"), Int64(12345), Bool(true)}));

	//remove
	EXPECT_NO_THROW(nkLs.Remove(1));
	EXPECT_EQ(nkLs,
		List({String("Test String"), Bool(true)}));
}

GTEST_TEST(TestList, Miscs)
{
	// Is null
	EXPECT_FALSE(List().IsNull());

	// Cast
	const auto kList = List();
	EXPECT_NO_THROW(kList.AsList());
	EXPECT_THROW(kList.AsNull(),       TypeError);
	EXPECT_THROW(kList.AsNumeric(),    TypeError);
	EXPECT_THROW(kList.AsString(),     TypeError);
	EXPECT_THROW(kList.AsDict(),       TypeError);
	EXPECT_THROW(kList.AsStaticDict(), TypeError);
	EXPECT_THROW(kList.AsBytes(),      TypeError);

	EXPECT_NO_THROW(List().AsList());
	EXPECT_THROW(List().AsNull(),       TypeError);
	EXPECT_THROW(List().AsNumeric(),    TypeError);
	EXPECT_THROW(List().AsString(),     TypeError);
	EXPECT_THROW(List().AsDict(),       TypeError);
	EXPECT_THROW(List().AsStaticDict(), TypeError);
	EXPECT_THROW(List().AsBytes(),      TypeError);

	// Copy
	static_assert(std::is_same<
		decltype(*List().Copy(List::Base::sk_null)),
		ListBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*List({String("Test")}).Copy(List::Base::sk_null), List({String("Test")}));

	static_assert(std::is_same<
		decltype(*List().Copy(List::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*List({String("Test")}).Copy(List::Base::Base::sk_null), List({String("Test")}));

	// Move
	auto mList = List({String("Test")});

	static_assert(std::is_same<
		decltype(*List().Move(List::Base::sk_null)),
		ListBaseObj&>::value, "Failed to test Move virtual func");
	mList = List({String("Test")});
	EXPECT_EQ(*mList.Move(List::Base::sk_null), List({String("Test")}));
	EXPECT_EQ(mList.size(), 0);

	static_assert(std::is_same<
		decltype(*List().Move(List::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Move virtual func");
	mList = List({String("Test")});
	EXPECT_EQ(*mList.Move(List::Base::Base::sk_null), List({String("Test")}));
	EXPECT_EQ(mList.size(), 0);
}

GTEST_TEST(TestList, ToString)
{
	std::string expRes = "[ null, 123, \"test\", { null : null } ]";
	std::string expSRes = "[null,123,\"test\",{null:null}]";

	auto testLs = List({
		Null(), Int64(123), String("test"), Dict({
			{Null(), Null()},}),});

	// DebugString
	{
		EXPECT_EQ(testLs.DebugString(), expRes);
		EXPECT_EQ(testLs.ShortDebugString(), expSRes);
	}

	// ToString
	{
		EXPECT_EQ(testLs.ToString(), expRes);
	}

	// DumpString
	{
		std::string res;
		EXPECT_NO_THROW(
			testLs.DumpString(ToOutIt<char>(std::back_inserter(res))));
		EXPECT_EQ(res, expRes);
	}
}

GTEST_TEST(TestList, BaseListIterators)
{
	// non-const
	{
		auto testLs = List({ Null(), Int64(123), String("test"), });
		ListBaseObj& testLsB = testLs;

		auto it = testLsB.begin();

		EXPECT_TRUE(it != testLsB.end());
		EXPECT_TRUE((*it) == Null());
		EXPECT_NO_THROW(++it);

		EXPECT_TRUE(it != testLsB.end());
		EXPECT_TRUE((*it) == Int64(123));
		EXPECT_TRUE((*it) != Int64(321));
		EXPECT_NO_THROW(++it);

		EXPECT_TRUE(it != testLsB.end());
		EXPECT_TRUE((*it) == String("test"));
		EXPECT_TRUE((*it) != String("testXX"));
		// mutate value
		EXPECT_NO_THROW((*it).AsString().push_back('Y'));
		EXPECT_TRUE((*it) == String("testY"));
		EXPECT_TRUE((*it) != String("testXX"));
		EXPECT_NO_THROW(++it);

		EXPECT_TRUE(it == testLsB.end());
	}

	// const
	{
		auto testLs = List({ Null(), Int64(123), String("test"), });
		const ListBaseObj& testLsB = testLs;

		auto it = testLsB.begin();

		EXPECT_TRUE(it != testLsB.end());
		EXPECT_TRUE((*it) == Null());
		EXPECT_NO_THROW(++it);

		EXPECT_TRUE(it != testLsB.end());
		EXPECT_TRUE((*it) == Int64(123));
		EXPECT_TRUE((*it) != Int64(321));
		EXPECT_NO_THROW(++it);

		EXPECT_TRUE(it != testLsB.end());
		EXPECT_TRUE((*it) == String("test"));
		EXPECT_TRUE((*it) != String("testXX"));
		EXPECT_NO_THROW(++it);

		EXPECT_TRUE(it == testLsB.end());
	}
}

GTEST_TEST(TestList, BaseListIndexing)
{

	// non-const
	{
		auto testLs = List({ Null(), Int64(123), String("test"), });
		ListBaseObj& testLsB = testLs;

		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[0] == Null()));
		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[1] == Int64(123)));
		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[2] == String("test")));
		EXPECT_NO_THROW((testLsB[2].AsString().push_back('Y')));
		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[2] == String("testY")));

		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[1] != Int64(321)));
		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[2] != String("testX")));

		EXPECT_THROW(testLsB[3], IndexError);
		EXPECT_THROW(testLsB[100], IndexError);
	}

	// const
	{
		auto testLs = List({ Null(), Int64(123), String("test"), });
		const ListBaseObj& testLsB = testLs;

		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[0] == Null()));
		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[1] == Int64(123)));
		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[2] == String("test")));

		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[1] != Int64(321)));
		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[2] != String("testX")));

		EXPECT_THROW(testLsB[3], IndexError);
		EXPECT_THROW(testLsB[100], IndexError);
	}
}

GTEST_TEST(TestList, BaseListContains)
{
	// const
	{
		auto testLs = List({ Null(), Int64(123), String("test"), });
		const ListBaseObj& testLsB = testLs;

		EXPECT_TRUE(testLsB.Contains(Int64(123)));
		EXPECT_FALSE(testLsB.Contains(Int64(321)));
	}
}

GTEST_TEST(TestList, BaseListPushBackAppend)
{

	// push_back
	{
		auto testLs = List({ Null(), Int64(123), String("test"), });
		ListBaseObj& testLsB = testLs;

		// R-value
		EXPECT_NO_THROW(testLsB.push_back(Object(Bool(true))));
		EXPECT_THROW(testLsB.push_back(Double(1.23)), TypeError);

		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[3] == Bool(true)));

		// L-value
		const auto val1 = Object(Bool(false));
		const auto val2 = Double(1.23);

		EXPECT_NO_THROW(testLsB.push_back(val1));
		EXPECT_THROW(testLsB.push_back(val2), TypeError);

		EXPECT_NO_THROW(EXPECT_TRUE(testLsB[4] == Bool(false)));
	}

	// Append
	{
		auto testLs = List({ Null(), Int64(123), String("test"), });
		ListBaseObj& testLsB = testLs;

		auto testLsA = List({ Bool(true), Double(0.0), });

		testLsB.Append(testLsA);
		EXPECT_TRUE(testLs ==
			List({ Null(), Int64(123), String("test"),
				Bool(true), Double(0.0), }));
	}
}
