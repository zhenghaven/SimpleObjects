// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.



#include <gtest/gtest.h>

#include <algorithm>

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

GTEST_TEST(TestStaticDict, StaticInt)
{
	using Key1 = Int64Key<1>;
	static_assert(std::is_same<Key1,
		StaticPrimitiveValue<Int64, 1> >::value,
		"Implementation Error");
	EXPECT_EQ(Key1().key, Int64(1));
	using Key2 = Int64Key<2>;
	static_assert(std::is_same<Key2,
		StaticPrimitiveValue<Int64, 2> >::value,
		"Implementation Error");
	EXPECT_EQ(Key2().key, Int64(2));
}

GTEST_TEST(TestStaticDict, KeyValuePairs)
{
	// Key types
	using Key1 = StrKey<SIMOBJ_KSTR("Key1")>;
	using Key2 = StrKey<SIMOBJ_KSTR("Key2")>;
	using Key3 = Int64Key<3>;
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
		typename Internal::DTupleFindElement<Key1, Tp>::type,
		String>::value,
		"Implementation Error");
	static_assert(Internal::DTupleFindElement<Key1, Tp>::index == 0,
		"Implementation Error");
	static_assert(std::is_same<
		typename Internal::DTupleFindElement<Key2, Tp>::type,
		Int64>::value,
		"Implementation Error");
	static_assert(Internal::DTupleFindElement<Key2, Tp>::index == 1,
		"Implementation Error");
	static_assert(std::is_same<
		typename Internal::DTupleFindElement<Key3, Tp>::type,
		List>::value,
		"Implementation Error");
	static_assert(Internal::DTupleFindElement<Key3, Tp>::index == 2,
		"Implementation Error");
	//    Will cause compile error
	// static_assert(std::is_same<
	// 	typename Internal::DTupleFindElement<KeyX, Tp>::type,
	// 	List>::value,
	// 	"Implementation Error");



	// Reference types
	// using KeyRefType = std::reference_wrapper<
	// 	typename std::add_const<HashableBaseObj>::type
	// >;
	using KeyRefType = HashableReferenceWrapper<const HashableBaseObj>;
	using ValRefType = std::reference_wrapper<BaseObj>;

	// Instantiate Tuple
	Tp tp1;

	// Reference array
	const auto refArray = Internal::DTupleToArray<Tp,
		const KeyRefType,
		const ValRefType>::Convert(tp1);
	// Reference map
	const auto refMap = Internal::DTupleToMap<Tp,
		KeyRefType,
		ValRefType,
		MapType>::Convert(tp1);

	// ensures the pointers are the same
	//    Array
	//        Key address
	EXPECT_EQ(&refArray[0].first.get(), &std::get<0>(tp1).first.key);
	EXPECT_EQ(&refArray[1].first.get(), &std::get<1>(tp1).first.key);
	EXPECT_EQ(&refArray[2].first.get(), &std::get<2>(tp1).first.key);
	//        Value address
	EXPECT_EQ(&refArray[0].second.get(),
		&static_cast<BaseObj&>(std::get<0>(tp1).second));
	EXPECT_EQ(&refArray[1].second.get(),
		&static_cast<BaseObj&>(std::get<1>(tp1).second));
	EXPECT_EQ(&refArray[2].second.get(),
		&static_cast<BaseObj&>(std::get<2>(tp1).second));
	//    Map
	//        Key address
	const auto findKey1 = String("Key1");
	const auto findKey2 = String("Key2");
	const auto findKey3 = Int64(3);
	EXPECT_EQ(&(refMap.find(findKey1)->first.get()),
		&std::get<0>(tp1).first.key);
	EXPECT_EQ(&(refMap.find(findKey2)->first.get()),
		&std::get<1>(tp1).first.key);
	EXPECT_EQ(&(refMap.find(findKey3)->first.get()),
		&std::get<2>(tp1).first.key);
	//        Value address
	EXPECT_EQ(&(refMap.find(findKey1)->second.get()),
		&static_cast<BaseObj&>(std::get<0>(tp1).second));
	EXPECT_EQ(&(refMap.find(findKey2)->second.get()),
		&static_cast<BaseObj&>(std::get<1>(tp1).second));
	EXPECT_EQ(&(refMap.find(findKey3)->second.get()),
		&static_cast<BaseObj&>(std::get<2>(tp1).second));

	//    ensures the initial values are correct
	EXPECT_EQ(refArray[0].first.get(), String("Key1"));
	EXPECT_EQ(refArray[1].first.get(), String("Key2"));
	EXPECT_EQ(refArray[2].first.get(), Int64(3));

	EXPECT_EQ(refArray[0].second.get(), String());
	EXPECT_EQ(refArray[1].second.get(), Int64());
	EXPECT_EQ(refArray[2].second.get(), List());

	EXPECT_EQ((refMap.find(findKey1)->second.get()),
		String());
	EXPECT_EQ((refMap.find(findKey2)->second.get()),
		Int64());
	EXPECT_EQ((refMap.find(findKey3)->second.get()),
		List());

	//    change values in tuples
	std::get<0>(tp1).second = String("ref array val1");
	std::get<1>(tp1).second = Int64(12345);
	std::get<2>(tp1).second = List({Null()});

	//    ensures the change is reflected in the tuple
	EXPECT_EQ(refArray[0].second.get(), String("ref array val1"));
	EXPECT_EQ(refArray[1].second.get(), Int64(12345));
	EXPECT_EQ(refArray[2].second.get(), List({Null()}));

	EXPECT_EQ((refMap.find(findKey1)->second.get()),
		String("ref array val1"));
	EXPECT_EQ((refMap.find(findKey2)->second.get()),
		Int64(12345));
	EXPECT_EQ((refMap.find(findKey3)->second.get()),
		List({Null()}));
}

using TestStaticDictBase1 = StaticDict<
	std::tuple<
		std::pair<StrKey<SIMOBJ_KSTR("Key2_1")>, Int64> > >;

class TestStaticDict1 : public TestStaticDictBase1
{
public:
	using Base = TestStaticDictBase1;

	using Base::Base;

	typename Base::GetRef<StrKey<SIMOBJ_KSTR("Key2_1")> >
	get_Key2_1()
	{
		return Base::get<StrKey<SIMOBJ_KSTR("Key2_1")> >();
	}

	typename Base::GetConstRef<StrKey<SIMOBJ_KSTR("Key2_1")> >
	get_Key2_1() const
	{
		return Base::get<StrKey<SIMOBJ_KSTR("Key2_1")> >();
	}

}; // class TestStaticDict1

// using TestStaticDictBase2 = StaticDict<
// 	std::tuple<
// 		std::pair<SIMOBJ_KSTR("Key2_1"), String>,
// 		std::pair<SIMOBJ_KSTR("Key2_2"), Int64>,
// 		std::pair<SIMOBJ_KSTR("Key2_2"), Null> > >;

GTEST_TEST(TestStaticDict, StaticDictBasic)
{
	// Some basic tests on a basic static Dict type
	TestStaticDict1 dict;
	const auto& kdict = static_cast<const TestStaticDict1&>(dict);
	EXPECT_EQ(dict.get_Key2_1().GetVal(), 0);
	dict.get_Key2_1() = Int64(12345);
	EXPECT_EQ(kdict.get_Key2_1(), Int64(12345));

	// iterators
	EXPECT_EQ((dict.begin() + 0)->first.get(), String("Key2_1"));
	EXPECT_EQ((dict.begin() + 0)->second.get(), Int64(12345));
	// TODO: (dict.begin() + 0)->second.get() = Int64(54321);
	// EXPECT_EQ((dict.begin() + 0)->second.get(), Int64(54321));
	// Expected compile error:
	// (dict.begin() + 0)->first.get() = String("Key2_x");

	// const iterators
	EXPECT_EQ((dict.cbegin() + 0)->first.get(), String("Key2_1"));
	EXPECT_EQ((dict.cbegin() + 0)->second.get(), Int64(12345));
	// Expected compile error:
	// (dict.cbegin() + 0)->first.get() = String("Key2_2");
	// (dict.cbegin() + 0)->second.get() = Int64(54321);

	EXPECT_EQ(dict.size(), 1);

	// index by key
	EXPECT_EQ(dict.at(String("Key2_1")), Int64(12345));
	EXPECT_EQ(kdict.at(String("Key2_1")), Int64(12345));
	EXPECT_EQ(dict[String("Key2_1")], Int64(12345));
	EXPECT_EQ(kdict[String("Key2_1")], Int64(12345));

	EXPECT_THROW(dict.at(String("Key2_x")), std::out_of_range);
	EXPECT_THROW(kdict.at(String("Key2_x")), std::out_of_range);
	EXPECT_THROW(dict[String("Key2_x")], std::out_of_range);
	EXPECT_THROW(kdict[String("Key2_x")], std::out_of_range);

	// index by key
	EXPECT_EQ(dict.at(0), Int64(12345));
	EXPECT_EQ(kdict.at(0), Int64(12345));
	EXPECT_EQ(dict[0], Int64(12345));
	EXPECT_EQ(kdict[0], Int64(12345));

	EXPECT_THROW(dict.at(100), std::out_of_range);
	EXPECT_THROW(kdict.at(100), std::out_of_range);
	EXPECT_THROW(dict[100], std::out_of_range);
	EXPECT_THROW(kdict[100], std::out_of_range);

	// has key
	EXPECT_TRUE(dict.HasKey(String("Key2_1")));
	EXPECT_FALSE(dict.HasKey(String("Key2_x")));

	// copy
	TestStaticDict1 dictcp(dict);
	EXPECT_TRUE(dictcp == dict);
	EXPECT_FALSE(dictcp != dict);
	dict.get_Key2_1() = Int64(54321);
	EXPECT_FALSE(dictcp == dict);
	EXPECT_TRUE(dictcp != dict);

	// move
	TestStaticDict1 dictmv(std::move(dictcp));
	EXPECT_TRUE(dictmv == dictcp);
	EXPECT_FALSE(dictmv != dictcp);
}
