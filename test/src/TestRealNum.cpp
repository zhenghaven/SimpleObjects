// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <memory>

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER
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

GTEST_TEST(TestRealNum, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestRealNum, Construction)
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

GTEST_TEST(TestRealNum, Setter)
{
	Bool   b_l( true);
	Int8   i8_l(-12);
	Int16  i16_l(-1234);
	Int32  i32_l(-123456);
	Int64  i64_l(-123456789012);
	UInt8  u8_l( 12);
	UInt16 u16_l(1234);
	UInt32 u32_l(123456);
	UInt64 u64_l(123456789012);
	Float  f_l(1e12F);
	Double d_l(1e123);

	Bool   b;
	Int8   i8;
	Int16  i16;
	Int32  i32;
	Int64  i64;
	UInt8  u8;
	UInt16 u16;
	UInt32 u32;
	UInt64 u64;
	Float  f;
	Double d;

	// bool
	EXPECT_THROW(b.Set(Double());, TypeError);
	EXPECT_THROW(b.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(b = Bool(); b.Set(Bool(true)););
	EXPECT_TRUE(b.GetVal() == true);
	EXPECT_NO_THROW(b = Bool(); b.Set(b_l));
	EXPECT_TRUE(b.GetVal() == true);
	//    bool -> bool
	EXPECT_NO_THROW(b = Bool(); b.Set(true););
	EXPECT_TRUE(b.GetVal() == true);
	//    uint8_t -> bool
	EXPECT_NO_THROW(b = Bool(); b.Set(uint8_t(1)););
	EXPECT_TRUE(b.GetVal() == true);
	EXPECT_THROW(b.Set((std::numeric_limits<uint8_t>::max)());, TypeError);
	//    uint32_t -> bool
	EXPECT_NO_THROW(b = Bool(); b.Set(uint32_t(1)););
	EXPECT_TRUE(b.GetVal() == true);
	EXPECT_THROW(b.Set((std::numeric_limits<uint32_t>::max)());, TypeError);
	//    uint64_t -> bool
	EXPECT_NO_THROW(b = Bool(); b.Set(uint64_t(1)););
	EXPECT_TRUE(b.GetVal() == true);
	EXPECT_THROW(b.Set((std::numeric_limits<uint64_t>::max)());, TypeError);
	//    int8_t -> bool
	EXPECT_NO_THROW(b = Bool(); b.Set(int8_t(1)););
	EXPECT_TRUE(b.GetVal() == true);
	EXPECT_THROW(b.Set((std::numeric_limits<int8_t>::max)());, TypeError);
	EXPECT_THROW(b.Set(std::numeric_limits<int8_t>::lowest());, TypeError);
	//    int32_t -> bool
	EXPECT_NO_THROW(b = Bool(); b.Set(int32_t(1)););
	EXPECT_TRUE(b.GetVal() == true);
	EXPECT_THROW(b.Set((std::numeric_limits<int32_t>::max)());, TypeError);
	EXPECT_THROW(b.Set(std::numeric_limits<int32_t>::lowest());, TypeError);
	//    int64_t -> bool
	EXPECT_NO_THROW(b = Bool(); b.Set(int64_t(1)););
	EXPECT_TRUE(b.GetVal() == true);
	EXPECT_THROW(b.Set((std::numeric_limits<int64_t>::max)());, TypeError);
	EXPECT_THROW(b.Set(std::numeric_limits<int64_t>::lowest());, TypeError);
	//    double -> bool
	EXPECT_NO_THROW(b = Bool(); b.Set(double(1)););
	EXPECT_TRUE(b.GetVal() == true);
	EXPECT_THROW(b.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(b.Set(std::numeric_limits<double>::lowest());, TypeError);

	// int8_t
	EXPECT_THROW(i8.Set(Double());, TypeError);
	EXPECT_THROW(i8.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(Int8(-12)););
	EXPECT_TRUE(i8.GetVal() == -12);
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(i8_l));
	EXPECT_TRUE(i8.GetVal() == -12);
	//    bool ->
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(true););
	EXPECT_TRUE(i8.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(uint8_t(12)););
	EXPECT_TRUE(i8.GetVal() == 12);
	EXPECT_THROW(i8.Set((std::numeric_limits<uint8_t>::max)());, TypeError);
	//    uint32_t ->
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(uint32_t(12)););
	EXPECT_TRUE(i8.GetVal() == 12);
	EXPECT_THROW(i8.Set((std::numeric_limits<uint32_t>::max)());, TypeError);
	//    uint64_t ->
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(uint64_t(12)););
	EXPECT_TRUE(i8.GetVal() == 12);
	EXPECT_THROW(i8.Set((std::numeric_limits<uint64_t>::max)());, TypeError);
	//    int8_t ->
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(int8_t(12)););
	EXPECT_TRUE(i8.GetVal() == 12);
	//    int32_t ->
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(int32_t(12)););
	EXPECT_TRUE(i8.GetVal() == 12);
	EXPECT_THROW(i8.Set((std::numeric_limits<int32_t>::max)());, TypeError);
	EXPECT_THROW(i8.Set(std::numeric_limits<int32_t>::lowest());, TypeError);
	//    int64_t ->
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(int64_t(12)););
	EXPECT_TRUE(i8.GetVal() == 12);
	EXPECT_THROW(i8.Set((std::numeric_limits<int64_t>::max)());, TypeError);
	EXPECT_THROW(i8.Set(std::numeric_limits<int64_t>::lowest());, TypeError);
	//    double ->
	EXPECT_NO_THROW(i8 = Int8(); i8.Set(double(12)););
	EXPECT_TRUE(i8.GetVal() == 12);
	EXPECT_THROW(i8.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(i8.Set(std::numeric_limits<double>::lowest());, TypeError);

	// int16_t
	EXPECT_THROW(i16.Set(Double());, TypeError);
	EXPECT_THROW(i16.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(Int16(-1234)););
	EXPECT_TRUE(i16.GetVal() == -1234);
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(i16_l));
	EXPECT_TRUE(i16.GetVal() == -1234);
	//    bool ->
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(true););
	EXPECT_TRUE(i16.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(uint8_t(12)););
	EXPECT_TRUE(i16.GetVal() == 12);
	//    uint32_t ->
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(uint32_t(12)););
	EXPECT_TRUE(i16.GetVal() == 12);
	EXPECT_THROW(i16.Set((std::numeric_limits<uint32_t>::max)());, TypeError);
	//    uint64_t ->
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(uint64_t(12)););
	EXPECT_TRUE(i16.GetVal() == 12);
	EXPECT_THROW(i16.Set((std::numeric_limits<uint64_t>::max)());, TypeError);
	//    int8_t ->
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(int8_t(12)););
	EXPECT_TRUE(i16.GetVal() == 12);
	//    int32_t ->
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(int32_t(12)););
	EXPECT_TRUE(i16.GetVal() == 12);
	EXPECT_THROW(i16.Set((std::numeric_limits<int32_t>::max)());, TypeError);
	EXPECT_THROW(i16.Set(std::numeric_limits<int32_t>::lowest());, TypeError);
	//    int64_t ->
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(int64_t(12)););
	EXPECT_TRUE(i16.GetVal() == 12);
	EXPECT_THROW(i16.Set((std::numeric_limits<int64_t>::max)());, TypeError);
	EXPECT_THROW(i16.Set(std::numeric_limits<int64_t>::lowest());, TypeError);
	//    double ->
	EXPECT_NO_THROW(i16 = Int16(); i16.Set(double(12)););
	EXPECT_TRUE(i16.GetVal() == 12);
	EXPECT_THROW(i16.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(i16.Set(std::numeric_limits<double>::lowest());, TypeError);

	// int32_t
	EXPECT_THROW(i32.Set(Double());, TypeError);
	EXPECT_THROW(i32.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(Int32(-123456)););
	EXPECT_TRUE(i32.GetVal() == -123456);
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(i32_l));
	EXPECT_TRUE(i32.GetVal() == -123456);
	//    bool ->
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(true););
	EXPECT_TRUE(i32.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(uint8_t(12)););
	EXPECT_TRUE(i32.GetVal() == 12);
	//    uint32_t ->
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(uint32_t(12)););
	EXPECT_TRUE(i32.GetVal() == 12);
	EXPECT_THROW(i32.Set((std::numeric_limits<uint32_t>::max)());, TypeError);
	//    uint64_t ->
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(uint64_t(12)););
	EXPECT_TRUE(i32.GetVal() == 12);
	EXPECT_THROW(i32.Set((std::numeric_limits<uint64_t>::max)());, TypeError);
	//    int8_t ->
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(int8_t(12)););
	EXPECT_TRUE(i32.GetVal() == 12);
	//    int32_t ->
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(int32_t(12)););
	EXPECT_TRUE(i32.GetVal() == 12);
	//    int64_t ->
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(int64_t(12)););
	EXPECT_TRUE(i32.GetVal() == 12);
	EXPECT_THROW(i32.Set((std::numeric_limits<int64_t>::max)());, TypeError);
	EXPECT_THROW(i32.Set(std::numeric_limits<int64_t>::lowest());, TypeError);
	//    double ->
	EXPECT_NO_THROW(i32 = Int32(); i32.Set(double(12)););
	EXPECT_TRUE(i32.GetVal() == 12);
	EXPECT_THROW(i32.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(i32.Set(std::numeric_limits<double>::lowest());, TypeError);

	// int64_t
	EXPECT_THROW(i64.Set(Double());, TypeError);
	EXPECT_THROW(i64.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(Int64(-123456789012)););
	EXPECT_TRUE(i64.GetVal() == -123456789012);
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(i64_l));
	EXPECT_TRUE(i64.GetVal() == -123456789012);
	//    bool ->
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(true););
	EXPECT_TRUE(i64.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(uint8_t(12)););
	EXPECT_TRUE(i64.GetVal() == 12);
	//    uint32_t ->
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(uint32_t(12)););
	EXPECT_TRUE(i64.GetVal() == 12);
	//    uint64_t ->
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(uint64_t(12)););
	EXPECT_TRUE(i64.GetVal() == 12);
	EXPECT_THROW(i64.Set((std::numeric_limits<uint64_t>::max)());, TypeError);
	//    int8_t ->
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(int8_t(12)););
	EXPECT_TRUE(i64.GetVal() == 12);
	//    int32_t ->
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(int32_t(12)););
	EXPECT_TRUE(i64.GetVal() == 12);
	//    int64_t ->
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(int64_t(12)););
	EXPECT_TRUE(i64.GetVal() == 12);
	//    double ->
	EXPECT_NO_THROW(i64 = Int64(); i64.Set(double(12)););
	EXPECT_TRUE(i64.GetVal() == 12);
	EXPECT_THROW(i64.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(i64.Set(std::numeric_limits<double>::lowest());, TypeError);

	// uint8_t
	EXPECT_THROW(u8.Set(Double());, TypeError);
	EXPECT_THROW(u8.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(UInt8(12)););
	EXPECT_TRUE(u8.GetVal() == 12);
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(u8_l));
	EXPECT_TRUE(u8.GetVal() == 12);
	//    bool ->
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(true););
	EXPECT_TRUE(u8.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(uint8_t(12)););
	EXPECT_TRUE(u8.GetVal() == 12);
	//    uint32_t ->
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(uint32_t(12)););
	EXPECT_TRUE(u8.GetVal() == 12);
	EXPECT_THROW(u8.Set((std::numeric_limits<uint32_t>::max)());, TypeError);
	//    uint64_t ->
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(uint64_t(12)););
	EXPECT_TRUE(u8.GetVal() == 12);
	EXPECT_THROW(u8.Set((std::numeric_limits<uint64_t>::max)());, TypeError);
	//    int8_t ->
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(int8_t(12)););
	EXPECT_TRUE(u8.GetVal() == 12);
	EXPECT_THROW(u8.Set(std::numeric_limits<int8_t>::lowest());, TypeError);
	//    int32_t ->
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(int32_t(12)););
	EXPECT_TRUE(u8.GetVal() == 12);
	EXPECT_THROW(u8.Set((std::numeric_limits<int32_t>::max)());, TypeError);
	EXPECT_THROW(u8.Set(std::numeric_limits<int32_t>::lowest());, TypeError);
	//    int64_t ->
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(int64_t(12)););
	EXPECT_TRUE(u8.GetVal() == 12);
	EXPECT_THROW(u8.Set((std::numeric_limits<int64_t>::max)());, TypeError);
	EXPECT_THROW(u8.Set(std::numeric_limits<int64_t>::lowest());, TypeError);
	//    double ->
	EXPECT_NO_THROW(u8 = UInt8(); u8.Set(double(12)););
	EXPECT_TRUE(u8.GetVal() == 12);
	EXPECT_THROW(u8.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(u8.Set(std::numeric_limits<double>::lowest());, TypeError);

	// uint16_t
	EXPECT_THROW(u16.Set(Double());, TypeError);
	EXPECT_THROW(u16.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(UInt16(1234)););
	EXPECT_TRUE(u16.GetVal() == 1234);
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(u16_l));
	EXPECT_TRUE(u16.GetVal() == 1234);
	//    bool ->
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(true););
	EXPECT_TRUE(u16.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(uint8_t(12)););
	EXPECT_TRUE(u16.GetVal() == 12);
	//    uint32_t ->
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(uint32_t(12)););
	EXPECT_TRUE(u16.GetVal() == 12);
	EXPECT_THROW(u16.Set((std::numeric_limits<uint32_t>::max)());, TypeError);
	//    uint64_t ->
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(uint64_t(12)););
	EXPECT_TRUE(u16.GetVal() == 12);
	EXPECT_THROW(u16.Set((std::numeric_limits<uint64_t>::max)());, TypeError);
	//    int8_t ->
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(int8_t(12)););
	EXPECT_TRUE(u16.GetVal() == 12);
	EXPECT_THROW(u16.Set(std::numeric_limits<int8_t>::lowest());, TypeError);
	//    int32_t ->
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(int32_t(12)););
	EXPECT_TRUE(u16.GetVal() == 12);
	EXPECT_THROW(u16.Set((std::numeric_limits<int32_t>::max)());, TypeError);
	EXPECT_THROW(u16.Set(std::numeric_limits<int32_t>::lowest());, TypeError);
	//    int64_t ->
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(int64_t(12)););
	EXPECT_TRUE(u16.GetVal() == 12);
	EXPECT_THROW(u16.Set((std::numeric_limits<int64_t>::max)());, TypeError);
	EXPECT_THROW(u16.Set(std::numeric_limits<int64_t>::lowest());, TypeError);
	//    double ->
	EXPECT_NO_THROW(u16 = UInt16(); u16.Set(double(12)););
	EXPECT_TRUE(u16.GetVal() == 12);
	EXPECT_THROW(u16.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(u16.Set(std::numeric_limits<double>::lowest());, TypeError);

	// uint32_t
	EXPECT_THROW(u32.Set(Double());, TypeError);
	EXPECT_THROW(u32.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(UInt32(123456)););
	EXPECT_TRUE(u32.GetVal() == 123456);
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(u32_l));
	EXPECT_TRUE(u32.GetVal() == 123456);
	//    bool ->
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(true););
	EXPECT_TRUE(u32.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(uint8_t(12)););
	EXPECT_TRUE(u32.GetVal() == 12);
	//    uint32_t ->
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(uint32_t(12)););
	EXPECT_TRUE(u32.GetVal() == 12);
	//    uint64_t ->
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(uint64_t(12)););
	EXPECT_TRUE(u32.GetVal() == 12);
	EXPECT_THROW(u32.Set((std::numeric_limits<uint64_t>::max)());, TypeError);
	//    int8_t ->
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(int8_t(12)););
	EXPECT_TRUE(u32.GetVal() == 12);
	EXPECT_THROW(u32.Set(std::numeric_limits<int8_t>::lowest());, TypeError);
	//    int32_t ->
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(int32_t(12)););
	EXPECT_TRUE(u32.GetVal() == 12);
	EXPECT_THROW(u32.Set(std::numeric_limits<int32_t>::lowest());, TypeError);
	//    int64_t ->
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(int64_t(12)););
	EXPECT_TRUE(u32.GetVal() == 12);
	EXPECT_THROW(u32.Set((std::numeric_limits<int64_t>::max)());, TypeError);
	EXPECT_THROW(u32.Set(std::numeric_limits<int64_t>::lowest());, TypeError);
	//    double ->
	EXPECT_NO_THROW(u32 = UInt32(); u32.Set(double(12)););
	EXPECT_TRUE(u32.GetVal() == 12);
	EXPECT_THROW(u32.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(u32.Set(std::numeric_limits<double>::lowest());, TypeError);

	// uint64_t
	EXPECT_THROW(u64.Set(Double());, TypeError);
	EXPECT_THROW(u64.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(UInt64(123456789012)););
	EXPECT_TRUE(u64.GetVal() == 123456789012);
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(u64_l));
	EXPECT_TRUE(u64.GetVal() == 123456789012);
	//    bool ->
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(true););
	EXPECT_TRUE(u64.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(uint8_t(12)););
	EXPECT_TRUE(u64.GetVal() == 12);
	//    uint32_t ->
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(uint32_t(12)););
	EXPECT_TRUE(u64.GetVal() == 12);
	//    uint64_t ->
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(uint64_t(12)););
	EXPECT_TRUE(u64.GetVal() == 12);
	//    int8_t ->
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(int8_t(12)););
	EXPECT_TRUE(u64.GetVal() == 12);
	EXPECT_THROW(u64.Set(std::numeric_limits<int8_t>::lowest());, TypeError);
	//    int32_t ->
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(int32_t(12)););
	EXPECT_TRUE(u64.GetVal() == 12);
	EXPECT_THROW(u64.Set(std::numeric_limits<int32_t>::lowest());, TypeError);
	//    int64_t ->
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(int64_t(12)););
	EXPECT_TRUE(u64.GetVal() == 12);
	EXPECT_THROW(u64.Set(std::numeric_limits<int64_t>::lowest());, TypeError);
	//    double ->
	EXPECT_NO_THROW(u64 = UInt64(); u64.Set(double(12)););
	EXPECT_TRUE(u64.GetVal() == 12);
	EXPECT_THROW(u64.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(u64.Set(std::numeric_limits<double>::lowest());, TypeError);

	// float
	EXPECT_THROW(f.Set(Double());, TypeError);
	EXPECT_THROW(f.Set(d_l);,      TypeError);
	EXPECT_NO_THROW(f = Float(); f.Set(Float(1e12F)););
	EXPECT_TRUE(f.GetVal() == 1e12F);
	EXPECT_NO_THROW(f = Float(); f.Set(f_l));
	EXPECT_TRUE(f.GetVal() == 1e12F);
	//    bool ->
	EXPECT_NO_THROW(f = Float(); f.Set(true););
	EXPECT_TRUE(f.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(f = Float(); f.Set(uint8_t(12)););
	EXPECT_TRUE(f.GetVal() == 12);
	//    uint32_t ->
	EXPECT_NO_THROW(f = Float(); f.Set(uint32_t(12)););
	EXPECT_TRUE(f.GetVal() == 12);
	//    uint64_t ->
	EXPECT_NO_THROW(f = Float(); f.Set(uint64_t(12)););
	EXPECT_TRUE(f.GetVal() == 12);
	//    int8_t ->
	EXPECT_NO_THROW(f = Float(); f.Set(int8_t(12)););
	EXPECT_TRUE(f.GetVal() == 12);
	//    int32_t ->
	EXPECT_NO_THROW(f = Float(); f.Set(int32_t(12)););
	EXPECT_TRUE(f.GetVal() == 12);
	//    int64_t ->
	EXPECT_NO_THROW(f = Float(); f.Set(int64_t(12)););
	EXPECT_TRUE(f.GetVal() == 12);
	//    double ->
	EXPECT_NO_THROW(f = Float(); f.Set(double(12)););
	EXPECT_TRUE(f.GetVal() == 12);
	EXPECT_THROW(f.Set((std::numeric_limits<double>::max)());, TypeError);
	EXPECT_THROW(f.Set(std::numeric_limits<double>::lowest());, TypeError);

	// double
	EXPECT_THROW(d.Set(Float());, TypeError);
	EXPECT_THROW(d.Set(f_l);,      TypeError);
	EXPECT_NO_THROW(d = Double(); d.Set(Double(1e123)););
	EXPECT_TRUE(d.GetVal() == 1e123);
	EXPECT_NO_THROW(d = Double(); d.Set(d_l));
	EXPECT_TRUE(d.GetVal() == 1e123);
	//    bool ->
	EXPECT_NO_THROW(d = Double(); d.Set(true););
	EXPECT_TRUE(d.GetVal() == 1);
	//    uint8_t ->
	EXPECT_NO_THROW(d = Double(); d.Set(uint8_t(12)););
	EXPECT_TRUE(d.GetVal() == 12);
	//    uint32_t ->
	EXPECT_NO_THROW(d = Double(); d.Set(uint32_t(12)););
	EXPECT_TRUE(d.GetVal() == 12);
	//    uint64_t ->
	EXPECT_NO_THROW(d = Double(); d.Set(uint64_t(12)););
	EXPECT_TRUE(d.GetVal() == 12);
	//    int8_t ->
	EXPECT_NO_THROW(d = Double(); d.Set(int8_t(12)););
	EXPECT_TRUE(d.GetVal() == 12);
	//    int32_t ->
	EXPECT_NO_THROW(d = Double(); d.Set(int32_t(12)););
	EXPECT_TRUE(d.GetVal() == 12);
	//    int64_t ->
	EXPECT_NO_THROW(d = Double(); d.Set(int64_t(12)););
	EXPECT_TRUE(d.GetVal() == 12);
	//    double ->
	EXPECT_NO_THROW(d = Double(); d.Set(double(12)););
	EXPECT_TRUE(d.GetVal() == 12);

}

GTEST_TEST(TestRealNum, Getter)
{
	// bool
	//      -> int8_t
	EXPECT_TRUE(Bool(true).AsCppInt8()   == static_cast<int8_t  >(1));
	//      -> int32_t
	EXPECT_TRUE(Bool(true).AsCppInt32()  == static_cast<int32_t >(1));
	//      -> int64_t
	EXPECT_TRUE(Bool(true).AsCppInt64()  == static_cast<int64_t >(1));
	//      -> uint8_t
	EXPECT_TRUE(Bool(true).AsCppUInt8()  == static_cast<uint8_t >(1));
	//      -> uint32_t
	EXPECT_TRUE(Bool(true).AsCppUInt32() == static_cast<uint32_t>(1));
	//      -> uint64_t
	EXPECT_TRUE(Bool(true).AsCppUInt64() == static_cast<uint64_t>(1));
	//      -> double
	EXPECT_TRUE(Bool(true).AsCppDouble() == static_cast<double  >(1));

	// int8_t
	//      -> int8_t
	EXPECT_TRUE(Int8(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_TRUE(Int8(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_TRUE(Int8(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	EXPECT_THROW(
		Int8(std::numeric_limits<int8_t>::lowest()).AsCppUInt8(), TypeError);
	EXPECT_TRUE(Int8(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_THROW(
		Int8(std::numeric_limits<int8_t>::lowest()).AsCppUInt32(), TypeError);
	EXPECT_TRUE(Int8(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_THROW(
		Int8(std::numeric_limits<int8_t>::lowest()).AsCppUInt64(), TypeError);
	EXPECT_TRUE(Int8(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(Int8(12).AsCppDouble() == static_cast<double  >(12));

	// int16_t
	//      -> int8_t
	EXPECT_THROW(
		Int16((std::numeric_limits<int16_t>::max)()).AsCppInt8(), TypeError);
	EXPECT_TRUE(Int16(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_TRUE(Int16(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_TRUE(Int16(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	EXPECT_THROW(
		Int16(std::numeric_limits<int16_t>::lowest()).AsCppUInt8(), TypeError);
	EXPECT_TRUE(Int16(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_THROW(
		Int16(std::numeric_limits<int16_t>::lowest()).AsCppUInt32(), TypeError);
	EXPECT_TRUE(Int16(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_THROW(
		Int16(std::numeric_limits<int16_t>::lowest()).AsCppUInt64(), TypeError);
	EXPECT_TRUE(Int16(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(Int16(12).AsCppDouble() == static_cast<double  >(12));

	// int32_t
	//      -> int8_t
	EXPECT_THROW(
		Int32((std::numeric_limits<int32_t>::max)()).AsCppInt8(), TypeError);
	EXPECT_TRUE(Int32(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_TRUE(Int32(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_TRUE(Int32(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	EXPECT_THROW(
		Int32(std::numeric_limits<int32_t>::lowest()).AsCppUInt8(), TypeError);
	EXPECT_TRUE(Int32(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_THROW(
		Int32(std::numeric_limits<int32_t>::lowest()).AsCppUInt32(), TypeError);
	EXPECT_TRUE(Int32(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_THROW(
		Int32(std::numeric_limits<int32_t>::lowest()).AsCppUInt64(), TypeError);
	EXPECT_TRUE(Int32(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(Int32(12).AsCppDouble() == static_cast<double  >(12));

	// int64_t
	EXPECT_THROW(
		Int64((std::numeric_limits<int64_t>::max)()).AsCppInt8(), TypeError);
	EXPECT_TRUE(Int64(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_THROW(
		Int64((std::numeric_limits<int64_t>::max)()).AsCppInt32(), TypeError);
	EXPECT_TRUE(Int64(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_TRUE(Int64(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	EXPECT_THROW(
		Int64(std::numeric_limits<int64_t>::lowest()).AsCppUInt8(), TypeError);
	EXPECT_TRUE(Int64(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_THROW(
		Int64(std::numeric_limits<int64_t>::lowest()).AsCppUInt32(), TypeError);
	EXPECT_TRUE(Int64(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_THROW(
		Int64(std::numeric_limits<int64_t>::lowest()).AsCppUInt64(), TypeError);
	EXPECT_TRUE(Int64(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(Int64(12).AsCppDouble() == static_cast<double  >(12));

	// uint8_t
	EXPECT_THROW(
		UInt8((std::numeric_limits<uint8_t>::max)()).AsCppInt8(), TypeError);
	EXPECT_TRUE(UInt8(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_TRUE(UInt8(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_TRUE(UInt8(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	EXPECT_TRUE(UInt8(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_TRUE(UInt8(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_TRUE(UInt8(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(UInt8(12).AsCppDouble() == static_cast<double  >(12));

	// uint16_t
	EXPECT_THROW(
		UInt16((std::numeric_limits<uint16_t>::max)()).AsCppInt8(), TypeError);
	EXPECT_TRUE(UInt16(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_TRUE(UInt16(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_TRUE(UInt16(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	EXPECT_THROW(
		UInt16((std::numeric_limits<uint16_t>::max)()).AsCppUInt8(), TypeError);
	EXPECT_TRUE(UInt16(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_TRUE(UInt16(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_TRUE(UInt16(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(UInt16(12).AsCppDouble() == static_cast<double  >(12));

	// uint32_t
	EXPECT_THROW(
		UInt32((std::numeric_limits<uint32_t>::max)()).AsCppInt8(), TypeError);
	EXPECT_TRUE(UInt32(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_THROW(
		UInt32((std::numeric_limits<uint32_t>::max)()).AsCppInt32(), TypeError);
	EXPECT_TRUE(UInt32(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_TRUE(UInt32(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	EXPECT_THROW(
		UInt32((std::numeric_limits<uint32_t>::max)()).AsCppUInt8(), TypeError);
	EXPECT_TRUE(UInt32(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_TRUE(UInt32(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_TRUE(UInt32(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(UInt32(12).AsCppDouble() == static_cast<double  >(12));

	// uint64_t
	EXPECT_THROW(
		UInt64((std::numeric_limits<uint64_t>::max)()).AsCppInt8(), TypeError);
	EXPECT_TRUE(UInt64(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_THROW(
		UInt64((std::numeric_limits<uint64_t>::max)()).AsCppInt32(), TypeError);
	EXPECT_TRUE(UInt64(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_THROW(
		UInt64((std::numeric_limits<uint64_t>::max)()).AsCppInt64(), TypeError);
	EXPECT_TRUE(UInt64(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	EXPECT_THROW(
		UInt64((std::numeric_limits<uint64_t>::max)()).AsCppUInt8(), TypeError);
	EXPECT_TRUE(UInt64(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_THROW(
		UInt64((std::numeric_limits<uint64_t>::max)()).AsCppUInt32(), TypeError);
	EXPECT_TRUE(UInt64(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_TRUE(UInt64(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(UInt64(12).AsCppDouble() == static_cast<double  >(12));

	// float
	EXPECT_THROW(
		Float((std::numeric_limits<float>::max)()).AsCppInt8(), TypeError);
	EXPECT_THROW(
		Float(std::numeric_limits<float>::lowest()).AsCppInt8(), TypeError);
	EXPECT_TRUE(Float(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_THROW(
		Float((std::numeric_limits<float>::max)()).AsCppInt32(), TypeError);
	EXPECT_THROW(
		Float(std::numeric_limits<float>::lowest()).AsCppInt32(), TypeError);
	EXPECT_TRUE(Float(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_THROW(
		Float((std::numeric_limits<float>::max)()).AsCppInt64(), TypeError);
	EXPECT_THROW(
		Float(std::numeric_limits<float>::lowest()).AsCppInt64(), TypeError);
	EXPECT_TRUE(Float(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	//      -> int64_t
	EXPECT_THROW(
		Float((std::numeric_limits<float>::max)()).AsCppUInt8(), TypeError);
	EXPECT_THROW(
		Float(std::numeric_limits<float>::lowest()).AsCppUInt8(), TypeError);
	EXPECT_TRUE(Float(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_THROW(
		Float((std::numeric_limits<float>::max)()).AsCppUInt32(), TypeError);
	EXPECT_THROW(
		Float(std::numeric_limits<float>::lowest()).AsCppUInt32(), TypeError);
	EXPECT_TRUE(Float(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_THROW(
		Float((std::numeric_limits<float>::max)()).AsCppUInt64(), TypeError);
	EXPECT_THROW(
		Float(std::numeric_limits<float>::lowest()).AsCppUInt64(), TypeError);
	EXPECT_TRUE(Float(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(Float(12).AsCppDouble() == static_cast<double  >(12));

	// double
	EXPECT_THROW(
		Double((std::numeric_limits<double>::max)()).AsCppInt8(), TypeError);
	EXPECT_THROW(
		Double(std::numeric_limits<double>::lowest()).AsCppInt8(), TypeError);
	EXPECT_TRUE(Double(12).AsCppInt8()   == static_cast<int8_t  >(12));
	//      -> int32_t
	EXPECT_THROW(
		Double((std::numeric_limits<double>::max)()).AsCppInt32(), TypeError);
	EXPECT_THROW(
		Double(std::numeric_limits<double>::lowest()).AsCppInt32(), TypeError);
	EXPECT_TRUE(Double(12).AsCppInt32()  == static_cast<int32_t >(12));
	//      -> int64_t
	EXPECT_THROW(
		Double((std::numeric_limits<double>::max)()).AsCppInt64(), TypeError);
	EXPECT_THROW(
		Double(std::numeric_limits<double>::lowest()).AsCppInt64(), TypeError);
	EXPECT_TRUE(Double(12).AsCppInt64()  == static_cast<int64_t >(12));
	//      -> uint8_t
	//      -> int64_t
	EXPECT_THROW(
		Double((std::numeric_limits<double>::max)()).AsCppUInt8(), TypeError);
	EXPECT_THROW(
		Double(std::numeric_limits<double>::lowest()).AsCppUInt8(), TypeError);
	EXPECT_TRUE(Double(12).AsCppUInt8()  == static_cast<uint8_t >(12));
	//      -> uint32_t
	EXPECT_THROW(
		Double((std::numeric_limits<double>::max)()).AsCppUInt32(), TypeError);
	EXPECT_THROW(
		Double(std::numeric_limits<double>::lowest()).AsCppUInt32(), TypeError);
	EXPECT_TRUE(Double(12).AsCppUInt32() == static_cast<uint32_t>(12));
	//      -> uint64_t
	EXPECT_THROW(
		Double((std::numeric_limits<double>::max)()).AsCppUInt64(), TypeError);
	EXPECT_THROW(
		Double(std::numeric_limits<double>::lowest()).AsCppUInt64(), TypeError);
	EXPECT_TRUE(Double(12).AsCppUInt64() == static_cast<uint64_t>(12));
	//      -> double
	EXPECT_TRUE(Double(12).AsCppDouble() == static_cast<double  >(12));
}

GTEST_TEST(TestRealNum, IsTrue)
{
	EXPECT_EQ((Bool(true)).IsTrue(), static_cast<bool>(true));
	EXPECT_EQ(Bool(false).IsTrue(), static_cast<bool>(false));

	// Integer -> bool
	EXPECT_EQ((Int8(2)).IsTrue(),
		static_cast<bool>(static_cast<int8_t>(2)));
	EXPECT_EQ((Int8(0)).IsTrue(),
		static_cast<bool>(static_cast<int8_t>(0)));
	EXPECT_EQ((Int16(2)).IsTrue(),
		static_cast<bool>(static_cast<int16_t>(2)));
	EXPECT_EQ((Int16(0)).IsTrue(),
		static_cast<bool>(static_cast<int16_t>(0)));
	EXPECT_EQ((Int32(2)).IsTrue(),
		static_cast<bool>(static_cast<int32_t>(2)));
	EXPECT_EQ((Int32(0)).IsTrue(),
		static_cast<bool>(static_cast<int32_t>(0)));
	EXPECT_EQ((Int64(2)).IsTrue(),
		static_cast<bool>(static_cast<int64_t>(2)));
	EXPECT_EQ((Int64(0)).IsTrue(),
		static_cast<bool>(static_cast<int64_t>(0)));

	EXPECT_EQ((UInt8(2)).IsTrue(),
		static_cast<bool>(static_cast<uint8_t>(2)));
	EXPECT_EQ((UInt8(0)).IsTrue(),
		static_cast<bool>(static_cast<uint8_t>(0)));
	EXPECT_EQ((UInt16(2)).IsTrue(),
		static_cast<bool>(static_cast<uint16_t>(2)));
	EXPECT_EQ((UInt16(0)).IsTrue(),
		static_cast<bool>(static_cast<uint16_t>(0)));
	EXPECT_EQ((UInt32(2)).IsTrue(),
		static_cast<bool>(static_cast<uint32_t>(2)));
	EXPECT_EQ((UInt32(0)).IsTrue(),
		static_cast<bool>(static_cast<uint32_t>(0)));
	EXPECT_EQ((UInt64(2)).IsTrue(),
		static_cast<bool>(static_cast<uint64_t>(2)));
	EXPECT_EQ((UInt64(0)).IsTrue(),
		static_cast<bool>(static_cast<uint64_t>(0)));

	// Float -> bool
	EXPECT_EQ((Float(0.001F)).IsTrue(),
		static_cast<bool>(static_cast<float>(0.001F)));
	EXPECT_EQ((Float(-0.001F)).IsTrue(),
		static_cast<bool>(static_cast<float>(-0.001F)));
	EXPECT_EQ((Float(0.0F)).IsTrue(),
		static_cast<bool>(static_cast<float>(0.0F)));
	EXPECT_EQ((Float(-0.0F)).IsTrue(),
		static_cast<bool>(static_cast<float>(-0.0F)));

	// Double -> bool
	EXPECT_EQ((Double(0.001)).IsTrue(),
		static_cast<bool>(static_cast<double>(0.001)));
	EXPECT_EQ((Double(-0.001)).IsTrue(),
		static_cast<bool>(static_cast<double>(-0.001)));
	EXPECT_EQ((Double(0.0)).IsTrue(),
		static_cast<bool>(static_cast<double>(0.0)));
	EXPECT_EQ((Double(-0.0)).IsTrue(),
		static_cast<bool>(static_cast<double>(-0.0)));
}

GTEST_TEST(TestRealNum, Assignment)
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

GTEST_TEST(TestRealNum, Comparison)
{
	// ==
	// same internal type
	EXPECT_EQ((Int32(123) == Int32(123)),
		static_cast<int32_t>(123) == static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) == Int32(1234)),
		static_cast<int32_t>(123) == static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) == Bool(true)),
		static_cast<int32_t>(123) == static_cast<int>(1));
	EXPECT_EQ((Int32(123) == Double(123.0)),
		static_cast<int32_t>(123) == static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) == Double(1234.0)),
		static_cast<int32_t>(123) == static_cast<double>(1234.0));

	// !=
	// same internal type
	EXPECT_EQ((Int32(123) != Int32(123)),
		static_cast<int32_t>(123) != static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) != Int32(1234)),
		static_cast<int32_t>(123) != static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) != Bool(true)),
		static_cast<int32_t>(123) != static_cast<int>(1));
	EXPECT_EQ((Int32(123) != Double(123.0)),
		static_cast<int32_t>(123) != static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) != Double(1234.0)),
		static_cast<int32_t>(123) != static_cast<double>(1234.0));

	// <=
	// same internal type
	EXPECT_EQ((Int32(1234) <= Int32(123)),
		static_cast<int32_t>(1234) <= static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) <= Int32(1234)),
		static_cast<int32_t>(123) <= static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) <= Bool(true)),
		static_cast<int32_t>(123) <= static_cast<int>(1));
	EXPECT_EQ((Int32(1234) <= Double(123.0)),
		static_cast<int32_t>(1234) <= static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) <= Double(1234.0)),
		static_cast<int32_t>(123) <= static_cast<double>(1234.0));

	// >=
	// same internal type
	EXPECT_EQ((Int32(123) >= Int32(123)),
		static_cast<int32_t>(123) >= static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) >= Int32(1234)),
		static_cast<int32_t>(123) >= static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) >= Bool(true)),
		static_cast<int32_t>(123) >= static_cast<int>(1));
	EXPECT_EQ((Int32(123) >= Double(123.0)),
		static_cast<int32_t>(123) >= static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) >= Double(1234.0)),
		static_cast<int32_t>(123) >= static_cast<double>(1234.0));

	// <
	// same internal type
	EXPECT_EQ((Int32(123) < Int32(123)),
		static_cast<int32_t>(123) < static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) < Int32(1234)),
		static_cast<int32_t>(123) < static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) < Bool(true)),
		static_cast<int32_t>(123) < static_cast<int>(1));
	EXPECT_EQ((Int32(123) < Double(123.0)),
		static_cast<int32_t>(123) < static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) < Double(1234.0)),
		static_cast<int32_t>(123) < static_cast<double>(1234.0));

	// >
	// same internal type
	EXPECT_EQ((Int32(1234) > Int32(123)),
		static_cast<int32_t>(1234) > static_cast<int32_t>(123));
	EXPECT_EQ((Int32(123) > Int32(1234)),
		static_cast<int32_t>(123) > static_cast<int32_t>(1234));

	// different internal type
	EXPECT_EQ((Int32(123) > Bool(true)),
		static_cast<int32_t>(123) > static_cast<int>(1));
	EXPECT_EQ((Int32(1234) > Double(123.0)),
		static_cast<int32_t>(1234) > static_cast<double>(123.0));
	EXPECT_EQ((Int32(123) > Double(1234.0)),
		static_cast<int32_t>(123) > static_cast<double>(1234.0));
}

GTEST_TEST(TestRealNum, BitwiseOperation)
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

GTEST_TEST(TestRealNum, SelfOperation)
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

GTEST_TEST(TestRealNum, Increment)
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

GTEST_TEST(TestRealNum, Operation)
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

GTEST_TEST(TestRealNum, Category)
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

GTEST_TEST(TestRealNum, CategoryName)
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

GTEST_TEST(TestRealNum, Miscs)
{
	// Is null
	EXPECT_FALSE(Bool().IsNull());

	// Cast
	const auto kNum = Int8();
	EXPECT_NO_THROW(kNum.AsRealNum());
	EXPECT_THROW(kNum.AsNull(),       TypeError);
	EXPECT_THROW(kNum.AsString(),     TypeError);
	EXPECT_THROW(kNum.AsList(),       TypeError);
	EXPECT_THROW(kNum.AsDict(),       TypeError);
	EXPECT_THROW(kNum.AsStaticDict(), TypeError);
	EXPECT_THROW(kNum.AsBytes(),      TypeError);
	EXPECT_NO_THROW(kNum.AsHashable());

	EXPECT_NO_THROW(Int16().AsRealNum());
	EXPECT_THROW(Int32().AsNull(),       TypeError);
	EXPECT_THROW(Int64().AsString(),     TypeError);
	EXPECT_THROW(Int64().AsList(),       TypeError);
	EXPECT_THROW(Int64().AsDict(),       TypeError);
	EXPECT_THROW(Int64().AsStaticDict(), TypeError);
	EXPECT_THROW(Int64().AsBytes(),      TypeError);
	EXPECT_NO_THROW(Int16().AsHashable());

	// Copy
	static_assert(std::is_same<
		decltype(*Int8().Copy(Int8::Base::sk_null)),
		RealNumBaseObj&>::value, "Failed to test Copy virtual func");
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
		RealNumBaseObj&>::value, "Failed to test Move virtual func");
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

GTEST_TEST(TestRealNum, Hash)
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

GTEST_TEST(TestRealNum, GetNumType)
{
	EXPECT_EQ(Bool().GetNumType(), RealNumType::Bool);
	EXPECT_EQ(Int8().GetNumType(), RealNumType::Int8);
	EXPECT_EQ(Int16().GetNumType(), RealNumType::Int16);
	EXPECT_EQ(Int32().GetNumType(), RealNumType::Int32);
	EXPECT_EQ(Int64().GetNumType(), RealNumType::Int64);

	EXPECT_EQ(UInt8().GetNumType(), RealNumType::UInt8);
	EXPECT_EQ(UInt16().GetNumType(), RealNumType::UInt16);
	EXPECT_EQ(UInt32().GetNumType(), RealNumType::UInt32);
	EXPECT_EQ(UInt64().GetNumType(), RealNumType::UInt64);

	EXPECT_EQ(Float().GetNumType(), RealNumType::Float);
	EXPECT_EQ(Double().GetNumType(), RealNumType::Double);
}

GTEST_TEST(TestRealNum, GetNumTypeName)
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

	virtual RealNumType GetNumType() const override
	{
		return RealNumType::Other;
	}

	virtual const char* GetNumTypeName() const override
	{
		return "Int8Ext";
	}
};

template<typename _RhsObjT, typename _RhsT>
static _RhsObjT ConstructRhs(_RhsT rhs)
{
	return _RhsObjT(static_cast<typename _RhsObjT::InternalType>(rhs));
}

template<typename _LhsT, typename _RhsT, typename CheckProgT>
static void CheckTestResBool(_LhsT lhs, _RhsT rhs, bool expRes, CheckProgT prog)
{
	bool rhsBool =
		Internal::RealNumCompare<_RhsT, int>::Compare(rhs, 0) != 0 ?
		true : false;

	EXPECT_EQ(prog(lhs, Bool  (rhsBool)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<Int8  >(rhs)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<Int16 >(rhs)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<Int32 >(rhs)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<Int64 >(rhs)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<UInt8 >(rhs)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<UInt16>(rhs)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<UInt32>(rhs)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<UInt64>(rhs)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<Float >(rhs)), expRes);
	EXPECT_EQ(prog(lhs, ConstructRhs<Double>(rhs)), expRes);
}

template<typename _T>
struct RealNumComparisonTests
{
	template<typename _RhsT>
	static void TestRealNumBaseLE(const _T& lhs, _RhsT rhs)
	{
		bool expRes =
			Internal::RealNumCompare<typename _T::InternalType, _RhsT>::
				Compare(lhs.GetVal(), rhs) <= 0;

		CheckTestResBool(lhs, rhs, expRes,
			CompareTestHelpers<RealNumBaseObj>::Le);
	}

	template<typename _RhsT>
	static void TestRealNumBaseGE(const _T& lhs, _RhsT rhs)
	{
		bool expRes =
			Internal::RealNumCompare<typename _T::InternalType, _RhsT>::
				Compare(lhs.GetVal(), rhs) >= 0;

		CheckTestResBool(lhs, rhs, expRes,
			CompareTestHelpers<RealNumBaseObj>::Ge);
	}

	template<typename _RhsT>
	static void TestRealNumBaseNE(const _T& lhs, _RhsT rhs)
	{
		bool expRes =
			Internal::RealNumCompare<typename _T::InternalType, _RhsT>::
				Compare(lhs.GetVal(), rhs) != 0;

		CheckTestResBool(lhs, rhs, expRes,
			CompareTestHelpers<RealNumBaseObj>::Neq);
	}
}; // struct RealNumComparisonTests

} // namespace

GTEST_TEST(TestRealNum, BaseIsEqual)
{
	// Base object
	using BaseObjCmp = CompareTestHelpers<BaseObj>;
	// Other types
	EXPECT_TRUE(BaseObjCmp::Neq(Int8(1), Null()));

	// Bool
	RealNumComparisonTests<Bool  >::TestRealNumBaseNE(Bool  (true), 1);
	RealNumComparisonTests<Bool  >::TestRealNumBaseNE(Bool  (true), 0);

	// Int8
	RealNumComparisonTests<Int8  >::TestRealNumBaseNE(Int8  (1), 1);
	RealNumComparisonTests<Int8  >::TestRealNumBaseNE(Int8  (1), 0);
	// Int16
	RealNumComparisonTests<Int16 >::TestRealNumBaseNE(Int16 (1), 1);
	RealNumComparisonTests<Int16 >::TestRealNumBaseNE(Int16 (1), 0);

	// Int32
	RealNumComparisonTests<Int32 >::TestRealNumBaseNE(Int32 (1), 1);
	RealNumComparisonTests<Int32 >::TestRealNumBaseNE(Int32 (1), 0);

	// Int64
	RealNumComparisonTests<Int64 >::TestRealNumBaseNE(Int64 (1), 1);
	RealNumComparisonTests<Int64 >::TestRealNumBaseNE(Int64 (1), 0);

	// UInt8
	RealNumComparisonTests<UInt8 >::TestRealNumBaseNE(UInt8 (1), 1);
	RealNumComparisonTests<UInt8 >::TestRealNumBaseNE(UInt8 (1), 0);

	// UInt16
	RealNumComparisonTests<UInt16>::TestRealNumBaseNE(UInt16(1), 1);
	RealNumComparisonTests<UInt16>::TestRealNumBaseNE(UInt16(1), 0);

	// UInt32
	RealNumComparisonTests<UInt32>::TestRealNumBaseNE(UInt32(1), 1);
	RealNumComparisonTests<UInt32>::TestRealNumBaseNE(UInt32(1), 0);

	// UInt64
	RealNumComparisonTests<UInt64>::TestRealNumBaseNE(UInt64(1), 1);
	RealNumComparisonTests<UInt64>::TestRealNumBaseNE(UInt64(1), 0);

	// Float
	RealNumComparisonTests<Float>::TestRealNumBaseNE(Float(1), 1);
	RealNumComparisonTests<Float>::TestRealNumBaseNE(Float(1), 0);

	// Double
	RealNumComparisonTests<Double>::TestRealNumBaseNE(Double(1), 1);
	RealNumComparisonTests<Double>::TestRealNumBaseNE(Double(1), 0);

	// Unsupported extensions
	auto checkProgRealNumBase = [](
		const RealNumBaseObj& a, const RealNumBaseObj& b) -> bool
	{
		return a != b;
	};
	EXPECT_THROW(checkProgRealNumBase(Int8(1), Int8Ext(1)),
		UnsupportedOperation);

	auto checkBaseObjNE = [](const BaseObj& a, const BaseObj& b) -> bool
	{
		return a != b;
	};

	EXPECT_TRUE(checkBaseObjNE(Int64(10), Int8(2)));
	EXPECT_FALSE(checkBaseObjNE(Int64(2), Int8(2)));

	EXPECT_TRUE(checkBaseObjNE(Int8(1), Null()));
}

GTEST_TEST(TestRealNum, BaseIsLessThan)
{
	// <
	RealNumComparisonTests<Bool  >::TestRealNumBaseLE(Bool  (false), 2);
	RealNumComparisonTests<Int8  >::TestRealNumBaseLE(Int8  (0), 2);
	RealNumComparisonTests<Int16 >::TestRealNumBaseLE(Int16 (0), 2);
	RealNumComparisonTests<Int32 >::TestRealNumBaseLE(Int32 (0), 2);
	RealNumComparisonTests<Int64 >::TestRealNumBaseLE(Int64 (0), 2);
	RealNumComparisonTests<UInt8 >::TestRealNumBaseLE(UInt8 (0), 2);
	RealNumComparisonTests<UInt16>::TestRealNumBaseLE(UInt16(0), 2);
	RealNumComparisonTests<UInt32>::TestRealNumBaseLE(UInt32(0), 2);
	RealNumComparisonTests<UInt64>::TestRealNumBaseLE(UInt64(0), 2);
	RealNumComparisonTests<Float >::TestRealNumBaseLE(Float (0.0), 2);
	RealNumComparisonTests<Double>::TestRealNumBaseLE(Double(0.0), 2);

	auto checkBaseObjLE = [](const BaseObj& a, const BaseObj& b) -> bool
	{
		return a >= b;
	};

	EXPECT_FALSE(checkBaseObjLE(Bool(false), Int8(2)));

	EXPECT_THROW(checkBaseObjLE(Int8(1), Null()), UnsupportedOperation);
}

GTEST_TEST(TestRealNum, BaseIsGreaterThan)
{
	// >
	RealNumComparisonTests<Bool>::TestRealNumBaseLE(Bool(true), 0);
	RealNumComparisonTests<Int8>::TestRealNumBaseLE(Int8(5), 2);
	RealNumComparisonTests<Int16>::TestRealNumBaseLE(Int16(5), 2);
	RealNumComparisonTests<Int32>::TestRealNumBaseLE(Int32(5), 2);
	RealNumComparisonTests<Int64>::TestRealNumBaseLE(Int64(5), 2);
	RealNumComparisonTests<UInt8>::TestRealNumBaseLE(UInt8(5), 2);
	RealNumComparisonTests<UInt16>::TestRealNumBaseLE(UInt16(5), 2);
	RealNumComparisonTests<UInt32>::TestRealNumBaseLE(UInt32(5), 2);
	RealNumComparisonTests<UInt64>::TestRealNumBaseLE(UInt64(5), 2);
	RealNumComparisonTests<Float>::TestRealNumBaseLE(Float(5.0), 2);
	RealNumComparisonTests<Double>::TestRealNumBaseLE(Double(5.0), 2);

	auto checkBaseObjLE = [](const BaseObj& a, const BaseObj& b) -> bool
	{
		return a <= b;
	};

	EXPECT_FALSE(checkBaseObjLE(Bool(true), Int8(0)));

	EXPECT_THROW(checkBaseObjLE(Int8(1), Null()), UnsupportedOperation);
}

GTEST_TEST(TestRealNum, ToString)
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
