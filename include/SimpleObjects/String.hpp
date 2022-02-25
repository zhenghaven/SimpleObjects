#pragma once

#include "StringBaseObject.hpp"

#include <algorithm>

#include "Utils.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _CtnType, typename _ToStringType>
class StringCat :
	public StringBaseObject<
		typename _CtnType::value_type,
		_ToStringType>
{
public: // Static member:

	using ContainerType = _CtnType;
	using ToStringType = _ToStringType;
	using Self = StringCat<ContainerType, ToStringType>;
	using Base = StringBaseObject<
		typename ContainerType::value_type, ToStringType>;

	typedef typename ContainerType::traits_type          traits_type;
	typedef typename ContainerType::allocator_type       allocator_type;
	typedef typename ContainerType::value_type           value_type;
	typedef typename ContainerType::size_type            size_type;
	typedef typename ContainerType::difference_type      difference_type;
	typedef typename ContainerType::reference            reference;
	typedef typename ContainerType::const_reference      const_reference;
	typedef typename ContainerType::pointer              pointer;
	typedef typename ContainerType::const_pointer        const_pointer;
	typedef typename Base::iterator                      iterator;
	typedef typename Base::const_iterator                const_iterator;
	typedef typename Base::iterator                      reverse_iterator;
	typedef typename Base::const_iterator                const_reverse_iterator;

	static constexpr size_type npos = ContainerType::npos;

	static constexpr ObjCategory sk_cat()
	{
		return ObjCategory::String;
	}

	// static_assert(std::is_same<Base::value_type, ContainerType::value_type>::value,
	// 	"value_type of base class does not match the internal type.");

	static_assert(std::is_same<value_type, char>::value,
		"Current implementation only supports char strings.");

public:

	StringCat() :
		m_data()
	{}

	StringCat(const_pointer str) :
		m_data(str)
	{}

	StringCat(const Self& other) :
		m_data(other.m_data)
	{}

	StringCat(Self&& other) :
		m_data(std::forward<ContainerType>(other.m_data))
	{}

	virtual ~StringCat() = default;

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

	virtual bool operator==(const Base& rhs) const override
	{
		auto ptr = m_data.data();
		return rhs.Equal(0, rhs.size(), ptr, ptr + size());
	}

	virtual bool operator>(const Base& rhs) const override
	{
		auto ptr = m_data.data();
		// rhs < this ==> this > rhs
		return rhs.LessThan(0, rhs.size(), ptr, ptr + size());
	}

	virtual bool operator<(const Base& rhs) const override
	{
		auto ptr = m_data.data();
		// rhs > this ==> this < rhs
		return rhs.GreaterThan(0, rhs.size(), ptr, ptr + size());
	}

	virtual std::size_t Hash() const override
	{
		return std::hash<ContainerType>()(m_data);
	}

	virtual size_t size() const override
	{
		return m_data.size();
	}

	using Base::begin;
	using Base::end;

	virtual iterator begin() override
	{
		return ToRdIt<false>(m_data.begin());
	}

	virtual iterator end() override
	{
		return ToRdIt<false>(m_data.end());
	}

	virtual const_iterator cbegin() const override
	{
		return ToRdIt<true>(m_data.cbegin());
	}

	virtual const_iterator cend() const override
	{
		return ToRdIt<true>(m_data.cend());
	}

	virtual reverse_iterator rbegin() override
	{
		return ToRdIt<false>(m_data.rbegin());
	}

	virtual reverse_iterator rend() override
	{
		return ToRdIt<false>(m_data.rend());
	}

	virtual const_reverse_iterator crbegin() const override
	{
		return ToRdIt<true>(m_data.crbegin());
	}

	virtual const_reverse_iterator crend() const override
	{
		return ToRdIt<true>(m_data.crend());
	}

	virtual value_type& at(size_t idx) override
	{
		return m_data[idx];
	}

	virtual const value_type& at(size_t idx) const override
	{
		return m_data[idx];
	}

	using Base::StartsWith;
	virtual bool StartsWith(
		const_iterator begin, const_iterator end) const override
	{
		return Internal::FindAt(cbegin(), cend(), begin, end);
	}

	using Base::EndsWith;
	virtual bool EndsWith(
		const_iterator begin, const_iterator end) const override
	{
		return Internal::FindAt(crbegin(), crend(),
			std::reverse_iterator<const_iterator >(end),
			std::reverse_iterator<const_iterator >(begin));
	}

	using Base::Contains;
	virtual const_iterator Contains(
		const_iterator begin, const_iterator end) const override
	{
		auto res = cbegin();
		for(; res != cend(); ++res)
		{
			if (Internal::FindAt(res, cend(), begin, end))
			{
				return res;
			}
		}
		return res;
	}

	virtual void push_back(const value_type& ch) override
	{
		m_data.push_back(ch);
	}

	virtual void pop_back() override
	{
		m_data.pop_back();
	}

	using Base::Append;
	virtual void Append(const_iterator begin, const_iterator end) override
	{
		std::copy(begin, end, std::back_inserter(m_data));
	}

	virtual void resize(size_t len) override
	{
		m_data.resize(len);
	}

	virtual void reserve(size_t len) override
	{
		m_data.reserve(len);
	}

	const_pointer c_str() const override
	{
		return m_data.c_str();
	}

	const ContainerType& GetVal() const
	{
		return m_data;
	}

	virtual bool LessThan(size_t pos1, size_t count1,
		const_pointer begin, const_pointer end) const override
	{
		// m_data < (begin, end)
		return std::lexicographical_compare(&m_data[pos1], &m_data[pos1 + count1],
			begin, end);
	}

	virtual bool GreaterThan(size_t pos1, size_t count1,
		const_pointer begin, const_pointer end) const override
	{
		// (begin, end) < m_data ==> m_data > (begin, end)
		return std::lexicographical_compare(begin, end,
			&m_data[pos1], &m_data[pos1 + count1]);
	}

	virtual bool Equal(size_t pos1, size_t count1,
		const_pointer begin, const_pointer end) const override
	{
		return ((end - begin) != size()) ?
			false :
			std::equal(&m_data[pos1], &m_data[pos1 + count1], begin);
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

}; // class StringCat

}//namespace SimpleObjects

// ========== Hash ==========
namespace std
{
	template<typename _CtnType, typename _ToStringType>
#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
	struct hash<SimpleObjects::StringCat<_CtnType, _ToStringType> > : hash<_CtnType>
	{
		using _ObjType = SimpleObjects::StringCat<_CtnType, _ToStringType>;
#else
	struct hash<SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::StringCat<_CtnType, _ToStringType> > : hash<_CtnType>
	{
		using _ObjType = SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::StringCat<_CtnType, _ToStringType>;
#endif
	public:
		using Base = std::hash<_CtnType>;

#if __cplusplus < 201703L
		typedef typename Base::result_type       result_type;
		typedef typename Base::argument_type     argument_type;
#endif

		size_t operator()(const _ObjType& cnt) const
		{
			return Base::operator()(cnt.m_data);
		}
	};
}
