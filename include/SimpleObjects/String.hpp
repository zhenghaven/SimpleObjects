#pragma once

#include "StringBaseObject.hpp"

#include <algorithm>
#include <string>

#include "Utils.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _StringCtnType>
class StringCat : public StringBaseObject<typename _StringCtnType::value_type>
{
public: // Static member:

	using _InternalType = _StringCtnType;
	using Base = StringBaseObject<typename _StringCtnType::value_type>;
	using Self = StringCat<_InternalType>;

	typedef typename _InternalType::traits_type          traits_type;
	typedef typename _InternalType::allocator_type       allocator_type;
	typedef typename _InternalType::value_type           value_type;
	typedef typename _InternalType::size_type            size_type;
	typedef typename _InternalType::difference_type      difference_type;
	typedef typename _InternalType::reference            reference;
	typedef typename _InternalType::const_reference      const_reference;
	typedef typename _InternalType::pointer              pointer;
	typedef typename _InternalType::const_pointer        const_pointer;
	typedef typename Base::iterator                      iterator;
	typedef typename Base::const_iterator                const_iterator;
	typedef typename Base::iterator                      reverse_iterator;
	typedef typename Base::const_iterator                const_reverse_iterator;

	static constexpr size_type npos = _InternalType::npos;

	static constexpr ObjCategory sk_cat()
	{
		return ObjCategory::String;
	}

	// static_assert(std::is_same<Base::value_type, _InternalType::value_type>::value,
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
		m_data(std::move(other.m_data))
	{}

	virtual ~StringCat() = default;

	Self& operator=(const Self& rhs)
	{
		m_data = rhs.m_data;
		return *this;
	}

	Self& operator=(Self&& rhs)
	{
		m_data = std::forward<_InternalType>(rhs.m_data);
		return *this;
	}

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	virtual bool operator==(const Base& rhs) const override
	{
		auto ptr = m_data.data();
		return rhs.Equal(0, rhs.Len(), ptr, ptr + Len());
	}

	virtual bool operator>(const Base& rhs) const override
	{
		auto ptr = m_data.data();
		// rhs < this ==> this > rhs
		return rhs.LessThan(0, rhs.Len(), ptr, ptr + Len());
	}

	virtual bool operator<(const Base& rhs) const override
	{
		auto ptr = m_data.data();
		// rhs > this ==> this < rhs
		return rhs.GreaterThan(0, rhs.Len(), ptr, ptr + Len());
	}

	virtual std::size_t Hash() const override
	{
		return std::hash<_InternalType>()(m_data);
	}

	virtual size_t Len() const override
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

	virtual value_type& At(size_t idx) override
	{
		return m_data[idx];
	}

	virtual const value_type& At(size_t idx) const override
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

	virtual void PushBack(const value_type& ch) override
	{
		m_data.push_back(ch);
	}

	virtual void PopBack() override
	{
		m_data.pop_back();
	}

	using Base::Append;
	virtual void Append(const_iterator begin, const_iterator end) override
	{
		std::copy(begin, end, std::back_inserter(m_data));
	}

	virtual void Resize(size_t len) override
	{
		m_data.resize(len);
	}

	virtual void Reserve(size_t len) override
	{
		m_data.reserve(len);
	}

	const_pointer CStr() const override
	{
		return m_data.c_str();
	}

	const _InternalType& GetVal() const
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
		return ((end - begin) != Len()) ?
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

	_InternalType m_data;

}; // class StringCat

using String = StringCat<std::string>;

}//namespace SimpleObjects

// ========== Hash ==========
namespace std
{
	template<typename _InternalType>
#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
	struct hash<SimpleObjects::StringCat<_InternalType> > : hash<_InternalType>
	{
		using _ObjType = SimpleObjects::StringCat<_InternalType>;
#else
	struct hash<SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::StringCat<_InternalType> > : hash<_InternalType>
	{
		using _ObjType = SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::StringCat<_InternalType>;
#endif
	public:
		using Base = std::hash<_InternalType>;

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
