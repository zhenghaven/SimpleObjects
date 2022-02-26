#pragma once

#include "BaseObject.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _KeyType, typename _ValType, typename _ToStringType>
class DictBaseObject : public BaseObject<_ToStringType>
{
public: // Static members

	using Self = DictBaseObject<_KeyType, _ValType, _ToStringType>;
	using Base = BaseObject<_ToStringType>;
	using ToStringType = _ToStringType;

	typedef _KeyType                                  key_type;
	typedef _ValType                                  mapped_type;
	typedef std::pair<const key_type, mapped_type>    value_type;
	typedef value_type&                               reference;
	typedef const value_type&                         const_reference;
	typedef FrIterator<value_type, false>             iterator;
	typedef FrIterator<value_type, true>              const_iterator;

	static constexpr Self* sk_null = nullptr;

public:
	DictBaseObject() = default;

	// LCOV_EXCL_START
	/**
	 * @brief Destroy the Dict Base Object
	 *
	 */
	virtual ~DictBaseObject() = default;
	// LCOV_EXCL_STOP

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

	using Base::operator==;
	using Base::operator!=;
	using Base::operator<;
	using Base::operator>;
	using Base::operator<=;
	using Base::operator>=;

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

	virtual mapped_type& at(const key_type& key) = 0;

	virtual const mapped_type& at(const key_type& key) const = 0;

	virtual mapped_type& operator[](const key_type& key) = 0;

	virtual const_iterator find(const key_type& key) const = 0;

	virtual iterator find(const key_type& key) = 0;

	virtual bool HasKey(const key_type& key) const = 0;

	virtual std::pair<iterator, bool> InsertOnly(
		const key_type& key, const mapped_type& other) = 0;

	virtual std::pair<iterator, bool> InsertOrAssign(
		const key_type& key, const mapped_type& other) = 0;

	virtual void Remove(const key_type& key) = 0;

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

}; // class DictBaseObject

} //namespace SimpleObjects
