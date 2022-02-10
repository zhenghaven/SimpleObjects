#pragma once

#include <iterator>
#include <memory>
#include <type_traits>

#include "Utils.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

//========================================
//||
//||          Interfaces
//||
//========================================

/**
 * @brief The interface of a basic iterator
 *
 * @tparam _TargetType The target type; e.g., the target type for a
 *         std::vector<uint8_t> vector will be uint8_t
 * @tparam _IsConst Is this a const iterator
 */
template<typename _TargetType, bool _IsConst>
class ForwardIteratorIf
{
public: // Static members:

	/**
	 * @brief The target type but with const, volatile, and reference specifiers
	 *        removed.
	 *
	 */
	using RawTargetType = typename std::remove_cv<
		typename std::remove_reference<_TargetType>::type>::type;

	static constexpr bool sk_isConst = _IsConst;

	/**
	 * @brief The actual target type. Based on _IsConst, it is either the raw
	 *        target type with const specifier (when _IsConst == true),
	 *        or the raw target type (when _IsConst == false).
	 *
	 */
	using ActTargetType = typename std::conditional<sk_isConst,
		typename std::add_const<RawTargetType>::type,
		RawTargetType>::type;

	using Self = ForwardIteratorIf<_TargetType, _IsConst>;

	using SelfPtr = std::unique_ptr<Self>;

	// some standard typedefs

	typedef std::ptrdiff_t                                            difference_type;
	typedef RawTargetType                                             value_type;
	typedef typename std::add_pointer<ActTargetType>::type            pointer;
	typedef typename std::add_pointer<
		typename std::add_const<RawTargetType>::type>::type           const_pointer;
	typedef typename std::add_lvalue_reference<ActTargetType>::type   reference;
	typedef std::forward_iterator_tag                                 iterator_category;

public:
	ForwardIteratorIf() = default;

	virtual ~ForwardIteratorIf() = default;

	virtual void Increment() = 0;

	virtual reference GetRef() = 0;

	virtual pointer GetPtr() = 0;

	virtual SelfPtr Copy(const Self& /*unused*/) const = 0;

}; //class ForwardIteratorIf

template<typename _TargetType, bool _IsConst>
class BidirectionalIteratorIf : public ForwardIteratorIf<_TargetType, _IsConst>
{
public: // Static members:

	using _Base = ForwardIteratorIf<_TargetType, _IsConst>;

	using Self = BidirectionalIteratorIf<_TargetType, _IsConst>;

	using SelfPtr = std::unique_ptr<Self>;

	typedef typename _Base::difference_type         difference_type;
	typedef typename _Base::value_type              value_type;
	typedef typename _Base::pointer                 pointer;
	typedef typename _Base::const_pointer           const_pointer;
	typedef typename _Base::reference               reference;
	typedef std::bidirectional_iterator_tag         iterator_category;

public:
	BidirectionalIteratorIf() = default;

	virtual ~BidirectionalIteratorIf() = default;

	virtual void Decrement() = 0;

	virtual SelfPtr Copy(const Self& /*unused*/) const = 0;

}; //class BidirectionalIteratorIf

template<typename _TargetType, bool _IsConst>
class RandomAccessIteratorIf : public BidirectionalIteratorIf<_TargetType, _IsConst>
{
public: // Static members:

	using _Base = BidirectionalIteratorIf<_TargetType, _IsConst>;

	using Self = RandomAccessIteratorIf<_TargetType, _IsConst>;

	using SelfPtr = std::unique_ptr<Self>;

	typedef typename _Base::difference_type         difference_type;
	typedef typename _Base::value_type              value_type;
	typedef typename _Base::pointer                 pointer;
	typedef typename _Base::const_pointer           const_pointer;
	typedef typename _Base::reference               reference;
	typedef std::random_access_iterator_tag         iterator_category;

public:
	RandomAccessIteratorIf() = default;

	virtual ~RandomAccessIteratorIf() = default;

	virtual void Offset(difference_type offset) = 0;

	virtual difference_type Diff(const Self& other) const = 0;

	virtual SelfPtr Copy(const Self& /*unused*/) const = 0;

}; //class RandomAccessIteratorIf

//========================================
//||
//||  Wrappers for C++ standard iterators
//||
//========================================

template<typename _OriItType, typename _TargetType, bool _IsConst>
class CppStdFwIteratorWrap : public ForwardIteratorIf<_TargetType, _IsConst>
{
public: // Static members:
	using _BaseIf = ForwardIteratorIf<_TargetType, _IsConst>;
	using _BaseIfPtr = std::unique_ptr<_BaseIf>;

	typedef typename _BaseIf::difference_type         difference_type;
	typedef typename _BaseIf::value_type              value_type;
	typedef typename _BaseIf::pointer                 pointer;
	typedef typename _BaseIf::const_pointer           const_pointer;
	typedef typename _BaseIf::reference               reference;
	typedef typename _BaseIf::iterator_category       iterator_category;

	static _BaseIfPtr Build(_OriItType oriIt)
	{
		// TODO: make_unique
		return _BaseIfPtr(new CppStdFwIteratorWrap(oriIt));
	}

	static_assert(
		std::is_base_of<iterator_category, typename _OriItType::iterator_category>::value,
		"The given C++ standard iterator must be a category based on forward iterator");

public:

	CppStdFwIteratorWrap(_OriItType oriIt) :
		_BaseIf::ForwardIteratorIf(),
		m_it(oriIt)
	{}

	CppStdFwIteratorWrap(const CppStdFwIteratorWrap& other) :
		m_it(other.m_it)
	{}

	CppStdFwIteratorWrap(CppStdFwIteratorWrap&& other) :
		m_it(std::forward<_OriItType>(other.m_it))
	{}

	virtual ~CppStdFwIteratorWrap() = default;

	virtual void Increment() override
	{
		++m_it;
	}

	virtual reference GetRef() override
	{
		return *m_it;
	}

	virtual pointer GetPtr() override
	{
		return &(this->GetRef());
	}

	virtual _BaseIfPtr Copy(const _BaseIf&) const override
	{
		// TODO: make_unique
		return _BaseIfPtr(new CppStdFwIteratorWrap(*this));
	}

public:

	_OriItType m_it;
}; // class CppStdFwIteratorWrap


template<typename _OriItType, typename _TargetType, bool _IsConst>
class CppStdBiIteratorWrap : public CppStdFwIteratorWrap<_OriItType, _TargetType, _IsConst>,
	public BidirectionalIteratorIf<_TargetType, _IsConst>
{
public: // Static members:
	using _BaseFwIf = ForwardIteratorIf<_TargetType, _IsConst>;
	using _BaseFwIfPtr = std::unique_ptr<_BaseFwIf>;

	using _BaseIf = BidirectionalIteratorIf<_TargetType, _IsConst>;
	using _BaseIfPtr = std::unique_ptr<_BaseIf>;

	using _Base = CppStdFwIteratorWrap<_OriItType, _TargetType, _IsConst>;

	typedef typename _BaseIf::difference_type         difference_type;
	typedef typename _BaseIf::value_type              value_type;
	typedef typename _BaseIf::pointer                 pointer;
	typedef typename _BaseIf::const_pointer           const_pointer;
	typedef typename _BaseIf::reference               reference;
	typedef typename _BaseIf::iterator_category       iterator_category;

	static _BaseIfPtr Build(_OriItType oriIt)
	{
		// TODO: make_unique
		return _BaseIfPtr(new CppStdBiIteratorWrap(oriIt));
	}

	static_assert(
		std::is_base_of<iterator_category, typename _OriItType::iterator_category>::value,
		"The given C++ standard iterator must be a category based on bidirectional iterator");

public:

	using _Base::CppStdFwIteratorWrap;

	virtual ~CppStdBiIteratorWrap() = default;

	virtual void Increment() override { return _Base::Increment(); }
	virtual reference GetRef() override { return _Base::GetRef(); }
	virtual pointer GetPtr() override { return _Base::GetPtr(); }

	virtual _BaseIfPtr Copy(const _BaseIf&) const override { return CopyImpl(); }
	virtual _BaseFwIfPtr Copy(const _BaseFwIf&) const override { return CopyImpl(); }

	virtual void Decrement() override
	{
		--(_Base::m_it);
	}

private:

	_BaseIfPtr CopyImpl() const
	{
		// TODO: make_unique
		return _BaseIfPtr(new CppStdBiIteratorWrap(*this));
	}

}; // class CppStdBiIteratorWrap

template<typename _OriItType, typename _TargetType, bool _IsConst>
class CppStdRdIteratorWrap : public CppStdBiIteratorWrap<_OriItType, _TargetType, _IsConst>,
	public RandomAccessIteratorIf<_TargetType, _IsConst>
{
public: // Static members:
	using Self = CppStdRdIteratorWrap<_OriItType, _TargetType, _IsConst>;

	using _BaseFwIf = ForwardIteratorIf<_TargetType, _IsConst>;
	using _BaseFwIfPtr = std::unique_ptr<_BaseFwIf>;

	using _BaseBiIf = BidirectionalIteratorIf<_TargetType, _IsConst>;
	using _BaseBiIfPtr = std::unique_ptr<_BaseBiIf>;

	using _BaseIf = RandomAccessIteratorIf<_TargetType, _IsConst>;
	using _BaseIfPtr = std::unique_ptr<_BaseIf>;

	using _Base = CppStdBiIteratorWrap<_OriItType, _TargetType, _IsConst>;

	typedef typename _BaseIf::difference_type         difference_type;
	typedef typename _BaseIf::value_type              value_type;
	typedef typename _BaseIf::pointer                 pointer;
	typedef typename _BaseIf::const_pointer           const_pointer;
	typedef typename _BaseIf::reference               reference;
	typedef typename _BaseIf::iterator_category       iterator_category;

	static _BaseIfPtr Build(_OriItType oriIt)
	{
		// TODO: make_unique
		return _BaseIfPtr(new CppStdRdIteratorWrap(oriIt));
	}

	static_assert(
		std::is_base_of<iterator_category, typename _OriItType::iterator_category>::value,
		"The given C++ standard iterator must be a category based on random access iterator");

public:

	using _Base::CppStdBiIteratorWrap;

	virtual ~CppStdRdIteratorWrap() = default;

	virtual void Increment() override { return _Base::Increment(); }
	virtual void Decrement() override { return _Base::Decrement(); }
	virtual reference GetRef() override { return _Base::GetRef(); }
	virtual pointer GetPtr() override { return _Base::GetPtr(); }

	virtual _BaseIfPtr Copy(const _BaseIf&) const override { return CopyImpl(); }
	virtual _BaseFwIfPtr Copy(const _BaseFwIf&) const override { return CopyImpl(); }
	virtual _BaseBiIfPtr Copy(const _BaseBiIf&) const override { return CopyImpl(); }

	virtual void Offset(difference_type offset) override
	{
		_Base::m_it += offset;
	}

	/**
	 * @brief NOTE: We assume here we are comparing two iterator with the same
	 *              child type, since in most cases, it does not make sense to
	 *              compare two different iterator types.
	 *
	 * @param other
	 * @return difference_type
	 */
	virtual difference_type Diff(const _BaseIf& other) const override
	{
		const auto& otherWrap = Internal::DownCast<Self>(other);
		return _Base::m_it - otherWrap.m_it;
	}


private:
	_BaseIfPtr CopyImpl() const
	{
		// TODO: make_unique
		return _BaseIfPtr(new CppStdRdIteratorWrap(*this));
	}

}; // class CppStdRdIteratorWrap

//========================================
//||
//||  Wrappers for iterators interfaces pointers
//||
//========================================

/**
 * @brief The wrapper of bidirectional iterator interface, so we can support
 *        different classes of iterator implementations
 *
 * @tparam _TargetType The target type; e.g., the target type for a
 *         std::vector<uint8_t> vector will be uint8_t
 * @tparam _IsConst Is this a const iterator
 */
template<typename _TargetType, bool _IsConst>
class BiIterator
{
public: // Static members:
	using WrappedIt = BidirectionalIteratorIf<_TargetType, _IsConst>;
	using WrappedItPtr = typename WrappedIt::SelfPtr;

	typedef typename WrappedIt::difference_type         difference_type;
	typedef typename WrappedIt::value_type              value_type;
	typedef typename WrappedIt::pointer                 pointer;
	typedef typename WrappedIt::const_pointer           const_pointer;
	typedef typename WrappedIt::reference               reference;
	typedef typename WrappedIt::iterator_category       iterator_category;

public:
	BiIterator() = delete;

	BiIterator(WrappedItPtr it) :
		m_it(std::move(it))
	{}

	// TODO: non-const to const copy & move

	BiIterator(const BiIterator& otherIt) :
		m_it(otherIt.m_it->Copy(*m_it))
	{}

	BiIterator(BiIterator&& otherIt):
		m_it(std::forward<WrappedItPtr>(otherIt.m_it))
	{}

	virtual ~BiIterator() = default;

	BiIterator& operator=(const BiIterator& rhs)
	{
		if (this != &rhs)
		{
			m_it = rhs.m_it->Copy(*m_it);
		}
		return *this;
	}

	BiIterator& operator=(BiIterator&& rhs)
	{
		if (this != &rhs)
		{
			m_it = std::move(rhs.m_it);
		}
		return *this;
	}

	reference operator*() const
	{
		return m_it->GetRef();
	}

	pointer operator->() const
	{
		return m_it->GetPtr();
	}

	BiIterator& operator++()
	{
		m_it->Increment();
		return *this;
	}

	BiIterator operator++(int)
	{
		BiIterator copy(*this);
		m_it->Increment();
		return copy;
	}

	BiIterator& operator--()
	{
		m_it->Decrement();
		return *this;
	}

	BiIterator operator--(int)
	{
		BiIterator copy(*this);
		m_it->Decrement();
		return copy;
	}

	template<bool _Rhs_IsConst>
	bool operator==(const BiIterator<_TargetType, _Rhs_IsConst>& rhs) const
	{
		return m_it->GetPtr() == rhs.m_it->GetPtr();
	}

	template<bool _Rhs_IsConst>
	bool operator!=(const BiIterator<_TargetType, _Rhs_IsConst>& rhs) const
	{
		return !(*this == rhs);
	}

private:
	WrappedItPtr m_it;

}; // class BiIterator

/**
 * @brief The wrapper of random access iterator interface, so we can support
 *        different classes of iterator implementations
 *
 * @tparam _TargetType The target type; e.g., the target type for a
 *         std::vector<uint8_t> vector will be uint8_t
 * @tparam _IsConst Is this a const iterator
 */
template<typename _TargetType, bool _IsConst>
class RdIterator
{
public: // Static members:
	using Self = RdIterator<_TargetType, _IsConst>;

	using WrappedIt = RandomAccessIteratorIf<_TargetType, _IsConst>;
	using WrappedItPtr = typename WrappedIt::SelfPtr;

	typedef typename WrappedIt::difference_type         difference_type;
	typedef typename WrappedIt::value_type              value_type;
	typedef typename WrappedIt::pointer                 pointer;
	typedef typename WrappedIt::const_pointer           const_pointer;
	typedef typename WrappedIt::reference               reference;
	typedef typename WrappedIt::iterator_category       iterator_category;

	friend class RdIterator<_TargetType, !_IsConst>;

public:
	RdIterator() = delete;

	RdIterator(WrappedItPtr it) :
		m_it(std::move(it))
	{}

	RdIterator(const RdIterator& otherIt) :
		m_it(otherIt.m_it->Copy(*m_it))
	{}

	RdIterator(RdIterator&& otherIt):
		m_it(std::forward<WrappedItPtr>(otherIt.m_it))
	{}

	virtual ~RdIterator() = default;

	RdIterator& operator=(const RdIterator& rhs)
	{
		if (this != &rhs)
		{
			m_it = rhs.m_it->Copy(*m_it);
		}
		return *this;
	}

	RdIterator& operator=(RdIterator&& rhs)
	{
		if (this != &rhs)
		{
			m_it = std::move(rhs.m_it);
		}
		return *this;
	}

	reference operator*() const
	{
		return m_it->GetRef();
	}

	reference operator[](difference_type idx) const
	{
		return m_it->GetPtr()[idx];
	}

	pointer operator->() const
	{
		return m_it->GetPtr();
	}

	RdIterator operator+(difference_type count) const
	{
		RdIterator copy(*this);
		copy += count;
		return copy;
	}

	RdIterator operator-(difference_type count) const
	{
		RdIterator copy(*this);
		copy -= count;
		return copy;
	}

	RdIterator& operator+=(difference_type count)
	{
		m_it->Offset(count);
		return *this;
	}

	RdIterator& operator++()
	{
		m_it->Increment();
		return *this;
	}

	RdIterator operator++(int)
	{
		RdIterator copy(*this);
		m_it->Increment();
		return copy;
	}

	RdIterator& operator-=(difference_type count)
	{
		m_it->Offset(-count);
		return *this;
	}

	RdIterator& operator--()
	{
		m_it->Decrement();
		return *this;
	}

	RdIterator operator--(int)
	{
		RdIterator copy(*this);
		m_it->Decrement();
		return copy;
	}

	template<bool _Rhs_IsConst>
	bool operator==(const RdIterator<_TargetType, _Rhs_IsConst>& rhs) const
	{
		return m_it->GetPtr() == rhs.m_it->GetPtr();
	}

	template<bool _Rhs_IsConst>
	bool operator!=(const RdIterator<_TargetType, _Rhs_IsConst>& rhs) const
	{
		return !(*this == rhs);
	}

	bool operator>(const Self& rhs) const
	{
		// ret_val <  0 -> this < other
		// ret_val == 0 -> this == other
		// ret_val >  0 -> this > other
		return m_it->Diff(*(rhs.m_it)) > 0;
	}

	bool operator<=(const Self& rhs) const
	{
		return !(*this > rhs);
	}

	bool operator<(const Self& rhs) const
	{
		// ret_val <  0 -> this < other
		// ret_val == 0 -> this == other
		// ret_val >  0 -> this > other
		return m_it->Diff(*(rhs.m_it)) < 0;
	}

	bool operator>=(const Self& rhs) const
	{
		return !(*this < rhs);
	}

	difference_type operator-(const Self& rhs) const
	{
		return m_it->Diff(*(rhs.m_it));
	}

private:
	WrappedItPtr m_it;

}; // class RdIterator

template<bool _IsConst,
	typename _OriItType,
	typename _ValType = typename _OriItType::value_type>
inline BiIterator<_ValType, _IsConst> ToBiIt(_OriItType it)
{
	using ItWrap = CppStdBiIteratorWrap<_OriItType, _ValType, _IsConst>;
	return BiIterator<_ValType, _IsConst>(ItWrap::Build(it));
}

template<bool _IsConst,
	typename _OriItType,
	typename _ValType = typename _OriItType::value_type>
inline RdIterator<_ValType, _IsConst> ToRdIt(_OriItType it)
{
	using ItWrap = CppStdRdIteratorWrap<_OriItType, _ValType, _IsConst>;
	return RdIterator<_ValType, _IsConst>(ItWrap::Build(it));
}

}//namespace SimpleObjects
