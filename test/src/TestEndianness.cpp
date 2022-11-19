// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER
#include <SimpleObjects/Endianness.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestEndianness, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestEndianness, Endianness)
{
	EXPECT_TRUE(
		(Endian::native == Endian::little) ||
		(Endian::native == Endian::big)
	);
}
