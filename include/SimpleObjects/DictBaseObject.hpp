// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "BaseObject.hpp"
#include "HashableBaseObject.hpp"

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

	using DictBase = typename Base::DictBase;

	typedef _KeyType                                  key_type;
	typedef _ValType                                  mapped_type;

	typedef FrIterator<key_type, true>                key_iterator;
	typedef FrIterator<mapped_type, false>            mapped_iterator;
	typedef FrIterator<mapped_type, true>             const_mapped_iterator;

	typedef FrIterator<std::tuple<key_iterator, mapped_iterator>, false>
		                                              iterator;
	typedef FrIterator<std::tuple<key_iterator, const_mapped_iterator>, true>
		                                              const_iterator;

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

	virtual DictBase& AsDict() override
	{
		return Internal::AsChildType<
				std::is_same<Self, DictBase>::value, Self, DictBase
			>::AsChild(*this, "Dict", this->GetCategoryName());
	}

	virtual const DictBase& AsDict() const override
	{
		return Internal::AsChildType<
				std::is_same<Self, DictBase>::value, Self, DictBase
			>::AsChild(*this, "Dict", this->GetCategoryName());
	}

	// ========== operators ==========

	virtual bool operator==(const Self& rhs) const
	{
		// reference: https://github.com/llvm/llvm-project/blob/main/libcxx/include/unordered_map#L1877

		if (size() != rhs.size())
		{
			return false;
		}
		auto xi = begin();
		auto xe = end();
		auto ye = rhs.ValsCEnd();
		for (; xi != xe; ++xi)
		{
			auto yj = rhs.FindVal((*std::get<0>(*xi)));
			if (yj == ye || !((*std::get<1>(*xi)) == *yj))
			{
				return false;
			}
		}
		return true;
	}

	virtual bool operator!=(const Self& rhs) const
	{
		return !(*this == rhs);
	}

	bool operator<(const Self& rhs) = delete;
	bool operator>(const Self& rhs) = delete;
	bool operator<=(const Self& rhs) = delete;
	bool operator>=(const Self& rhs) = delete;

	virtual bool operator==(const Base& rhs) const override
	{
		if (rhs.GetCategory() != ObjCategory::Dict)
		{
			return false;
		}
		return *this == rhs.AsDict();
	}

	using Base::operator!=;

	virtual bool operator<(const Base& rhs) const override
	{
		throw UnsupportedOperation("<",
			this->GetCategoryName(), rhs.GetCategoryName());
	}

	virtual bool operator>(const Base& rhs) const override
	{
		throw UnsupportedOperation(">",
			this->GetCategoryName(), rhs.GetCategoryName());
	}

	using Base::operator<=;
	using Base::operator>=;

	// ========== Functions that doesn't have value_type in prototype ==========

	virtual size_t size() const = 0;

	// ========== Functions that involves value_type in prototype ==========

	mapped_type& operator[](const key_type& key)
	{
		auto it = DictBaseFindValOrAddDefault(key);
		return *it;
	}

	const mapped_type& operator[](const key_type& key) const
	{
		auto it = FindVal(key);
		if (it != ValsCEnd())
		{
			return *it;
		}
		throw KeyError(key.ShortDebugString(), KeyError::sk_keyName);
	}

	const_mapped_iterator FindVal(const key_type& key) const
	{
		return DictBaseFindVal(key);
	}

	mapped_iterator FindVal(const key_type& key)
	{
		return DictBaseFindVal(key);
	}

	bool HasKey(const key_type& key) const
	{
		return FindVal(key) != ValsCEnd();
	}

	bool InsertOnly(const key_type& key, const mapped_type& val)
	{
		return DictBaseInsertOnly(key, val);
	}

	bool InsertOnly(key_type&& key, mapped_type&& val)
	{
		return DictBaseInsertOnly(
			std::forward<key_type>(key),
			std::forward<mapped_type>(val));
	}

	bool InsertOrAssign(const key_type& key, const mapped_type& val)
	{
		return DictBaseInsertOrAssign(key, val);
	}

	bool InsertOrAssign(key_type&& key, mapped_type&& val)
	{
		return DictBaseInsertOrAssign(
			std::forward<key_type>(key),
			std::forward<mapped_type>(val));
	}

	void Remove(const key_type& key)
	{
		return DictBaseRemove(key);
	}

	// ========== iterators ==========

	virtual key_iterator KeysBegin() const = 0;

	virtual key_iterator KeysEnd() const = 0;

	virtual const_mapped_iterator ValsCBegin() const = 0;

	virtual const_mapped_iterator ValsCEnd() const = 0;

	virtual const_mapped_iterator ValsBegin() const
	{
		return ValsCBegin();
	}

	virtual const_mapped_iterator ValsEnd() const
	{
		return ValsCEnd();
	}

	virtual mapped_iterator ValsBegin() = 0;

	virtual mapped_iterator ValsEnd() = 0;

	iterator begin()
	{
		return FwItZip<false>(KeysBegin(), ValsBegin());
	}

	iterator end()
	{
		return FwItZip<false>(KeysEnd(), ValsEnd());
	}

	const_iterator cbegin() const
	{
		return FwItZip<true>(KeysBegin(), ValsCBegin());
	}

	const_iterator cend() const
	{
		return FwItZip<true>(KeysEnd(), ValsCEnd());
	}

	const_iterator begin() const
	{
		return cbegin();
	}

	const_iterator end() const
	{
		return cend();
	}

	// ========== Copy and Move ==========

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

protected:

	virtual const_mapped_iterator DictBaseFindVal(
		const key_type& key) const = 0;

	virtual mapped_iterator DictBaseFindVal(const key_type& key) = 0;

	virtual mapped_iterator DictBaseFindValOrAddDefault(
		const key_type& key) = 0;

	virtual bool DictBaseInsertOnly(
		const key_type& key, const mapped_type& val) = 0;

	virtual bool DictBaseInsertOnly(key_type&& key, mapped_type&& val) = 0;

	virtual bool DictBaseInsertOrAssign(
		const key_type& key, const mapped_type& val) = 0;

	virtual bool DictBaseInsertOrAssign(
		key_type&& key, mapped_type&& val) = 0;

	virtual void DictBaseRemove(const key_type& key) = 0;

}; // class DictBaseObject

} //namespace SimpleObjects
