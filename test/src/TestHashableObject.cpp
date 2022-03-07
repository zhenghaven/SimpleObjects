// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

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

GTEST_TEST(TestHashableObj, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

GTEST_TEST(TestHashableObj, Construction)
{
	HashableObject val1;
	EXPECT_TRUE(val1.IsNull());

	HashableObject val2 = String("Test");

	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new HashableObject(String("Test")));
		base.reset();
	});

	// Copy/Move
	HashableObject valCpy1(val1);
	HashableObject valMov1(std::move(valCpy1));

	// Copy/Move internal objects
	auto tmpStr = String("Test");
	HashableObject valCpy2(tmpStr);
	HashableObject valMov2(std::move(tmpStr));
}

GTEST_TEST(TestHashableObj, Assignment)
{
	auto tmpStr = String("Test");
	HashableObject tmpHObj = String("Test");

	HashableObject valCpy1;
	HashableObject valMov1;

	// Copy/Move
	valCpy1 = tmpHObj;
	valMov1 = std::move(tmpHObj);
	tmpHObj = valCpy1;

	// Copy/Move internal objects
	valCpy1 = tmpStr;
	valMov1 = std::move(tmpStr);
}

GTEST_TEST(TestHashableObj, Category)
{
	HashableObject val;
	EXPECT_EQ((val).GetCategory(), ObjCategory::Null);
	EXPECT_EQ((val = String("Test")).GetCategory(), ObjCategory::String);
	EXPECT_EQ((val = Int8(123)).GetCategory(), ObjCategory::Integer);
}

GTEST_TEST(TestHashableObj, CategoryName)
{
	HashableObject val;
	EXPECT_EQ((val).GetCategoryName(), std::string("Null"));
	EXPECT_EQ((val = String("Test")).GetCategoryName(), std::string("String"));
	EXPECT_EQ((val = Int8(123)).GetCategoryName(), std::string("Integer"));
}

GTEST_TEST(TestHashableObj, Cast)
{
	HashableObject obj;
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
}

GTEST_TEST(TestHashableObj, Hash)
{
	HashableObject objStr = String("Test");
	std::string cppStr = "Test";

	EXPECT_EQ(std::hash<HashableObject>()(objStr), std::hash<std::string>()(cppStr));
}

GTEST_TEST(TestHashableObj, Copy)
{
	EXPECT_EQ(
		*HashableObject(String("Test")).Copy(HashableObject::Base::sk_null),
		String("Test"));
	EXPECT_EQ(
		*HashableObject(String("Test")).Move(HashableObject::Base::sk_null),
		String("Test"));
}

GTEST_TEST(TestHashableObj, Compare)
{
	EXPECT_TRUE(HashableObject(String("")) != HashableObject(Bool(false)));
	EXPECT_TRUE(HashableObject() != HashableObject(Bool(false)));

	EXPECT_TRUE(HashableObject() == HashableObject(Null()));
	EXPECT_TRUE(HashableObject(String("Test")) == HashableObject(String("Test")));
	EXPECT_TRUE(HashableObject(String("Test")) ==
		static_cast<const HashableBaseObj&>(String("Test")));
}
