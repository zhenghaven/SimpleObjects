// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

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

GTEST_TEST(TestBaseObjects, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
}

namespace
{

class UnkownType : public BaseObject<std::string>
{
public:
	using Base = BaseObject<std::string>;
	using Self = UnkownType;

	UnkownType() = default;

	virtual ~UnkownType() = default;

	virtual ObjCategory GetCategory() const override
	{
		return static_cast<ObjCategory>(100);
	}

	virtual const char* GetCategoryName() const override
	{
		return "Unknown";
	}

	virtual std::unique_ptr<Base> Copy(const Base* /*unused*/) const override
	{
		// TODO: make_unique
		return std::unique_ptr<Self>(new Self(*this));
	}

	virtual std::unique_ptr<Base> Move(const Base* /*unused*/) override
	{
		// TODO: make_unique
		return std::unique_ptr<Self>(new Self(std::move(*this)));
	}

	virtual std::string DebugString() const override
	{
		return "UnkownType";
	}

	virtual std::string ShortDebugString() const override
	{
		return DebugString();
	}

	virtual ToStringType ToString() const override
	{
		return Internal::ToString<ToStringType>("UnkownType");
	}

	virtual void DumpString(OutIterator<typename ToStringType::value_type> outIt) const override
	{
		using StrValType = typename ToStringType::value_type;
		static constexpr StrValType str[] = "UnkownType";
		std::copy(std::begin(str), std::end(str) - 1, outIt);
	}

}; // class UnkownType

} // namespace

GTEST_TEST(TestBaseObjects, CompareOnUnkownCat)
{
	EXPECT_THROW((void)(UnkownType() != UnkownType()), UnsupportedOperation);
	EXPECT_THROW((void)(UnkownType() >= UnkownType()), UnsupportedOperation);
	EXPECT_THROW((void)(UnkownType() <= UnkownType()), UnsupportedOperation);
}
