#pragma once

#include "BaseObject.hpp"

#include <memory>

#include "Null.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

class Object : public BaseObject
{
public: // Static members

	using Base = BaseObject;

	using Ptr = std::unique_ptr<BaseObject>;

public:
	Object() :
		Object(None())
	{}

	Object(const Object& other) :
		Object(*other.m_ptr)
	{}

	Object(Object&& other) :
		m_ptr(std::forward<Ptr>(other.m_ptr))
	{}

	Object(const Base& other) :
		m_ptr(other.Copy(Base::sk_null))
	{}

	Object(Base&& other) :
		m_ptr(other.Move(Base::sk_null))
	{}

	virtual ~Object() = default;

	Object& operator=(const Object& rhs)
	{
		*this = *rhs.m_ptr;
		return *this;
	}

	Object& operator=(Object&& rhs)
	{
		m_ptr = std::forward<Ptr>(rhs.m_ptr);
		return *this;
	}

	Object& operator=(const Base& rhs)
	{
		m_ptr = rhs.Copy(Base::sk_null);
		return *this;
	}

	Object& operator=(Base&& rhs)
	{
		m_ptr = rhs.Move(Base::sk_null);
		return *this;
	}

	// BaseObject virtual functions

	virtual ObjCategory GetCategory() const override
	{
		return m_ptr->GetCategory();
	}

	virtual const char* GetCategoryName() const override
	{
		return m_ptr->GetCategoryName();
	}

	virtual bool IsNull() const override
	{
		return m_ptr->IsNull();
	}

	virtual NullBase& AsNull() override
	{
		return m_ptr->AsNull();
	}

	virtual const NullBase& AsNull() const override
	{
		return m_ptr->AsNull();
	}

	virtual NumericBase& AsNumeric() override
	{
		return m_ptr->AsNumeric();
	}

	virtual const NumericBase& AsNumeric() const override
	{
		return m_ptr->AsNumeric();
	}

	virtual StringBase& AsString() override
	{
		return m_ptr->AsString();
	}

	virtual const StringBase& AsString() const override
	{
		return m_ptr->AsString();
	}

	virtual ListBase& AsList() override
	{
		return m_ptr->AsList();
	}

	virtual const ListBase& AsList() const override
	{
		return m_ptr->AsList();
	}

	virtual DictBase& AsDict() override
	{
		return m_ptr->AsDict();
	}

	virtual const DictBase& AsDict() const override
	{
		return m_ptr->AsDict();
	}

	virtual std::unique_ptr<Base> Copy(const Base* unused) const override
	{
		return m_ptr->Copy(unused);
	}

	virtual std::unique_ptr<Base> Move(const Base* unused) override
	{
		return m_ptr->Move(unused);
	}

private:

	Ptr m_ptr;

}; // class Object

} //namespace SimpleObjects
