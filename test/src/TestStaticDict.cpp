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

GTEST_TEST(TestStaticDict, StaticString)
{
	// Key types
	using Key1 = StrKey<SIMOBJ_KSTR("Key1")>;
	static_assert(std::is_same<Key1,
		StaticString<String, 'K', 'e', 'y', '1'> >::value,
		"Implementation Error");
	EXPECT_EQ(Key1().key, String("Key1"));
	using Key2 = StrKey<SIMOBJ_KSTR("Key2")>;
	static_assert(std::is_same<Key2,
		StaticString<String, 'K', 'e', 'y', '2'> >::value,
		"Implementation Error");
	EXPECT_EQ(Key2().key, String("Key2"));
	using Key3 = StrKey<SIMOBJ_KSTR("Key3")>;
	static_assert(std::is_same<Key3,
		StaticString<String, 'K', 'e', 'y', '3'> >::value,
		"Implementation Error");
	EXPECT_EQ(Key3().key, String("Key3"));
	using KeyX = StrKey<SIMOBJ_KSTR("KeyX")>;
	static_assert(std::is_same<KeyX,
		StaticString<String, 'K', 'e', 'y', 'X'> >::value,
		"Implementation Error");
	EXPECT_EQ(KeyX().key, String("KeyX"));
}

GTEST_TEST(TestStaticDict, KeyValuePairs)
{
	// Key types
	using Key1 = StrKey<SIMOBJ_KSTR("Key1")>;
	using Key2 = StrKey<SIMOBJ_KSTR("Key2")>;
	using Key3 = StrKey<SIMOBJ_KSTR("Key3")>;
	using KeyX = StrKey<SIMOBJ_KSTR("KeyX")>;

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
		typename DTupleFindElement<Key1, Tp>::type,
		String>::value,
		"Implementation Error");
	static_assert(DTupleFindElement<Key1, Tp>::index == 0,
		"Implementation Error");
	static_assert(std::is_same<
		typename DTupleFindElement<Key2, Tp>::type,
		Int64>::value,
		"Implementation Error");
	static_assert(DTupleFindElement<Key2, Tp>::index == 1,
		"Implementation Error");
	static_assert(std::is_same<
		typename DTupleFindElement<Key3, Tp>::type,
		List>::value,
		"Implementation Error");
	static_assert(DTupleFindElement<Key3, Tp>::index == 2,
		"Implementation Error");
	//    Will cause compile error
	// static_assert(std::is_same<
	// 	typename DTupleFindElement<KeyX, Tp>::type,
	// 	List>::value,
	// 	"Implementation Error");



	// Reference types
	using KeyRefType = std::reference_wrapper<
		typename std::add_const<HashableBaseObj>::type
	>;
	using ValRefType = std::reference_wrapper<
		typename std::add_const<BaseObj>::type
	>;

	// Instantiate Tuple
	Tp tp1;

	// Reference array
	const auto refArray = DTupleToArray<Tp,
		KeyRefType,
		ValRefType>::Convert(tp1);

	EXPECT_EQ(refArray[0].first.get(), String("Key1"));
	EXPECT_EQ(refArray[1].first.get(), String("Key2"));
	EXPECT_EQ(refArray[2].first.get(), String("Key3"));

	EXPECT_EQ(refArray[0].second.get(), String());
	EXPECT_EQ(refArray[1].second.get(), Int64());
	EXPECT_EQ(refArray[2].second.get(), List());

	std::get<0>(tp1).second = String("ref array val1");
	std::get<1>(tp1).second = Int64(12345);
	std::get<2>(tp1).second = List({Null()});

	EXPECT_EQ(refArray[0].second.get(), String("ref array val1"));
	EXPECT_EQ(refArray[1].second.get(), Int64(12345));
	EXPECT_EQ(refArray[2].second.get(), List({Null()}));
}
