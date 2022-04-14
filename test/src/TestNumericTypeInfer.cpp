// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <SimpleObjects/NumericTypeInfer.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
} // namespace SimpleObjects_Test

GTEST_TEST(TestNumericTypeInfer, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestNumericTypeInfer, InferBinOpRetType)
{
	// same type
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, bool>::RetType,
		bool>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, int8_t>::RetType,
		int8_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int16_t, int16_t>::RetType,
		int16_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int32_t, int32_t>::RetType,
		int32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int64_t, int64_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint8_t, uint8_t>::RetType,
		uint8_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint16_t, uint16_t>::RetType,
		uint16_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint32_t, uint32_t>::RetType,
		uint32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint64_t, uint64_t>::RetType,
		uint64_t>::value,
		"InferBinOpRetType test failed.");

	// bool
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, int8_t>::RetType,
		int8_t>::value && std::is_same<
		Internal::InferBinOpRetType<int8_t, bool>::RetType,
		int8_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, int16_t>::RetType,
		int16_t>::value && std::is_same<
		Internal::InferBinOpRetType<int16_t, bool>::RetType,
		int16_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, int32_t>::RetType,
		int32_t>::value && std::is_same<
		Internal::InferBinOpRetType<int32_t, bool>::RetType,
		int32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, int64_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<int64_t, bool>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, uint8_t>::RetType,
		uint8_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint8_t, bool>::RetType,
		uint8_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, uint16_t>::RetType,
		uint16_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint16_t, bool>::RetType,
		uint16_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, uint32_t>::RetType,
		uint32_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint32_t, bool>::RetType,
		uint32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, uint64_t>::RetType,
		uint64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint64_t, bool>::RetType,
		uint64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, float>::RetType,
		float>::value && std::is_same<
		Internal::InferBinOpRetType<float, bool>::RetType,
		float>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<bool, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, bool>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// int8_t
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, int16_t>::RetType,
		int16_t>::value && std::is_same<
		Internal::InferBinOpRetType<int16_t, int8_t>::RetType,
		int16_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, int32_t>::RetType,
		int32_t>::value && std::is_same<
		Internal::InferBinOpRetType<int32_t, int8_t>::RetType,
		int32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, int64_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<int64_t, int8_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, uint8_t>::RetType,
		int16_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint8_t, int8_t>::RetType,
		int16_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, uint16_t>::RetType,
		int32_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint16_t, int8_t>::RetType,
		int32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, uint32_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint32_t, int8_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, uint64_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint64_t, int8_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, float>::RetType,
		float>::value && std::is_same<
		Internal::InferBinOpRetType<float, int8_t>::RetType,
		float>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int8_t, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, int8_t>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// int16_t
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int16_t, int32_t>::RetType,
		int32_t>::value && std::is_same<
		Internal::InferBinOpRetType<int32_t, int16_t>::RetType,
		int32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int16_t, int64_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<int64_t, int16_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int16_t, uint8_t>::RetType,
		int16_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint8_t, int16_t>::RetType,
		int16_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int16_t, uint16_t>::RetType,
		int32_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint16_t, int16_t>::RetType,
		int32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int16_t, uint32_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint32_t, int16_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int16_t, uint64_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint64_t, int16_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int16_t, float>::RetType,
		float>::value && std::is_same<
		Internal::InferBinOpRetType<float, int16_t>::RetType,
		float>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int16_t, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, int16_t>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// int32_t
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int32_t, int64_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<int64_t, int32_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int32_t, uint8_t>::RetType,
		int32_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint8_t, int32_t>::RetType,
		int32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int32_t, uint16_t>::RetType,
		int32_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint16_t, int32_t>::RetType,
		int32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int32_t, uint32_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint32_t, int32_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int32_t, uint64_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint64_t, int32_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int32_t, float>::RetType,
		float>::value && std::is_same<
		Internal::InferBinOpRetType<float, int32_t>::RetType,
		float>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int32_t, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, int32_t>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// int64_t
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int64_t, uint8_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint8_t, int64_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int64_t, uint16_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint16_t, int64_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int64_t, uint32_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint32_t, int64_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int64_t, uint64_t>::RetType,
		int64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint64_t, int64_t>::RetType,
		int64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int64_t, float>::RetType,
		float>::value && std::is_same<
		Internal::InferBinOpRetType<float, int64_t>::RetType,
		float>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<int64_t, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, int64_t>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// uint8_t
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint8_t, uint16_t>::RetType,
		uint16_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint16_t, uint8_t>::RetType,
		uint16_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint8_t, uint32_t>::RetType,
		uint32_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint32_t, uint8_t>::RetType,
		uint32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint8_t, uint64_t>::RetType,
		uint64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint64_t, uint8_t>::RetType,
		uint64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint8_t, float>::RetType,
		float>::value && std::is_same<
		Internal::InferBinOpRetType<float, uint8_t>::RetType,
		float>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint8_t, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, uint8_t>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// uint16_t
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint16_t, uint32_t>::RetType,
		uint32_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint32_t, uint16_t>::RetType,
		uint32_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint16_t, uint64_t>::RetType,
		uint64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint64_t, uint16_t>::RetType,
		uint64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint16_t, float>::RetType,
		float>::value && std::is_same<
		Internal::InferBinOpRetType<float, uint16_t>::RetType,
		float>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint16_t, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, uint16_t>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// uint32_t
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint32_t, uint64_t>::RetType,
		uint64_t>::value && std::is_same<
		Internal::InferBinOpRetType<uint64_t, uint32_t>::RetType,
		uint64_t>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint32_t, float>::RetType,
		float>::value && std::is_same<
		Internal::InferBinOpRetType<float, uint32_t>::RetType,
		float>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint32_t, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, uint32_t>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// uint64_t
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint64_t, float>::RetType,
		float>::value && std::is_same<
		Internal::InferBinOpRetType<float, uint64_t>::RetType,
		float>::value,
		"InferBinOpRetType test failed.");
	static_assert(std::is_same<
		Internal::InferBinOpRetType<uint64_t, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, uint64_t>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// float
	static_assert(std::is_same<
		Internal::InferBinOpRetType<float, double>::RetType,
		double>::value && std::is_same<
		Internal::InferBinOpRetType<double, float>::RetType,
		double>::value,
		"InferBinOpRetType test failed.");

	// double
}