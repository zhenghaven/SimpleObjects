#pragma once

#include "BaseObject.hpp"

#include "NumericBaseObject.hpp"
#include "StringBaseObject.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

inline bool BaseObject::operator==(const BaseObject& rhs) const
{
	auto lhsCat = GetCategory();
	auto rhsCat = rhs.GetCategory();

	if ((lhsCat == rhsCat) ||
		(IsNumericCat(lhsCat) && IsNumericCat(rhsCat)))
	{
		// lhsCat == rhsCat -> Same Cat
		// IsNumericCat(lhsCat) && IsNumericCat(rhsCat) -> Same Cat
		switch (lhsCat)
		{
		case ObjCategory::Null:
			return true; // both sides are null
		case ObjCategory::Bool:
		case ObjCategory::Integer:
		case ObjCategory::Real:
			return this->AsNumeric() == rhs.AsNumeric(); // both sides are numeric
		case ObjCategory::String:
			return this->AsString() == rhs.AsString();
		case ObjCategory::List:
			return this->AsList() == rhs.AsList();
		case ObjCategory::Dict:
			return this->AsDict() == rhs.AsDict();
		default:
			throw UnsupportedOperation("==",
				this->GetCategoryName(),
				rhs.GetCategoryName());
		}
	}
	else
	{
		return false;
	}
}

inline bool BaseObject::operator<(const BaseObject& rhs) const
{
	auto lhsCat = GetCategory();
	auto rhsCat = rhs.GetCategory();

	if ((lhsCat == rhsCat) ||
		(IsNumericCat(lhsCat) && IsNumericCat(rhsCat)))
	{
		// lhsCat == rhsCat -> Same Cat
		// IsNumericCat(lhsCat) && IsNumericCat(rhsCat) -> Same Cat
		switch (lhsCat)
		{
		// Numeric is comparable
		case ObjCategory::Bool:
		case ObjCategory::Integer:
		case ObjCategory::Real:
			return this->AsNumeric() < rhs.AsNumeric(); // both sides are numeric
		// String is comparable
		case ObjCategory::String:
			return this->AsString() < rhs.AsString();
		// Others are not comparable
		case ObjCategory::Null:
		case ObjCategory::List:
		case ObjCategory::Dict:
		default:
			break;
		}
	}
	throw UnsupportedOperation("<",
		this->GetCategoryName(),
		rhs.GetCategoryName());
}

inline bool BaseObject::operator>(const BaseObject& rhs) const
{
	auto lhsCat = GetCategory();
	auto rhsCat = rhs.GetCategory();

	if ((lhsCat == rhsCat) ||
		(IsNumericCat(lhsCat) && IsNumericCat(rhsCat)))
	{
		// lhsCat == rhsCat -> Same Cat
		// IsNumericCat(lhsCat) && IsNumericCat(rhsCat) -> Same Cat
		switch (lhsCat)
		{
		// Numeric is comparable
		case ObjCategory::Bool:
		case ObjCategory::Integer:
		case ObjCategory::Real:
			return this->AsNumeric() > rhs.AsNumeric(); // both sides are numeric
		// String is comparable
		case ObjCategory::String:
			return this->AsString() > rhs.AsString();
		// Others are not comparable
		case ObjCategory::Null:
		case ObjCategory::List:
		case ObjCategory::Dict:
		default:
			break;
		}
	}
	throw UnsupportedOperation(">",
		this->GetCategoryName(),
		rhs.GetCategoryName());
}

}//namespace SimpleObjects
