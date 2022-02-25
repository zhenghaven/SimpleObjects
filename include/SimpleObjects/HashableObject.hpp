#pragma once

#include "HashableBaseObject.hpp"

#include <memory>

#include "Null.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

class HashableObject : public HashableBaseObject
{
public: // Static members

	using Base = HashableBaseObject;

	using Ptr = std::unique_ptr<HashableBaseObject>;

public:
	HashableObject() :
		HashableObject(Null())
	{}

	HashableObject(const HashableObject& other) :
		HashableObject(*other.m_ptr)
	{}

	HashableObject(HashableObject&& other) :
		m_ptr(std::forward<Ptr>(other.m_ptr))
	{}

	HashableObject(const Base& other) :
		m_ptr(other.Copy(Base::sk_null))
	{}

	HashableObject(Base&& other) :
		m_ptr(other.Move(Base::sk_null))
	{}

	virtual ~HashableObject() = default;

	HashableObject& operator=(const HashableObject& rhs)
	{
		*this = *rhs.m_ptr;
		return *this;
	}

	HashableObject& operator=(HashableObject&& rhs)
	{
		m_ptr = std::forward<Ptr>(rhs.m_ptr);
		return *this;
	}

	HashableObject& operator=(const Base& rhs)
	{
		m_ptr = rhs.Copy(Base::sk_null);
		return *this;
	}

	HashableObject& operator=(Base&& rhs)
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

	// HashableBaseObject virtual functions

	virtual std::size_t Hash() const override
	{
		return m_ptr->Hash();
	}

	using Base::Copy;
	virtual std::unique_ptr<Base> Copy(const Base* unused) const override
	{
		return m_ptr->Copy(unused);
	}

	using Base::Move;
	virtual std::unique_ptr<Base> Move(const Base* unused) override
	{
		return m_ptr->Move(unused);
	}

private:

	Ptr m_ptr;

}; // class HashableObject

}//namespace SimpleObjects

// ========== Hash ==========
namespace std
{
	template<>
#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
	struct hash<SimpleObjects::HashableObject> :
		public hash<SimpleObjects::HashableBaseObject>
	{
		using _ObjType = SimpleObjects::HashableObject;
#else
	struct hash<SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::HashableObject> :
		public hash<SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::HashableBaseObject>
	{
		using _ObjType = SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::HashableObject;
#endif
	}; // struct hash
}
