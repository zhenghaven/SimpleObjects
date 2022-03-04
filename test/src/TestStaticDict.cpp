// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.



#include <gtest/gtest.h>

#include <algorithm>

#include <SimpleObjects/StaticDict.hpp>
#include <SimpleObjects/DefaultTypes.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
} // namespace SimpleObjects_Test

GTEST_TEST(TestStaticDict, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

//=====
template<typename _ValType, _ValType ..._data>
using FromStrSeq = FromDataSeqImpl<String, _ValType, _data...>;
template<typename _StrSeq>
using StrKey = typename _StrSeq::template ToOther<FromStrSeq>::type;
//=====

GTEST_TEST(TestStaticDict, KeyValuePairs)
{
	// Key types
	using Key1 = StrKey<SIMOBJ_KSTR("Key1")>;
	static_assert(std::is_same<Key1,
		StaticString<String, 'K', 'e', 'y', '1'> >::value,
		"Implementation Error");
	using Key2 = StrKey<SIMOBJ_KSTR("Key2")>;
	static_assert(std::is_same<Key2,
		StaticString<String, 'K', 'e', 'y', '2'> >::value,
		"Implementation Error");
	using Key3 = StrKey<SIMOBJ_KSTR("Key3")>;
	static_assert(std::is_same<Key3,
		StaticString<String, 'K', 'e', 'y', '3'> >::value,
		"Implementation Error");
	using KeyX = StrKey<SIMOBJ_KSTR("KeyX")>;
	static_assert(std::is_same<KeyX,
		StaticString<String, 'K', 'e', 'y', 'X'> >::value,
		"Implementation Error");


	using Tp = std::tuple<
		std::pair<Key1, String>,
		std::pair<Key2, Int64>,
		std::pair<Key3, List> >;


	// Get a pair from the tuple
	static_assert(std::is_same<
		typename std::tuple_element<1, Tp>::type,
		std::pair<Key2, Int64> >::value,
		"Implementation Error");
	// Get the key of a pair in the tuple
	static_assert(std::is_same<
		typename std::tuple_element<0,
			typename std::tuple_element<1, Tp>::type
		>::type,
		Key2>::value,
		"Implementation Error");
	// Get the value of a pair in the tuple
	static_assert(std::is_same<
		typename std::tuple_element<1,
			typename std::tuple_element<1, Tp>::type
		>::type,
		Int64>::value,
		"Implementation Error");


	// Tuple find element
	static_assert(std::is_same<
		typename TupleFindElement<Key1, Tp>::type,
		String>::value,
		"Implementation Error");
	static_assert(std::is_same<
		typename TupleFindElement<Key2, Tp>::type,
		Int64>::value,
		"Implementation Error");
	static_assert(std::is_same<
		typename TupleFindElement<Key3, Tp>::type,
		List>::value,
		"Implementation Error");
	//    Will cause compile error
	// static_assert(std::is_same<
	// 	typename TupleFindElement<KeyX, Tp>::type,
	// 	List>::value,
	// 	"Implementation Error");
}
