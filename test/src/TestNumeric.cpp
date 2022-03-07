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
} // namespace SimpleObjects_Test

GTEST_TEST(TestNumeric, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

GTEST_TEST(TestNumeric, Construction)
{
	// Default
	EXPECT_NO_THROW({
		Bool().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Bool());
		base.reset();
	});
	EXPECT_NO_THROW({
		Int8().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Int8());
		base.reset();
	});
	EXPECT_NO_THROW({
		Int16().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Int16());
		base.reset();
	});
	EXPECT_NO_THROW({
		Int32().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Int32());
		base.reset();
	});
	EXPECT_NO_THROW({
		Int64().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Int64());
		base.reset();
	});
	EXPECT_NO_THROW({
		UInt8().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new UInt8());
		base.reset();
	});
	EXPECT_NO_THROW({
		UInt16().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new UInt16());
		base.reset();
	});
	EXPECT_NO_THROW({
		UInt32().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new UInt32());
		base.reset();
	});
	EXPECT_NO_THROW({
		UInt64().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new UInt64());
		base.reset();
	});
	EXPECT_NO_THROW({
		Float().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Float());
		base.reset();
	});
	EXPECT_NO_THROW({
		Double().GetVal();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new Double());
		base.reset();
	});

	const int testVal1 = 1234567;
	int testVal2 = 7654321;
	const Int32 testVal3(testVal1);

	// Copy/move _InternalType
	EXPECT_EQ(Int32(testVal1).GetVal(), testVal1);
	EXPECT_EQ(Int32(std::move(testVal2)).GetVal(), testVal2);

	// Copy/move _InternalType
	EXPECT_EQ(Int32(testVal3).GetVal(), testVal1);
	EXPECT_EQ(Int32(Int32(testVal2)).GetVal(), testVal2);
}

GTEST_TEST(TestNumeric, Cast)
{
	EXPECT_EQ(static_cast<bool>(Bool(true)),
		static_cast<bool>(true));
	EXPECT_EQ(static_cast<bool>(Bool(false)),
		static_cast<bool>(false));

	// Integer -> bool
	EXPECT_EQ(static_cast<bool>(Int8(2)),
		static_cast<bool>(static_cast<int8_t>(2)));
	EXPECT_EQ(static_cast<bool>(Int8(1)),
		static_cast<bool>(static_cast<int8_t>(1)));
	EXPECT_EQ(static_cast<bool>(Int8(0)),
		static_cast<bool>(static_cast<int8_t>(0)));
	EXPECT_EQ(static_cast<bool>(Int16(2)),
		static_cast<bool>(static_cast<int16_t>(2)));
	EXPECT_EQ(static_cast<bool>(Int16(1)),
		static_cast<bool>(static_cast<int16_t>(1)));
	EXPECT_EQ(static_cast<bool>(Int16(0)),
		static_cast<bool>(static_cast<int16_t>(0)));
	EXPECT_EQ(static_cast<bool>(Int32(2)),
		static_cast<bool>(static_cast<int32_t>(2)));
	EXPECT_EQ(static_cast<bool>(Int32(1)),
		static_cast<bool>(static_cast<int32_t>(1)));
	EXPECT_EQ(static_cast<bool>(Int32(0)),
		static_cast<bool>(static_cast<int32_t>(0)));
	EXPECT_EQ(static_cast<bool>(Int64(2)),
		static_cast<bool>(static_cast<int64_t>(2)));
	EXPECT_EQ(static_cast<bool>(Int64(1)),
		static_cast<bool>(static_cast<int64_t>(1)));
	EXPECT_EQ(static_cast<bool>(Int64(0)),
		static_cast<bool>(static_cast<int64_t>(0)));

	EXPECT_EQ(static_cast<bool>(UInt8(2)),
		static_cast<bool>(static_cast<uint8_t>(2)));
	EXPECT_EQ(static_cast<bool>(UInt8(1)),
		static_cast<bool>(static_cast<uint8_t>(1)));
	EXPECT_EQ(static_cast<bool>(UInt8(0)),
		static_cast<bool>(static_cast<uint8_t>(0)));
	EXPECT_EQ(static_cast<bool>(UInt16(2)),
		static_cast<bool>(static_cast<uint16_t>(2)));
	EXPECT_EQ(static_cast<bool>(UInt16(1)),
		static_cast<bool>(static_cast<uint16_t>(1)));
	EXPECT_EQ(static_cast<bool>(UInt16(0)),
		static_cast<bool>(static_cast<uint16_t>(0)));
	EXPECT_EQ(static_cast<bool>(UInt32(2)),
		static_cast<bool>(static_cast<uint32_t>(2)));
	EXPECT_EQ(static_cast<bool>(UInt32(1)),
		static_cast<bool>(static_cast<uint32_t>(1)));
	EXPECT_EQ(static_cast<bool>(UInt32(0)),
		static_cast<bool>(static_cast<uint32_t>(0)));
	EXPECT_EQ(static_cast<bool>(UInt64(2)),
		static_cast<bool>(static_cast<uint64_t>(2)));
	EXPECT_EQ(static_cast<bool>(UInt64(1)),
		static_cast<bool>(static_cast<uint64_t>(1)));
	EXPECT_EQ(static_cast<bool>(UInt64(0)),
		static_cast<bool>(static_cast<uint64_t>(0)));

	// Float -> bool
	EXPECT_EQ(static_cast<bool>(Float(0.001F)),
		static_cast<bool>(static_cast<float>(0.001F)));
	EXPECT_EQ(static_cast<bool>(Float(-0.001F)),
		static_cast<bool>(static_cast<float>(-0.001F)));
	EXPECT_EQ(static_cast<bool>(Float(0.0F)),
		static_cast<bool>(static_cast<float>(0.0F)));
	EXPECT_EQ(static_cast<bool>(Float(-0.0F)),
		static_cast<bool>(static_cast<float>(-0.0F)));

	// Double -> bool
	EXPECT_EQ(static_cast<bool>(Double(0.001)),
		static_cast<bool>(static_cast<double>(0.001)));
	EXPECT_EQ(static_cast<bool>(Double(-0.001)),
		static_cast<bool>(static_cast<double>(-0.001)));
	EXPECT_EQ(static_cast<bool>(Double(0.0)),
		static_cast<bool>(static_cast<double>(0.0)));
	EXPECT_EQ(static_cast<bool>(Double(-0.0)),
		static_cast<bool>(static_cast<double>(-0.0)));
}

GTEST_TEST(TestNumeric, Assignment)
{
	Int32 testVar;

	const int testVal1 = 1234567;
	int testVal2 = 7654321;
	const Int32 testVal3(testVal1);

	// Copy/move _InternalType
	EXPECT_EQ((testVar = testVal1).GetVal(), testVal1);
	EXPECT_EQ((testVar = std::move(testVal2)).GetVal(), testVal2);

	// Copy/move _InternalType
	EXPECT_EQ((testVar = testVal3).GetVal(), testVal1);
	EXPECT_EQ((testVar = Int32(testVal2)).GetVal(), testVal2);
}

GTEST_TEST(TestNumeric, Comparison)
{
	// ==
	// same internal type
	EXPECT_EQ((Int32(123) == Int32(123)).GetVal(),
		static_cast<int32_t>(123) == static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) == Int32(1234)).GetVal(),
		static_cast<int32_t>(123) == static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) == Bool(true)).GetVal(),
		static_cast<int32_t>(123) == static_cast<int>(1));
	EXPECT_EQ((Int32(123) == Double(123.0)).GetVal(),
		static_cast<int32_t>(123) == static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) == Double(1234.0)).GetVal(),
		static_cast<int32_t>(123) == static_cast<double>(1234.0));

	// !=
	// same internal type
	EXPECT_EQ((Int32(123) != Int32(123)).GetVal(),
		static_cast<int32_t>(123) != static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) != Int32(1234)).GetVal(),
		static_cast<int32_t>(123) != static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) != Bool(true)).GetVal(),
		static_cast<int32_t>(123) != static_cast<int>(1));
	EXPECT_EQ((Int32(123) != Double(123.0)).GetVal(),
		static_cast<int32_t>(123) != static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) != Double(1234.0)).GetVal(),
		static_cast<int32_t>(123) != static_cast<double>(1234.0));

	// <=
	// same internal type
	EXPECT_EQ((Int32(1234) <= Int32(123)).GetVal(),
		static_cast<int32_t>(1234) <= static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) <= Int32(1234)).GetVal(),
		static_cast<int32_t>(123) <= static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) <= Bool(true)).GetVal(),
		static_cast<int32_t>(123) <= static_cast<int>(1));
	EXPECT_EQ((Int32(1234) <= Double(123.0)).GetVal(),
		static_cast<int32_t>(1234) <= static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) <= Double(1234.0)).GetVal(),
		static_cast<int32_t>(123) <= static_cast<double>(1234.0));

	// >=
	// same internal type
	EXPECT_EQ((Int32(123) >= Int32(123)).GetVal(),
		static_cast<int32_t>(123) >= static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) >= Int32(1234)).GetVal(),
		static_cast<int32_t>(123) >= static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) >= Bool(true)).GetVal(),
		static_cast<int32_t>(123) >= static_cast<int>(1));
	EXPECT_EQ((Int32(123) >= Double(123.0)).GetVal(),
		static_cast<int32_t>(123) >= static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) >= Double(1234.0)).GetVal(),
		static_cast<int32_t>(123) >= static_cast<double>(1234.0));

	// <
	// same internal type
	EXPECT_EQ((Int32(123) < Int32(123)).GetVal(),
		static_cast<int32_t>(123) < static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) < Int32(1234)).GetVal(),
		static_cast<int32_t>(123) < static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) < Bool(true)).GetVal(),
		static_cast<int32_t>(123) < static_cast<int>(1));
	EXPECT_EQ((Int32(123) < Double(123.0)).GetVal(),
		static_cast<int32_t>(123) < static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) < Double(1234.0)).GetVal(),
		static_cast<int32_t>(123) < static_cast<double>(1234.0));

	// >
	// same internal type
	EXPECT_EQ((Int32(1234) > Int32(123)).GetVal(),
		static_cast<int32_t>(1234) > static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) > Int32(1234)).GetVal(),
		static_cast<int32_t>(123) > static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) > Bool(true)).GetVal(),
		static_cast<int32_t>(123) > static_cast<int>(1));
	EXPECT_EQ((Int32(1234) > Double(123.0)).GetVal(),
		static_cast<int32_t>(1234) > static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) > Double(1234.0)).GetVal(),
		static_cast<int32_t>(123) > static_cast<double>(1234.0));
}

GTEST_TEST(TestNumeric, BitwiseOperation)
{
	// &
	EXPECT_EQ((Int32(12345) & Int32(6)).GetVal(),
		static_cast<int32_t>(12345) & static_cast<int32_t>(6));

	// |
	EXPECT_EQ((Int32(12345) | Int32(6)).GetVal(),
		static_cast<int32_t>(12345) | static_cast<int32_t>(6));

	// ^
	EXPECT_EQ((Int32(12345) ^ Int32(6)).GetVal(),
		static_cast<int32_t>(12345) ^ static_cast<int32_t>(6));

	// <<
	EXPECT_EQ((Int32(12345) << Int32(2)).GetVal(),
		static_cast<int32_t>(12345) << static_cast<int32_t>(2));

	// >>
	EXPECT_EQ((Int32(12345) >> Int32(2)).GetVal(),
		static_cast<int32_t>(12345) >> static_cast<int32_t>(2));

	// ~
	EXPECT_EQ((~Int32(12345)).GetVal(),
		~static_cast<int32_t>(12345));
}

GTEST_TEST(TestNumeric, SelfOperation)
{
	Int32 initObjVal(12345);
	int32_t initIntVal = 12345;

	// +=
	EXPECT_EQ((initObjVal += Int32(123)).GetVal(),
		(initIntVal += static_cast<int32_t>(123)));
	EXPECT_EQ((initObjVal += Double(123.0)).GetVal(),
		(initIntVal = static_cast<int32_t>(initIntVal + static_cast<double>(123.0))));

	// -=
	EXPECT_EQ((initObjVal -= Int32(123)).GetVal(),
		(initIntVal -= static_cast<int32_t>(123)));
	EXPECT_EQ((initObjVal -= Double(123.0)).GetVal(),
		(initIntVal = static_cast<int32_t>(initIntVal - static_cast<double>(123.0))));

	// *=
	EXPECT_EQ((initObjVal *= Int32(12)).GetVal(),
		(initIntVal *= static_cast<int32_t>(12)));
	EXPECT_EQ((initObjVal *= Double(12.0)).GetVal(),
		(initIntVal = static_cast<int32_t>(initIntVal * static_cast<double>(12.0))));

	// /=
	EXPECT_EQ((initObjVal /= Int32(12)).GetVal(),
		(initIntVal /= static_cast<int32_t>(12)));
	EXPECT_EQ((initObjVal /= Double(12.0)).GetVal(),
		(initIntVal = static_cast<int32_t>(initIntVal / static_cast<double>(12.0))));

	// %=
	EXPECT_EQ((initObjVal %= Int32(12)).GetVal(),
		(initIntVal %= static_cast<int32_t>(12)));

	// reset initial value
	initObjVal = Int32(12345);
	initIntVal = 12345;
	EXPECT_EQ(initObjVal.GetVal(), initIntVal);

	// &=
	EXPECT_EQ((initObjVal &= Int32(12)).GetVal(),
		(initIntVal &= static_cast<int32_t>(12)));

	// reset initial value
	initObjVal = Int32(12345);
	initIntVal = 12345;
	EXPECT_EQ(initObjVal.GetVal(), initIntVal);

	// |=
	EXPECT_EQ((initObjVal |= Int32(12)).GetVal(),
		(initIntVal |= static_cast<int32_t>(12)));

	// reset initial value
	initObjVal = Int32(12345);
	initIntVal = 12345;
	EXPECT_EQ(initObjVal.GetVal(), initIntVal);

	// ^=
	EXPECT_EQ((initObjVal ^= Int32(12)).GetVal(),
		(initIntVal ^= static_cast<int32_t>(12)));
}

GTEST_TEST(TestNumeric, Increment)
{
	Int32 initObjVal(12345);
	int32_t initIntVal = 12345;

	// ++i
	EXPECT_EQ((++initObjVal).GetVal(), (++initIntVal));
	EXPECT_EQ((initObjVal).GetVal(), (initIntVal));

	// --i
	EXPECT_EQ((--initObjVal).GetVal(), (--initIntVal));
	EXPECT_EQ((initObjVal).GetVal(), (initIntVal));

	// i++
	EXPECT_EQ((initObjVal++).GetVal(), (initIntVal++));
	EXPECT_EQ((initObjVal).GetVal(), (initIntVal));

	// i--
	EXPECT_EQ((initObjVal--).GetVal(), (initIntVal--));
	EXPECT_EQ((initObjVal).GetVal(), (initIntVal));

	// -
	EXPECT_EQ((-initObjVal).GetVal(), (-initIntVal));
	EXPECT_EQ((initObjVal).GetVal(), (initIntVal));
}

GTEST_TEST(TestNumeric, Operation)
{
	// +
	// bool, bool
	auto resbnb = Bool(true) + Bool(false);
	EXPECT_EQ(resbnb.GetVal(), static_cast<bool>(true) + static_cast<bool>(false));
	// int8_t, int8_t
	auto res8n8 = Int8(23) + Int8(12);
	EXPECT_EQ(res8n8.GetVal(), static_cast<int8_t>(23) + static_cast<int8_t>(12));

	// -
	auto res16n8 = Int16(23) - Int8(12);
	EXPECT_EQ(res16n8.GetVal(), static_cast<int16_t>(23) - static_cast<int8_t>(12));

	// *
	auto res16nu8 = Int16(23) * UInt8(12);
	EXPECT_EQ(res16nu8.GetVal(), static_cast<int16_t>(23) * static_cast<uint8_t>(12));

	// /
	auto res32nu16 = Int32(23) / UInt16(12);
	EXPECT_NEAR(res32nu16.GetVal(), static_cast<int32_t>(23) / static_cast<uint16_t>(12),
		0.0001);
	auto res32ndbl = Int32(23) / Double(2.2);
	EXPECT_NEAR(res32ndbl.GetVal(), static_cast<int32_t>(23) / static_cast<double>(2.2),
		0.0001);

	// %
	auto res32n16 = Int32(23) % Int16(12);
	EXPECT_EQ(res32n16.GetVal(), static_cast<int32_t>(23) % static_cast<int16_t>(12));
}

GTEST_TEST(TestNumeric, Category)
{
	// ===== Bool
	static_assert(Bool::sk_cat() == ObjCategory::Bool, "Category failed.");
	EXPECT_EQ(Bool::sk_cat(), ObjCategory::Bool);

	Bool valBool;
	EXPECT_EQ(valBool.GetCategory(), ObjCategory::Bool);

	// ===== Int8
	static_assert(Int8::sk_cat() == ObjCategory::Integer, "Category failed.");
	EXPECT_EQ(Int8::sk_cat(), ObjCategory::Integer);

	Int8 valInt8;
	EXPECT_EQ(valInt8.GetCategory(), ObjCategory::Integer);

	// ===== Int16
	static_assert(Int16::sk_cat() == ObjCategory::Integer, "Category failed.");
	EXPECT_EQ(Int16::sk_cat(), ObjCategory::Integer);

	Int16 valInt16;
	EXPECT_EQ(valInt16.GetCategory(), ObjCategory::Integer);

	// ===== Int32
	static_assert(Int32::sk_cat() == ObjCategory::Integer, "Category failed.");
	EXPECT_EQ(Int32::sk_cat(), ObjCategory::Integer);

	Int32 valInt32;
	EXPECT_EQ(valInt32.GetCategory(), ObjCategory::Integer);

	// ===== Int64
	static_assert(Int64::sk_cat() == ObjCategory::Integer, "Category failed.");
	EXPECT_EQ(Int64::sk_cat(), ObjCategory::Integer);

	Int64 valInt64;
	EXPECT_EQ(valInt64.GetCategory(), ObjCategory::Integer);

	// ===== UInt8
	static_assert(UInt8::sk_cat() == ObjCategory::Integer, "Category failed.");
	EXPECT_EQ(UInt8::sk_cat(), ObjCategory::Integer);

	UInt8 valUInt8;
	EXPECT_EQ(valUInt8.GetCategory(), ObjCategory::Integer);

	// ===== UInt16
	static_assert(UInt16::sk_cat() == ObjCategory::Integer, "Category failed.");
	EXPECT_EQ(UInt16::sk_cat(), ObjCategory::Integer);

	UInt16 valUInt16;
	EXPECT_EQ(valUInt16.GetCategory(), ObjCategory::Integer);

	// ===== UInt32
	static_assert(UInt32::sk_cat() == ObjCategory::Integer, "Category failed.");
	EXPECT_EQ(UInt32::sk_cat(), ObjCategory::Integer);

	UInt32 valUInt32;
	EXPECT_EQ(valUInt32.GetCategory(), ObjCategory::Integer);

	// ===== UInt64
	static_assert(UInt64::sk_cat() == ObjCategory::Integer, "Category failed.");
	EXPECT_EQ(UInt64::sk_cat(), ObjCategory::Integer);

	UInt64 valUInt64;
	EXPECT_EQ(valUInt64.GetCategory(), ObjCategory::Integer);

	// ===== Float
	static_assert(Float::sk_cat() == ObjCategory::Real, "Category failed.");

	Float valFlt;
	EXPECT_EQ(valFlt.GetCategory(), ObjCategory::Real);

	// ===== Double
	static_assert(Double::sk_cat() == ObjCategory::Real, "Category failed.");

	Double valDlb;
	EXPECT_EQ(valDlb.GetCategory(), ObjCategory::Real);
}

GTEST_TEST(TestNumeric, CategoryName)
{
	EXPECT_EQ(Bool().GetCategoryName(), std::string("Bool"));

	EXPECT_EQ(Int8().GetCategoryName(), std::string("Integer"));
	EXPECT_EQ(Int16().GetCategoryName(), std::string("Integer"));
	EXPECT_EQ(Int32().GetCategoryName(), std::string("Integer"));
	EXPECT_EQ(Int64().GetCategoryName(), std::string("Integer"));

	EXPECT_EQ(UInt8().GetCategoryName(), std::string("Integer"));
	EXPECT_EQ(UInt16().GetCategoryName(), std::string("Integer"));
	EXPECT_EQ(UInt32().GetCategoryName(), std::string("Integer"));
	EXPECT_EQ(UInt64().GetCategoryName(), std::string("Integer"));

	EXPECT_EQ(Float().GetCategoryName(), std::string("Real"));
	EXPECT_EQ(Double().GetCategoryName(), std::string("Real"));
}

GTEST_TEST(TestNumeric, Miscs)
{
	// Is null
	EXPECT_FALSE(Bool().IsNull());

	// Cast
	const auto kNum = Int8();
	EXPECT_NO_THROW(kNum.AsNumeric());
	EXPECT_THROW(kNum.AsNull(),       TypeError);
	EXPECT_THROW(kNum.AsString(),     TypeError);
	EXPECT_THROW(kNum.AsList(),       TypeError);
	EXPECT_THROW(kNum.AsDict(),       TypeError);
	EXPECT_THROW(kNum.AsStaticDict(), TypeError);

	EXPECT_NO_THROW(Int16().AsNumeric());
	EXPECT_THROW(Int32().AsNull(),       TypeError);
	EXPECT_THROW(Int64().AsString(),     TypeError);
	EXPECT_THROW(Int64().AsList(),       TypeError);
	EXPECT_THROW(Int64().AsDict(),       TypeError);
	EXPECT_THROW(Int64().AsStaticDict(), TypeError);

	// Copy
	static_assert(std::is_same<
		decltype(*Int8().Copy(Int8::Base::sk_null)),
		NumericBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Bool(true).Copy(Bool::Base::sk_null), Bool(true));
	EXPECT_EQ(*Int8(123).Copy(Int8::Base::sk_null), Int8(123));
	EXPECT_EQ(*Int16(123).Copy(Int16::Base::sk_null), Int16(123));
	EXPECT_EQ(*Int32(123).Copy(Int32::Base::sk_null), Int32(123));
	EXPECT_EQ(*Int64(123).Copy(Int64::Base::sk_null), Int64(123));
	EXPECT_EQ(*UInt8(123).Copy(UInt8::Base::sk_null), UInt8(123));
	EXPECT_EQ(*UInt16(123).Copy(UInt16::Base::sk_null), UInt16(123));
	EXPECT_EQ(*UInt32(123).Copy(UInt32::Base::sk_null), UInt32(123));
	EXPECT_EQ(*UInt64(123).Copy(UInt64::Base::sk_null), UInt64(123));
	EXPECT_EQ(*Float(123).Copy(Float::Base::sk_null), Float(123));
	EXPECT_EQ(*Double(123).Copy(Double::Base::sk_null), Double(123));

	static_assert(std::is_same<
		decltype(*Int8().Copy(Int8::Base::Base::sk_null)),
		HashableBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Int8(123).Copy(Int8::Base::Base::sk_null), Int8(123));

	static_assert(std::is_same<
		decltype(*Int8().Copy(Int8::Base::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Int8(123).Copy(Int8::Base::Base::Base::sk_null), Int8(123));

	// Move
	static_assert(std::is_same<
		decltype(*Int8().Move(Int8::Base::sk_null)),
		NumericBaseObj&>::value, "Failed to test Move virtual func");
	EXPECT_EQ(*Bool(true).Move(Bool::Base::sk_null), Bool(true));
	EXPECT_EQ(*Int8(123).Move(Int8::Base::sk_null), Int8(123));
	EXPECT_EQ(*Int16(123).Move(Int16::Base::sk_null), Int16(123));
	EXPECT_EQ(*Int32(123).Move(Int32::Base::sk_null), Int32(123));
	EXPECT_EQ(*Int64(123).Move(Int64::Base::sk_null), Int64(123));
	EXPECT_EQ(*UInt8(123).Move(UInt8::Base::sk_null), UInt8(123));
	EXPECT_EQ(*UInt16(123).Move(UInt16::Base::sk_null), UInt16(123));
	EXPECT_EQ(*UInt32(123).Move(UInt32::Base::sk_null), UInt32(123));
	EXPECT_EQ(*UInt64(123).Move(UInt64::Base::sk_null), UInt64(123));
	EXPECT_EQ(*Float(123).Move(Float::Base::sk_null), Float(123));
	EXPECT_EQ(*Double(123).Move(Double::Base::sk_null), Double(123));

	static_assert(std::is_same<
		decltype(*Int8().Move(Int8::Base::Base::sk_null)),
		HashableBaseObj&>::value, "Failed to test Move virtual func");
	EXPECT_EQ(*Int8(123).Move(Int8::Base::Base::sk_null), Int8(123));

	static_assert(std::is_same<
		decltype(*Int8().Move(Int8::Base::Base::Base::sk_null)),
		BaseObj&>::value, "Failed to test Move virtual func");
	EXPECT_EQ(*Int8(123).Move(Int8::Base::Base::Base::sk_null), Int8(123));
}

GTEST_TEST(TestNumeric, Hash)
{
	EXPECT_NE(Bool(true).Hash(), Bool(false).Hash());

	EXPECT_NE(Int8(0).Hash(), Int8(1).Hash());
	EXPECT_NE(Int16(0).Hash(), Int16(1).Hash());
	EXPECT_NE(Int32(0).Hash(), Int32(1).Hash());
	EXPECT_NE(Int64(0).Hash(), Int64(1).Hash());

	EXPECT_NE(UInt8(0).Hash(), UInt8(1).Hash());
	EXPECT_NE(UInt16(0).Hash(), UInt16(1).Hash());
	EXPECT_NE(UInt32(0).Hash(), UInt32(1).Hash());
	EXPECT_NE(UInt64(0).Hash(), UInt64(1).Hash());

	EXPECT_NE(Float(0).Hash(), Float(1).Hash());
	EXPECT_NE(Double(0).Hash(), Double(1).Hash());
}

GTEST_TEST(TestNumeric, GetNumType)
{
	EXPECT_EQ(Bool().GetNumType(), NumericType::Bool);
	EXPECT_EQ(Int8().GetNumType(), NumericType::Int8);
	EXPECT_EQ(Int16().GetNumType(), NumericType::Int16);
	EXPECT_EQ(Int32().GetNumType(), NumericType::Int32);
	EXPECT_EQ(Int64().GetNumType(), NumericType::Int64);

	EXPECT_EQ(UInt8().GetNumType(), NumericType::UInt8);
	EXPECT_EQ(UInt16().GetNumType(), NumericType::UInt16);
	EXPECT_EQ(UInt32().GetNumType(), NumericType::UInt32);
	EXPECT_EQ(UInt64().GetNumType(), NumericType::UInt64);

	EXPECT_EQ(Float().GetNumType(), NumericType::Float);
	EXPECT_EQ(Double().GetNumType(), NumericType::Double);
}

GTEST_TEST(TestNumeric, GetNumTypeName)
{
	EXPECT_EQ(Bool().GetNumTypeName(), std::string("Bool"));
	EXPECT_EQ(Int8().GetNumTypeName(), std::string("Int8"));
	EXPECT_EQ(Int16().GetNumTypeName(), std::string("Int16"));
	EXPECT_EQ(Int32().GetNumTypeName(), std::string("Int32"));
	EXPECT_EQ(Int64().GetNumTypeName(), std::string("Int64"));

	EXPECT_EQ(UInt8().GetNumTypeName(), std::string("UInt8"));
	EXPECT_EQ(UInt16().GetNumTypeName(), std::string("UInt16"));
	EXPECT_EQ(UInt32().GetNumTypeName(), std::string("UInt32"));
	EXPECT_EQ(UInt64().GetNumTypeName(), std::string("UInt64"));

	EXPECT_EQ(Float().GetNumTypeName(), std::string("Float"));
	EXPECT_EQ(Double().GetNumTypeName(), std::string("Double"));
}

namespace
{
	class Int8Ext : public Int8
	{
	public:
		using Int8::Int8;

		virtual NumericType GetNumType() const override
		{
			return NumericType::Other;
		}

		virtual const char* GetNumTypeName() const override
		{
			return "Int8Ext";
		}
	};
}

GTEST_TEST(TestNumeric, BaseIsEqual)
{
	// Base object
	using ObjPtr = std::unique_ptr<BaseObj>;

	// Other types
	EXPECT_TRUE(*ObjPtr(new Int8(1)) != *ObjPtr(new Null()));

	// Bool
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Bool(true)), true != true);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Bool(false)), true != false);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Bool(true)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(2)) != *ObjPtr(new Bool(true)), 2 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Int8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Int16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Bool(true)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(2)) != *ObjPtr(new Bool(true)), 2 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Int16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Int32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Bool(true)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(2)) != *ObjPtr(new Bool(true)), 2 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Int32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Int64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Bool(true)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(2)) != *ObjPtr(new Bool(true)), 2 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Int64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new UInt8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Bool(true)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(2)) != *ObjPtr(new Bool(true)), 2 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new UInt8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new UInt16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Bool(true)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(2)) != *ObjPtr(new Bool(true)), 2 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new UInt16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new UInt32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Bool(true)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(2)) != *ObjPtr(new Bool(true)), 2 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new UInt32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new UInt64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Bool(true)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(2)) != *ObjPtr(new Bool(true)), 2 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new UInt64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Float(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Bool(true)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Float(2.0)) != *ObjPtr(new Bool(true)), 2.0 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Float(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Double(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Bool(true)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Double(2.0)) != *ObjPtr(new Bool(true)), 2.0 != 1);
	EXPECT_EQ(*ObjPtr(new Bool(true)) != *ObjPtr(new Double(2.0)), 1 != 2.0);

	// Int8
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Int8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Int16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Int16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Int8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Int32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Int32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Int8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Int64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Int64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Int8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new UInt8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new UInt8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Int8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new UInt16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new UInt16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Int8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new UInt32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new UInt32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Int8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new UInt64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new UInt64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Int8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Float(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Float(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Int8(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Int8(2)), 1.0 != 2);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Double(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Int8(1)) != *ObjPtr(new Double(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Int8(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Int8(2)), 1.0 != 2);

	// Int16
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Int16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Int16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Int32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Int32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Int16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Int16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Int64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Int64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Int16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Int16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new UInt8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new UInt8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Int16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Int16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new UInt16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new UInt16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Int16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Int16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new UInt32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new UInt32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Int16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Int16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new UInt64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new UInt64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Int16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Int16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Float(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Float(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Int16(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Int16(2)), 1.0 != 2);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Double(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Int16(1)) != *ObjPtr(new Double(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Int16(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Int16(2)), 1.0 != 2);

	// Int32
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Int32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Int32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Int64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Int64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Int32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Int32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new UInt8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new UInt8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Int32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Int32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new UInt16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new UInt16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Int32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Int32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new UInt32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new UInt32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Int32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Int32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new UInt64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new UInt64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Int32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Int32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Float(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Float(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Int32(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Int32(2)), 1.0 != 2);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Double(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Int32(1)) != *ObjPtr(new Double(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Int32(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Int32(2)), 1.0 != 2);

	// Int64
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Int64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Int64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new UInt8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new UInt8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Int64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Int64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new UInt16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new UInt16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Int64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Int64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new UInt32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new UInt32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Int64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Int64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new UInt64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new UInt64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Int64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Int64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Float(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Float(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Int64(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Int64(2)), 1.0 != 2);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Double(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new Int64(1)) != *ObjPtr(new Double(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Int64(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Int64(2)), 1.0 != 2);

	// UInt8
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new UInt8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new UInt8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new UInt16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new UInt16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new UInt8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new UInt8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new UInt32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new UInt32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new UInt8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new UInt8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new UInt64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new UInt64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new UInt8(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new UInt8(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Float(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Float(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new UInt8(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new UInt8(2)), 1.0 != 2);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Double(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new UInt8(1)) != *ObjPtr(new Double(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new UInt8(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new UInt8(2)), 1.0 != 2);

	// UInt16
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new UInt16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new UInt16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new UInt32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new UInt32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new UInt16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new UInt16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new UInt64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new UInt64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new UInt16(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new UInt16(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Float(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Float(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new UInt16(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new UInt16(2)), 1.0 != 2);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Double(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new UInt16(1)) != *ObjPtr(new Double(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new UInt16(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new UInt16(2)), 1.0 != 2);

	// UInt32
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new UInt32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new UInt32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new UInt64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new UInt64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new UInt32(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new UInt32(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Float(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Float(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new UInt32(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new UInt32(2)), 1.0 != 2);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Double(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new UInt32(1)) != *ObjPtr(new Double(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new UInt32(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new UInt32(2)), 1.0 != 2);

	// UInt64
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new UInt64(1)), 1 != 1);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new UInt64(2)), 1 != 2);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Float(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Float(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new UInt64(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new UInt64(2)), 1.0 != 2);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Double(1.0)), 1 != 1.0);
	EXPECT_EQ(*ObjPtr(new UInt64(1)) != *ObjPtr(new Double(2.0)), 1 != 2.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new UInt64(1)), 1.0 != 1);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new UInt64(2)), 1.0 != 2);

	// Float
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Float(1.0)), 1.0 != 1.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Float(2.0)), 1.0 != 2.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Double(1.0)), 1.0 != 1.0);
	EXPECT_EQ(*ObjPtr(new Float(1.0)) != *ObjPtr(new Double(2.0)), 1.0 != 2.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Float(1.0)), 1.0 != 1.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Float(2.0)), 1.0 != 2.0);

	// Double
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Double(1.0)), 1.0 != 1.0);
	EXPECT_EQ(*ObjPtr(new Double(1.0)) != *ObjPtr(new Double(2.0)), 1.0 != 2.0);

	// Unsupported extensions
	EXPECT_THROW(
		(void)(*ObjPtr(new Int8(1)) != *ObjPtr(new Int8Ext(1))),
		UnsupportedOperation);

	// different objs
	EXPECT_TRUE(*ObjPtr(new Int8(1)) != *ObjPtr(new Null()));



	// Numeric base object
	using NumPtr = std::unique_ptr<NumericBaseObj>;

	EXPECT_EQ(*NumPtr(new Int8(1)) != *NumPtr(new Int8(1)), 1 != 1);
	EXPECT_EQ(*NumPtr(new Int8(1)) != *NumPtr(new Int8(2)), 1 != 2);
}

GTEST_TEST(TestNumeric, BaseIsLessThan)
{
	using NumPtr = std::unique_ptr<NumericBaseObj>;

	// <
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Bool(false)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Int8(0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Int8(1)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Int16(0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Int16(1)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Int32(0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Int32(1)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Int64(0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Int64(1)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new UInt8(0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new UInt8(1)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new UInt16(0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new UInt16(1)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new UInt32(0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new UInt32(1)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new UInt64(0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new UInt64(1)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Float(0.0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Float(1.0)) >= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Double(0.0)) >= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Double(1.0)) >= *NumPtr(new Double(2.0)));

	using ObjPtr = std::unique_ptr<BaseObj>;

	EXPECT_FALSE(*ObjPtr(new Bool(false)) >= *ObjPtr(new Int8(2)));

	// different objs
	EXPECT_THROW(
		(void)(*ObjPtr(new Int8(1)) >= *ObjPtr(new Null())),
		UnsupportedOperation);
}

GTEST_TEST(TestNumeric, BaseIsGreaterThan)
{
	using NumPtr = std::unique_ptr<NumericBaseObj>;

	// >
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new Bool(false)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new Int8(0)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new Int16(0)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new Int32(0)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new Int64(0)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new UInt8(0)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new UInt16(0)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new UInt32(0)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new UInt64(0)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new Float(0.0)));
	EXPECT_FALSE(*NumPtr(new Bool(true)) <= *NumPtr(new Double(0.0)));

	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Int8(5)) <= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Int16(5)) <= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Int32(5)) <= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Int64(5)) <= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new UInt8(5)) <= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new UInt16(5)) <= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new UInt32(5)) <= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new UInt64(5)) <= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Float(5.0)) <= *NumPtr(new Double(2.0)));

	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new Bool(true)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new Int8(2)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new Int16(2)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new Int32(2)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new Int64(2)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new UInt8(2)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new UInt16(2)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new UInt32(2)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new UInt64(2)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new Float(2.0)));
	EXPECT_FALSE(*NumPtr(new Double(5.0)) <= *NumPtr(new Double(2.0)));

	using ObjPtr = std::unique_ptr<BaseObj>;

	EXPECT_FALSE(*ObjPtr(new Bool(true)) <= *ObjPtr(new Int8(0)));

	// different objs
	EXPECT_THROW(
		(void)(*ObjPtr(new Int8(1)) <= *ObjPtr(new Null())),
		UnsupportedOperation);
}

GTEST_TEST(TestNumeric, ToString)
{
	{
		const std::string expRes = "true";
		// DebugString
		{
			EXPECT_EQ(Bool(true).DebugString(), expRes);
			EXPECT_EQ(Bool(true).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(Bool(true).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				Bool(true).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "false";
		// DebugString
		{
			EXPECT_EQ(Bool(false).DebugString(), expRes);
			EXPECT_EQ(Bool(false).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(Bool(false).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				Bool(false).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "123";
		// DebugString
		{
			EXPECT_EQ(Int8(123).DebugString(), expRes);
			EXPECT_EQ(Int8(123).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(Int8(123).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				Int8(123).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "123";
		// DebugString
		{
			EXPECT_EQ(Int16(123).DebugString(), expRes);
			EXPECT_EQ(Int16(123).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(Int16(123).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				Int16(123).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "123";
		// DebugString
		{
			EXPECT_EQ(Int32(123).DebugString(), expRes);
			EXPECT_EQ(Int32(123).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(Int32(123).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				Int32(123).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "123";
		// DebugString
		{
			EXPECT_EQ(Int64(123).DebugString(), expRes);
			EXPECT_EQ(Int64(123).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(Int64(123).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				Int64(123).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "123";
		// DebugString
		{
			EXPECT_EQ(UInt8(123).DebugString(), expRes);
			EXPECT_EQ(UInt8(123).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(UInt8(123).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				UInt8(123).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "123";
		// DebugString
		{
			EXPECT_EQ(UInt16(123).DebugString(), expRes);
			EXPECT_EQ(UInt16(123).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(UInt16(123).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				UInt16(123).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "123";
		// DebugString
		{
			EXPECT_EQ(UInt32(123).DebugString(), expRes);
			EXPECT_EQ(UInt32(123).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(UInt32(123).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				UInt32(123).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "123";
		// DebugString
		{
			EXPECT_EQ(UInt64(123).DebugString(), expRes);
			EXPECT_EQ(UInt64(123).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(UInt64(123).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				UInt64(123).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "0.0";
		// DebugString
		{
			EXPECT_EQ(Float(0.0).DebugString(), expRes);
			EXPECT_EQ(Float(0.0).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(Float(0.0).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				Float(0.0).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
	{
		const std::string expRes = "0.0";
		// DebugString
		{
			EXPECT_EQ(Double(0.0).DebugString(), expRes);
			EXPECT_EQ(Double(0.0).ShortDebugString(), expRes);
		}
		// ToString & DumpString
		{
			EXPECT_EQ(Double(0.0).ToString(), expRes);

			std::string res;
			EXPECT_NO_THROW(
				Double(0.0).DumpString(ToOutIt<char>(std::back_inserter(res))));
			EXPECT_EQ(res, expRes);
		}
	}
}
