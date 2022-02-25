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

	static constexpr Self* sk_null = nullptr;

public:
	NumericBaseObject() = default;

	virtual ~NumericBaseObject() = default;

	virtual NumericType GetNumType() const = 0;

	virtual const char* GetNumTypeName() const = 0;

	virtual Self& AsNumeric() override
	{
		return *this;
	}

	virtual const Self& AsNumeric() const override
	{
		return *this;
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
