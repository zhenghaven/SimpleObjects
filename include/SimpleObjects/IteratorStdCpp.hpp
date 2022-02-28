#pragma once

#include <memory>

#include "IteratorIf.hpp"
#include "Utils.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

//========================================
//||
//||  Wrappers for C++ standard iterators
//||
//========================================

template<typename _OriItType, typename _TargetType>
class CppStdOutIteratorWrap : public OutputIteratorIf<_TargetType>
{
public: // Static members:
	using _BaseIf = OutputIteratorIf<_TargetType>;
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
		return _BaseIfPtr(new CppStdOutIteratorWrap(oriIt));
	}

	static_assert(
		std::is_base_of<iterator_category, typename _OriItType::iterator_category>::value,
		"The given C++ standard iterator must be a category based on output iterator");

public:

	CppStdOutIteratorWrap(_OriItType oriIt) :
		_BaseIf::OutputIteratorIf(),
		m_it(oriIt)
	{}

	CppStdOutIteratorWrap(const CppStdOutIteratorWrap& other) :
		_BaseIf::OutputIteratorIf(other),
		m_it(other.m_it)
	{}

	CppStdOutIteratorWrap(CppStdOutIteratorWrap&& other) :
		_BaseIf::OutputIteratorIf(std::forward<_BaseIf>(other)),
		m_it(std::forward<_OriItType>(other.m_it))
	{}

	virtual ~CppStdOutIteratorWrap() = default;

	virtual void Increment() override
	{
		++m_it;
	}

	virtual void Put(const value_type& val) override
	{
		*m_it = val;
	}

	virtual void Put(value_type&& val) override
	{
		*m_it = std::forward<value_type>(val);
	}

	virtual _BaseIfPtr Copy(const _BaseIf&) const override
	{
		// TODO: make_unique
		return _BaseIfPtr(new CppStdOutIteratorWrap(*this));
	}

public:

	_OriItType m_it;
}; // class CppStdOutIteratorWrap

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
		_BaseIf::ForwardIteratorIf(other),
		m_it(other.m_it)
	{}

	CppStdFwIteratorWrap(CppStdFwIteratorWrap&& other) :
		_BaseIf::ForwardIteratorIf(std::forward<_BaseIf>(other)),
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

}//namespace SimpleObjects
