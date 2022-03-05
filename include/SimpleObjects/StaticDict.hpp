// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.



#pragma once

#include "ConstSequence.hpp"
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

	using KSeq = StrSeq<ch...>;

public:
	StaticString() :
		key(KSeq::sk_str())
	{}

	StaticString(const StaticString& other):
		key(other.key)
	{}

	// No move constructor
	StaticString(StaticString&& other) = delete;

	~StaticString() = default;

	// No copy assignment
	StaticString& operator=(const StaticString&) = delete;

	// No Move assignment
	StaticString& operator=(StaticString&&) = delete;

	const _StrType key;
}; // class StaticString

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
struct DTupleToArray
{
	using ArrayType = std::array<
		std::pair<_KeyRefType, _ValRefType>,
		std::tuple_size<_Tp>::value
	>;

	struct ItemFuncType {
		template <typename ItemType>
		typename ArrayType::value_type
		operator()(ItemType& item) const
		{
			return typename ArrayType::value_type(
				std::get<0>(item).key,
				std::get<1>(item)
			);
		}
	}; // struct ItemFuncType

	static ArrayType Convert(_Tp& tp)
	{
		return Internal::TupleToAggregate<ArrayType, _Tp>::Convert(
			tp,
			ItemFuncType()
		);
	}
}; // struct DTupleToArray

template<
	typename _Tp,
	typename _KeyRefType,
	typename _ValRefType,
	template<typename, typename> typename _MapType>
struct DTupleToMap
{
	using MapType = _MapType<_KeyRefType,_ValRefType>;

	struct ItemFuncType {
		template <typename ItemType>
		typename MapType::value_type
		operator()(ItemType& item) const
		{
			return typename MapType::value_type(
				std::get<0>(item).key,
				std::get<1>(item)
			);
		}
	}; // struct ItemFuncType

	static MapType Convert(_Tp& tp)
	{
		return Internal::TupleToAggregate<MapType, _Tp>::Convert(
			tp,
			ItemFuncType()
		);
	}
}; // struct DTupleToMap

} // namespace Internal

//template<typename
class StaticDict
{

};
} // namespace SimpleObjects
