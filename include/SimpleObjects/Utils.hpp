#pragma once

#include <type_traits>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

namespace Internal
{

/**
 * @brief Default case - The type being tested is not bool,
 *        so we keep its original type
 */
template<typename _ThisValType, typename _OtherValType>
struct BoolToInt
{
	static constexpr const _ThisValType& Convert(const _ThisValType& v)
	{ return v; }
};

/**
 * @brief Specialized case - The type being tested is bool,
 *        so we convert it to the other value type
 */
template<typename _OtherValType>
struct BoolToInt<bool, _OtherValType>
{
	/**
	 * @brief Reference: 4.7 [conv.integral] / 4:
	 *        If the source type is bool, the value false is converted to zero
	 *        and the value true is converted to one.
	 *
	 * @tparam _OtherValType The type of the return value
	 * @param b The input bool value
	 * @return The converted value
	 */
	static constexpr _OtherValType Convert(bool b)
	{ return b ? static_cast<_OtherValType>(1) : static_cast<_OtherValType>(0); }
};

template<bool _val>
struct IfConstexpr {};

template<>
struct IfConstexpr<true>
{
	template<typename _TrOpType, typename _FaOpType>
	static void Eval(_TrOpType tOp, _FaOpType fOp) { tOp(); }
};

template<>
struct IfConstexpr<false>
{
	template<typename _TrOpType, typename _FaOpType>
	static void Eval(_TrOpType tOp, _FaOpType fOp) { fOp(); }
};

/**
 * @brief Find for *some string* (i.e., string B) in the
 *        *other string* (i.e., string A).
 *        Pre-conditions (checked by the **caller**):
 *            a) aBegin < aEnd
 *            b) bBegin < bEnd
 *            c) std::distance(aBegin, aEnd) >= std::distance(bBegin, bEnd)
 *
 * @tparam _FindInIt The iterator type of string A
 * @tparam _FindForIt The iterator type of string B
 * @param aBegin The begining of the string A.
 * @param aEnd   The end of the string A.
 * @param bBegin The begining of the string B.
 * @param bEnd   The end of the string B.
 * @return true if the string B is found inside the string A, otherwise, false.
 */
template<typename _FindInIt, typename _FindForIt>
inline bool FindAt(const _FindInIt& aBegin, const _FindInIt& aEnd,
	const _FindForIt& bBegin, const _FindForIt& bEnd)
{
	auto ita = aBegin;
	auto itb = bBegin;
	for(; ita != aEnd && itb != bEnd; ++ita, ++itb)
	{
		if (*ita != *itb)
		{
			return false;
		}
	}
	return (itb == bEnd) ? true : false;
}

template<typename _ToType, typename _FromType>
inline _ToType& DownCast(_FromType& from)
{
	static_assert(std::is_base_of<_FromType, _ToType>::value,
		"This function should only be used for downcasting.");

#ifdef SIMPLEOBJECTS_DOWNCAST_USE_STATIC_CAST
	return static_cast<_ToType&>(from);
#else
	return dynamic_cast<_ToType&>(from);
#endif
}

template<typename _ToType, typename _FromType>
inline const _ToType& DownCast(const _FromType& from)
{
	static_assert(std::is_base_of<_FromType, _ToType>::value,
		"This function should only be used for downcasting.");

#ifdef SIMPLEOBJECTS_DOWNCAST_USE_STATIC_CAST
	return static_cast<const _ToType&>(from);
#else
	return dynamic_cast<const _ToType&>(from);
#endif
}

} // namespace Internal

} // namespace SimpleObjects
