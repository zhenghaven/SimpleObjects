#pragma once

#include "BaseObject.hpp"

#include "Iterator.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _ValType>
class ListBaseObject : public BaseObject
{
public: // Static Objects

	using Self = ListBaseObject<_ValType>;

	typedef _ValType                            value_type;
	typedef value_type&                         reference;
	typedef const value_type&                   const_reference;
	typedef value_type*                         pointer;
	typedef const value_type*                   const_pointer;
	typedef RdIterator<value_type, false>       iterator;
	typedef RdIterator<value_type, true>        const_iterator;

public:
	ListBaseObject() = default;

	virtual ~ListBaseObject() = default;

	virtual const char* GetCategoryName() const override
	{
		return "List";
	}

	virtual Self& AsList() override
	{
		return *this;
	}

	virtual const Self& AsList() const override
	{
		return *this;
	}

	virtual bool operator==(const Self& rhs) const = 0;

	virtual bool operator!=(const Self& rhs) const
	{
		return !(*this == rhs);
	}

	virtual iterator begin() = 0;
	virtual iterator end() = 0;

	virtual const_iterator cbegin() const = 0;
	virtual const_iterator cend() const = 0;

	virtual iterator rbegin() = 0;
	virtual iterator rend() = 0;

	virtual const_iterator crbegin() const = 0;
	virtual const_iterator crend() const = 0;

	virtual const_iterator begin() const
	{
		return this->cbegin();
	}

	virtual const_iterator end() const
	{
		return this->cend();
	}

	virtual size_t Len() const = 0;

	virtual reference At(size_t idx) = 0;

	virtual const_reference At(size_t idx) const = 0;

	virtual reference operator[](size_t idx)
	{
		return this->At(idx);
	}

	virtual const_reference operator[](size_t idx) const
	{
		return this->At(idx);
	}

	virtual iterator Contains(const_reference other) = 0;

	virtual const_iterator Contains(const_reference other) const = 0;

	virtual void PushBack(const_reference ch) = 0;

	virtual void PopBack() = 0;

	virtual void Append(const_iterator begin, const_iterator end) = 0;

	virtual void Append(const Self& other)
	{
		return this->Append(other.cbegin(), other.cend());
	}

	virtual const_pointer Data() const = 0;

	virtual void Resize(size_t len) = 0;

	virtual void Reserve(size_t len) = 0;

	virtual void Insert(size_t idx, const_reference other) = 0;

	virtual void Remove(size_t idx) = 0;

}; // class ListBaseObject

} //namespace SimpleObjects
