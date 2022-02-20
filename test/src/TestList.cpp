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

GTEST_TEST(TestList, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

GTEST_TEST(TestList, Construction)
{
	// Default
	EXPECT_NO_THROW({
		List().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObject> base;
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
	EXPECT_EQ(cpLs.Len(), 0);
	cpLs = testLs;
	EXPECT_EQ(cpLs, testLs);
	cpLs = cpLs;
	EXPECT_EQ(cpLs, testLs);

	List mvLs;
	EXPECT_EQ(mvLs.Len(), 0);
	mvLs = std::move(cpLs);
	EXPECT_EQ(mvLs, testLs);
	mvLs = std::move(mvLs);
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

GTEST_TEST(TestList, Compare)
{
	// ==
	EXPECT_TRUE(
		List({String("Test String"), Bool(true), Int64(12345)}) !=
		List({String("Test String"), Bool(true)}));
	EXPECT_TRUE(
		List({String("Test String"), Bool(true), Int64(12345)}) !=
		List({String("Test String"), Bool(true), Int64(12000)}));
	EXPECT_FALSE(
		List({String("Test String"), Bool(true), Int64(12345)}) !=
		List({String("Test String"), Bool(true), Int64(12345)}));

	// == diff obj
	EXPECT_TRUE(List() != Null());
	EXPECT_TRUE(List() != String());

	// <
	EXPECT_THROW(List() < List(), UnsupportedOperation);

	// < diff obj
	EXPECT_THROW(List() < String(), UnsupportedOperation);

	// >
	EXPECT_THROW(List() > List(), UnsupportedOperation);

	// > diff obj
	EXPECT_THROW(List() < String(), UnsupportedOperation);
}

GTEST_TEST(TestList, Len)
{
	EXPECT_EQ(List({String("Test String"), Bool(true), Int64(12345)}).Len(), 3);
	EXPECT_EQ(List({String("Test String"), Bool(true)}).Len(), 2);
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
	// non const
	List nkLs = {String("Test String"), Bool(true), Int64(12345)};
	EXPECT_EQ(nkLs.Contains(Int64(12345)), nkLs.begin() + 2);
	EXPECT_EQ(nkLs.Contains(Int64(12000)), nkLs.end());

	// const
	const List kLs = {String("Test String"), Bool(true), Int64(12345)};
	EXPECT_EQ(kLs.Contains(Int64(12345)), kLs.begin() + 2);
	EXPECT_EQ(kLs.Contains(Int64(12000)), kLs.end());
}

GTEST_TEST(TestList, PushPopBack)
{
	//pushback
	List nkLs{String("Test String"),};
	EXPECT_EQ(nkLs, List({String("Test String"),}));
	EXPECT_NO_THROW(nkLs.PushBack(Int64(12345)));
	EXPECT_EQ(nkLs, List({String("Test String"),Int64(12345)}));

	//popback
	EXPECT_NO_THROW(nkLs.PopBack());
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
	EXPECT_EQ(nkLs.Len(), 0);

	//Reserve
	EXPECT_NO_THROW(nkLs.Reserve(3));

	//Resize
	EXPECT_NO_THROW(nkLs.Resize(3));
	EXPECT_EQ(nkLs,
		List({Null(), Null(), Null()}));
}

GTEST_TEST(TestList, Data)
{
	//Data
	List nkLs{String("Test String"),};
	EXPECT_EQ(nkLs.Data(), &nkLs[0]);
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
	EXPECT_THROW(kList.AsNull(), TypeError);
	EXPECT_THROW(kList.AsNumeric(), TypeError);
	EXPECT_THROW(kList.AsString(), TypeError);

	EXPECT_NO_THROW(List().AsList());
	EXPECT_THROW(List().AsNull(), TypeError);
	EXPECT_THROW(List().AsNumeric(), TypeError);
	EXPECT_THROW(List().AsString(), TypeError);

	// Copy
	static_assert(std::is_same<
		decltype(*List().Copy(List::Base::sk_null)),
		ListBaseObject<Object>&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*List({String("Test")}).Copy(List::Base::sk_null), List({String("Test")}));

	static_assert(std::is_same<
		decltype(*List().Copy(List::Base::Base::sk_null)),
		BaseObject&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*List({String("Test")}).Copy(List::Base::Base::sk_null), List({String("Test")}));

	// Move
	auto mList = List({String("Test")});

	static_assert(std::is_same<
		decltype(*List().Move(List::Base::sk_null)),
		ListBaseObject<Object>&>::value, "Failed to test Move virtual func");
	mList = List({String("Test")});
	EXPECT_EQ(*mList.Move(List::Base::sk_null), List({String("Test")}));
	EXPECT_EQ(mList.Len(), 0);

	static_assert(std::is_same<
		decltype(*List().Move(List::Base::Base::sk_null)),
		BaseObject&>::value, "Failed to test Move virtual func");
	mList = List({String("Test")});
	EXPECT_EQ(*mList.Move(List::Base::Base::sk_null), List({String("Test")}));
	EXPECT_EQ(mList.Len(), 0);
}
