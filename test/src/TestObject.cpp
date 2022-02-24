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

GTEST_TEST(TestObject, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

GTEST_TEST(TestObject, Construction)
{
	Object val1;
	EXPECT_TRUE(val1.IsNull());

	Object val2 = String("Test");

	EXPECT_NO_THROW({
		std::unique_ptr<BaseObject> base;
		base.reset(new Object(String("Test")));
		base.reset();
	});

	// Copy/Move
	Object valCpy1(val1);
	Object valMov1(std::move(valCpy1));

	// Copy/Move internal objects
	auto tmpStr = String("Test");
	Object valCpy2(tmpStr);
	Object valMov2(std::move(tmpStr));
}

GTEST_TEST(TestObject, Assignment)
{
	auto tmpStr = String("Test");
	Object tmpHObj = String("Test");

	Object valCpy1;
	Object valMov1;

	// Copy/Move
	valCpy1 = tmpHObj;
	valMov1 = std::move(tmpHObj);
	tmpHObj = valCpy1;

	// Copy/Move internal objects
	valCpy1 = tmpStr;
	valMov1 = std::move(tmpStr);
}

GTEST_TEST(TestObject, Category)
{
	Object val;
	EXPECT_EQ((val).GetCategory(), ObjCategory::Null);
	EXPECT_EQ((val = String("Test")).GetCategory(), ObjCategory::String);
	EXPECT_EQ((val = Int8(123)).GetCategory(), ObjCategory::Integer);
}

GTEST_TEST(TestObject, CategoryName)
{
	Object val;
	EXPECT_EQ((val).GetCategoryName(), std::string("Null"));
	EXPECT_EQ((val = String("Test")).GetCategoryName(), std::string("String"));
	EXPECT_EQ((val = Int8(123)).GetCategoryName(), std::string("Integer"));
}

GTEST_TEST(TestObject, Cast)
{
	Object obj;
	EXPECT_NO_THROW(obj.AsNull());
	EXPECT_THROW(obj.AsNumeric(), TypeError);
	EXPECT_THROW(obj.AsString(), TypeError);
	EXPECT_THROW(obj.AsList(), TypeError);
	EXPECT_THROW(obj.AsDict(), TypeError);
	// test const version
	[obj](){
		EXPECT_NO_THROW(obj.AsNull());
		EXPECT_THROW(obj.AsNumeric(), TypeError);
		EXPECT_THROW(obj.AsString(), TypeError);
		EXPECT_THROW(obj.AsList(), TypeError);
		EXPECT_THROW(obj.AsDict(), TypeError);
	}();

	obj = Bool(true);
	EXPECT_THROW(obj.AsNull(), TypeError);
	EXPECT_NO_THROW(obj.AsNumeric());
	EXPECT_THROW(obj.AsString(), TypeError);
	EXPECT_THROW(obj.AsList(), TypeError);
	EXPECT_THROW(obj.AsDict(), TypeError);
	// test const version
	[obj](){
		EXPECT_THROW(obj.AsNull(), TypeError);
		EXPECT_NO_THROW(obj.AsNumeric());
		EXPECT_THROW(obj.AsString(), TypeError);
		EXPECT_THROW(obj.AsList(), TypeError);
		EXPECT_THROW(obj.AsDict(), TypeError);
	}();

	obj = String("Test");
	EXPECT_THROW(obj.AsNull(), TypeError);
	EXPECT_THROW(obj.AsNumeric(), TypeError);
	EXPECT_NO_THROW(obj.AsString());
	EXPECT_THROW(obj.AsList(), TypeError);
	EXPECT_THROW(obj.AsDict(), TypeError);
	// test const version
	[obj](){
		EXPECT_THROW(obj.AsNull(), TypeError);
		EXPECT_THROW(obj.AsNumeric(), TypeError);
		EXPECT_NO_THROW(obj.AsString());
		EXPECT_THROW(obj.AsList(), TypeError);
		EXPECT_THROW(obj.AsDict(), TypeError);
	}();

	obj = List();
	EXPECT_THROW(obj.AsNull(), TypeError);
	EXPECT_THROW(obj.AsNumeric(), TypeError);
	EXPECT_THROW(obj.AsString(), TypeError);
	EXPECT_NO_THROW(obj.AsList());
	EXPECT_THROW(obj.AsDict(), TypeError);
	// test const version
	[obj](){
		EXPECT_THROW(obj.AsNull(), TypeError);
		EXPECT_THROW(obj.AsNumeric(), TypeError);
		EXPECT_THROW(obj.AsString(), TypeError);
		EXPECT_NO_THROW(obj.AsList());
		EXPECT_THROW(obj.AsDict(), TypeError);
	}();

	obj = Dict();
	EXPECT_THROW(obj.AsNull(), TypeError);
	EXPECT_THROW(obj.AsNumeric(), TypeError);
	EXPECT_THROW(obj.AsString(), TypeError);
	EXPECT_THROW(obj.AsList(), TypeError);
	EXPECT_NO_THROW(obj.AsDict());
	// test const version
	[obj](){
		EXPECT_THROW(obj.AsNull(), TypeError);
		EXPECT_THROW(obj.AsNumeric(), TypeError);
		EXPECT_THROW(obj.AsString(), TypeError);
		EXPECT_THROW(obj.AsList(), TypeError);
		EXPECT_NO_THROW(obj.AsDict());
	}();
}

GTEST_TEST(TestObject, Copy)
{
	EXPECT_EQ(
		*Object(String("Test")).Copy(Object::Base::sk_null),
		String("Test"));
	EXPECT_EQ(
		*Object(String("Test")).Move(Object::Base::sk_null),
		String("Test"));
}

GTEST_TEST(TestObject, Compare)
{
	EXPECT_TRUE(Object(String("")) != Object(Bool(false)));
	EXPECT_TRUE(Object() != Object(Bool(false)));

	EXPECT_TRUE(Object() == Object(Null()));
	EXPECT_TRUE(Object(String("Test")) == Object(String("Test")));
	EXPECT_TRUE(Object(String("Test")) == String("Test"));
}
