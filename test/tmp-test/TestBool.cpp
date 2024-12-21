#include <gtest/gtest.h>

#include <memory>

#include <SimpleObjects/SimpleObjects.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestBool, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

GTEST_TEST(TestBool, Construction)
{
	const bool testTrue = true;
	const bool testFalse = false;
	bool testTrue2 = true;
	bool testFalse2 = false;

	// Default
	EXPECT_EQ(Bool().GetVal(), false);
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObject> base;
		base.reset(new Bool());
		base.reset();
	});

	// Copy/move bool
	EXPECT_EQ(Bool(testTrue).GetVal(), true);
	EXPECT_EQ(Bool(testFalse).GetVal(), false);
	EXPECT_EQ(Bool(std::move(testTrue2)).GetVal(), true);
	EXPECT_EQ(Bool(std::move(testFalse2)).GetVal(), false);

	const Bool testTrueObj(true);
	const Bool testFalseObj(false);

	// Copy/move Bool
	EXPECT_EQ(Bool(testTrueObj).GetVal(), true);
	EXPECT_EQ(Bool(testFalseObj).GetVal(), false);
	EXPECT_EQ(Bool(Bool(true)).GetVal(), true);
	EXPECT_EQ(Bool(Bool(false)).GetVal(), false);
}

GTEST_TEST(TestBool, Cast)
{
	EXPECT_EQ(static_cast<bool>(Bool(true)), true);
	EXPECT_EQ(static_cast<bool>(Bool(false)), false);
}

GTEST_TEST(TestBool, Assignment)
{
	const bool testTrue = true;
	const bool testFalse = false;
	Bool testVar;

	// Copy/move bool
	EXPECT_EQ((testVar = testTrue).GetVal(), true);
	EXPECT_EQ((testVar = testFalse).GetVal(), false);
	EXPECT_EQ((testVar = true).GetVal(), true);
	EXPECT_EQ((testVar = false).GetVal(), false);

	const Bool testTrueObj(true);
	const Bool testFalseObj(false);

	// Copy/move Bool
	EXPECT_EQ((testVar = testTrueObj).GetVal(), true);
	EXPECT_EQ((testVar = testFalseObj).GetVal(), false);
	EXPECT_EQ((testVar = Bool(true)).GetVal(), true);
	EXPECT_EQ((testVar = Bool(false)).GetVal(), false);
}

GTEST_TEST(TestBool, Equality)
{
	const Bool testTrueObj(true);
	const Bool testFalseObj(false);

	// Bool to bool
	EXPECT_TRUE(testTrueObj == true);
	EXPECT_FALSE(testTrueObj == false);
	EXPECT_TRUE(testFalseObj == false);
	EXPECT_FALSE(testFalseObj == true);

	EXPECT_FALSE(testTrueObj != true);
	EXPECT_TRUE(testTrueObj != false);
	EXPECT_FALSE(testFalseObj != false);
	EXPECT_TRUE(testFalseObj != true);

	// bool to Bool
	EXPECT_TRUE(true == testTrueObj);
	EXPECT_FALSE(false == testTrueObj);
	EXPECT_TRUE(false == testFalseObj);
	EXPECT_FALSE(true == testFalseObj);

	EXPECT_FALSE(true != testTrueObj);
	EXPECT_TRUE(false != testTrueObj);
	EXPECT_FALSE(false != testFalseObj);
	EXPECT_TRUE(true != testFalseObj);

	// Bool to Bool
	EXPECT_TRUE(testTrueObj == Bool(true));
	EXPECT_FALSE(testTrueObj == Bool(false));
	EXPECT_TRUE(testFalseObj == Bool(false));
	EXPECT_FALSE(testFalseObj == Bool(true));

	EXPECT_FALSE(testTrueObj != Bool(true));
	EXPECT_TRUE(testTrueObj != Bool(false));
	EXPECT_FALSE(testFalseObj != Bool(false));
	EXPECT_TRUE(testFalseObj != Bool(true));
}

GTEST_TEST(TestBool, Category)
{
	static_assert(Bool::sk_cat() == ObjCategory::Bool, "Category failed.");
	EXPECT_EQ(Bool::sk_cat(), ObjCategory::Bool);

	Bool val;
	EXPECT_EQ(val.GetCategory(), ObjCategory::Bool);
}