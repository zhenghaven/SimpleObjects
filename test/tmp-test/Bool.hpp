#pragma once

#include "BaseObject.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

class Bool : public BaseObject
{
public: // Static member:

	static constexpr ObjCategory sk_cat()
	{
		return ObjCategory::Bool;
	}

	using _InternalType = bool;

public:

	Bool() :
		m_data(static_cast<_InternalType>(0))
	{}

	Bool(const _InternalType& other) :
		m_data(other)
	{}

	Bool(_InternalType&& other) noexcept :
		m_data(std::forward<_InternalType>(other))
	{}

	Bool(const Bool& other) :
		m_data(other.m_data)
	{}

	Bool(Bool&& other) noexcept :
		m_data(std::forward<_InternalType>(other.m_data))
	{}

	virtual ~Bool() = default;

	operator bool() const
	{
		return m_data;
	}

	Bool& operator=(const _InternalType& rhs)
	{
		m_data = rhs;

		return *this;
	}

	Bool& operator=(_InternalType&& rhs) noexcept
	{
		m_data = std::forward<_InternalType>(rhs);

		return *this;
	}

	Bool& operator=(const Bool& rhs)
	{
		m_data = rhs.m_data;

		return *this;
	}

	Bool& operator=(Bool&& rhs) noexcept
	{
		m_data = std::forward<_InternalType>(rhs.m_data);

		return *this;
	}

	bool operator==(const _InternalType& rhs) const
	{
		return m_data == rhs;
	}

	bool operator!=(const _InternalType& rhs) const
	{
		return m_data != rhs;
	}

	bool operator==(const Bool& rhs) const
	{
		return m_data == rhs.m_data;
	}

	bool operator!=(const Bool& rhs) const
	{
		return m_data != rhs.m_data;
	}

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	const _InternalType& GetVal() const
	{
		return m_data;
	}

private:

	_InternalType m_data;
}; //class Bool

inline bool operator==(const Bool::_InternalType& lhs, const Bool& rhs)
{
	return rhs == lhs;
}

inline bool operator!=(const Bool::_InternalType& lhs, const Bool& rhs)
{
	return rhs != lhs;
}

}//namespace SimpleObjects
