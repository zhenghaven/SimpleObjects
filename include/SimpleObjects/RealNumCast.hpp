// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once


#include <limits>

#include "Exception.hpp"
#include "RealNumCompare.hpp"
#include "RealNumTraits.hpp"


#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _DstValType, typename _SrcValType>
struct RealNumCast;


template<typename _ValType>
struct RealNumCast<_ValType, _ValType>
{
	static void Set(_ValType& dst, const _ValType& src)
	{
		dst = src;
	}
}; // struct RealNumCast<_ValType, _ValType>


template<typename _DstValType, typename _SrcValType>
struct RealNumCast
{
	static void Set(_DstValType& dst, const _SrcValType& src)
	{
		using namespace Internal;

		// // Check if a "check" is needed
		// if (DstType.Lowest <= SrcType.Lowest) and (SrcType.Max <= DstType.Max)
		//    Src's possible range is within Dst's range => no need to check
		// else
		//    Src's value might fall outside of Dst's range => need to check
		static constexpr bool isCheckNeed = (
			!(
				RealNumCompare<_DstValType, _SrcValType>::LessEqual(
					std::numeric_limits<_DstValType>::lowest(),
					std::numeric_limits<_SrcValType>::lowest()) &&
				RealNumCompare<_SrcValType, _DstValType>::LessEqual(
					std::numeric_limits<_SrcValType>::max(),
					std::numeric_limits<_DstValType>::max())
			));

		if (isCheckNeed)
		{
			// // ==> to check `src`:
			// if (src < DstType.Lowest) or (DstType.Max < src)
			//    throw
			const bool isOutRange = (
					(RealNumCompare<_SrcValType, _DstValType>::Less(
						src,
						std::numeric_limits<_DstValType>::lowest())) ||
					(RealNumCompare<_DstValType, _SrcValType>::Less(
						std::numeric_limits<_DstValType>::max(),
						src))
				);
			if (isOutRange)
			{
				throw TypeError(RealNumTraits<_DstValType>::sk_numTypeName(),
					RealNumTraits<_SrcValType>::sk_numTypeName());
			}
		}

		// value range should have passed the check at this point
		dst = static_cast<_DstValType>(src);
	}
}; // struct RealNumCast

} // namespace SimpleObjects
