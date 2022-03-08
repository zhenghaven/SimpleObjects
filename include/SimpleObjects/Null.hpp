// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "HashableBaseObject.hpp"
#include "ToString.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _ToStringType>
class NullImpl : public HashableBaseObject<_ToStringType>
{
public: // Static member:

	using ToStringType = _ToStringType;
	using Self = NullImpl<_ToStringType>;
	using Base = HashableBaseObject<_ToStringType>;
	using BaseBase = typename Base::Base;

	static_assert(std::is_same<BaseBase, BaseObject<_ToStringType> >::value,
		"Expecting Base::Base to be BaseObject class");

	using NullBase = typename BaseBase::NullBase;

	static constexpr ObjCategory sk_cat()
	{
		return ObjCategory::Null;
	}

	static constexpr Self* sk_null = nullptr;

public:

	NullImpl() = default;

	virtual ~NullImpl() = default;

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	virtual const char* GetCategoryName() const override
	{
		return "Null";
	}

	virtual std::size_t Hash() const override
	{
		// In a fix of GCC that adds support for std::hash<nullptr_t>, it will
		// always return zero for hash(nullptr)
		// see: https://gcc.gnu.org/git/?p=gcc.git&a=commit;h=17a73b3c47f58155350af2e1ca359e915ffedcae
		return 0;
	}

	using BaseBase::Set;

	virtual void Set(const BaseBase& other) override
	{
		try
		{
			const Self& casted = dynamic_cast<const Self&>(other);
			*this = casted;
		}
		catch(const std::bad_cast&)
		{
			throw TypeError("Null", this->GetCategoryName());
		}
	}

	virtual void Set(BaseBase&& other) override
	{
		try
		{
			Self&& casted = dynamic_cast<Self&&>(other);
			*this = std::forward<Self>(casted);
		}
		catch(const std::bad_cast&)
		{
			throw TypeError("Null", this->GetCategoryName());
		}
	}

	virtual bool IsNull() const override
	{
		return true;
	}

	virtual bool IsTrue() const override
	{
		return false;
	}

	virtual NullBase& AsNull() override
	{
		return Internal::AsChildType<
				std::is_same<Self, NullBase>::value, Self, NullBase
			>::AsChild(*this, "Null", this->GetCategoryName());
	}

	virtual const NullBase& AsNull() const override
	{
		return Internal::AsChildType<
				std::is_same<Self, NullBase>::value, Self, NullBase
			>::AsChild(*this, "Null", this->GetCategoryName());
	}

	virtual bool operator==(const Self& rhs) const
	{
		return true;
	}

	virtual bool operator!=(const Self& rhs) const
	{
		return false;
	}

	bool operator<(const Self& rhs) const = delete;
	bool operator>(const Self& rhs) const = delete;
	bool operator<=(const Self& rhs) const = delete;
	bool operator>=(const Self& rhs) const = delete;

	virtual bool operator==(const BaseBase& rhs) const override
	{
		return rhs.IsNull();
	}

	using BaseBase::operator!=;

	virtual bool operator<(const BaseBase& rhs) const override
	{
		throw UnsupportedOperation("<",
			this->GetCategoryName(), rhs.GetCategoryName());
	}

	virtual bool operator>(const BaseBase& rhs) const override
	{
		throw UnsupportedOperation(">",
			this->GetCategoryName(), rhs.GetCategoryName());
	}

	using BaseBase::operator<=;
	using BaseBase::operator>=;

	using Base::Copy;
	virtual std::unique_ptr<Base> Copy(const Base* /*unused*/) const override
	{
		return CopyImpl();
	}

	using Base::Move;
	virtual std::unique_ptr<Base> Move(const Base* /*unused*/) override
	{
		return CopyImpl();
	}

	virtual std::string DebugString() const override
	{
		return "null";
	}

	virtual std::string ShortDebugString() const override
	{
		return DebugString();
	}

	virtual ToStringType ToString() const override
	{
		return Internal::ToString<ToStringType>("null");
	}

	virtual void DumpString(OutIterator<typename ToStringType::value_type> outIt) const override
	{
		using StrValType = typename ToStringType::value_type;
		static constexpr StrValType str[] = "null";
		std::copy(std::begin(str), std::end(str) - 1, outIt);
	}

private:

	std::unique_ptr<Self> CopyImpl() const
	{
		// TODO: make_unique
		return std::unique_ptr<Self>(new Self());
	}

}; //class NullImpl

}//namespace SimpleObjects
