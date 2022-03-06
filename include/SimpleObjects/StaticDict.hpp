// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.



#pragma once

#include <array>

#include "ConstSequence.hpp"
#include "StaticDictBaseObject.hpp"
#include "Utils.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _StrType, char... ch>
class StaticString
{
public: // static members:

	using Self = StaticString<_StrType, ch...>;
	using KSeq = StrSeq<ch...>;

public:
	StaticString() :
		key(KSeq::sk_str())
	{}

	StaticString(const Self& other):
		key(other.key)
	{}

	// No move constructor
	StaticString(Self&& other) = delete;

	~StaticString() = default;

	// No copy assignment
	StaticString& operator=(const Self&) = delete;

	// No Move assignment
	StaticString& operator=(Self&&) = delete;

	bool operator==(const Self&) const
	{
		return true;
	}

	bool operator!=(const Self&) const
	{
		return false;
	}

	const _StrType key;
}; // class StaticString

template<typename _ObjType, typename _ObjType::InternalType _Val>
class StaticPrimitiveValue
{
public: // static members:

	using Self = StaticPrimitiveValue<_ObjType, _Val>;

public:
	StaticPrimitiveValue() :
		key(_Val)
	{}

	StaticPrimitiveValue(const Self& other):
		key(other.key)
	{}

	// No move constructor
	StaticPrimitiveValue(Self&& other) = delete;

	~StaticPrimitiveValue() = default;

	// No copy assignment
	StaticPrimitiveValue& operator=(const Self&) = delete;

	// No Move assignment
	StaticPrimitiveValue& operator=(Self&&) = delete;

	bool operator==(const Self&) const
	{
		return true;
	}

	bool operator!=(const Self&) const
	{
		return false;
	}

	const _ObjType key;

}; // class StaticPrimitiveValue

namespace Internal
{

/**
 * @brief Convert from const data sequence to static string class type
 *
 * @tparam _StrType
 * @tparam _ValType
 * @tparam _data
 */
template<typename _StrType, typename _ValType, _ValType ..._data>
struct FromDataSeqImpl;

template<typename _StrType, char ..._ch>
struct FromDataSeqImpl<_StrType, char, _ch...>
{
	using type = StaticString<_StrType, _ch...>;
}; // struct FromDataSeq

/**
 * @brief Find an element (std::pair) from a given std::tuple based on the type
 *        of the given key
 *
 * @tparam _itemIdx
 * @tparam _Key
 * @tparam _Tp
 */
template<size_t _itemIdx, bool _Found, typename _Key, typename _Tp>
struct DTupleFindElementImpl;

// recursive case: non-zero and not found
template<size_t _itemIdx, typename _Key, typename _Tp>
struct DTupleFindElementImpl<_itemIdx, false, _Key, _Tp>
{
	static constexpr size_t index = DTupleFindElementImpl<
			// Next index
			_itemIdx - 1,
			// is found in next index?
			std::is_same<
				_Key,
				typename std::tuple_element<0,
					typename std::tuple_element<_itemIdx - 1, _Tp>::type
				>::type
			>::value,
			// Key
			_Key,
			// Tuple
			_Tp
		>::index;
}; // struct DTupleFindElementImpl

// base case 1: any index and found
template<size_t _itemIdx, typename _Key, typename _Tp>
struct DTupleFindElementImpl<_itemIdx, true, _Key, _Tp>
{
	static constexpr size_t index = _itemIdx;
}; // struct DTupleFindElementImpl

// base case 2: 0 and not found
template<typename _Key, typename _Tp>
struct DTupleFindElementImpl<0, false, _Key, _Tp>
{
}; // struct DTupleFindElementImpl

template<typename _Key, typename _Tp>
struct DTupleFindElement
{
	static constexpr size_t index = DTupleFindElementImpl<
		std::tuple_size<_Tp>::value, false, _Key, _Tp>::index;
	using type = typename std::tuple_element<1,
			typename std::tuple_element<index, _Tp>::type
		>::type;
}; // struct DTupleFindElement

template<typename _Tp, typename _KeyRefType, typename _ValRefType>
struct DTupleToArray;

template<typename _KeyRefType, typename _ValRefType, typename ..._DPairs>
struct DTupleToArray<std::tuple<_DPairs...>, _KeyRefType, _ValRefType>
{
	using ArrayType = std::array<
		std::pair<_KeyRefType, _ValRefType>,
		sizeof...(_DPairs)
	>;
	using type = ArrayType;

	static ArrayType Callback(_DPairs&... p)
	{
		using ArrayValueType = typename ArrayType::value_type;
		return {
			ArrayValueType(std::get<0>(p).key, std::get<1>(p))...
		};
	}

	static ArrayType Convert(std::tuple<_DPairs...>& tp)
	{
		return Internal::TupleUnpackCall<
				ArrayType, std::tuple<_DPairs...>
			>::UnpackCall(
				tp,
				Callback
			);
	}

}; // struct DTupleToArray

template<
	typename _Tp,
	typename _KeyRefType,
	typename _ValRefType,
	template<typename, typename> typename _MapType>
struct DTupleToMap;

template<
	typename _KeyRefType,
	typename _ValRefType,
	template<typename, typename> typename _MapType,
	typename ..._DPairs>
struct DTupleToMap<
	std::tuple<_DPairs...>,
	_KeyRefType,
	_ValRefType,
	_MapType>
{
	using MapType = _MapType<_KeyRefType,_ValRefType>;
	using type = MapType;

	static MapType Callback(_DPairs&... p)
	{
		using MapValueType = typename MapType::value_type;
		return {
			MapValueType(std::get<0>(p).key, std::get<1>(p))...
		};
	}

	static MapType Convert(std::tuple<_DPairs...>& tp)
	{
		return Internal::TupleUnpackCall<
				MapType, std::tuple<_DPairs...>
			>::UnpackCall(
				tp,
				Callback
			);
	}

}; // struct DTupleToMap

template<typename _Pair>
struct DPairMove;

template<typename _First, typename _Second>
struct DPairMove<std::pair<_First, _Second> >
{
	static std::pair<_First, _Second> Move(std::pair<_First, _Second>&& p)
	{
		return std::pair<_First, _Second>(
			_First(p.first), // copy key
			std::forward<_Second>(p.second) // move value
		);
	}
}; // struct DPairMove

template<typename _Tp>
struct DTupleMove;

template<typename ..._DPairs>
struct DTupleMove<std::tuple<_DPairs...> >
{
	static std::tuple<_DPairs...> MoveCallback(_DPairs&&... p)
	{
		return std::tuple<_DPairs...>(
			DPairMove<_DPairs>::Move(std::forward<_DPairs>(p))...
		);
	}

	static std::tuple<_DPairs...> Move(std::tuple<_DPairs...>&& tp)
	{
		return Internal::TupleUnpackCall<
				std::tuple<_DPairs...>, std::tuple<_DPairs...>
			>::UnpackCall(
				std::forward<std::tuple<_DPairs...> >(tp),
				MoveCallback
			);
	}
};

} // namespace Internal

/**
 * @brief Static Dict type class, where the number of items and key to
 *        value type mapping is static
 *
 * @tparam _Tp             The type of the tuple defining the core data store
 * @tparam _DynKeyType     The key type for the dynamic access API
 * @tparam _DynValType     The value type for the dynamic access API
 * @tparam _KeyRefWrapType A reference wrapper type that supports hash
 *                         (and less than) on its wrapped type
 * @tparam _RefWrapType    A normal reference wrapper type
 * @tparam _MapType        The type of the map used to store the key and value
 *                         reference for dynamic access
 * @tparam _ToStringType   Return type for the ToString method (and the
 *                         container type to be used to store the
 *                         intermediate data)
 */
template<
	typename _Tp,
	typename _DynKeyType,
	typename _DynValType,
	template<typename> typename _KeyRefWrapType,
	template<typename> typename _RefWrapType,
	template<typename, typename> typename _MapType,
	typename _ToStringType>
class StaticDictImpl :
	public StaticDictBaseObject<
		_DynKeyType,
		_DynValType,
		_KeyRefWrapType,
		_RefWrapType,
		_ToStringType>
{
public: // Static members:

	using Self = StaticDictImpl<
		_Tp,
		_DynKeyType,
		_DynValType,
		_KeyRefWrapType,
		_RefWrapType,
		_MapType,
		_ToStringType>;
	using Base = StaticDictBaseObject<
		_DynKeyType,
		_DynValType,
		_KeyRefWrapType,
		_RefWrapType,
		_ToStringType>;
	using ToStringType = _ToStringType;
	using TupleCore = _Tp;

	typedef _DynKeyType                               key_type;
	typedef _DynValType                               mapped_type;
	typedef _KeyRefWrapType<const key_type>           key_const_ref_type;
	typedef _RefWrapType<mapped_type>                 mapped_ref_type;
	typedef _RefWrapType<const mapped_type>           mapped_const_ref_type;

	typedef std::pair<const key_const_ref_type, const mapped_ref_type>
		iterator_value_type;
	typedef std::pair<const key_const_ref_type, const mapped_const_ref_type>
		const_iterator_value_type;
	typedef RdIterator<iterator_value_type,       true>  iterator;
	typedef RdIterator<const_iterator_value_type, true>  const_iterator;

	static constexpr Self* sk_null = nullptr;

	using RefArrayType  = Internal::DTupleToArray<TupleCore,
		const key_const_ref_type,
		const mapped_ref_type>;
	using KRefArrayType = Internal::DTupleToArray<TupleCore,
		const key_const_ref_type,
		const mapped_const_ref_type>;
	using RefMapType    = Internal::DTupleToMap<TupleCore,
		key_const_ref_type,
		mapped_ref_type,
		_MapType>;

	static constexpr size_t sk_size = std::tuple_size<TupleCore>::value;

	template<typename _Key>
	using Get = typename Internal::DTupleFindElement<_Key, TupleCore>::type;

	template<typename _Key>
	using GetRef = typename std::add_lvalue_reference<Get<_Key> >::type;

	template<typename _Key>
	using GetConstRef = typename std::add_lvalue_reference<
		typename std::add_const<Get<_Key> >::type
	>::type;

	static constexpr ObjCategory sk_cat()
	{
		return ObjCategory::StaticDict;
	}

public:

	StaticDictImpl() :
		m_data(),
		m_refArray(RefArrayType::Convert(m_data)),
		m_krefArray(KRefArrayType::Convert(m_data)),
		m_refmap(RefMapType::Convert(m_data))
	{}

	StaticDictImpl(const StaticDictImpl& other) :
		m_data(other.m_data),
		m_refArray(RefArrayType::Convert(m_data)),
		m_krefArray(KRefArrayType::Convert(m_data)),
		m_refmap(RefMapType::Convert(m_data))
	{}

	StaticDictImpl(StaticDictImpl&& other) :
		m_data(
			Internal::DTupleMove<TupleCore>::Move(
				std::forward<TupleCore>(other.m_data))),
		m_refArray(RefArrayType::Convert(m_data)),
		m_krefArray(KRefArrayType::Convert(m_data)),
		m_refmap(RefMapType::Convert(m_data))
	{}

	virtual ~StaticDictImpl() = default;

	template<typename _Key>
	GetRef<_Key> get()
	{
		static constexpr size_t idx =
			Internal::DTupleFindElement<_Key, TupleCore>::index;
		return std::get<idx>(m_data).second;
	}

	template<typename _Key>
	GetConstRef<_Key> get() const
	{
		static constexpr size_t idx =
			Internal::DTupleFindElement<_Key, TupleCore>::index;
		return std::get<idx>(m_data).second;
	}

	virtual bool operator==(const Base& rhs) const override
	{
		if (sk_size != rhs.size())
		{
			return false;
		}

		auto ita = m_krefArray.cbegin();
		auto itb = rhs.cbegin();
		auto itae = m_krefArray.cend();
		auto itbe = rhs.cend();
		for (; ita != itae && itb != itbe; ++ita, ++itb)
		{
			if (ita->first.get() != itb->first.get() ||
				ita->second.get() != itb->second.get())
			{
				return false;
			}
		}
		return true;
	}

	virtual bool operator==(const Self& rhs) const
	{
		return m_data == rhs.m_data;
	}

	virtual bool operator!=(const Self& rhs) const
	{
		return m_data != rhs.m_data;
	}

	virtual iterator begin() override
	{
		return ToRdIt<true>(m_refArray.cbegin());
	}

	virtual iterator end() override
	{
		return ToRdIt<true>(m_refArray.cend());
	}

	virtual const_iterator cbegin() const override
	{
		return ToRdIt<true>(m_krefArray.cbegin());
	}

	virtual const_iterator cend() const override
	{
		return ToRdIt<true>(m_krefArray.cend());
	}

	virtual size_t size() const override
	{
		return sk_size;
	}

	virtual mapped_type& at(const key_type& key) override
	{
		return m_refmap.at(key).get();
	}

	virtual const mapped_type& at(const key_type& key) const override
	{
		return m_refmap.at(key).get();
	}

	virtual mapped_type& operator[](const key_type& key) override
	{
		return at(key);
	}

	virtual const mapped_type& operator[](const key_type& key) const override
	{
		return at(key);
	}

	virtual mapped_type& at(size_t idx) override
	{
		return m_refArray.at(idx).second.get();
	}

	virtual const mapped_type& at(size_t idx) const override
	{
		return m_refArray.at(idx).second.get();
	}

	virtual mapped_type& operator[](size_t idx) override
	{
		return at(idx);
	}

	virtual const mapped_type& operator[](size_t idx) const override
	{
		return at(idx);
	}

	virtual bool HasKey(const key_type& key) const override
	{
		return m_refmap.find(key) != m_refmap.cend();
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

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	virtual std::string DebugString() const override
	{
		std::string res;
		res += '{';
		res += ' ';
		size_t i = 0;
		for (const auto& item : m_krefArray)
		{
			res += item.first.get().DebugString();
			res += " : ";
			res += item.second.get().DebugString();
			if (i < sk_size - 1)
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
		for (const auto& item : m_krefArray)
		{
			res += item.first.get().ShortDebugString();
			res += ":";
			res += item.second.get().ShortDebugString();
			if (i < sk_size - 1)
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
		for (const auto& item : m_krefArray)
		{
			res += item.first.get().ToString();
			res += Internal::ToString<ToStringType>(" : ");
			res += item.second.get().ToString();
			if (i < sk_size - 1)
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
		for (const auto& item : m_krefArray)
		{
			item.first.get().DumpString(outIt);
			*outIt++ = ' ';
			*outIt++ = ':';
			*outIt++ = ' ';
			item.second.get().DumpString(outIt);
			if (i < sk_size - 1)
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

	_Tp m_data;
	typename RefArrayType::type m_refArray;
	typename KRefArrayType::type m_krefArray;
	typename RefMapType::type m_refmap;

}; // class StaticDictImpl

} // namespace SimpleObjects
