#include <gtest/gtest.h>

#include <string>

#include <SimpleObjects/String.hpp>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
} // namespace SimpleObjects_Test

GTEST_TEST(TestIterator, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

GTEST_TEST(TestIterator, ItTraits)
{
	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, false>::difference_type,
		std::ptrdiff_t>::value, "ItTraits test failed.");
	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, false>::value_type,
		char>::value, "ItTraits test failed.");
	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, false>::pointer,
		char*>::value, "ItTraits test failed.");
	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, false>::reference,
		char&>::value, "ItTraits test failed.");
	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, false>::iterator_category,
		std::random_access_iterator_tag>::value, "ItTraits test failed.");

	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, true>::difference_type,
		std::ptrdiff_t>::value, "ItTraits test failed.");
	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, true>::value_type,
		char>::value, "ItTraits test failed.");
	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, true>::pointer,
		const char*>::value, "ItTraits test failed.");
	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, true>::reference,
		const char&>::value, "ItTraits test failed.");
	static_assert(std::is_same<
		typename CppStdRdIteratorWrap<std::string::iterator, char, true>::iterator_category,
		std::random_access_iterator_tag>::value, "ItTraits test failed.");
}

GTEST_TEST(TestIterator, RdIterator)
{
	using _String = StringCat<std::string, std::string>;

	std::string testCtn = "abcdef";
	_String testStr = "abcdef";

	// Copy/Move constructor
	{
		auto its1 = testStr.begin() + 2;
		auto its2 = decltype(its1)(its1);
		EXPECT_EQ(its1.operator->(), its2.operator->());
		auto its3 = decltype(its1)(std::move(its2));
		EXPECT_EQ(its1.operator->(), its3.operator->());
	}
	{
		auto its1 = testStr.cbegin() + 2;
		auto its2 = decltype(its1)(its1);
		EXPECT_EQ(its1.operator->(), its2.operator->());
		auto its3 = decltype(its1)(std::move(its2));
		EXPECT_EQ(its1.operator->(), its3.operator->());
	}

	// Copy/Move Assignment
	{
		auto its1 = testStr.begin() + 2;
		auto its2 = testStr.begin();
		auto its3 = testStr.begin();

		its2 = its1;
		EXPECT_EQ(its1.operator->(), its2.operator->());
		its3 = std::move(its2);
		EXPECT_EQ(its1.operator->(), its3.operator->());
	}
	{
		auto its1 = testStr.cbegin() + 2;
		auto its2 = testStr.cbegin();
		auto its3 = testStr.cbegin();

		its2 = its1;
		EXPECT_EQ(its1.operator->(), its2.operator->());
		its3 = std::move(its2);
		EXPECT_EQ(its1.operator->(), its3.operator->());
	}

	// for loop
	{
		auto itc = testCtn.begin();
		for(const auto& ch : testStr)
		{
			EXPECT_EQ(ch, *itc++);
		}

		auto its = testStr.begin();
		for(const auto& ch : testCtn)
		{
			EXPECT_EQ(ch, *its++);
		}

		itc = testCtn.begin();
		for(auto it = static_cast<const _String&>(testStr).begin();
			it != static_cast<const _String&>(testStr).end();
			++it, ++itc)
		{
			EXPECT_EQ(*itc, *it);
		}
	}

	// for loop reverse
	{
		auto itc = testCtn.rbegin();
		for(auto it = testStr.rbegin(); it != testStr.rend(); ++it, ++itc)
		{
			EXPECT_EQ(*itc, *it);
		}

		itc = testCtn.rbegin();
		for(auto it = testStr.crbegin(); it != testStr.crend(); ++it, ++itc)
		{
			EXPECT_EQ(*itc, *it);
		}
	}

	// various incrementor (non-const)
	{
		auto itc = testCtn.begin();
		auto its = testStr.begin();

		EXPECT_EQ(*itc++, *its++);
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*itc--, *its--);
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*++itc, *++its);
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*--itc, *--its);
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*(itc += 2), *(its += 2));
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*(itc -= 2), *(its -= 2));
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		(itc += 3);
		(its += 3);

		EXPECT_EQ(*(itc + 2), *(its + 2));
		EXPECT_EQ(*(itc + 2).operator->(), *(its + 2).operator->());

		EXPECT_EQ(*(itc - 2), *(its - 2));
		EXPECT_EQ(*(itc - 2).operator->(), *(its - 2).operator->());
	}
	// various incrementor (const)
	{
		auto itc = testCtn.cbegin();
		auto its = testStr.cbegin();

		EXPECT_EQ(*itc++, *its++);
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*itc--, *its--);
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*++itc, *++its);
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*--itc, *--its);
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*(itc += 2), *(its += 2));
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		EXPECT_EQ(*(itc -= 2), *(its -= 2));
		EXPECT_EQ(*itc.operator->(), *its.operator->());

		(itc += 3);
		(its += 3);

		EXPECT_EQ(*(itc + 2), *(its + 2));
		EXPECT_EQ(*(itc + 2).operator->(), *(its + 2).operator->());

		EXPECT_EQ(*(itc - 2), *(its - 2));
		EXPECT_EQ(*(itc - 2).operator->(), *(its - 2).operator->());
	}

	// index
	{
		EXPECT_EQ(testCtn.begin()[0], testStr.begin()[0]);
		EXPECT_EQ(testCtn.begin()[1], testStr.begin()[1]);
		EXPECT_EQ(testCtn.begin()[2], testStr.begin()[2]);
		EXPECT_EQ(testCtn.cbegin()[0], testStr.cbegin()[0]);
		EXPECT_EQ(testCtn.cbegin()[1], testStr.cbegin()[1]);
		EXPECT_EQ(testCtn.cbegin()[2], testStr.cbegin()[2]);
	}

	// compare
	{
		EXPECT_TRUE(testStr.begin() + 3 != testStr.begin() + 2);
		EXPECT_TRUE(testStr.begin() + 3 >= testStr.begin() + 2);
		EXPECT_TRUE(testStr.begin() + 1 <= testStr.begin() + 2);

		//EXPECT_TRUE(testStr.begin() + 3 != testStr.cbegin() + 2);
		//EXPECT_TRUE(testStr.cbegin() + 3 != testStr.begin() + 2);
	}
}

GTEST_TEST(TestIterator, OutIterator)
{
	// Assignment
	{
		std::string testStr;
		auto it = ToOutIt<char>(std::back_inserter(testStr));
		*it++ = 't';
		*it++ = 'e';
		*it++ = 's';
		*it++ = 't';
		*it++ = '1';
		*it++ = '2';
		*it++ = '3';
		EXPECT_EQ(testStr, "test123");
	}

	// Copy
	{
		std::string testStr;
		char srcStr[] = "test456";
		auto it = ToOutIt<char>(std::back_inserter(testStr));
		std::copy(std::begin(srcStr), std::end(srcStr) - 1, it);
		EXPECT_EQ(testStr, "test456");
	}

	// Insert
	{
		std::string testStr = "t9";
		char srcStr[] = "est78";
		auto it = ToOutIt<char>(std::insert_iterator<std::string>(
			testStr, testStr.begin() + 1));
		std::copy(std::begin(srcStr), std::end(srcStr) - 1, it);
		EXPECT_EQ(testStr, "test789");
	}
}
