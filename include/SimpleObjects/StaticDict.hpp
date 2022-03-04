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

template<typename _StrType, char... chars>
class StaticString
{}; // class StaticString

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
struct TupleFindElementImpl;

// recursive case: non-zero and not found
template<size_t _itemIdx, typename _Key, typename _Tp>
struct TupleFindElementImpl<_itemIdx, false, _Key, _Tp>
{
	using type = typename TupleFindElementImpl<
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
		>::type;
}; // struct TupleFindElementImpl

// base case 1: any index and found
template<size_t _itemIdx, typename _Key, typename _Tp>
struct TupleFindElementImpl<_itemIdx, true, _Key, _Tp>
{
	using type = typename std::tuple_element<1,
			typename std::tuple_element<_itemIdx, _Tp>::type
		>::type;
}; // struct TupleFindElementImpl

// base case 2: 0 and not found
template<typename _Key, typename _Tp>
struct TupleFindElementImpl<0, false, _Key, _Tp>
{
}; // struct TupleFindElementImpl

template<typename _Key, typename _Tp>
struct TupleFindElement
{
	using type = typename TupleFindElementImpl<
		std::tuple_size<_Tp>::value, false, _Key, _Tp>::type;
}; // struct TupleFindElement

class StaticDict
{

};

namespace Internal
{

} // namespace Internal
} // namespace SimpleObjects
