#pragma once

#include "BaseObject.hpp"

#include "HashableObject.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _ValType>
class DictBaseObject : public BaseObject
{
public: // Static members

	using Self = DictBaseObject<_ValType>;

	typedef HashableObject                            key_type;
	typedef _ValType                                  mapped_type;
	typedef std::pair<const key_type, mapped_type>    value_type;
	typedef value_type&                               reference;
	typedef const value_type&                         const_reference;
	typedef RdIterator<value_type, false>             iterator;
	typedef RdIterator<value_type, true>              const_iterator;

public:
	DictBaseObject() = default;

	virtual ~DictBaseObject() = default;

	virtual const char* GetCategoryName() const override
	{
		return "Dict";
	}

	virtual Self& AsDict() override
	{
		return *this;
	}

	virtual const Self& AsDict() const override
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

	virtual const_iterator begin() const
	{
		return this->cbegin();
	}

	virtual const_iterator end() const
	{
		return this->cend();
	}

	virtual size_t size() const = 0;

	virtual reference at(const key_type& key) = 0;

	virtual const_reference at(const key_type& key) const = 0;

	virtual reference operator[](const key_type& key)
	{
		return this->at(key);
	}

	virtual const_reference operator[](const key_type& key) const
	{
		return this->at(key);
	}

	virtual const_iterator HasKey(const key_type& key) const = 0;

	virtual iterator HasKey(const key_type& key) = 0;

	virtual void InsertOrAssign(const key_type& key, const_reference other) = 0;

	virtual void Remove(const_iterator it) = 0;

}; // class DictBaseObject

} //namespace SimpleObjects
