// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.



#include <gtest/gtest.h>

#include <algorithm>

#include <SimpleObjects/DefaultTypes.hpp>

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

GTEST_TEST(TestStaticDict, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
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
	// using KeyX = StrKey<SIMOBJ_KSTR("KeyX")>;

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



	// Copy
	Tp tp2;
	EXPECT_TRUE(std::get<0>(tp2).second == String());
	EXPECT_TRUE(std::get<1>(tp2).second == Int64());
	EXPECT_TRUE(std::get<2>(tp2).second == List());

	Internal::DTupleAssign::Copy(tp2, tp1);
	EXPECT_TRUE(std::get<0>(tp2).second == String("ref array val1"));
	EXPECT_TRUE(std::get<1>(tp2).second == Int64(12345));
	EXPECT_TRUE(std::get<2>(tp2).second == List({Null()}));

	// Move
	Tp tp3;
	const auto refArray3 = Internal::DTupleToArray<Tp,
		const KeyRefType,
		const ValRefType>::Convert(tp3);
	EXPECT_TRUE(refArray3[0].second.get() == String());
	EXPECT_TRUE(refArray3[1].second.get() == Int64());
	EXPECT_TRUE(refArray3[2].second.get() == List());

	Internal::DTupleAssign::Move(tp3, std::move(tp2));

	//    ensure the source is moved
	EXPECT_TRUE(std::get<0>(tp2).second == String());
	EXPECT_TRUE(std::get<1>(tp2).second == Int64(12345));
	EXPECT_TRUE(std::get<2>(tp2).second == List());

	//    ensure the original references are still valid
	const auto refArray3_1 = Internal::DTupleToArray<Tp,
		const KeyRefType,
		const ValRefType>::Convert(tp3);
	EXPECT_EQ(&refArray3[0].first.get(), &refArray3_1[0].first.get());
	EXPECT_EQ(&refArray3[1].first.get(), &refArray3_1[1].first.get());
	EXPECT_EQ(&refArray3[2].first.get(), &refArray3_1[2].first.get());
	EXPECT_EQ(&refArray3[0].second.get(), &refArray3_1[0].second.get());
	EXPECT_EQ(&refArray3[1].second.get(), &refArray3_1[1].second.get());
	EXPECT_EQ(&refArray3[2].second.get(), &refArray3_1[2].second.get());

	//    ensure the value is updated
	EXPECT_TRUE(std::get<0>(tp3).second == String("ref array val1"));
	EXPECT_TRUE(std::get<1>(tp3).second == Int64(12345));
	EXPECT_TRUE(std::get<2>(tp3).second == List({Null()}));
}

using TestStaticDictBase1 = StaticDict<
	std::tuple<
		std::pair<StrKey<SIMOBJ_KSTR("Key1_1")>, Int64> > >;

class TestStaticDict1 : public TestStaticDictBase1
{
public:
	using Base = TestStaticDictBase1;

	using Base::Base;

	typename Base::template GetRef<StrKey<SIMOBJ_KSTR("Key1_1")> >
	get_Key1_1()
	{
		return Base::template get<StrKey<SIMOBJ_KSTR("Key1_1")> >();
	}

	typename Base::template GetConstRef<StrKey<SIMOBJ_KSTR("Key1_1")> >
	get_Key1_1() const
	{
		return Base::template get<StrKey<SIMOBJ_KSTR("Key1_1")> >();
	}

}; // class TestStaticDict1

using TestStaticDictBase2 = StaticDict<
	std::tuple<
		std::pair<StrKey<SIMOBJ_KSTR("Key2_1")>, String>,
		std::pair<StrKey<SIMOBJ_KSTR("Key2_2")>, Int64>,
		std::pair<StrKey<SIMOBJ_KSTR("Key2_3")>, TestStaticDict1> > >;

class TestStaticDict2 : public TestStaticDictBase2
{
public:
	using Base = TestStaticDictBase2;

	using Base::Base;

	typename Base::template GetRef<StrKey<SIMOBJ_KSTR("Key2_1")> >
	get_Key2_1()
	{
		return Base::template get<StrKey<SIMOBJ_KSTR("Key2_1")> >();
	}

	typename Base::template GetConstRef<StrKey<SIMOBJ_KSTR("Key2_1")> >
	get_Key2_1() const
	{
		return Base::template get<StrKey<SIMOBJ_KSTR("Key2_1")> >();
	}

	typename Base::template GetRef<StrKey<SIMOBJ_KSTR("Key2_2")> >
	get_Key2_2()
	{
		return Base::template get<StrKey<SIMOBJ_KSTR("Key2_2")> >();
	}

	typename Base::template GetConstRef<StrKey<SIMOBJ_KSTR("Key2_2")> >
	get_Key2_2() const
	{
		return Base::template get<StrKey<SIMOBJ_KSTR("Key2_2")> >();
	}

	typename Base::template GetRef<StrKey<SIMOBJ_KSTR("Key2_3")> >
	get_Key2_3()
	{
		return Base::template get<StrKey<SIMOBJ_KSTR("Key2_3")> >();
	}

	typename Base::template GetConstRef<StrKey<SIMOBJ_KSTR("Key2_3")> >
	get_Key2_3() const
	{
		return Base::template get<StrKey<SIMOBJ_KSTR("Key2_3")> >();
	}

}; // class TestStaticDict2

GTEST_TEST(TestStaticDict, StaticDictBasic)
{
	// Some basic tests on a basic static Dict type
	TestStaticDict1 dict;
	const auto& kdict = static_cast<const TestStaticDict1&>(dict);
	EXPECT_EQ(dict.get_Key1_1().GetVal(), 0);
	dict.get_Key1_1() = Int64(12345);
	EXPECT_EQ(kdict.get_Key1_1(), Int64(12345));

	// iterators
	EXPECT_EQ((dict.begin() + 0)->first.get(), String("Key1_1"));
	EXPECT_EQ((dict.begin() + 0)->second.get(), Int64(12345));
	// TODO: (dict.begin() + 0)->second.get() = Int64(54321);
	// EXPECT_EQ((dict.begin() + 0)->second.get(), Int64(54321));
	EXPECT_NE(dict.begin(), dict.end());
	// Expected compile error:
	// (dict.begin() + 0)->first.get() = String("KeyX");

	// const iterators
	EXPECT_EQ((dict.cbegin() + 0)->first.get(), String("Key1_1"));
	EXPECT_EQ((dict.cbegin() + 0)->second.get(), Int64(12345));
	EXPECT_NE(dict.cbegin(), dict.cend());
	EXPECT_EQ((kdict.begin() + 0)->first.get(), String("Key1_1"));
	EXPECT_EQ((kdict.begin() + 0)->second.get(), Int64(12345));
	EXPECT_NE(kdict.begin(), kdict.end());
	// Expected compile error:
	// (dict.cbegin() + 0)->first.get() = String("Key2_2");
	// (dict.cbegin() + 0)->second.get() = Int64(54321);

	EXPECT_EQ(dict.size(), 1);

	// index by key
	EXPECT_EQ(dict.at(String("Key1_1")), Int64(12345));
	EXPECT_EQ(kdict.at(String("Key1_1")), Int64(12345));
	EXPECT_EQ(dict[String("Key1_1")], Int64(12345));
	EXPECT_EQ(kdict[String("Key1_1")], Int64(12345));

	EXPECT_THROW(dict.at(String("KeyX")), KeyError);
	EXPECT_THROW(kdict.at(String("KeyX")), KeyError);
	EXPECT_THROW(dict[String("KeyX")], KeyError);
	EXPECT_THROW(kdict[String("KeyX")], KeyError);

	// index by key
	EXPECT_EQ(dict.at(0), Int64(12345));
	EXPECT_EQ(kdict.at(0), Int64(12345));
	EXPECT_EQ(dict[0], Int64(12345));
	EXPECT_EQ(kdict[0], Int64(12345));

	EXPECT_THROW(dict.at(100), IndexError);
	EXPECT_THROW(kdict.at(100), IndexError);
	EXPECT_THROW(dict[100], IndexError);
	EXPECT_THROW(kdict[100], IndexError);

	// has key
	EXPECT_TRUE(dict.HasKey(String("Key1_1")));
	EXPECT_FALSE(dict.HasKey(String("KeyX")));

	// copy
	TestStaticDict1 dictcp(dict);
	EXPECT_TRUE(dictcp == dict);
	EXPECT_FALSE(dictcp != dict);
	dict.get_Key1_1() = Int64(54321);
	EXPECT_FALSE(dictcp == dict);
	EXPECT_TRUE(dictcp != dict);
	EXPECT_TRUE(*(dict.Copy(StaticDictBaseObj::sk_null)) == dict);
	EXPECT_TRUE(*(dict.Copy(BaseObj::sk_null)) == dict);

	// move
	TestStaticDict1 dictmv(std::move(dictcp));
	EXPECT_TRUE(dictmv == dictcp);
	EXPECT_FALSE(dictmv != dictcp);
	dictcp = dict;
	EXPECT_TRUE(*(dictcp.Move(StaticDictBaseObj::sk_null)) == dict);
	dictcp = dict;
	EXPECT_TRUE(*(dictcp.Move(BaseObj::sk_null)) == dict);
}

GTEST_TEST(TestStaticDict, Construction)
{
	// Default
	EXPECT_NO_THROW({
		TestStaticDict2().get_Key2_1();
	});
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObj> base;
		base.reset(new TestStaticDict2());
		base.reset();
	});

	// Copy & Move
	TestStaticDict2 dict;
	dict.get_Key2_1() = String("val2_1");
	dict.get_Key2_2() = Int64(12345);
	dict.get_Key2_3().get_Key1_1() = Int64(54321);
	TestStaticDict2 dictCp = dict;
	EXPECT_EQ(dictCp.get_Key2_1(), String("val2_1"));
	EXPECT_EQ(dictCp.get_Key2_2(), Int64(12345));
	EXPECT_EQ(dictCp.get_Key2_3().get_Key1_1(), Int64(54321));
	TestStaticDict2 dictMv = std::move(dictCp);
	EXPECT_EQ(dictCp.get_Key2_1(), String());
	EXPECT_EQ(dictMv.get_Key2_1(), String("val2_1"));
	EXPECT_EQ(dictMv.get_Key2_2(), Int64(12345));
	EXPECT_EQ(dictMv.get_Key2_3().get_Key1_1(), Int64(54321));
}

GTEST_TEST(TestStaticDict, Assignment)
{
	TestStaticDict2 dict;
	dict.get_Key2_1() = String("val2_1");
	dict.get_Key2_2() = Int64(12345);
	dict.get_Key2_3().get_Key1_1() = Int64(54321);

	TestStaticDict2 dictCp;
	EXPECT_EQ(dictCp.get_Key2_1(), String());
	EXPECT_EQ(dictCp.get_Key2_2(), Int64());
	EXPECT_EQ(dictCp.get_Key2_3().get_Key1_1(), Int64());
	dictCp = dict;
	EXPECT_EQ(dictCp.get_Key2_1(), String("val2_1"));
	EXPECT_EQ(dictCp.get_Key2_2(), Int64(12345));
	EXPECT_EQ(dictCp.get_Key2_3().get_Key1_1(), Int64(54321));
	// We want to ensure self assignment is OK,
	// meanwhile to avoid compiler warning
	TestStaticDict2* dictCpPtr = nullptr;
	dictCpPtr = &dictCp;
	dictCp = *dictCpPtr; // self copy ==> no op
	EXPECT_EQ(dictCp.get_Key2_1(), String("val2_1"));
	EXPECT_EQ(dictCp.get_Key2_2(), Int64(12345));
	EXPECT_EQ(dictCp.get_Key2_3().get_Key1_1(), Int64(54321));

	TestStaticDict2 dictMv;
	EXPECT_EQ(dictMv.get_Key2_1(), String());
	EXPECT_EQ(dictMv.get_Key2_2(), Int64());
	EXPECT_EQ(dictMv.get_Key2_3().get_Key1_1(), Int64());
	dictMv = std::move(dictCp);
	EXPECT_EQ(dictCp.get_Key2_1(), String());
	EXPECT_EQ(dictMv.get_Key2_1(), String("val2_1"));
	EXPECT_EQ(dictMv.get_Key2_2(), Int64(12345));
	EXPECT_EQ(dictMv.get_Key2_3().get_Key1_1(), Int64(54321));
	TestStaticDict2* dictMvPtr = nullptr;
	dictMvPtr = &dictMv;
	dictMv = std::move(*dictMvPtr); // self move ==> no op
	EXPECT_EQ(dictMv.get_Key2_1(), String("val2_1"));
	EXPECT_EQ(dictMv.get_Key2_2(), Int64(12345));
	EXPECT_EQ(dictMv.get_Key2_3().get_Key1_1(), Int64(54321));
}

GTEST_TEST(TestStaticDict, Category)
{
	static_assert(TestStaticDict2::sk_cat() == ObjCategory::StaticDict, "Category failed.");
	EXPECT_EQ(TestStaticDict2::sk_cat(), ObjCategory::StaticDict);

	TestStaticDict2 val;
	EXPECT_EQ(val.GetCategory(), ObjCategory::StaticDict);
}

GTEST_TEST(TestStaticDict, CategoryName)
{
	EXPECT_EQ(TestStaticDict2().GetCategoryName(), std::string("StaticDict"));
}

GTEST_TEST(TestStaticDict, Setters)
{
	TestStaticDict1 dc1_1;
	TestStaticDict1 dc1_2;
	TestStaticDict2 dc2_1;
	TestStaticDict2 dc2_2;
	EXPECT_NO_THROW(dc1_1.Set(TestStaticDict1()));
	EXPECT_NO_THROW(dc1_1.Set(dc1_2));
	EXPECT_NO_THROW(dc2_1.Set(TestStaticDict2()));
	EXPECT_NO_THROW(dc2_1.Set(dc2_2));

	EXPECT_THROW(dc1_1.Set(TestStaticDict2()), TypeError);
	EXPECT_THROW(dc1_1.Set(dc2_1), TypeError);
	EXPECT_THROW(dc2_1.Set(TestStaticDict1()), TypeError);
	EXPECT_THROW(dc2_1.Set(dc1_1), TypeError);

	EXPECT_THROW(dc2_1.Set(static_cast<bool >(true)), TypeError);
	EXPECT_THROW(dc2_1.Set(static_cast<uint8_t >(1)), TypeError);
	EXPECT_THROW(dc2_1.Set(static_cast< int8_t >(1)), TypeError);
	EXPECT_THROW(dc2_1.Set(static_cast<uint32_t>(1)), TypeError);
	EXPECT_THROW(dc2_1.Set(static_cast< int32_t>(1)), TypeError);
	EXPECT_THROW(dc2_1.Set(static_cast<uint64_t>(1)), TypeError);
	EXPECT_THROW(dc2_1.Set(static_cast< int64_t>(1)), TypeError);
	EXPECT_THROW(dc2_1.Set(static_cast<double>(1.0)), TypeError);
}

GTEST_TEST(TestStaticDict, Getters)
{
	TestStaticDict1 dc1_1;
	TestStaticDict2 dc2_1;
	EXPECT_TRUE(dc1_1.IsTrue());
	EXPECT_TRUE(dc2_1.IsTrue());

	EXPECT_THROW(dc2_1.AsCppUInt8() ,  TypeError);
	EXPECT_THROW(dc2_1.AsCppInt8()  ,  TypeError);
	EXPECT_THROW(dc2_1.AsCppUInt32(),  TypeError);
	EXPECT_THROW(dc2_1.AsCppInt32() ,  TypeError);
	EXPECT_THROW(dc2_1.AsCppUInt64(),  TypeError);
	EXPECT_THROW(dc2_1.AsCppInt64() ,  TypeError);
	EXPECT_THROW(dc2_1.AsCppDouble() , TypeError);
}

GTEST_TEST(TestStaticDict, Compare)
{
	TestStaticDict2 dict1;
	dict1.get_Key2_1() = String("val2_1");
	dict1.get_Key2_2() = Int64(12345);
	dict1.get_Key2_3().get_Key1_1() = Int64(54321);
	TestStaticDict2 dict2;
	dict2.get_Key2_1() = String("val2_1");
	dict2.get_Key2_2() = Int64(12345);
	dict2.get_Key2_3().get_Key1_1() = Int64(54321);
	TestStaticDict2 dict3;
	dict3.get_Key2_1() = String("val2_1");
	dict3.get_Key2_2() = Int64(55555);
	dict3.get_Key2_3().get_Key1_1() = Int64(54321);

	// ==
	EXPECT_TRUE( dict1 == dict2);
	EXPECT_FALSE(dict1 != dict2);
	EXPECT_TRUE( dict1 != dict3);
	EXPECT_FALSE(dict1 == dict3);

	using DictBaseCmp = CompareTestHelpers<StaticDictBaseObj>;

	EXPECT_FALSE(DictBaseCmp::Neq(dict1, dict2));
	EXPECT_TRUE(DictBaseCmp::Neq(dict1, dict3));
	EXPECT_TRUE(DictBaseCmp::Neq(dict1, dict3.get_Key2_3()));

	// == diff obj
	using BaseObjCmp = CompareTestHelpers<BaseObj>;

	EXPECT_TRUE(BaseObjCmp::Neq(dict1, Null()));
	EXPECT_TRUE(BaseObjCmp::Neq(dict1, String()));

	// <
	EXPECT_THROW(BaseObjCmp::Lt(dict1, Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Lt(dict1, Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Gt(dict1, Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Le(dict1, Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Le(dict1, dict1), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Ge(dict1, Null()), UnsupportedOperation);
	EXPECT_THROW(BaseObjCmp::Ge(dict1, dict1), UnsupportedOperation);
}

GTEST_TEST(TestStaticDict, Len)
{
	TestStaticDict2 dict1;
	EXPECT_EQ(dict1.size(), 3);
	EXPECT_EQ(dict1.get_Key2_3().size(), 1);
}

GTEST_TEST(TestStaticDict, Iterator)
{
	TestStaticDict2 dict1;
	dict1.get_Key2_1() = String("val2_1");
	dict1.get_Key2_2() = Int64(12345);
	dict1.get_Key2_3().get_Key1_1() = Int64(54321);
	const TestStaticDict2& kdict1 = dict1;

	using _ExpArrayItemT = std::pair<String, std::reference_wrapper<BaseObj> >;
	std::array<_ExpArrayItemT, 3> expRes =
	{
		_ExpArrayItemT(String("Key2_1"), dict1.get_Key2_1()),
		_ExpArrayItemT(String("Key2_2"), dict1.get_Key2_2()),
		_ExpArrayItemT(String("Key2_3"), dict1.get_Key2_3()),
	};

	// const it
	auto expIt = expRes.cbegin();
	for(auto it = dict1.cbegin();
		it != dict1.cend() && expIt != expRes.cend();
		it++, ++expIt)
	{
		EXPECT_TRUE(it->first.get()  == expIt->first);
		EXPECT_TRUE(it->second.get() == expIt->second.get());
	}

	// const obj begin & end
	expIt = expRes.cbegin();
	for(auto it = kdict1.begin();
		it != kdict1.end() && expIt != expRes.cend();
		++it, ++expIt)
	{
		EXPECT_TRUE(it->first.get()  == expIt->first);
		EXPECT_TRUE(it->second.get() == expIt->second.get());
	}

	// it
	expIt = expRes.cbegin();
	for(auto it = dict1.begin();
		it != dict1.end() && expIt != expRes.cend();
		it++, ++expIt)
	{
		EXPECT_TRUE(it->first.get()  == expIt->first);
		EXPECT_TRUE(it->second.get() == expIt->second.get());
	}
}

GTEST_TEST(TestStaticDict, At)
{
	TestStaticDict2 dict1;
	dict1.get_Key2_1() = String("val2_1");
	dict1.get_Key2_2() = Int64(12345);
	dict1.get_Key2_3().get_Key1_1() = Int64(54321);

	EXPECT_TRUE(dict1[String("Key2_1")] == String("val2_1"));
	EXPECT_TRUE(dict1[String("Key2_2")] == Int64(12345));
	EXPECT_TRUE(dict1[String("Key2_3")] == dict1.get_Key2_3());
	EXPECT_THROW(dict1[String("KeyX")], KeyError);

	EXPECT_TRUE(dict1[0] == String("val2_1"));
	EXPECT_TRUE(dict1[1] == Int64(12345));
	EXPECT_TRUE(dict1[2] == dict1.get_Key2_3());
	EXPECT_THROW(dict1[100], IndexError);

	const TestStaticDict2& kdict1 = dict1;

	EXPECT_TRUE(kdict1[String("Key2_1")] == String("val2_1"));
	EXPECT_TRUE(kdict1[String("Key2_2")] == Int64(12345));
	EXPECT_TRUE(kdict1[String("Key2_3")] == kdict1.get_Key2_3());
	EXPECT_THROW(kdict1[String("KeyX")], KeyError);

	EXPECT_TRUE(kdict1[0] == String("val2_1"));
	EXPECT_TRUE(kdict1[1] == Int64(12345));
	EXPECT_TRUE(kdict1[2] == kdict1.get_Key2_3());
	EXPECT_THROW(kdict1[100], IndexError);
}

GTEST_TEST(TestStaticDict, FindKey)
{
	TestStaticDict2 dict1;

	EXPECT_TRUE(dict1.HasKey(String("Key2_1")));
	EXPECT_TRUE(dict1.HasKey(String("Key2_2")));
	EXPECT_TRUE(dict1.HasKey(String("Key2_3")));
	EXPECT_FALSE(dict1.HasKey(String("KeyX")));
}

GTEST_TEST(TestStaticDict, Miscs)
{
	TestStaticDict2 dict1;
	dict1.get_Key2_1() = String("val2_1");
	dict1.get_Key2_2() = Int64(12345);
	dict1.get_Key2_3().get_Key1_1() = Int64(54321);

	// Is null
	EXPECT_FALSE(dict1.IsNull());

	// Cast
	EXPECT_NO_THROW(dict1.AsStaticDict());
	EXPECT_THROW(dict1.AsDict(),    TypeError);
	EXPECT_THROW(dict1.AsNull(),    TypeError);
	EXPECT_THROW(dict1.AsRealNum(), TypeError);
	EXPECT_THROW(dict1.AsString(),  TypeError);
	EXPECT_THROW(dict1.AsList(),    TypeError);
	EXPECT_THROW(dict1.AsBytes(),   TypeError);

	const auto& kDict1 = dict1;
	EXPECT_NO_THROW(kDict1.AsStaticDict());
	EXPECT_THROW(kDict1.AsDict(),    TypeError);
	EXPECT_THROW(kDict1.AsNull(),    TypeError);
	EXPECT_THROW(kDict1.AsRealNum(), TypeError);
	EXPECT_THROW(kDict1.AsString(),  TypeError);
	EXPECT_THROW(kDict1.AsList(),    TypeError);
	EXPECT_THROW(kDict1.AsBytes(),   TypeError);

	// Copy
	static_assert(std::is_same<
		decltype(*dict1.Copy(StaticDictBaseObj::sk_null)),
		StaticDictBaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(
		*dict1.Copy(StaticDictBaseObj::sk_null),
		dict1);

	static_assert(std::is_same<
		decltype(*dict1.Copy(BaseObj::sk_null)),
		BaseObj&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(
		*dict1.Copy(BaseObj::sk_null),
		dict1);

	// Move
	TestStaticDict2 mDict = dict1;

	static_assert(std::is_same<
		decltype(*TestStaticDict2().Move(StaticDictBaseObj::sk_null)),
		StaticDictBaseObj&>::value, "Failed to test Move virtual func");
	mDict = dict1;
	EXPECT_TRUE(mDict.get_Key2_1() == String("val2_1"));
	EXPECT_EQ(
		*mDict.Move(StaticDictBaseObj::sk_null),
		dict1);
	EXPECT_TRUE(mDict.get_Key2_1() == String());

	static_assert(std::is_same<
		decltype(*TestStaticDict2().Move(BaseObj::sk_null)),
		BaseObj&>::value, "Failed to test Move virtual func");
	mDict = dict1;
	EXPECT_TRUE(mDict.get_Key2_1() == String("val2_1"));
	EXPECT_EQ(
		*mDict.Move(BaseObj::sk_null),
		dict1);
	EXPECT_TRUE(mDict.get_Key2_1() == String());
}

GTEST_TEST(TestStaticDict, ToString)
{
	TestStaticDict2 dict1;
	dict1.get_Key2_1() = String("val2_1");
	dict1.get_Key2_2() = Int64(12345);
	dict1.get_Key2_3().get_Key1_1() = Int64(54321);

	std::string expRes1 = "{ \"Key2_1\" : \"val2_1\", \"Key2_2\" : 12345, \"Key2_3\" : { \"Key1_1\" : 54321 } }";
	std::string expSRes1 = "{\"Key2_1\":\"val2_1\",\"Key2_2\":12345,\"Key2_3\":{\"Key1_1\":54321}}";

	// DebugString
	{
		EXPECT_TRUE(dict1.DebugString() == expRes1);
		EXPECT_TRUE(dict1.ShortDebugString() == expSRes1);
	}

	// ToString
	{
		EXPECT_TRUE(dict1.ToString() == expRes1);
	}

	// DumpString
	{
		std::string res;
		EXPECT_NO_THROW(
			dict1.DumpString(ToOutIt<char>(std::back_inserter(res))));
		EXPECT_TRUE(res == expRes1);
	}
}
