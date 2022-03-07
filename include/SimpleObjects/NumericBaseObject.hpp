// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "HashableBaseObject.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

/**
 * @brief Defining a interface class for numeric objects
 *
 */
template<typename _ToStringType>
class NumericBaseObject : public HashableBaseObject<_ToStringType>
{
public: // Static Member

	using ToStringType = _ToStringType;
	using Self = NumericBaseObject<_ToStringType>;
	using Base = HashableBaseObject<_ToStringType>;
	using BaseBase = typename Base::Base;

	static_assert(std::is_same<BaseBase, BaseObject<_ToStringType> >::value,
		"Expecting Base::Base to be BaseObject class");

	using NumericBase = typename BaseBase::NumericBase;

	static constexpr Self* sk_null = nullptr;

public:
	NumericBaseObject() = default;

	// LCOV_EXCL_START
	/**
	 * @brief Destroy the Numeric Base Object
	 *
	 */
	virtual ~NumericBaseObject() = default;
	// LCOV_EXCL_STOP

	virtual NumericType GetNumType() const = 0;

	virtual const char* GetNumTypeName() const = 0;

	virtual NumericBase& AsNumeric() override
	{
		return Internal::AsChildType<
				std::is_same<Self, NumericBase>::value, Self, NumericBase
			>::AsChild(*this, "Numeric Category", this->GetCategoryName());
	}

	virtual const NumericBase& AsNumeric() const override
	{
		return Internal::AsChildType<
				std::is_same<Self, NumericBase>::value, Self, NumericBase
			>::AsChild(*this, "Numeric Category", this->GetCategoryName());
	}

	virtual bool operator==(const Self& rhs) const = 0;

	virtual bool operator!=(const Self& rhs) const
	{
		return !(*this == rhs);
	}

	virtual bool operator<(const Self& rhs) const = 0;

	virtual bool operator>=(const Self& rhs) const
	{
		return !(*this < rhs);
	}

	virtual bool operator>(const Self& rhs) const = 0;

	virtual bool operator<=(const Self& rhs) const
	{
		return !(*this > rhs);
	}

	virtual bool operator==(const BaseBase& rhs) const override
	{
		const auto rhsCat = rhs.GetCategory();
		if (rhsCat != ObjCategory::Bool &&
			rhsCat != ObjCategory::Integer &&
			rhsCat != ObjCategory::Real)
		{
			return false;
		}
		return *this == rhs.AsNumeric();
	}

	using BaseBase::operator!=;

	virtual bool operator<(const BaseBase& rhs) const override
	{
		const auto rhsCat = rhs.GetCategory();
		if (rhsCat != ObjCategory::Bool &&
			rhsCat != ObjCategory::Integer &&
			rhsCat != ObjCategory::Real)
		{
			throw UnsupportedOperation("<",
				this->GetCategoryName(), rhs.GetCategoryName());
		}
		return *this < rhs.AsNumeric();
	}

	virtual bool operator>(const BaseBase& rhs) const override
	{
		const auto rhsCat = rhs.GetCategory();
		if (rhsCat != ObjCategory::Bool &&
			rhsCat != ObjCategory::Integer &&
			rhsCat != ObjCategory::Real)
		{
			throw UnsupportedOperation(">",
				this->GetCategoryName(), rhs.GetCategoryName());
		}
		return *this > rhs.AsNumeric();
	}

	using BaseBase::operator<=;
	using BaseBase::operator>=;

	virtual std::unique_ptr<Self> Copy(const Self* /*unused*/) const = 0;

	virtual std::unique_ptr<Self> Move(const Self* /*unused*/) = 0;

	using Base::Copy;
	virtual std::unique_ptr<Base> Copy(const Base* /*unused*/) const override
	{
		return Copy(sk_null);
	}

	using Base::Move;
	virtual std::unique_ptr<Base> Move(const Base* /*unused*/) override
	{
		return Move(sk_null);
	}

}; // class NumericBaseObject

}//namespace SimpleObjects
