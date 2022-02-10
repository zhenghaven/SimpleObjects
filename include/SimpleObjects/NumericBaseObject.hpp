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
class NumericBaseObject : public HashableBaseObject
{
public: // Static Member

	using Base = HashableBaseObject;

	static constexpr NumericBaseObject* sk_null = nullptr;

public:
	NumericBaseObject() = default;

	virtual ~NumericBaseObject() = default;

	virtual NumericType GetNumType() const = 0;

	virtual const char* GetNumTypeName() const = 0;

	virtual NumericBaseObject& AsNumeric() override
	{
		return *this;
	}

	virtual const NumericBaseObject& AsNumeric() const override
	{
		return *this;
	}

	virtual bool operator==(const NumericBaseObject& rhs) const = 0;

	virtual bool operator!=(const NumericBaseObject& rhs) const
	{
		return !(*this == rhs);
	}

	virtual bool operator<(const NumericBaseObject& rhs) const = 0;

	virtual bool operator>=(const NumericBaseObject& rhs) const
	{
		return !(*this < rhs);
	}

	virtual bool operator>(const NumericBaseObject& rhs) const = 0;

	virtual bool operator<=(const NumericBaseObject& rhs) const
	{
		return !(*this > rhs);
	}

	virtual std::unique_ptr<NumericBaseObject> Copy(const NumericBaseObject* /*unused*/) const = 0;

	virtual std::unique_ptr<NumericBaseObject> Move(const NumericBaseObject* /*unused*/) = 0;

	using Base::Copy;
	virtual std::unique_ptr<HashableBaseObject> Copy(const HashableBaseObject* /*unused*/) const override
	{
		return Copy(sk_null);
	}

	using Base::Move;
	virtual std::unique_ptr<HashableBaseObject> Move(const HashableBaseObject* /*unused*/) override
	{
		return Move(sk_null);
	}

}; // class NumericBaseObject

}//namespace SimpleObjects
