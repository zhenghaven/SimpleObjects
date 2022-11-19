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

GTEST_TEST(TestObject, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestObject, Construction)
{
	Object val1;
	EXPECT_TRUE(val1.IsNull());

	Object val2 = String("Test");

	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Object(String("Test")));
		base.reset();
	});

	// Copy/Move
	Object valCpy1(val2);
	EXPECT_TRUE(valCpy1.BaseObjectIsEqual(String("Test")));
	Object valMov1(std::move(valCpy1));
	EXPECT_TRUE(valMov1.BaseObjectIsEqual(String("Test")));

	// Copy/Move internal objects
	auto tmpStr = String("Test");
	Object valCpy2(tmpStr);
	EXPECT_TRUE(valCpy2.BaseObjectIsEqual(String("Test")));
	Object valMov2(std::move(tmpStr));
	EXPECT_TRUE(valMov2.BaseObjectIsEqual(String("Test")));

	Object valMov3(String("Test").Move(Object::sk_null));
	EXPECT_TRUE(valMov3.BaseObjectIsEqual(String("Test")));
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
	EXPECT_THROW(obj.AsRealNum(),    TypeError);
	EXPECT_THROW(obj.AsString(),     TypeError);
	EXPECT_THROW(obj.AsList(),       TypeError);
	EXPECT_THROW(obj.AsDict(),       TypeError);
	EXPECT_THROW(obj.AsStaticDict(), TypeError);
	EXPECT_THROW(obj.AsBytes(),      TypeError);
	EXPECT_NO_THROW(obj.AsHashable());
	// test const version
	[obj](){
		EXPECT_NO_THROW(obj.AsNull());
		EXPECT_THROW(obj.AsRealNum(),    TypeError);
		EXPECT_THROW(obj.AsString(),     TypeError);
		EXPECT_THROW(obj.AsList(),       TypeError);
		EXPECT_THROW(obj.AsDict(),       TypeError);
		EXPECT_THROW(obj.AsStaticDict(), TypeError);
		EXPECT_THROW(obj.AsBytes(),      TypeError);
		EXPECT_NO_THROW(obj.AsHashable());
	}();

	obj = Bool(true);
	EXPECT_THROW(obj.AsNull(),       TypeError);
	EXPECT_NO_THROW(obj.AsRealNum());
	EXPECT_THROW(obj.AsString(),     TypeError);
	EXPECT_THROW(obj.AsList(),       TypeError);
	EXPECT_THROW(obj.AsDict(),       TypeError);
	EXPECT_THROW(obj.AsStaticDict(), TypeError);
	EXPECT_THROW(obj.AsBytes(),      TypeError);
	EXPECT_NO_THROW(obj.AsHashable());
	// test const version
	[obj](){
		EXPECT_THROW(obj.AsNull(),       TypeError);
		EXPECT_NO_THROW(obj.AsRealNum());
		EXPECT_THROW(obj.AsString(),     TypeError);
		EXPECT_THROW(obj.AsList(),       TypeError);
		EXPECT_THROW(obj.AsDict(),       TypeError);
		EXPECT_THROW(obj.AsStaticDict(), TypeError);
		EXPECT_THROW(obj.AsBytes(),      TypeError);
		EXPECT_NO_THROW(obj.AsHashable());
	}();

	obj = String("Test");
	EXPECT_THROW(obj.AsNull(),       TypeError);
	EXPECT_THROW(obj.AsRealNum(),    TypeError);
	EXPECT_NO_THROW(obj.AsString());
	EXPECT_THROW(obj.AsList(),       TypeError);
	EXPECT_THROW(obj.AsDict(),       TypeError);
	EXPECT_THROW(obj.AsStaticDict(), TypeError);
	EXPECT_THROW(obj.AsBytes(),      TypeError);
	EXPECT_NO_THROW(obj.AsHashable());
	// test const version
	[obj](){
		EXPECT_THROW(obj.AsNull(),       TypeError);
		EXPECT_THROW(obj.AsRealNum(),    TypeError);
		EXPECT_NO_THROW(obj.AsString());
		EXPECT_THROW(obj.AsList(),       TypeError);
		EXPECT_THROW(obj.AsDict(),       TypeError);
		EXPECT_THROW(obj.AsStaticDict(), TypeError);
		EXPECT_THROW(obj.AsBytes(),      TypeError);
		EXPECT_NO_THROW(obj.AsHashable());
	}();

	obj = List();
	EXPECT_THROW(obj.AsNull(),       TypeError);
	EXPECT_THROW(obj.AsRealNum(),    TypeError);
	EXPECT_THROW(obj.AsString(),     TypeError);
	EXPECT_NO_THROW(obj.AsList());
	EXPECT_THROW(obj.AsDict(),       TypeError);
	EXPECT_THROW(obj.AsStaticDict(), TypeError);
	EXPECT_THROW(obj.AsBytes(),      TypeError);
	EXPECT_THROW(obj.AsHashable(),   TypeError);
	// test const version
	[obj](){
		EXPECT_THROW(obj.AsNull(),       TypeError);
		EXPECT_THROW(obj.AsRealNum(),    TypeError);
		EXPECT_THROW(obj.AsString(),     TypeError);
		EXPECT_NO_THROW(obj.AsList());
		EXPECT_THROW(obj.AsDict(),       TypeError);
		EXPECT_THROW(obj.AsStaticDict(), TypeError);
		EXPECT_THROW(obj.AsBytes(),      TypeError);
		EXPECT_THROW(obj.AsHashable(),   TypeError);
	}();

	obj = Dict();
	EXPECT_THROW(obj.AsNull(),       TypeError);
	EXPECT_THROW(obj.AsRealNum(),    TypeError);
	EXPECT_THROW(obj.AsString(),     TypeError);
	EXPECT_THROW(obj.AsList(),       TypeError);
	EXPECT_NO_THROW(obj.AsDict());
	EXPECT_THROW(obj.AsStaticDict(), TypeError);
	EXPECT_THROW(obj.AsBytes(),      TypeError);
	EXPECT_THROW(obj.AsHashable(),   TypeError);
	// test const version
	[obj](){
		EXPECT_THROW(obj.AsNull(),       TypeError);
		EXPECT_THROW(obj.AsRealNum(),    TypeError);
		EXPECT_THROW(obj.AsString(),     TypeError);
		EXPECT_THROW(obj.AsList(),       TypeError);
		EXPECT_NO_THROW(obj.AsDict());
		EXPECT_THROW(obj.AsStaticDict(), TypeError);
		EXPECT_THROW(obj.AsBytes(),      TypeError);
		EXPECT_THROW(obj.AsHashable(),   TypeError);
	}();

	obj = Bytes();
	EXPECT_THROW(obj.AsNull(),       TypeError);
	EXPECT_THROW(obj.AsRealNum(),    TypeError);
	EXPECT_THROW(obj.AsString(),     TypeError);
	EXPECT_THROW(obj.AsList(),       TypeError);
	EXPECT_THROW(obj.AsDict(),       TypeError);
	EXPECT_THROW(obj.AsStaticDict(), TypeError);
	EXPECT_NO_THROW(obj.AsBytes());
	EXPECT_NO_THROW(obj.AsHashable());
	// test const version
	[obj](){
		EXPECT_THROW(obj.AsNull(),       TypeError);
		EXPECT_THROW(obj.AsRealNum(),    TypeError);
		EXPECT_THROW(obj.AsString(),     TypeError);
		EXPECT_THROW(obj.AsList(),       TypeError);
		EXPECT_THROW(obj.AsDict(),       TypeError);
		EXPECT_THROW(obj.AsStaticDict(), TypeError);
		EXPECT_NO_THROW(obj.AsBytes());
		EXPECT_NO_THROW(obj.AsHashable());
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
	// Self
	//    !=
	EXPECT_TRUE(
		Object(String("")) !=
		Object(Bool(false)));
	EXPECT_TRUE(
		Object() !=
		Object(Bool(false)));

	//    ==
	EXPECT_TRUE(
		Object() ==
		Object(Null()));
	EXPECT_TRUE(
		Object(String("Test")) ==
		Object(String("Test")));

	//    <
	EXPECT_TRUE(
		Object(Int64(12345)) <
		Object(Int64(54321)));
	EXPECT_THROW(
		(void)(Object() <
		Object(Bool(false))), UnsupportedOperation);

	//    >
	EXPECT_TRUE(
		Object(Int64(54321)) >
		Object(Int64(12345)));
	EXPECT_THROW(
		(void)(Object(String("test")) >
		Object(Bool(false))), UnsupportedOperation);

	//    <=
	EXPECT_TRUE(
		Object(Int64(12345)) <=
		Object(Int64(54321)));
	EXPECT_THROW(
		(void)(Object(List()) <=
		Object(Bool(false))), UnsupportedOperation);

	//    >=
	EXPECT_TRUE(
		Object(Int64(54321)) >=
		Object(Int64(12345)));
	EXPECT_THROW(
		(void)(Object(Dict()) >=
		Object(Bool(false))), UnsupportedOperation);

	// Base
	//    ==, !=
	EXPECT_TRUE(
		Object(String("Test")) ==
		static_cast<const BaseObj&>(String("Test")));
	EXPECT_FALSE(
		Object(String("Test")) !=
		static_cast<const BaseObj&>(String("Test")));

	//    <
	EXPECT_TRUE(
		Object(Int64(12345)) <
		static_cast<const BaseObj&>(Int64(54321)));
	EXPECT_THROW(
		(void)(Object() <
		static_cast<const BaseObj&>(Bool(false))), UnsupportedOperation);

	//    >
	EXPECT_TRUE(
		Object(Int64(54321)) >
		static_cast<const BaseObj&>(Int64(12345)));
	EXPECT_THROW(
		(void)(Object(String("test")) >
		static_cast<const BaseObj&>(Bool(false))), UnsupportedOperation);

	//    <=
	EXPECT_TRUE(
		Object(Int64(12345)) <=
		static_cast<const BaseObj&>(Int64(54321)));
	EXPECT_THROW(
		(void)(Object(List()) <=
		static_cast<const BaseObj&>(Bool(false))), UnsupportedOperation);

	//    >=
	EXPECT_TRUE(
		Object(Int64(54321)) >=
		static_cast<const BaseObj&>(Int64(12345)));
	EXPECT_THROW(
		(void)(Object(Dict()) >=
		static_cast<const BaseObj&>(Bool(false))), UnsupportedOperation);
}

GTEST_TEST(TestObject, Setters)
{
	String str1;
	EXPECT_NO_THROW(Object(String()).Set(String()));
	EXPECT_NO_THROW(Object(String()).Set(str1));

	Null null1;
	EXPECT_THROW(Object(String()).Set(Null()), TypeError);
	EXPECT_THROW(Object(String()).Set(null1), TypeError);

	Object b   = Bool();
	Object i8  = Int8();
	Object i32 = Int32();
	Object i64 = Int64();
	Object u8  = UInt8();
	Object u32 = UInt32();
	Object u64 = UInt64();
	Object d   = Double();

	EXPECT_NO_THROW(b.Set((std::numeric_limits<bool>::max)()));
	EXPECT_TRUE(b == Object(Bool((std::numeric_limits<bool>::max)())));
	EXPECT_NO_THROW(i8.Set(std::numeric_limits<int8_t>::lowest()));
	EXPECT_TRUE(i8 == Object(Int8(std::numeric_limits<int8_t>::lowest())));
	EXPECT_NO_THROW(i32.Set(std::numeric_limits<int32_t>::lowest()));
	EXPECT_TRUE(i32 == Object(Int32(std::numeric_limits<int32_t>::lowest())));
	EXPECT_NO_THROW(i64.Set(std::numeric_limits<int64_t>::lowest()));
	EXPECT_TRUE(i64 == Object(Int64(std::numeric_limits<int64_t>::lowest())));
	EXPECT_NO_THROW(u8.Set((std::numeric_limits<uint8_t>::max)()));
	EXPECT_TRUE(u8 == Object(UInt8((std::numeric_limits<uint8_t>::max)())));
	EXPECT_NO_THROW(u32.Set((std::numeric_limits<uint32_t>::max)()));
	EXPECT_TRUE(u32 == Object(UInt32((std::numeric_limits<uint32_t>::max)())));
	EXPECT_NO_THROW(u64.Set((std::numeric_limits<uint64_t>::max)()));
	EXPECT_TRUE(u64 == Object(UInt64((std::numeric_limits<uint64_t>::max)())));
	EXPECT_NO_THROW(d.Set((std::numeric_limits<double>::max)()));
	EXPECT_TRUE(d == Object(Double((std::numeric_limits<double>::max)())));
}

GTEST_TEST(TestObject, Getters)
{
	EXPECT_FALSE(Object(String()).IsTrue());
	EXPECT_TRUE( Object(String("T")).IsTrue());

	Object i8  = Int8(std::numeric_limits<int8_t>::lowest());
	EXPECT_TRUE(i8.AsCppInt8() == std::numeric_limits<int8_t>::lowest());
	Object i32 = Int32(std::numeric_limits<int32_t>::lowest());
	EXPECT_TRUE(i32.AsCppInt32() == std::numeric_limits<int32_t>::lowest());
	Object i64 = Int64(std::numeric_limits<int64_t>::lowest());
	EXPECT_TRUE(i64.AsCppInt64() == std::numeric_limits<int64_t>::lowest());
	Object u8  = UInt8((std::numeric_limits<uint8_t>::max)());
	EXPECT_TRUE(u8.AsCppUInt8() == (std::numeric_limits<uint8_t>::max)());
	Object u32 = UInt32((std::numeric_limits<uint32_t>::max)());
	EXPECT_TRUE(u32.AsCppUInt32() == (std::numeric_limits<uint32_t>::max)());
	Object u64 = UInt64((std::numeric_limits<uint64_t>::max)());
	EXPECT_TRUE(u64.AsCppUInt64() == (std::numeric_limits<uint64_t>::max)());
	Object d   = Double((std::numeric_limits<double>::max)());
	EXPECT_TRUE(d.AsCppDouble() == (std::numeric_limits<double>::max)());
}
