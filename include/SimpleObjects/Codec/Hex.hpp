// Copyright (c) 2023 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once


#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <array>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>


#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{
namespace Codec
{


enum class HexPad : uint8_t
{
	Disabled,
	Front,
}; // enum class HexPad


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


template<
	typename _ValType,
	typename _CharType
>
struct HexValueLut
{
	using value_type = _ValType;

	using CharType = _CharType;

	static constexpr value_type GetValue(CharType ch)
	{
		return (ch >= '0' && ch <= '9') ? (ch - '0') :
			(ch >= 'A' && ch <= 'F') ? (ch - 'A' + 10) :
			(ch >= 'a' && ch <= 'f') ? (ch - 'a' + 10) :
			throw std::invalid_argument("Invalid hex character");
	}
}; // struct HexValueLut


template<typename _It>
inline void BitWiseShiftBytesRight(_It begin, _It end, size_t shift)
{
	using _InputValType = typename std::iterator_traits<_It>::value_type;

	if (shift == 0 || shift > 8)
	{
		throw std::invalid_argument("Invalid shift value");
	}
	const size_t shiftComplement = 8 - shift;

	auto shiftedBits = _InputValType();

	while (begin != end)
	{
		auto currVal = *begin;
		*begin++ = (currVal >> shift) | shiftedBits;
		shiftedBits = currVal << shiftComplement;
	}
}


template<
	typename _Alphabet,
	size_t _InputValSize
>
struct BytesToHexImpl;

template<
	typename _Alphabet
>
struct BytesToHexImpl<_Alphabet, 1>
{
	using Alphabet = _Alphabet;
	using AlphabetValType = typename Alphabet::value_type;

	static constexpr size_t sk_inputValSize = 1;

	template<
		bool     _KeepLeadingZero,
		typename _OutIt,
		typename _InValType,
		typename _PrefixType
	>
	static _OutIt EncodeSingle(
		_OutIt destIt,
		const _InValType& val,
		const _PrefixType& prefix
	)
	{
		static_assert(
			std::is_integral<_InValType>::value &&
				sizeof(_InValType) == sk_inputValSize,
			"Only support encoding of 1-byte integral type"
		);

		static constexpr auto sk_lut = Alphabet::Alphabet();

		// Add prefix
		destIt = std::copy(std::begin(prefix), std::end(prefix), destIt);

		// the first nibble (half of byte)
		auto firstNibble = (val >> 4) & 0x0F;
		auto secondNibble = val       & 0x0F;

		if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
			constexpr
#endif
		(_KeepLeadingZero)
		{
			// we want to keep both nibbles, no matter they are zeros or not
			*destIt++ = sk_lut[firstNibble];
			*destIt++ = sk_lut[secondNibble];
		}
		else
		{
			if (firstNibble != 0)
			{
				// both nibbles are meaningful
				*destIt++ = sk_lut[firstNibble];
				*destIt++ = sk_lut[secondNibble];
			}
			else if (secondNibble != 0)
			{
				// only the second nibble is meaningful
				*destIt++ = sk_lut[secondNibble];
			}
			// else both nibbles are zero, do nothing
		}

		return destIt;
	}


	template<
		bool     _KeepLeadingZero,
		typename _OutIt,
		typename _InIt,
		typename _PrefixType
	>
	static _OutIt Encode(
		_OutIt destIt,
		_InIt begin,
		_InIt end,
		const _PrefixType& prefix
	)
	{
		// skip leading zeros if needed
		if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
			constexpr
#endif
		(!_KeepLeadingZero)
		{
			while (begin != end && *begin == 0)
			{
				++begin;
			}
		}

		// first byte
		if (begin != end)
		{
			auto val = *begin++;
			using _InValType =
				typename std::remove_reference<decltype(val)>::type;

			destIt =
				EncodeSingle<_KeepLeadingZero, _OutIt, _InValType, _PrefixType>(
					destIt,
					val,
					prefix
				);
		}

		// the rest of bytes
		while (begin != end)
		{
			auto val = *begin++;
			using _InValType =
				typename std::remove_reference<decltype(val)>::type;

			destIt = EncodeSingle<true, _OutIt, _InValType, _PrefixType>(
				destIt,
				val,
				_PrefixType()
			);
		}

		return destIt;
	}

}; // struct BytesToHexImpl<_Alphabet, 1>



template<
	typename _HexValueLut,
	size_t _OutputValSize
>
struct HexToBytesImpl;


template<typename _HexValueLut>
struct HexToBytesImpl<_HexValueLut, 1>
{
	using HexValueLut = _HexValueLut;
	static constexpr size_t sk_outputValSize = 1;


	template<
		typename _OutputType,
		typename _InputCharType
	>
	static _OutputType DecodeSingle(
		const _InputCharType& nibbleCh1,
		const _InputCharType& nibbleCh2
	)
	{
		static_assert(
			std::is_integral<_OutputType>::value &&
				sizeof(_OutputType) == sk_outputValSize,
			"Only support decoding to 1-byte integral type"
		);

		auto nibble1 = HexValueLut::GetValue(nibbleCh1);
		auto nibble2 = HexValueLut::GetValue(nibbleCh2);

		return (nibble1 << 4) | nibble2;
	}


	template<
		bool     _KeepLeadingZeroBytes,
		HexPad   _PadOpt, // ignored
		typename _DestValType,
		typename _OutIt,
		typename _InIt
	>
	static _OutIt Decode(
		_OutIt destIt,
		_InIt begin,
		_InIt end,
		size_t& outDecodedSize,
		std::input_iterator_tag
	)
	{
		// skip leading zeros if needed
		if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
			constexpr
#endif
		(!_KeepLeadingZeroBytes)
		{
			while (begin != end)
			{
				auto nibbleCh1  = *begin++;
				outDecodedSize += 1;

				using _InputCharType =
					typename std::remove_reference<decltype(nibbleCh1)>::type;

				auto nibbleCh2 = _InputCharType('0');
				if (begin != end)
				{
					nibbleCh2 = *begin++;
					outDecodedSize += 1;
				}

				if (nibbleCh1 != '0' || nibbleCh2 != '0')
				{
					// we found the first non-zero byte
					*destIt++ =
						DecodeSingle<_DestValType, _InputCharType>(
							nibbleCh1,
							nibbleCh2
						);
					break;
				}
				// else both nibbles are zero, skip
			}
		}

		while (begin != end)
		{
			auto nibbleCh1  = *begin++;
			outDecodedSize += 1;

			using _InputCharType =
				typename std::remove_reference<decltype(nibbleCh1)>::type;

			auto nibbleCh2 = _InputCharType('0');
			if (begin != end)
			{
				nibbleCh2 = *begin++;
				outDecodedSize += 1;
			}

			*destIt++ =
				DecodeSingle<_DestValType, _InputCharType>(
					nibbleCh1,
					nibbleCh2
				);
		}

		return destIt;
	}


	template<
		bool     _KeepLeadingZeroBytes,
		HexPad   _PadOpt,
		typename _DestValType,
		typename _OutIt,
		typename _InIt,
		typename std::enable_if<
			_PadOpt == HexPad::Disabled || _PadOpt == HexPad::Front,
			int
		>::type = 0
	>
	static _OutIt Decode(
		_OutIt destIt,
		_InIt begin,
		_InIt end,
		size_t& outDecodedSize,
		std::random_access_iterator_tag
	)
	{
		auto inputSize = end - begin;

		if ((begin != end) && (inputSize % 2 != 0))
		{
			// input is not empty, AND
			// there're odd number of bytes,
			// where the first byte is a single nibble

			if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
				constexpr
#endif
			(_PadOpt == HexPad::Disabled)
			{
				throw std::invalid_argument(
					"Odd number of characters in input string"
				);
			}

			if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
				constexpr
#endif
			(_PadOpt == HexPad::Front)
			{
				// Thus, we need to pad it with a zero

				auto nibbleCh2 = *begin++;
				outDecodedSize += 2;

				using _InputCharType =
					typename std::remove_reference<decltype(nibbleCh2)>::type;

				if(
					(_KeepLeadingZeroBytes) || // we want to keep leading zero bytes
					(nibbleCh2 != '0') // OR, the first byte is not zero
				)
				{
					*destIt++ =
						DecodeSingle<_DestValType, _InputCharType>(
							_InputCharType('0'),
							nibbleCh2
						);
				}
			}
		}

		// now the rest of number bytes should be even
		// use the regular function to decode the rest
		return Decode<_KeepLeadingZeroBytes, HexPad::Disabled, _DestValType>(
			destIt,
			begin,
			end,
			outDecodedSize,
			std::input_iterator_tag()
		);
	}


	template<
		bool     _KeepLeadingZeroBytes,
		HexPad   _PadOpt,
		typename _DestValType,
		typename _OutIt,
		typename _InIt
	>
	static _OutIt Decode(
		_OutIt destIt,
		_InIt begin,
		_InIt end,
		size_t& outDecodedSize
	)
	{
		return Decode<_KeepLeadingZeroBytes, _PadOpt, _DestValType>(
			destIt,
			begin,
			end,
			outDecodedSize,
			typename std::iterator_traits<_InIt>::iterator_category()
		);
	}
}; // struct HexToBytesImpl<_HexValueLut, 1>


inline constexpr bool HexDecodeCanPadInPlace(std::input_iterator_tag)
{
	return false;
}

inline constexpr bool HexDecodeCanPadInPlace(std::random_access_iterator_tag)
{
	return true;
}

template<typename _InIt>
inline constexpr bool HexDecodeCanPadInPlace()
{
	return HexDecodeCanPadInPlace(
		typename std::iterator_traits<_InIt>::iterator_category()
	);
}


template<
	typename _Alphabet,
	typename _HexValueLut
>
struct Hex
{
	using Alphabet = _Alphabet;
	using AlphabetValType = typename Alphabet::value_type;
	using PrefixType = std::basic_string<AlphabetValType>;

	using HexValueLut = _HexValueLut;


	//==========
	// Encoding functions
	//==========


	template<
		typename _OutContainer,
		bool     _KeepLeadingZero,
		typename _InContainer,
		typename std::enable_if<
			sizeof(typename _InContainer::value_type) == 1,
			int
		>::type = 0
	>
	static _OutContainer Encode(
		const _InContainer& src,
		const PrefixType& prefix = PrefixType()
	)
	{
		static constexpr size_t sk_inValTypeSize =
			sizeof(typename _InContainer::value_type);

		_OutContainer dest;
		dest.reserve(src.size() * 2 + prefix.size());

		BytesToHexImpl<Alphabet, sk_inValTypeSize>::
			template Encode<_KeepLeadingZero>(
				std::back_inserter(dest),
				std::begin(src),
				std::end(src),
				prefix
			);

		return dest;
	}

	template<
		typename _OutContainer,
		typename _InContainer,
		typename std::enable_if<
			sizeof(typename _InContainer::value_type) == 1,
			int
		>::type = 0
	>
	static _OutContainer Encode(
		const _InContainer& src,
		const PrefixType& prefix = PrefixType()
	)
	{
		// default to keep leading zeros
		return Encode<_OutContainer, true>(src, prefix);
	}


	template<
		typename _OutContainer,
		bool     _KeepLeadingZero,
		typename _InIt,
		typename std::enable_if<
			sizeof(typename std::iterator_traits<_InIt>::value_type) == 1,
			int
		>::type = 0
	>
	static _OutContainer Encode(
		_InIt begin,
		_InIt end,
		const PrefixType& prefix = PrefixType()
	)
	{
		static constexpr size_t sk_inValTypeSize =
			sizeof(typename std::iterator_traits<_InIt>::value_type);

		_OutContainer dest;

		BytesToHexImpl<Alphabet, sk_inValTypeSize>::
			template Encode<_KeepLeadingZero>(
				std::back_inserter(dest),
				begin,
				end,
				prefix
			);

		return dest;
	}


	template<
		typename _OutContainer,
		typename _InIt,
		typename std::enable_if<
			sizeof(typename std::iterator_traits<_InIt>::value_type) == 1,
			int
		>::type = 0
	>
	static _OutContainer Encode(
		_InIt begin,
		_InIt end,
		const PrefixType& prefix = PrefixType()
	)
	{
		// default to keep leading zeros
		return Encode<_OutContainer, true>(begin, end, prefix);
	}


	template<
		bool     _KeepLeadingZero,
		typename _OutIt,
		typename _InIt,
		typename std::enable_if<
			sizeof(typename std::iterator_traits<_InIt>::value_type) == 1,
			int
		>::type = 0
	>
	static _OutIt Encode(
		_OutIt destIt,
		_InIt begin,
		_InIt end,
		const PrefixType& prefix = PrefixType()
	)
	{
		static constexpr size_t sk_inValTypeSize =
			sizeof(typename std::iterator_traits<_InIt>::value_type);

		return BytesToHexImpl<Alphabet, sk_inValTypeSize>::
			template Encode<_KeepLeadingZero>(
				destIt,
				begin,
				end,
				prefix
			);
	}


	template<
		typename _OutIt,
		typename _InIt,
		typename std::enable_if<
			sizeof(typename std::iterator_traits<_InIt>::value_type) == 1,
			int
		>::type = 0
	>
	static _OutIt Encode(
		_OutIt destIt,
		_InIt begin,
		_InIt end,
		const PrefixType& prefix = PrefixType()
	)
	{
		// default to keep leading zeros
		return Encode<true>(destIt, begin, end, prefix);
	}


	//==========
	// Decoding functions
	//==========


	template<
		typename _OutContainer,
		bool     _KeepLeadingZero,
		HexPad   _PadOpt,
		typename _InContainer,
		typename std::enable_if<
			(sizeof(typename _OutContainer::value_type) == 1) &&
			(_PadOpt == HexPad::Disabled || _PadOpt == HexPad::Front),
			int
		>::type = 0
	>
	static _OutContainer Decode(
		const _InContainer& src
	)
	{
		using _OutputValType = typename _OutContainer::value_type;
		static constexpr size_t sk_outputValSize = sizeof(_OutputValType);
		using _InItType = typename _InContainer::const_iterator;
		static constexpr bool sk_canPadInPlace =
			HexDecodeCanPadInPlace<_InItType>();


		if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
		constexpr
#endif
		(_PadOpt == HexPad::Disabled)
		{
			if (src.size() % 2 != 0)
			{
				throw std::invalid_argument("Odd number of hex digits");
			}
		}

		_OutContainer dest;
		dest.reserve((src.size() + 1) / 2);

		size_t decodedSize = 0;
		HexToBytesImpl<HexValueLut, sk_outputValSize>::
			template Decode<_KeepLeadingZero, _PadOpt, _OutputValType>(
				std::back_inserter(dest),
				std::begin(src),
				std::end(src),
				decodedSize
			);

		if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
		constexpr
#endif
		(!sk_canPadInPlace)
		{
			// the input iterator is not a random access iterator
			// we may need to shift bytes afterwards
			if (decodedSize % 2 != 0)
			{
				// odd number of nibbles, need to shift bytes
				BitWiseShiftBytesRight(dest.begin(), dest.end(), 4);
			}
		}

		return dest;
	}

	template<
		typename _OutContainer,
		typename _InContainer,
		typename std::enable_if<
			sizeof(typename _OutContainer::value_type) == 1,
			int
		>::type = 0
	>
	static _OutContainer Decode(
		const _InContainer& src
	)
	{
		// default to keep leading zeros
		return Decode<_OutContainer, true, HexPad::Disabled>(src);
	}


	template<
		typename _OutContainer,
		bool     _KeepLeadingZero,
		HexPad   _PadOpt,
		typename _InIt,
		typename std::enable_if<
			(sizeof(typename _OutContainer::value_type) == 1) &&
			(_PadOpt == HexPad::Disabled || _PadOpt == HexPad::Front),
			int
		>::type = 0
	>
	static _OutContainer Decode(
		_InIt begin, _InIt end
	)
	{
		using _OutputValType = typename _OutContainer::value_type;
		static constexpr size_t sk_outputValSize = sizeof(_OutputValType);
		static constexpr bool sk_canPadInPlace =
			HexDecodeCanPadInPlace<_InIt>();

		_OutContainer dest;

		size_t decodedSize = 0;
		HexToBytesImpl<HexValueLut, sk_outputValSize>::
			template Decode<_KeepLeadingZero, _PadOpt, _OutputValType>(
				std::back_inserter(dest),
				begin,
				end,
				decodedSize
			);

		if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
		constexpr
#endif
		(!sk_canPadInPlace)
		{
			// the input iterator is not a random access iterator
			// we may need to shift bytes afterwards
			if (decodedSize % 2 != 0)
			{
				// odd number of nibbles
				if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
				constexpr
#endif
				(_PadOpt == HexPad::Disabled)
				{
					throw std::invalid_argument("Odd number of hex digits");
				}
				else
				{
					// need to shift bytes
					BitWiseShiftBytesRight(dest.begin(), dest.end(), 4);
				}
			}
		}

		return dest;
	}

	template<
		typename _OutContainer,
		typename _InIt,
		typename std::enable_if<
			sizeof(typename _OutContainer::value_type) == 1,
			int
		>::type = 0
	>
	static _OutContainer Decode(
		_InIt begin, _InIt end
	)
	{
		// default to keep leading zeros
		return Decode<_OutContainer, true, HexPad::Disabled>(begin, end);
	}


	template<
		bool     _KeepLeadingZero,
		HexPad   _PadOpt,
		typename _OutIt,
		typename _InIt,
		typename std::enable_if<
			(_PadOpt == HexPad::Disabled || _PadOpt == HexPad::Front),
			int
		>::type = 0
	>
	static _OutIt Decode(
		_OutIt dest,
		_InIt begin, _InIt end
	)
	{
		using _OutItValType = typename std::iterator_traits<_OutIt>::value_type;
		using _OutputValType = typename std::conditional<
			std::is_same<_OutItValType, void>::value,
			typename HexValueLut::value_type,
			_OutItValType
		>::type;

		static constexpr size_t sk_outputValSize = sizeof(_OutputValType);
		static constexpr bool sk_canPadInPlace =
			HexDecodeCanPadInPlace<_InIt>();

		size_t decodedSize = 0;
		dest = HexToBytesImpl<HexValueLut, sk_outputValSize>::
			template Decode<_KeepLeadingZero, _PadOpt, _OutputValType>(
				dest,
				begin,
				end,
				decodedSize
			);

		if
#if defined(__cpp_if_constexpr) && __cpp_if_constexpr != 0
		constexpr
#endif
		(!sk_canPadInPlace)
		{
			// the input iterator is not a random access iterator
			// we may need to shift bytes afterwards
			if (decodedSize % 2 != 0)
			{
				// odd number of nibbles
				throw std::invalid_argument("Odd number of hex digits");
			}
		}

		return dest;
	}

	template<
		typename _OutIt,
		typename _InIt
	>
	static _OutIt Decode(
		_OutIt dest,
		_InIt begin, _InIt end
	)
	{
		// default to keep leading zeros
		return Decode<true, HexPad::Disabled>(dest, begin, end);
	}

}; // struct Hex



} // namespace Internal


struct Hex :
	public Internal::Hex<
		Internal::HexLowerCaseAlphabet<char>,
		Internal::HexValueLut<uint8_t, char>
	>
{}; // struct Hex


struct HEX :
	public Internal::Hex<
		Internal::HexUpperCaseAlphabet<char>,
		Internal::HexValueLut<uint8_t, char>
	>
{}; // struct HEX


} // namespace Codec
} // namespace SimpleObjects