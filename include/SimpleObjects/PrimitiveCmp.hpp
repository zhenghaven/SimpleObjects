// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <cstdint>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{
namespace Internal
{

template<typename _T>
struct IsPrimitiveType;

template<typename _T> struct IsPrimitiveType : std::false_type {};

template<> struct IsPrimitiveType<bool    > : std::true_type {};
template<> struct IsPrimitiveType<int8_t  > : std::true_type {};
template<> struct IsPrimitiveType<int16_t > : std::true_type {};
template<> struct IsPrimitiveType<int32_t > : std::true_type {};
template<> struct IsPrimitiveType<int64_t > : std::true_type {};
template<> struct IsPrimitiveType<uint8_t > : std::true_type {};
template<> struct IsPrimitiveType<uint16_t> : std::true_type {};
template<> struct IsPrimitiveType<uint32_t> : std::true_type {};
template<> struct IsPrimitiveType<uint64_t> : std::true_type {};
template<> struct IsPrimitiveType<float   > : std::true_type {};
template<> struct IsPrimitiveType<double  > : std::true_type {};

static_assert(IsPrimitiveType<bool    >::value, "Implementation Error");
static_assert(IsPrimitiveType<int8_t  >::value, "Implementation Error");
static_assert(IsPrimitiveType<int16_t >::value, "Implementation Error");
static_assert(IsPrimitiveType<int32_t >::value, "Implementation Error");
static_assert(IsPrimitiveType<int64_t >::value, "Implementation Error");
static_assert(IsPrimitiveType<uint8_t >::value, "Implementation Error");
static_assert(IsPrimitiveType<uint16_t>::value, "Implementation Error");
static_assert(IsPrimitiveType<uint32_t>::value, "Implementation Error");
static_assert(IsPrimitiveType<uint64_t>::value, "Implementation Error");
static_assert(IsPrimitiveType<float   >::value, "Implementation Error");
static_assert(IsPrimitiveType<double  >::value, "Implementation Error");

template<bool _IsTSigned, bool _IsUSigned>
struct cmp_impl;

template<>
struct cmp_impl<true, true>
{
	template<typename T, typename U>
	static constexpr bool cmp_equal(T t, U u) noexcept
	{ return t == u; }

	template<typename T, typename U>
	static constexpr bool cmp_less(T t, U u) noexcept
	{ return t < u; }
}; // struct cmp_impl

template<>
struct cmp_impl<false, false>
{
	template<typename T, typename U>
	static constexpr bool cmp_equal(T t, U u) noexcept
	{ return t == u; }

	template<typename T, typename U>
	static constexpr bool cmp_less(T t, U u) noexcept
	{ return t < u; }
}; // struct cmp_impl

template<>
struct cmp_impl<true, false>
{
	template<typename T, typename U>
	static constexpr bool cmp_equal(T t, U u) noexcept
	{
		using UT = typename std::make_unsigned<T>::type;
		return (t < 0 ? false : UT(t) == u);
	}

	template<typename T, typename U>
	static constexpr bool cmp_less(T t, U u) noexcept
	{
		using UT = typename std::make_unsigned<T>::type;
		return (t < 0 ? true : UT(t) < u);
	}
}; // struct cmp_impl

template<>
struct cmp_impl<false, true>
{
	template<typename T, typename U>
	static constexpr bool cmp_equal(T t, U u) noexcept
	{
		using UU = typename std::make_unsigned<U>::type;
		return (u < 0 ? false : t == UU(u));
	}

	template<typename T, typename U>
	static constexpr bool cmp_less(T t, U u) noexcept
	{
		using UU = typename std::make_unsigned<U>::type;
		return (u < 0 ? false : t < UU(u));
	}
}; // struct cmp_impl

/**
 * @brief A comparison that is safe against lossy integer conversion.
 *        source: https://en.cppreference.com/w/cpp/utility/intcmp
 *        Even though this is provided in C++20, we still need to support
 *        older versions
 *
 * @tparam T
 * @tparam U
 * @param t
 * @param u
 * @return
 */
template<typename T, typename U>
inline constexpr bool cmp_equal(T t, U u) noexcept
{
	static_assert(IsPrimitiveType<T>::value, "Expecting a primitive type");
	static_assert(IsPrimitiveType<U>::value, "Expecting a primitive type");

	return cmp_impl<std::is_signed<T>::value,
		std::is_signed<U>::value>::cmp_equal(t, u);
}

template<typename T, typename U>
inline constexpr bool cmp_less(T t, U u) noexcept
{
	static_assert(IsPrimitiveType<T>::value, "Expecting a primitive type");
	static_assert(IsPrimitiveType<U>::value, "Expecting a primitive type");

	return cmp_impl<std::is_signed<T>::value,
		std::is_signed<U>::value>::cmp_less(t, u);
}

template<typename T, typename U>
inline constexpr bool cmp_greater(T t, U u) noexcept
{
	return cmp_less(u, t);
}

/**
 * @brief Comparison for custom class types. Implementation is not given.
 *        The user should provide their own implementation using template
 *        specialization
 *
 * @tparam _LhsType
 * @tparam _RhsType
 */
template<typename _LhsType, typename _RhsType>
struct CustomCompare;

template<bool _IsBothPrimitive, typename _LhsType, typename _RhsType>
struct CompareImpl;

template<typename _LhsType, typename _RhsType>
struct CompareImpl<true, _LhsType, _RhsType>
{
	static constexpr bool Equal(_LhsType lhs, _RhsType rhs)
	{
		return cmp_equal(lhs, rhs);
	}

	static constexpr bool Less(_LhsType lhs, _RhsType rhs)
	{
		return cmp_less(lhs, rhs);
	}

	static constexpr bool Greater(_LhsType lhs, _RhsType rhs)
	{
		return cmp_greater(lhs, rhs);
	}
}; // struct CompareImpl

template<typename _LhsType, typename _RhsType>
struct CompareImpl<false, _LhsType, _RhsType>
{
	static constexpr bool Equal(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CustomCompare<_LhsType, _RhsType>::Equal(lhs, rhs);
	}

	static constexpr bool Less(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CustomCompare<_LhsType, _RhsType>::Less(lhs, rhs);
	}

	static constexpr bool Greater(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CustomCompare<_LhsType, _RhsType>::Greater(lhs, rhs);
	}
}; // struct CompareImpl

template<typename _LhsType, typename _RhsType>
struct CompareFilterDouble;

template<typename _LhsType, typename _RhsType>
struct CompareFilterDouble
{ // next to impl

	static constexpr bool sk_isBothPrimitive = (
		IsPrimitiveType<_LhsType>::value &&
		IsPrimitiveType<_RhsType>::value);

	static constexpr bool Equal(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareImpl<
			sk_isBothPrimitive, _LhsType, _RhsType>::Equal(lhs, rhs);
	}

	static constexpr bool Less(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareImpl<
			sk_isBothPrimitive, _LhsType, _RhsType>::Less(lhs, rhs);
	}

	static constexpr bool Greater(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareImpl<
			sk_isBothPrimitive, _LhsType, _RhsType>::Greater(lhs, rhs);
	}
}; // struct CompareFilterDouble

template<typename _RhsType>
struct CompareFilterDouble<double, _RhsType>
{
	static constexpr bool Equal(double lhs, const _RhsType& rhs)
	{ return lhs == rhs; }
	static constexpr bool Less(double lhs, const _RhsType& rhs)
	{ return lhs < rhs; }
	static constexpr bool Greater(double lhs, const _RhsType& rhs)
	{ return lhs > rhs; }
}; // struct CompareFilterDouble

template<typename _LhsType>
struct CompareFilterDouble<_LhsType, double>
{
	static constexpr bool Equal(const _LhsType& lhs, double rhs)
	{ return lhs == rhs; }
	static constexpr bool Less(const _LhsType& lhs, double rhs)
	{ return lhs < rhs; }
	static constexpr bool Greater(const _LhsType& lhs, double rhs)
	{ return lhs > rhs; }
}; // struct CompareFilterDouble

template<typename _LhsType, typename _RhsType>
struct CompareFilterFloat;

template<typename _LhsType, typename _RhsType>
struct CompareFilterFloat
{ // next to filter double
	static constexpr bool Equal(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterDouble<_LhsType, _RhsType>::Equal(lhs, rhs);
	}
	static constexpr bool Less(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterDouble<_LhsType, _RhsType>::Less(lhs, rhs);
	}
	static constexpr bool Greater(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterDouble<_LhsType, _RhsType>::Greater(lhs, rhs);
	}
}; // struct CompareFilterFloat

template<typename _RhsType>
struct CompareFilterFloat<float, _RhsType>
{
	static constexpr bool Equal(float lhs, const _RhsType& rhs)
	{ return lhs == rhs; }
	static constexpr bool Less(float lhs, const _RhsType& rhs)
	{ return lhs < rhs; }
	static constexpr bool Greater(float lhs, const _RhsType& rhs)
	{ return lhs > rhs; }
}; // struct CompareFilterFloat

template<typename _LhsType>
struct CompareFilterFloat<_LhsType, float>
{
	static constexpr bool Equal(const _LhsType& lhs, float rhs)
	{ return lhs == rhs; }
	static constexpr bool Less(const _LhsType& lhs, float rhs)
	{ return lhs < rhs; }
	static constexpr bool Greater(const _LhsType& lhs, float rhs)
	{ return lhs > rhs; }
}; // struct CompareFilterFloat

template<typename _LhsType, typename _RhsType>
struct CompareFilterBool;

template<typename _LhsType, typename _RhsType>
struct CompareFilterBool
{ // next to filter float
	static constexpr bool Equal(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterFloat<_LhsType, _RhsType>::Equal(lhs, rhs);
	}
	static constexpr bool Less(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterFloat<_LhsType, _RhsType>::Less(lhs, rhs);
	}
	static constexpr bool Greater(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterFloat<_LhsType, _RhsType>::Greater(lhs, rhs);
	}
}; // struct CompareFilterBool

template<typename _RhsType>
struct CompareFilterBool<bool, _RhsType>
{
	static constexpr bool Equal(bool lhs, const _RhsType& rhs)
	{ return static_cast<_RhsType>(lhs) == rhs; }
	static constexpr bool Less(bool lhs, const _RhsType& rhs)
	{ return static_cast<_RhsType>(lhs) < rhs; }
	static constexpr bool Greater(bool lhs, const _RhsType& rhs)
	{ return static_cast<_RhsType>(lhs) > rhs; }
}; // struct CompareFilterBool

template<typename _LhsType>
struct CompareFilterBool<_LhsType, bool>
{
	static constexpr bool Equal(const _LhsType& lhs, bool rhs)
	{ return lhs == static_cast<_LhsType>(rhs); }
	static constexpr bool Less(const _LhsType& lhs, bool rhs)
	{ return lhs < static_cast<_LhsType>(rhs); }
	static constexpr bool Greater(const _LhsType& lhs, bool rhs)
	{ return lhs > static_cast<_LhsType>(rhs); }
}; // struct CompareFilterBool

template<typename _LhsType, typename _RhsType>
struct CompareFilterSame;

template<typename _LhsType, typename _RhsType>
struct CompareFilterSame
{ // next to filter bool
	static constexpr bool Equal(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterBool<_LhsType, _RhsType>::Equal(lhs, rhs);
	}
	static constexpr bool Less(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterBool<_LhsType, _RhsType>::Less(lhs, rhs);
	}
	static constexpr bool Greater(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterBool<_LhsType, _RhsType>::Greater(lhs, rhs);
	}
}; // struct CompareFilterSame

template<typename _Type>
struct CompareFilterSame<_Type, _Type>
{
	static constexpr bool Equal(const _Type& lhs, const _Type& rhs)
	{ return lhs == rhs; }
	static constexpr bool Less(const _Type& lhs, const _Type& rhs)
	{ return lhs < rhs; }
	static constexpr bool Greater(const _Type& lhs, const _Type& rhs)
	{ return lhs > rhs; }
}; // struct CompareFilterSame

template<typename _LhsType, typename _RhsType>
struct Compare;

template<typename _LhsType, typename _RhsType>
struct Compare
{
	static constexpr bool Equal(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterSame<_LhsType, _RhsType>::Equal(lhs, rhs);
	}

	static constexpr bool Less(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterSame<_LhsType, _RhsType>::Less(lhs, rhs);
	}

	static constexpr bool Greater(const _LhsType& lhs, const _RhsType& rhs)
	{
		return CompareFilterSame<_LhsType, _RhsType>::Greater(lhs, rhs);
	}

	static constexpr bool LessEqual(const _LhsType& lhs, const _RhsType& rhs)
	{
		return !Greater(lhs, rhs);
	}

	static constexpr bool GreaterEqual(const _LhsType& lhs, const _RhsType& rhs)
	{
		return !Less(lhs, rhs);
	}
}; // struct Compare

static_assert(!Compare<uint32_t, int32_t>::Equal(
	static_cast<uint32_t>(10), static_cast<int32_t>(-10)),
	"Implementation Error");
static_assert(Compare<uint32_t, int32_t>::Equal(
	static_cast<uint32_t>(10), static_cast<int32_t>(10)),
	"Implementation Error");

// static_assert(!(static_cast<uint32_t>(10) > static_cast<int32_t>(-20)),
// 	"Implementation Error");
static_assert(Compare<uint32_t, int32_t>::Greater(
	static_cast<uint32_t>(10), static_cast<int32_t>(-20)),
	"Implementation Error");
// static_assert(!(static_cast<int32_t>(-20) < static_cast<uint32_t>(10)),
// 	"Implementation Error");
static_assert(Compare<int32_t, uint32_t>::Less(
	static_cast<int32_t>(-20), static_cast<uint32_t>(10)),
	"Implementation Error");

// static_assert(!(static_cast<uint32_t>(10) >= static_cast<int32_t>(-20)),
// 	"Implementation Error");
static_assert(Compare<uint32_t, int32_t>::GreaterEqual(
	static_cast<uint32_t>(10), static_cast<int32_t>(-20)),
	"Implementation Error");
// static_assert(!(static_cast<int32_t>(-20) <= static_cast<uint32_t>(10)),
// 	"Implementation Error");
static_assert(Compare<int32_t, uint32_t>::LessEqual(
	static_cast<int32_t>(-20), static_cast<uint32_t>(10)),
	"Implementation Error");

static_assert((static_cast<uint32_t>(10) >= static_cast<double>(-20)),
	"Implementation Error");
static_assert(Compare<uint32_t, double>::GreaterEqual(
	static_cast<uint32_t>(10), static_cast<double>(-20)),
	"Implementation Error");
static_assert((static_cast<double>(-20) <= static_cast<uint32_t>(10)),
	"Implementation Error");
static_assert(Compare<double, uint32_t>::LessEqual(
	static_cast<double>(-20), static_cast<uint32_t>(10)),
	"Implementation Error");

} // namespace Internal
} // namespace SimpleObjects
