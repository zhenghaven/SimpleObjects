// Copyright (c) 2023 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once


#include <array>

#include "HexUtils.hpp"


#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{
namespace Codec
{


namespace Internal
{


template<typename _ValType>
struct  HexUpperCaseAlphabet
{
	using value_type = _ValType;

	static constexpr std::array<_ValType, 16> Alphabet()
	{
		return {
			'0', '1', '2', '3', '4', '5', '6', '7',
			'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
		};
	}
}; // struct HexUpperCaseAlphabet

template<typename _ValType>
struct  HexLowerCaseAlphabet
{
	using value_type = _ValType;

	static constexpr std::array<_ValType, 16> Alphabet()
	{
		return {
			'0', '1', '2', '3', '4', '5', '6', '7',
			'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
		};
	}
}; // struct HexLowerCaseAlphabet


template<bool _KeepLeadingZero, typename _Alphabet>
struct HexEncodeSingleImpl;

template<typename _Alphabet>
struct HexEncodeSingleImpl<true, _Alphabet>
{
	using Alphabet = _Alphabet;

	template<typename _OutIt, typename _NibbleType>
	static _OutIt Encode(
		_OutIt destIt,
		_NibbleType nibble1,
		_NibbleType nibble2
	)
	{
		static constexpr auto sk_lut = Alphabet::Alphabet();

		// we want to keep both nibbles, no matter they are zeros or not
		*destIt++ = sk_lut[nibble1];
		*destIt++ = sk_lut[nibble2];

		return destIt;
	}
}; // struct HexEncodeSingleImpl<true>

template<typename _Alphabet>
struct HexEncodeSingleImpl<false, _Alphabet>
{
	using Alphabet = _Alphabet;

	template<typename _OutIt, typename _NibbleType>
	static _OutIt Encode(
		_OutIt destIt,
		_NibbleType nibble1,
		_NibbleType nibble2
	)
	{
		static constexpr auto sk_lut = Alphabet::Alphabet();

		if (nibble1 != 0)
		{
			// both nibbles are meaningful
			*destIt++ = sk_lut[nibble1];
			*destIt++ = sk_lut[nibble2];
		}
		else if (nibble2 != 0)
		{
			// only the second nibble is meaningful
			*destIt++ = sk_lut[nibble2];
		}
		// else both nibbles are zero, do nothing

		return destIt;
	}
}; // struct HexEncodeSingleImpl<false>


template<bool _KeepLeadingZero>
struct HexEncodeSkipZerosImpl;

template<>
struct HexEncodeSkipZerosImpl<true>
{
	template<typename _InIt>
	static _InIt Encode(_InIt begin, _InIt /* end */)
	{
		// Dont't skip
		return begin;
	}
}; // struct HexEncodeSkipZerosImpl<true>

template<>
struct HexEncodeSkipZerosImpl<false>
{
	template<typename _InIt>
	static _InIt Encode(_InIt begin, _InIt end)
	{
		while (begin != end && *begin == 0)
		{
			++begin;
		}
		return begin;
	}
}; // struct HexEncodeSkipZerosImpl<false>


} // namespace Internal


} // namespace Codec
} // namespace SimpleObjects
