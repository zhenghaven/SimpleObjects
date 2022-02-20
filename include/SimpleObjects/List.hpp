#pragma once

#include "ListBaseObject.hpp"

#include <memory>
#include <vector>

#include "Object.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _CtnType>
class ListCat : public ListBaseObject<typename _CtnType::value_type>
{
public: // Static member:

	using ContainerType = _CtnType;
	using Base = ListBaseObject<typename _CtnType::value_type>;
	using Self = ListCat<ContainerType>;

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

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	virtual bool operator==(const Base& rhs) const override
	{
		if (Len() != rhs.Len())
		{
			return false;
		}
		auto ita = cbegin();
		auto itb = rhs.cbegin();
		for (; ita != cend() && itb != rhs.cend(); ++ita, ++itb)
		{
			if (*ita != *itb)
			{
				return false;
			}
		}
		return true;
	}
	using Base::operator==;
	using Base::operator!=;
	using Base::operator<;
	using Base::operator>;
	using Base::operator<=;
	using Base::operator>=;

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

	virtual iterator Contains(const_reference other)
	{
		auto it = m_data.begin();
		for (; it != m_data.end() && *it != other; ++it) {}
		return ToRdIt<false>(it);
	}

	virtual const_iterator Contains(const_reference other) const
	{
		auto it = m_data.begin();
		for (; it != m_data.end() && *it != other; ++it) {}
		return ToRdIt<true>(it);
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

	const_pointer Data() const override
	{
		return m_data.data();
	}

	virtual void Insert(size_t idx, const_reference other)
	{
		m_data.insert(m_data.begin() + idx, other);
	}

	virtual void Remove(size_t idx)
	{
		m_data.erase(m_data.begin() + idx);
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

using List = ListCat<std::vector<Object> >;

}//namespace SimpleObjects