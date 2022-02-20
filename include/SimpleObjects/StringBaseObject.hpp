#pragma once

#include "HashableBaseObject.hpp"

#include "Iterator.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

/**
 * @brief Defining a interface class for objects that are string-like
 *
 * @tparam _CharType type of each charactor value.
 */
template<typename _CharType>
class StringBaseObject : public HashableBaseObject
{
public: // Static members

	using Self = StringBaseObject<_CharType>;
	using Base = HashableBaseObject;

	typedef _CharType                           value_type;
	typedef value_type&                         reference;
	typedef const value_type&                   const_reference;
	typedef value_type*                         pointer;
	typedef const value_type*                   const_pointer;
	typedef RdIterator<value_type, false>       iterator;
	typedef RdIterator<value_type, true>        const_iterator;

	static constexpr Self* sk_null = nullptr;

public:
	StringBaseObject() = default;

	virtual ~StringBaseObject() = default;

	virtual const char* GetCategoryName() const override
	{
		return "String";
	}

	virtual StringBase& AsString() override
	{
		return *this;
	}

	virtual const StringBase& AsString() const override
	{
		return *this;
	}

	virtual std::unique_ptr<StringBaseObject> Copy(const StringBaseObject* /*unused*/) const = 0;

	virtual std::unique_ptr<StringBaseObject> Move(const StringBaseObject* /*unused*/) = 0;

	using Base::Copy;
	virtual std::unique_ptr<Base> Copy(const Base* /*unused*/) const override
	{
		return Copy(sk_null);
	}

	using Base::Move;
	virtual std::unique_ptr<Base> Move(const Base* /*unused*/) override
	{
		return Move(sk_null);
	}

	virtual size_t Len() const = 0;

	virtual iterator begin() = 0;
	virtual iterator end() = 0;

	virtual const_iterator cbegin() const = 0;
	virtual const_iterator cend() const = 0;

	virtual iterator rbegin() = 0;
	virtual iterator rend() = 0;

	virtual const_iterator crbegin() const = 0;
	virtual const_iterator crend() const = 0;

	virtual const_iterator begin() const
	{
		return this->cbegin();
	}

	virtual const_iterator end() const
	{
		return this->cend();
	}

	virtual reference At(size_t idx) = 0;

	virtual const_reference At(size_t idx) const = 0;

	virtual reference operator[](size_t idx)
	{
		return this->At(idx);
	}

	virtual const_reference operator[](size_t idx) const
	{
		return this->At(idx);
	}

	virtual bool StartsWith(const_iterator begin,
		const_iterator end) const = 0;

	virtual bool StartsWith(const Self& other) const
	{
		if (this->Len() < other.Len())
		{
			return false;
		}
		return this->StartsWith(other.cbegin(), other.end());
	}

	virtual bool EndsWith(
		const_iterator begin, const_iterator end) const = 0;

	virtual bool EndsWith(const Self& other) const
	{
		if (this->Len() < other.Len())
		{
			return false;
		}
		return this->EndsWith(other.cbegin(), other.end());
	}

	virtual const_iterator Contains(
		const_iterator begin, const_iterator end) const = 0;

	virtual const_iterator Contains(const Self& other) const
	{
		if (this->Len() < other.Len())
		{
			return cend();
		}
		return this->Contains(other.cbegin(), other.end());
	}

	virtual void PushBack(const_reference ch) = 0;

	virtual void PopBack() = 0;

	virtual void Append(const_iterator begin,
		const_iterator end) = 0;

	virtual void Append(const Self& other)
	{
		return this->Append(other.cbegin(), other.cend());
	}

	virtual const_pointer CStr() const = 0;

	virtual void Resize(size_t len) = 0;

	virtual void Reserve(size_t len) = 0;

	//virtual std::unique_ptr<Self> Copy() const = 0;

	//virtual std::unique_ptr<Self> Slice(size_t begin, size_t end) const = 0;

	virtual bool operator==(const Self& rhs) const = 0;

	virtual bool operator>(const Self& rhs) const = 0;

	virtual bool operator<(const Self& rhs) const = 0;

	virtual bool operator!=(const Self& rhs) const
	{
		return !(*this == rhs);
	}

	virtual bool operator<=(const Self& rhs) const
	{
		return !(*this > rhs);
	}

	virtual bool operator>=(const Self& rhs) const
	{
		return !(*this < rhs);
	}

	virtual Self& operator+=(const Self& rhs)
	{
		this->Append(rhs);
		return *this;
	}

	/**
	 * @brief lexicographical compare this string with the other
	 *
	 * @param pos1   the begin position of this string
	 * @param count1 the length since the begin position to be compared
	 * @param begin  the begin of the other string
	 * @param end    the end of the other string
	 * @return compare result
	 */
	virtual bool LessThan(size_t pos1, size_t count1,
		const_pointer begin, const_pointer end) const = 0;

	virtual bool GreaterThan(size_t pos1, size_t count1,
		const_pointer begin, const_pointer end) const = 0;

	virtual bool Equal(size_t pos1, size_t count1,
		const_pointer begin, const_pointer end) const = 0;

}; // class StringBaseObject

}//namespace SimpleObjects