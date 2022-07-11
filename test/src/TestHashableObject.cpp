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
	(void)tmp;
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
	HashableObject valCpy1(val2);
	EXPECT_TRUE(valCpy1.BaseObjectIsEqual(String("Test")));
	HashableObject valMov1(std::move(valCpy1));
	EXPECT_TRUE(valMov1.BaseObjectIsEqual(String("Test")));

	// Copy/Move internal objects
	auto tmpStr = String("Test");
	HashableObject valCpy2(tmpStr);
	EXPECT_TRUE(valCpy2.BaseObjectIsEqual(String("Test")));
	HashableObject valMov2(std::move(tmpStr));
	EXPECT_TRUE(valMov2.BaseObjectIsEqual(String("Test")));

	HashableObject valMov3(String("Test").Move(HashableBaseObj::sk_null));
	EXPECT_TRUE(valMov3.BaseObjectIsEqual(String("Test")));
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

	obj = Bytes({ 0x12U });
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
	// Self
	//    !=
	EXPECT_TRUE(
		HashableObject(String("")) !=
		HashableObject(Bool(false)));
	EXPECT_TRUE(
		HashableObject() !=
		HashableObject(Bool(false)));

	EXPECT_TRUE(
		HashableObject() ==
		HashableObject(Null()));
	EXPECT_TRUE(
		HashableObject(String("Test")) ==
		HashableObject(String("Test")));

	//    <
	EXPECT_TRUE(
		HashableObject(Int64(12345)) <
		HashableObject(Int64(54321)));
	EXPECT_THROW(
		(void)(HashableObject() <
		HashableObject(Bool(false))), UnsupportedOperation);

	//    >
	EXPECT_TRUE(
		HashableObject(Int64(54321)) >
		HashableObject(Int64(12345)));
	EXPECT_THROW(
		(void)(HashableObject(String("test")) >
		HashableObject(Bool(false))), UnsupportedOperation);

	//    <=
	EXPECT_TRUE(
		HashableObject(Int8(123)) <=
		HashableObject(Int64(54321)));
	EXPECT_THROW(
		(void)(HashableObject() <=
		HashableObject(Bool(false))), UnsupportedOperation);

	//    >=
	EXPECT_TRUE(
		HashableObject(Int64(54321)) >=
		HashableObject(Bool(true)));
	EXPECT_THROW(
		(void)(HashableObject(String("test")) >=
		HashableObject(Bool(false))), UnsupportedOperation);

	// Base
	//    ==, !=
	EXPECT_TRUE(HashableObject(String("Test")) ==
		static_cast<const BaseObj&>(String("Test")));
	EXPECT_TRUE(HashableObject(String("Test")) !=
		static_cast<const BaseObj&>(Int64(12345)));

	//    <
	EXPECT_TRUE(
		HashableObject(Int64(12345)) <
		static_cast<const BaseObj&>(Int64(54321)));
	EXPECT_THROW(
		(void)(HashableObject() <
		static_cast<const BaseObj&>(Bool(false))), UnsupportedOperation);

	//    >
	EXPECT_TRUE(
		HashableObject(Int64(54321)) >
		static_cast<const BaseObj&>(Int32(12345)));
	EXPECT_THROW(
		(void)(HashableObject(String("test")) >
		static_cast<const BaseObj&>(Bool(false))), UnsupportedOperation);

	//    <=
	EXPECT_TRUE(
		HashableObject(Int64(12345)) <=
		static_cast<const BaseObj&>(Int32(54321)));
	EXPECT_THROW(
		(void)(HashableObject() <=
		static_cast<const BaseObj&>(Bool(false))), UnsupportedOperation);

	//    >=
	EXPECT_TRUE(
		HashableObject(Int64(54321)) >=
		static_cast<const BaseObj&>(Int64(12345)));
	EXPECT_THROW(
		(void)(HashableObject(String("test")) >=
		static_cast<const BaseObj&>(Bool(false))), UnsupportedOperation);
}

GTEST_TEST(TestHashableObj, Setters)
{
	String str1;
	EXPECT_NO_THROW(HashableObject(String()).Set(String()));
	EXPECT_NO_THROW(HashableObject(String()).Set(str1));

	Null null1;
	EXPECT_THROW(HashableObject(String()).Set(Null()), TypeError);
	EXPECT_THROW(HashableObject(String()).Set(null1), TypeError);

	HashableObject b   = Bool();
	HashableObject i8  = Int8();
	HashableObject i32 = Int32();
	HashableObject i64 = Int64();
	HashableObject u8  = UInt8();
	HashableObject u32 = UInt32();
	HashableObject u64 = UInt64();
	HashableObject d   = Double();

	EXPECT_NO_THROW(b.Set(std::numeric_limits<bool>::max()));
	EXPECT_TRUE(b == HashableObject(Bool(std::numeric_limits<bool>::max())));
	EXPECT_NO_THROW(i8.Set(std::numeric_limits<int8_t>::lowest()));
	EXPECT_TRUE(i8 == HashableObject(Int8(std::numeric_limits<int8_t>::lowest())));
	EXPECT_NO_THROW(i32.Set(std::numeric_limits<int32_t>::lowest()));
	EXPECT_TRUE(i32 == HashableObject(Int32(std::numeric_limits<int32_t>::lowest())));
	EXPECT_NO_THROW(i64.Set(std::numeric_limits<int64_t>::lowest()));
	EXPECT_TRUE(i64 == HashableObject(Int64(std::numeric_limits<int64_t>::lowest())));
	EXPECT_NO_THROW(u8.Set(std::numeric_limits<uint8_t>::max()));
	EXPECT_TRUE(u8 == HashableObject(UInt8(std::numeric_limits<uint8_t>::max())));
	EXPECT_NO_THROW(u32.Set(std::numeric_limits<uint32_t>::max()));
	EXPECT_TRUE(u32 == HashableObject(UInt32(std::numeric_limits<uint32_t>::max())));
	EXPECT_NO_THROW(u64.Set(std::numeric_limits<uint64_t>::max()));
	EXPECT_TRUE(u64 == HashableObject(UInt64(std::numeric_limits<uint64_t>::max())));
	EXPECT_NO_THROW(d.Set(std::numeric_limits<double>::max()));
	EXPECT_TRUE(d == HashableObject(Double(std::numeric_limits<double>::max())));
}

GTEST_TEST(TestHashableObj, Getters)
{
	EXPECT_FALSE(HashableObject(String()).IsTrue());
	EXPECT_TRUE( HashableObject(String("T")).IsTrue());

	HashableObject i8  = Int8(std::numeric_limits<int8_t>::lowest());
	EXPECT_TRUE(i8.AsCppInt8() == std::numeric_limits<int8_t>::lowest());
	HashableObject i32 = Int32(std::numeric_limits<int32_t>::lowest());
	EXPECT_TRUE(i32.AsCppInt32() == std::numeric_limits<int32_t>::lowest());
	HashableObject i64 = Int64(std::numeric_limits<int64_t>::lowest());
	EXPECT_TRUE(i64.AsCppInt64() == std::numeric_limits<int64_t>::lowest());
	HashableObject u8  = UInt8(std::numeric_limits<uint8_t>::max());
	EXPECT_TRUE(u8.AsCppUInt8() == std::numeric_limits<uint8_t>::max());
	HashableObject u32 = UInt32(std::numeric_limits<uint32_t>::max());
	EXPECT_TRUE(u32.AsCppUInt32() == std::numeric_limits<uint32_t>::max());
	HashableObject u64 = UInt64(std::numeric_limits<uint64_t>::max());
	EXPECT_TRUE(u64.AsCppUInt64() == std::numeric_limits<uint64_t>::max());
	HashableObject d   = Double(std::numeric_limits<double>::max());
	EXPECT_TRUE(d.AsCppDouble() == std::numeric_limits<double>::max());
}
