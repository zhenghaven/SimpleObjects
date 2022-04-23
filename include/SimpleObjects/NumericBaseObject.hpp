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

	// ========== Comparisons ==========

	// ===== This class

	virtual bool RealNumBaseEqual(const Self& rhs) const = 0;

	virtual int RealNumBaseCmp(const Self& rhs) const = 0;

	bool operator==(const Self& rhs) const
	{
		return RealNumBaseEqual(rhs);
	}

#ifdef __cpp_lib_three_way_comparison
	std::strong_ordering operator<=>(const Self& rhs) const
	{
		auto cmpRes = RealNumBaseCmp(rhs);
		return cmpRes == 0 ? std::strong_ordering::equal :
				(cmpRes < 0 ? std::strong_ordering::less :
				(std::strong_ordering::greater));
	}
#else
	bool operator!=(const Self& rhs) const
	{
		return !(*this == rhs);
	}

	bool operator<(const Self& rhs) const
	{
		return RealNumBaseCmp(rhs) < 0;
	}

	bool operator>(const Self& rhs) const
	{
		return RealNumBaseCmp(rhs) > 0;
	}

	bool operator<=(const Self& rhs) const
	{
		return !(*this > rhs);
	}

	bool operator>=(const Self& rhs) const
	{
		return !(*this < rhs);
	}
#endif

	// ===== BaseObject class

	virtual bool BaseObjectIsEqual(const BaseBase& rhs) const override
	{
		switch (rhs.GetCategory())
		{
		case ObjCategory::Bool:
		case ObjCategory::Integer:
		case ObjCategory::Real:
			return RealNumBaseEqual(rhs.AsNumeric());
		default:
			return false;
		}
	}

	virtual ObjectOrder BaseObjectCompare(const BaseBase& rhs) const override
	{
		switch (rhs.GetCategory())
		{
		case ObjCategory::Bool:
		case ObjCategory::Integer:
		case ObjCategory::Real:
		{
			auto cmpRes = RealNumBaseCmp(rhs.AsNumeric());
			return cmpRes == 0 ? ObjectOrder::Equal :
					(cmpRes < 0 ? ObjectOrder::Less :
					(ObjectOrder::Greater));
		}
		default:
			return ObjectOrder::NotEqualUnordered;
		}
	}

	using Base::operator==;
	using Base::operator!=;
	using Base::operator<;
	using Base::operator>;
	using Base::operator<=;
	using Base::operator>=;

	// ========== Interface copy/Move ==========

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
