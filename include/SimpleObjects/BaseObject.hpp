#pragma once

#include <string>

#include "Exception.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

enum class ObjCategory
{
	Null,
	Bool,
	Integer,
	Real,
	String,
	List,
	Dict,
};

enum class NumericType
{
	Bool,
	Int8,
	Int16,
	Int32,
	Int64,
	UInt8,
	UInt16,
	UInt32,
	UInt64,
	Float,
	Double,
	// All enum type above are RESERVED for Numeric<> class ONLY

	Other,  // for future extensions, use this
};

inline constexpr bool IsNumericCat(ObjCategory cat)
{
	return cat == ObjCategory::Bool ||
		cat == ObjCategory::Integer ||
		cat == ObjCategory::Real;
}

// Forward declarations
class NumericBaseObject;
template<typename _CharType>
class StringBaseObject;
class Null;

class BaseObject
{
public: // Static members:

	using NullBase = Null;

	using NumericBase = NumericBaseObject;

	using StringBase = StringBaseObject<char>;

	static constexpr BaseObject* sk_null = nullptr;

public:

	BaseObject() = default;

	virtual ~BaseObject() = default;

	virtual ObjCategory GetCategory() const = 0;

	virtual const char* GetCategoryName() const = 0;

	/**
	 * @brief Compare if two objects are the same.
	 *        If two object are the same category, or they both are numeric types,
	 *        their equality will be checked by the child class, otherwise,
	 *        return false
	 *
	 * @param rhs The other object to test with
	 * @return whether two objects are equal
	 */
	virtual bool operator==(const BaseObject& rhs) const;

	virtual bool operator!=(const BaseObject& rhs) const
	{
		return !((*this) == rhs);
	}

	virtual bool operator<(const BaseObject& rhs) const;

	virtual bool operator>=(const BaseObject& rhs) const
	{
		return !((*this) < rhs);
	}

	virtual bool operator>(const BaseObject& rhs) const;

	virtual bool operator<=(const BaseObject& rhs) const
	{
		return !((*this) > rhs);
	}

	// TODO:
	// +=
	// +
	// slice

	virtual bool IsNull() const
	{
		return false;
	}

	virtual NullBase& AsNull()
	{
		throw TypeError("Null", this->GetCategoryName());
	}

	virtual const NullBase& AsNull() const
	{
		throw TypeError("Null", this->GetCategoryName());
	}

	virtual NumericBase& AsNumeric()
	{
		throw TypeError("Numeric Category", this->GetCategoryName());
	}

	virtual const NumericBase& AsNumeric() const
	{
		throw TypeError("Numeric Category", this->GetCategoryName());
	}

	virtual StringBase& AsString()
	{
		throw TypeError("String", this->GetCategoryName());
	}

	virtual const StringBase& AsString() const
	{
		throw TypeError("String", this->GetCategoryName());
	}

	virtual std::unique_ptr<BaseObject> Copy(const BaseObject* /*unused*/) const = 0;

	virtual std::unique_ptr<BaseObject> Move(const BaseObject* /*unused*/) = 0;

}; // class BaseObject

}//namespace SimpleObjects
