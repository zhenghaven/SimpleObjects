// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "BaseObject.hpp"

#include "Iterator.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _ValType, typename _ToStringType>
class ListBaseObject : public BaseObject<_ToStringType>
{
public: // Static Objects

	using ToStringType = _ToStringType;
	using Self = ListBaseObject<_ValType, _ToStringType>;
	using Base = BaseObject<_ToStringType>;

	using ListBase = typename Base::ListBase;

	typedef _ValType                            value_type;
	typedef value_type&                         reference;
	typedef const value_type&                   const_reference;
	typedef value_type*                         pointer;
	typedef const value_type*                   const_pointer;
	typedef RdIterator<value_type, false>       iterator;
	typedef RdIterator<value_type, true>        const_iterator;

	static constexpr Self* sk_null = nullptr;

public:
	ListBaseObject() = default;

	// LCOV_EXCL_START
	/**
	 * @brief Destroy the List Base Object
	 *
	 */
	virtual ~ListBaseObject() = default;
	// LCOV_EXCL_STOP

	virtual const char* GetCategoryName() const override
	{
		return "List";
	}

	virtual ListBase& AsList() override
	{
		return Internal::AsChildType<
				std::is_same<Self, ListBase>::value, Self, ListBase
			>::AsChild(*this, "List", this->GetCategoryName());
	}

	virtual const ListBase& AsList() const override
	{
		return Internal::AsChildType<
				std::is_same<Self, ListBase>::value, Self, ListBase
			>::AsChild(*this, "List", this->GetCategoryName());
	}

	virtual bool operator==(const Self& rhs) const = 0;

	virtual bool operator!=(const Self& rhs) const
	{
		return !(*this == rhs);
	}

	virtual bool operator<(const Self& rhs) const = 0;

	virtual bool operator>(const Self& rhs) const = 0;

	virtual bool operator<=(const Self& rhs) const
	{
		return !(*this > rhs);
	}

	virtual bool operator>=(const Self& rhs) const
	{
		return !(*this < rhs);
	}

	virtual bool operator==(const Base& rhs) const override
	{
		if (rhs.GetCategory() != ObjCategory::List)
		{
			return false;
		}
		return *this == rhs.AsList();
	}

	using Base::operator!=;

	virtual bool operator<(const Base& rhs) const override
	{
		if (rhs.GetCategory() != ObjCategory::List)
		{
			throw UnsupportedOperation("<",
				this->GetCategoryName(), rhs.GetCategoryName());
		}
		return *this < rhs.AsList();
	}

	virtual bool operator>(const Base& rhs) const override
	{
		if (rhs.GetCategory() != ObjCategory::List)
		{
			throw UnsupportedOperation(">",
				this->GetCategoryName(), rhs.GetCategoryName());
		}
		return *this > rhs.AsList();
	}

	using Base::operator<=;
	using Base::operator>=;

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

	virtual size_t size() const = 0;

	virtual reference at(size_t idx) = 0;

	virtual const_reference at(size_t idx) const = 0;

	virtual reference operator[](size_t idx)
	{
		return this->at(idx);
	}

	virtual const_reference operator[](size_t idx) const
	{
		return this->at(idx);
	}

	virtual iterator Contains(const_reference other) = 0;

	virtual const_iterator Contains(const_reference other) const = 0;

	virtual void push_back(value_type&& ch) = 0;

	virtual void push_back(const_reference ch) = 0;

	virtual void pop_back() = 0;

	virtual void Append(const_iterator begin, const_iterator end) = 0;

	virtual void Append(const Self& other)
	{
		return this->Append(other.cbegin(), other.cend());
	}

	virtual const_pointer data() const = 0;

	virtual void resize(size_t len) = 0;

	virtual void reserve(size_t len) = 0;

	virtual void Insert(size_t idx, const_reference other) = 0;

	virtual void Remove(size_t idx) = 0;

	virtual std::unique_ptr<Self> Copy(const Self* /*unused*/) const = 0;

	virtual std::unique_ptr<Self> Move(const Self* /*unused*/) = 0;

	virtual std::unique_ptr<Base> Copy(const Base* /*unused*/) const override
	{
		return Copy(sk_null);
	}

	virtual std::unique_ptr<Base> Move(const Base* /*unused*/) override
	{
		return Move(sk_null);
	}

}; // class ListBaseObject

} //namespace SimpleObjects
