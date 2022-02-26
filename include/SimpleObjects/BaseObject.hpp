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
template<typename _ToStringType>
class NullImpl;
template<typename _ToStringType>
class NumericBaseObject;
template<typename _CharType, typename _ToStringType>
class StringBaseObject;
template<typename _ValType,  typename _ToStringType>
class ListBaseObject;
template<typename _KeyType,  typename _ValType,     typename _ToStringType>
class DictBaseObject;

template<typename _ToStringType>
class HashableObjectImpl;
template<typename _ToStringType>
class ObjectImpl;

template<typename _ToStringType>
class BaseObject
{
public: // Static members:

	using Self = BaseObject<_ToStringType>;
	using ToStringType = _ToStringType;


	using NullBase    = NullImpl<ToStringType>;

	using NumericBase = NumericBaseObject<ToStringType>;

	using StringBase  = StringBaseObject<char, ToStringType>;

	using ListBase    = ListBaseObject<ObjectImpl<ToStringType>, ToStringType>;

	using DictBase    = DictBaseObject<HashableObjectImpl<ToStringType>,
		                               ObjectImpl<ToStringType>,
		                               ToStringType>;

	static constexpr Self* sk_null = nullptr;

public:

	BaseObject() = default;

	// LCOV_EXCL_START
	/**
	 * @brief Destroy the Base Object
	 *
	 */
	virtual ~BaseObject() = default;
	// LCOV_EXCL_STOP

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
	virtual bool operator==(const Self& rhs) const;

	virtual bool operator!=(const Self& rhs) const
	{
		return !((*this) == rhs);
	}

	virtual bool operator<(const Self& rhs) const;

	virtual bool operator>=(const Self& rhs) const
	{
		return !((*this) < rhs);
	}

	virtual bool operator>(const Self& rhs) const;

	virtual bool operator<=(const Self& rhs) const
	{
		return !((*this) > rhs);
	}

	// TODO:
	// +=
	// +
	// slice
	// CppStr

	// String(objs)
	// String::CppStr

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

	virtual ListBase& AsList()
	{
		throw TypeError("List", this->GetCategoryName());
	}

	virtual const ListBase& AsList() const
	{
		throw TypeError("List", this->GetCategoryName());
	}

	virtual DictBase& AsDict()
	{
		throw TypeError("Dict", this->GetCategoryName());
	}

	virtual const DictBase& AsDict() const
	{
		throw TypeError("Dict", this->GetCategoryName());
	}

	virtual std::unique_ptr<Self> Copy(const Self* /*unused*/) const = 0;

	virtual std::unique_ptr<Self> Move(const Self* /*unused*/) = 0;

}; // class BaseObject

}//namespace SimpleObjects
