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

GTEST_TEST(TestNull, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

GTEST_TEST(TestNull, Construction)
{
	Null val1;
	Null val2 = Null();
	EXPECT_NO_THROW({
		std::unique_ptr<BaseObject> base;
		base.reset(new Null());
		base.reset();
	});
}

GTEST_TEST(TestNull, Category)
{
	static_assert(Null::sk_cat() == ObjCategory::Null, "Category failed.");
	EXPECT_EQ(Null::sk_cat(), ObjCategory::Null);

	Null val;
	EXPECT_EQ(val.GetCategory(), ObjCategory::Null);
}


GTEST_TEST(TestNull, CategoryName)
{
	EXPECT_EQ(Null().GetCategoryName(), std::string("Null"));
}

GTEST_TEST(TestNull, Hash)
{
	EXPECT_EQ(Null().Hash(), 0);
}

GTEST_TEST(TestNull, Miscs)
{
	// Is Null
	EXPECT_TRUE(Null().IsNull());

	// Cast
	const auto kNull = Null();
	EXPECT_NO_THROW(kNull.AsNull());
	EXPECT_THROW(kNull.AsNumeric(), TypeError);
	EXPECT_THROW(kNull.AsString(), TypeError);

	EXPECT_NO_THROW(Null().AsNull());
	EXPECT_THROW(Null().AsNumeric(), TypeError);
	EXPECT_THROW(Null().AsString(), TypeError);

	// Copy
	static_assert(std::is_same<
		decltype(*Null().Copy(Null::Base::sk_null)),
		HashableBaseObject&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Null().Copy(Null::Base::sk_null), Null());

	static_assert(std::is_same<
		decltype(*Null().Copy(Null::Base::Base::sk_null)),
		BaseObject&>::value, "Failed to test Copy virtual func");
	EXPECT_EQ(*Null().Copy(Null::Base::Base::sk_null), Null());

	// Move
	static_assert(std::is_same<
		decltype(*Null().Move(Null::Base::sk_null)),
		HashableBaseObject&>::value, "Failed to test Move virtual func");
	EXPECT_EQ(*Null().Move(Null::Base::sk_null), Null());

	static_assert(std::is_same<
		decltype(*Null().Move(Null::Base::Base::sk_null)),
		BaseObject&>::value, "Failed to test Move virtual func");
	EXPECT_EQ(*Null().Move(Null::Base::Base::sk_null), Null());
}

GTEST_TEST(TestNull, BaseCompare)
{
	using ObjPtr = std::unique_ptr<BaseObject>;

	EXPECT_EQ(*ObjPtr(new Null()) != *ObjPtr(new Null()), nullptr != nullptr);

	EXPECT_THROW(*ObjPtr(new Null()) >= *ObjPtr(new Null()), UnsupportedOperation);
	EXPECT_THROW(*ObjPtr(new Null()) <= *ObjPtr(new Null()), UnsupportedOperation);
}
