// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "DictBaseObject.hpp"

#include <memory>

#include "ToString.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _CtnType, typename _ToStringType>
class DictCat :
	public DictBaseObject<
		typename _CtnType::key_type,
		typename _CtnType::mapped_type,
		_ToStringType>
{
public: // Static member:

	using ContainerType = _CtnType;
	using ToStringType = _ToStringType;
	using Self = DictCat<_CtnType, _ToStringType>;
	using Base = DictBaseObject<
		typename _CtnType::key_type,
		typename _CtnType::mapped_type,
		_ToStringType>;
	using BaseBase = typename Base::Base;

	static_assert(std::is_same<BaseBase, BaseObject<_ToStringType> >::value,
		"Expecting Base::Base to be BaseObject class");

	typedef typename ContainerType::key_type             key_type;
	typedef typename ContainerType::mapped_type          mapped_type;
	typedef typename ContainerType::value_type           value_type;
	typedef typename ContainerType::difference_type      difference_type;
	typedef typename ContainerType::reference            reference;
	typedef typename ContainerType::const_reference      const_reference;
	typedef typename ContainerType::pointer              pointer;
	typedef typename ContainerType::const_pointer        const_pointer;
	typedef typename Base::iterator                      iterator;
	typedef typename Base::const_iterator                const_iterator;

	static constexpr ObjCategory sk_cat()
	{
		return ObjCategory::Dict;
	}

public:

	DictCat() :
		m_data()
	{}

	DictCat(std::initializer_list<value_type> l) :
		m_data(l)
	{}

	DictCat(const Self& other) :
		m_data(other.m_data)
	{}

	DictCat(Self&& other) :
		m_data(std::forward<ContainerType>(other.m_data))
	{}

	virtual ~DictCat() = default;

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

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	// overrides Base::operator==
	virtual bool operator==(const Base& rhs) const override
	{
		// reference: https://github.com/llvm/llvm-project/blob/main/libcxx/include/unordered_map#L1877
		if (size() != rhs.size())
		{
			return false;
		}
		auto xi = m_data.begin();
		auto xe = m_data.end();
		auto ye = rhs.end();
		for (; xi != xe; ++xi)
		{
			auto yj = rhs.find(xi->first);
			if (yj == ye || !(*xi == *yj))
			{
				return false;
			}
		}
		return true;
	}

	using BaseBase::operator==;

	using Base::operator!=;

	virtual bool operator==(const Self& rhs) const
	{
		return m_data == rhs.m_data;
	}
	virtual bool operator!=(const Self& rhs) const
	{
		return !(m_data == rhs.m_data);
	}

	bool operator<(const Self& rhs) = delete;
	bool operator>(const Self& rhs) = delete;
	bool operator<=(const Self& rhs) = delete;
	bool operator>=(const Self& rhs) = delete;

	using Base::operator<;
	using Base::operator>;
	using Base::operator<=;
	using Base::operator>=;

	virtual size_t size() const override
	{
		return m_data.size();
	}

	using Base::begin;
	using Base::end;

	virtual iterator begin() override
	{
		return ToFrIt<false>(m_data.begin());
	}

	virtual iterator end() override
	{
		return ToFrIt<false>(m_data.end());
	}

	virtual const_iterator cbegin() const override
	{
		return ToFrIt<true>(m_data.cbegin());
	}

	virtual const_iterator cend() const override
	{
		return ToFrIt<true>(m_data.cend());
	}

	virtual mapped_type& at(const key_type& key) override
	{
		return m_data.at(key);
	}

	virtual const mapped_type& at(const key_type& key) const override
	{
		return m_data.at(key);
	}

	virtual mapped_type& operator[](const key_type& key) override
	{
		return m_data[key];
	}

	virtual const_iterator find(const key_type& key) const override
	{
		return ToFrIt<true>(m_data.find(key));
	}

	virtual iterator find(const key_type& key) override
	{
		return ToFrIt<false>(m_data.find(key));
	}

	virtual bool HasKey(const key_type& key) const override
	{
		return m_data.find(key) != m_data.cend();
	}

	virtual std::pair<iterator, bool> InsertOnly(
		const key_type& key, const mapped_type& other) override
	{
		auto it = m_data.find(key);
		if (it == m_data.end())
		{
			// insert
			it = m_data.emplace(key, other).first;
			return {ToFrIt<false>(it), true};
		}
		return {ToFrIt<false>(it), false};
	}

	virtual std::pair<iterator, bool> InsertOrAssign(
		const key_type& key, const mapped_type& other) override
	{
		auto it = m_data.find(key);
		if (it == m_data.end())
		{
			// insert
			it = m_data.emplace(key, other).first;
			return {ToFrIt<false>(it), true};
		}
		else
		{
			// assign
			(*it).second = other;
			return {ToFrIt<false>(it), false};
		}
	}

	virtual void Remove(const key_type& key) override
	{
		m_data.erase(key);
	}

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

	const ContainerType& GetVal() const
	{
		return m_data;
	}

	virtual std::string DebugString() const override
	{
		std::string res;
		res += '{';
		res += ' ';
		size_t i = 0;
		for (const auto& item : m_data)
		{
			res += item.first.DebugString();
			res += " : ";
			res += item.second.DebugString();
			if (i < m_data.size() - 1)
			{
				res += ',';
				res += ' ';
			}
			++i;
		}
		res += ' ';
		res += '}';
		return res;
	}

	virtual std::string ShortDebugString() const override
	{
		std::string res;
		res += '{';
		size_t i = 0;
		for (const auto& item : m_data)
		{
			res += item.first.ShortDebugString();
			res += ":";
			res += item.second.ShortDebugString();
			if (i < m_data.size() - 1)
			{
				res += ',';
			}
			++i;
		}
		res += '}';
		return res;
	}

	virtual ToStringType ToString() const override
	{
		auto res = Internal::ToString<ToStringType>("{ ");
		size_t i = 0;
		for (const auto& item : m_data)
		{
			res += item.first.ToString();
			res += Internal::ToString<ToStringType>(" : ");
			res += item.second.ToString();
			if (i < m_data.size() - 1)
			{
				res += Internal::ToString<ToStringType>(", ");
			}
			++i;
		}
		res += Internal::ToString<ToStringType>(" }");
		return res;
	}

	virtual void DumpString(OutIterator<typename ToStringType::value_type> outIt) const override
	{
		*outIt++ = '{';
		*outIt++ = ' ';
		size_t i = 0;
		for (const auto& item : m_data)
		{
			item.first.DumpString(outIt);
			*outIt++ = ' ';
			*outIt++ = ':';
			*outIt++ = ' ';
			item.second.DumpString(outIt);
			if (i < m_data.size() - 1)
			{
				*outIt++ = ',';
				*outIt++ = ' ';
			}
			++i;
		}
		*outIt++ = ' ';
		*outIt++ = '}';
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

}; // class DictCat

}//namespace SimpleObjects
