// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "ListBaseObject.hpp"

#include <memory>

#include "ToString.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _CtnType, typename _ToStringType>
class ListCat :
	public ListBaseObject<
		BaseObject<_ToStringType>,
		_ToStringType>
{
public: // Static member:

	using ContainerType = _CtnType;
	using ToStringType  = _ToStringType;
	using Self = ListCat<_CtnType, _ToStringType>;
	using Base = ListBaseObject<BaseObject<_ToStringType>, _ToStringType>;
	using BaseBase = typename Base::Base;

	static_assert(std::is_same<BaseBase, BaseObject<_ToStringType> >::value,
		"Expecting Base::Base to be BaseObject class");

	typedef typename ContainerType::allocator_type       allocator_type;
	typedef typename ContainerType::value_type           value_type;
	typedef typename ContainerType::size_type            size_type;
	typedef typename ContainerType::difference_type      difference_type;
	typedef typename ContainerType::reference            reference;
	typedef typename ContainerType::const_reference      const_reference;
	typedef typename ContainerType::pointer              pointer;
	typedef typename ContainerType::const_pointer        const_pointer;
	typedef RdIterator<value_type, false>                iterator;
	typedef RdIterator<value_type, true>                 const_iterator;
	typedef RdIterator<value_type, false>                reverse_iterator;
	typedef RdIterator<value_type, true>                 const_reverse_iterator;

	typedef BaseBase                                     base_value_type;
	typedef BaseBase&                                    base_reference;
	typedef const BaseBase&                              base_const_reference;
	typedef RdIterator<base_value_type, false>           base_iterator;
	typedef RdIterator<base_value_type, true>            base_const_iterator;

	static constexpr ObjCategory sk_cat()
	{
		return ObjCategory::List;
	}

public:

	ListCat() :
		m_data()
	{}

	ListCat(std::initializer_list<value_type> l) :
		m_data(l)
	{}

	ListCat(const Self& other) :
		m_data(other.m_data)
	{}

	ListCat(Self&& other) :
		m_data(std::forward<ContainerType>(other.m_data))
	{}

	virtual ~ListCat() = default;

	Self& operator=(const Self& rhs)
	{
		if (this != &rhs)
		{
			m_data = rhs.m_data;
		}
		return *this;
	}

	Self& operator=(Self&& rhs)
	{
		if (this != &rhs)
		{
			m_data = std::forward<ContainerType>(rhs.m_data);
		}
		return *this;
	}

	const ContainerType& GetVal() const
	{
		return m_data;
	}

	// ========== operators ==========

	using Base::operator==;
	using Base::operator!=;

	using Base::operator<;
	using Base::operator>;

	using Base::operator<=;
	using Base::operator>=;

	virtual bool operator==(const Self& rhs) const
	{
		return m_data == rhs.m_data;
	}

	virtual bool operator!=(const Self& rhs) const
	{
		return m_data != rhs.m_data;
	}

	virtual bool operator<(const Self& rhs) const
	{
		return m_data < rhs.m_data;
	}

	virtual bool operator>(const Self& rhs) const
	{
		return m_data > rhs.m_data;
	}

	virtual bool operator<=(const Self& rhs) const
	{
		return m_data <= rhs.m_data;
	}

	virtual bool operator>=(const Self& rhs) const
	{
		return m_data >= rhs.m_data;
	}

	// ========== Functions provided by this class ==========

	iterator begin()
	{
		return ToRdIt<false>(m_data.begin());
	}

	iterator end()
	{
		return ToRdIt<false>(m_data.end());
	}

	const_iterator cbegin() const
	{
		return ToRdIt<true>(m_data.cbegin());
	}

	const_iterator cend() const
	{
		return ToRdIt<true>(m_data.cend());
	}

	const_iterator begin() const
	{
		return cbegin();
	}

	const_iterator end() const
	{
		return cend();
	}

	reverse_iterator rbegin()
	{
		return ToRdIt<false>(m_data.rbegin());
	}

	reverse_iterator rend()
	{
		return ToRdIt<false>(m_data.rend());
	}

	const_reverse_iterator crbegin() const
	{
		return ToRdIt<true>(m_data.crbegin());
	}

	const_reverse_iterator crend() const
	{
		return ToRdIt<true>(m_data.crend());
	}

	const_pointer data() const
	{
		return m_data.data();
	}

	value_type& operator[](size_t idx)
	{
		try
		{
			return m_data.at(idx);
		}
		catch(const std::out_of_range&)
		{
			throw IndexError(idx);
		}
	}

	const value_type& operator[](size_t idx) const
	{
		try
		{
			return m_data.at(idx);
		}
		catch(const std::out_of_range&)
		{
			throw IndexError(idx);
		}
	}

	bool Contains(const_reference val) const
	{
		auto e = cend();
		return std::find(cbegin(), e, val) != e;
	}

	void push_back(value_type&& ch)
	{
		m_data.push_back(std::forward<value_type>(ch));
	}

	void push_back(const value_type& ch)
	{
		m_data.push_back(ch);
	}

	void Append(const_iterator begin, const_iterator end)
	{
		while (begin != end)
		{
			push_back(*begin);
			++begin;
		}
	}

	void Append(const Self& other)
	{
		Append(other.cbegin(), other.cend());
	}

	void Insert(size_t idx, const_reference other)
	{
		m_data.insert(m_data.begin() + idx, other);
	}

	// ========== Overrides BaseObject ==========

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	using BaseBase::Set;

	virtual void Set(const BaseBase& other) override
	{
		try
		{
			const Self& casted = dynamic_cast<const Self&>(other);
			*this = casted;
		}
		catch(const std::bad_cast&)
		{
			throw TypeError("List", other.GetCategoryName());
		}
	}

	virtual void Set(BaseBase&& other) override
	{
		try
		{
			Self&& casted = dynamic_cast<Self&&>(other);
			*this = std::forward<Self>(casted);
		}
		catch(const std::bad_cast&)
		{
			throw TypeError("List", other.GetCategoryName());
		}
	}

	virtual bool IsTrue() const override
	{
		return m_data.size() > 0;
	}

	// ========== Overrides ListBaseObject ==========

	virtual size_t size() const override
	{
		return m_data.size();
	}

	virtual void pop_back() override
	{
		m_data.pop_back();
	}

	virtual void resize(size_t len) override
	{
		m_data.resize(len);
	}

	virtual void reserve(size_t len) override
	{
		m_data.reserve(len);
	}

	virtual void Remove(size_t idx) override
	{
		m_data.erase(m_data.begin() + idx);
	}

	// ========== Interface copy/Move ==========

	using Base::Copy;
	virtual std::unique_ptr<Base> Copy(const Base* /*unused*/) const override
	{
		return CopyImpl();
	}

	using Base::Move;
	virtual std::unique_ptr<Base> Move(const Base* /*unused*/) override
	{
		return MoveImpl();
	}

	// ========== To string ==========

	virtual std::string DebugString() const override
	{
		std::string res;
		res += '[';
		res += ' ';
		size_t i = 0;
		for (const auto& item : m_data)
		{
			res += item.DebugString();
			if (i < m_data.size() - 1)
			{
				res += ',';
				res += ' ';
			}
			++i;
		}
		res += ' ';
		res += ']';
		return res;
	}

	virtual std::string ShortDebugString() const override
	{
		std::string res;
		res += '[';
		size_t i = 0;
		for (const auto& item : m_data)
		{
			res += item.ShortDebugString();
			if (i < m_data.size() - 1)
			{
				res += ',';
			}
			++i;
		}
		res += ']';
		return res;
	}

	virtual ToStringType ToString() const override
	{
		auto res = Internal::ToString<ToStringType>("[ ");
		size_t i = 0;
		for (const auto& item : m_data)
		{
			res += item.ToString();
			if (i < m_data.size() - 1)
			{
				res += Internal::ToString<ToStringType>(", ");
			}
			++i;
		}
		res += Internal::ToString<ToStringType>(" ]");
		return res;
	}

	virtual void DumpString(OutIterator<typename ToStringType::value_type> outIt) const override
	{
		*outIt++ = '[';
		*outIt++ = ' ';
		size_t i = 0;
		for (const auto& item : m_data)
		{
			item.DumpString(outIt);
			if (i < m_data.size() - 1)
			{
				*outIt++ = ',';
				*outIt++ = ' ';
			}
			++i;
		}
		*outIt++ = ' ';
		*outIt++ = ']';
	}

protected:

	virtual base_iterator ListBaseBegin() override
	{
		return ToRdIt<false,
			typename ContainerType::iterator,
			base_value_type>(m_data.begin());
	}

	virtual base_iterator ListBaseEnd() override
	{
		return ToRdIt<false,
			typename ContainerType::iterator,
			base_value_type>(m_data.end());
	}

	virtual base_const_iterator ListBaseBegin() const override
	{
		return ToRdIt<true,
			typename ContainerType::const_iterator,
			base_value_type>(m_data.cbegin());
	}

	virtual base_const_iterator ListBaseEnd() const override
	{
		return ToRdIt<true,
			typename ContainerType::const_iterator,
			base_value_type>(m_data.cend());
	}

	virtual base_reference ListBaseAt(size_t idx) override
	{
		return Self::operator[](idx);
	}

	virtual base_const_reference ListBaseAt(size_t idx) const override
	{
		return Self::operator[](idx);
	}

	virtual void ListBasePushBack(base_value_type&& val) override
	{
		try
		{
			value_type&& casted = dynamic_cast<value_type&&>(val);
			m_data.push_back(std::forward<value_type>(casted));
		}
		catch(const std::bad_cast&)
		{
			throw TypeError("value type of the List", val.GetCategoryName());
		}
	}

	virtual void ListBasePushBack(base_const_reference val) override
	{
		try
		{
			const value_type& casted = dynamic_cast<const value_type&>(val);
			m_data.push_back(casted);
		}
		catch(const std::bad_cast&)
		{
			throw TypeError("value type of the List", val.GetCategoryName());
		}
	}

private:

	std::unique_ptr<Self> CopyImpl() const
	{
		// TODO: make_unique
		return std::unique_ptr<Self>(new Self(*this));
	}

	std::unique_ptr<Self> MoveImpl()
	{
		// TODO: make_unique
		return std::unique_ptr<Self>(new Self(std::move(*this)));
	}

	ContainerType m_data;

}; // class ListCat

}//namespace SimpleObjects
