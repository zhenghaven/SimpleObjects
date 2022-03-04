// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

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

template<typename _ToStringType>
class ObjectImpl : public BaseObject<_ToStringType>
{
public: // Static members

	using ToStringType = _ToStringType;
	using Self = ObjectImpl<_ToStringType>;
	using Base = BaseObject<_ToStringType>;

	using NullBase     = typename Base::NullBase;
	using NumericBase  = typename Base::NumericBase;
	using StringBase   = typename Base::StringBase;
	using ListBase     = typename Base::ListBase;
	using DictBase     = typename Base::DictBase;
	using StatDictBase = typename Base::StatDictBase;

	using BasePtr = std::unique_ptr<Base>;

public:
	ObjectImpl() :
		ObjectImpl(NullImpl<ToStringType>())
	{}

	ObjectImpl(const Self& other) :
		ObjectImpl(*other.m_ptr)
	{}

	ObjectImpl(Self&& other) :
		m_ptr(std::forward<BasePtr>(other.m_ptr))
	{}

	ObjectImpl(const Base& other) :
		m_ptr(other.Copy(Base::sk_null))
	{}

	ObjectImpl(Base&& other) :
		m_ptr(other.Move(Base::sk_null))
	{}

	virtual ~ObjectImpl() = default;

	Self& operator=(const Self& rhs)
	{
		*this = *rhs.m_ptr;
		return *this;
	}

	Self& operator=(Self&& rhs)
	{
		m_ptr = std::forward<BasePtr>(rhs.m_ptr);
		return *this;
	}

	Self& operator=(const Base& rhs)
	{
		m_ptr = rhs.Copy(Base::sk_null);
		return *this;
	}

	Self& operator=(Base&& rhs)
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

	virtual StatDictBase& AsStaticDict() override
	{
		return m_ptr->AsStaticDict();
	}

	virtual const StatDictBase& AsStaticDict() const override
	{
		return m_ptr->AsStaticDict();
	}

	virtual std::unique_ptr<Base> Copy(const Base* unused) const override
	{
		return m_ptr->Copy(unused);
	}

	virtual std::unique_ptr<Base> Move(const Base* unused) override
	{
		return m_ptr->Move(unused);
	}

	virtual std::string DebugString() const override
	{
		return m_ptr->DebugString();
	}

	virtual std::string ShortDebugString() const override
	{
		return m_ptr->ShortDebugString();
	}

	virtual ToStringType ToString() const override
	{
		return m_ptr->ToString();
	}

	virtual void DumpString(OutIterator<typename ToStringType::value_type> outIt) const override
	{
		return m_ptr->DumpString(outIt);
	}

private:

	BasePtr m_ptr;

}; // class ObjectImpl

} //namespace SimpleObjects
