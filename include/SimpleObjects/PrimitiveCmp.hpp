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

/**
 * @brief Compare for `less than` (i.e., `<`) for C++ primitive types;
 *        this is used to address the "sign/unsigned mismatch issue"
 *
 * @tparam _LhsType The type of the left hand side value
 * @tparam _RhsType The type of the right hand side value
 * @param lhs The left hand side value
 * @param rhs The right hand side value
 * @return true if lhs < rhs, otherwise, false
 */
template<typename _LhsType, typename _RhsType>
bool PrimitiveCmpLt(_LhsType lhs, _RhsType rhs);

/**
 * @brief Compare for `greater than` (i.e., `>`) for C++ primitive types;
 *        this is used to address the "sign/unsigned mismatch issue"
 *
 * @tparam _LhsType The type of the left hand side value
 * @tparam _RhsType The type of the right hand side value
 * @param lhs The left hand side value
 * @param rhs The right hand side value
 * @return true if lhs > rhs, otherwise, false
 */
template<typename _LhsType, typename _RhsType>
bool PrimitiveCmpGt(_LhsType lhs, _RhsType rhs);

//==================== Implementations ====================

//========== PrimitiveCmpLt ==========

// LHS is same as RHS
template<typename _RLhsType>
inline bool PrimitiveCmpLt(_RLhsType lhs, _RLhsType rhs)
{
	return lhs < rhs;
}

// uint8_t
/* 8  : 8  */
/* 8  : 16 */ template<>
inline bool PrimitiveCmpLt(uint8_t lhs, uint16_t rhs)
{ return static_cast<uint16_t>(lhs) < (rhs); }
/* 8  : 32 */ template<>
inline bool PrimitiveCmpLt(uint8_t lhs, uint32_t rhs)
{ return static_cast<uint32_t>(lhs) < (rhs); }
/* 8  : 64 */ template<>
inline bool PrimitiveCmpLt(uint8_t lhs, uint64_t rhs)
{ return static_cast<uint64_t>(lhs) < (rhs); }
/* 8  : 8  */ template<>
inline bool PrimitiveCmpLt(uint8_t lhs, int8_t rhs)
{ return rhs < 0 ?
		false : (lhs) < static_cast<uint8_t>(rhs); }
/* 8  : 16 */ template<>
inline bool PrimitiveCmpLt(uint8_t lhs, int16_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint16_t>(lhs) < static_cast<uint16_t>(rhs); }
/* 8  : 32 */ template<>
inline bool PrimitiveCmpLt(uint8_t lhs, int32_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs); }
/* 8  : 64 */ template<>
inline bool PrimitiveCmpLt(uint8_t lhs, int64_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 8  : F  */ template<>
inline bool PrimitiveCmpLt(uint8_t lhs, float rhs)
{ return static_cast<float>(lhs) < (rhs); }
/* 8  : D  */ template<>
inline bool PrimitiveCmpLt(uint8_t lhs, double rhs)
{ return static_cast<double>(lhs) < (rhs); }

// uint16_t
/* 16 : 8  */ template<>
inline bool PrimitiveCmpLt(uint16_t lhs, uint8_t rhs)
{ return (lhs) < static_cast<uint16_t>(rhs); }
/* 16 : 16 */
/* 16 : 32 */ template<>
inline bool PrimitiveCmpLt(uint16_t lhs, uint32_t rhs)
{ return static_cast<uint32_t>(lhs) < (rhs); }
/* 16 : 64 */ template<>
inline bool PrimitiveCmpLt(uint16_t lhs, uint64_t rhs)
{ return static_cast<uint64_t>(lhs) < (rhs); }
/* 16 : 8  */ template<>
inline bool PrimitiveCmpLt(uint16_t lhs, int8_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint16_t>(lhs) < static_cast<uint16_t>(rhs); }
/* 16 : 16 */ template<>
inline bool PrimitiveCmpLt(uint16_t lhs, int16_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint16_t>(lhs) < static_cast<uint16_t>(rhs); }
/* 16 : 32 */ template<>
inline bool PrimitiveCmpLt(uint16_t lhs, int32_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs); }
/* 16 : 64 */ template<>
inline bool PrimitiveCmpLt(uint16_t lhs, int64_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 16 : F  */ template<>
inline bool PrimitiveCmpLt(uint16_t lhs, float rhs)
{ return static_cast<float>(lhs) < (rhs); }
/* 16 : D  */ template<>
inline bool PrimitiveCmpLt(uint16_t lhs, double rhs)
{ return static_cast<double>(lhs) < (rhs); }

// uint32_t
/* 32 : 8  */ template<>
inline bool PrimitiveCmpLt(uint32_t lhs, uint8_t rhs)
{ return (lhs) < static_cast<uint32_t>(rhs); }
/* 32 : 16 */ template<>
inline bool PrimitiveCmpLt(uint32_t lhs, uint16_t rhs)
{ return (lhs) < static_cast<uint32_t>(rhs); }
/* 32 : 32 */
/* 32 : 64 */ template<>
inline bool PrimitiveCmpLt(uint32_t lhs, uint64_t rhs)
{ return static_cast<uint64_t>(lhs) < (rhs); }
/* 32 : 8  */ template<>
inline bool PrimitiveCmpLt(uint32_t lhs, int8_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs); }
/* 32 : 16 */ template<>
inline bool PrimitiveCmpLt(uint32_t lhs, int16_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs); }
/* 32 : 32 */ template<>
inline bool PrimitiveCmpLt(uint32_t lhs, int32_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs); }
/* 32 : 64 */ template<>
inline bool PrimitiveCmpLt(uint32_t lhs, int64_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 32 : F  */ template<>
inline bool PrimitiveCmpLt(uint32_t lhs, float rhs)
{ return static_cast<float>(lhs) < (rhs); }
/* 32 : D  */ template<>
inline bool PrimitiveCmpLt(uint32_t lhs, double rhs)
{ return static_cast<double>(lhs) < (rhs); }

// uint64_t
/* 64 : 8  */ template<>
inline bool PrimitiveCmpLt(uint64_t lhs, uint8_t rhs)
{ return (lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 16 */ template<>
inline bool PrimitiveCmpLt(uint64_t lhs, uint16_t rhs)
{ return (lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 32 */ template<>
inline bool PrimitiveCmpLt(uint64_t lhs, uint32_t rhs)
{ return (lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 64 */
/* 64 : 8  */ template<>
inline bool PrimitiveCmpLt(uint64_t lhs, int8_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 16 */ template<>
inline bool PrimitiveCmpLt(uint64_t lhs, int16_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 32 */ template<>
inline bool PrimitiveCmpLt(uint64_t lhs, int32_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 64 */ template<>
inline bool PrimitiveCmpLt(uint64_t lhs, int64_t rhs)
{ return rhs < 0 ?
		false : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 64 : F  */ template<>
inline bool PrimitiveCmpLt(uint64_t lhs, float rhs)
{ return static_cast<float>(lhs) < (rhs); }
/* 64 : D  */ template<>
inline bool PrimitiveCmpLt(uint64_t lhs, double rhs)
{ return static_cast<double>(lhs) < (rhs); }

// int8_t
/* 8  : 8  */ template<>
inline bool PrimitiveCmpLt(int8_t lhs, uint8_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint8_t>(lhs) < (rhs); }
/* 8  : 16 */ template<>
inline bool PrimitiveCmpLt(int8_t lhs, uint16_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint16_t>(lhs) < (rhs); }
/* 8  : 32 */ template<>
inline bool PrimitiveCmpLt(int8_t lhs, uint32_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint32_t>(lhs) < (rhs); }
/* 8  : 64 */ template<>
inline bool PrimitiveCmpLt(int8_t lhs, uint64_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint64_t>(lhs) < (rhs); }
/* 8  : 8  */
/* 8  : 16 */ template<>
inline bool PrimitiveCmpLt(int8_t lhs, int16_t rhs)
{ return static_cast<int16_t>(lhs) < (rhs); }
/* 8  : 32 */ template<>
inline bool PrimitiveCmpLt(int8_t lhs, int32_t rhs)
{ return static_cast<int32_t>(lhs) < (rhs); }
/* 8  : 64 */ template<>
inline bool PrimitiveCmpLt(int8_t lhs, int64_t rhs)
{ return static_cast<int64_t>(lhs) < (rhs); }
/* 8  : F  */ template<>
inline bool PrimitiveCmpLt(int8_t lhs, float rhs)
{ return static_cast<float>(lhs) < (rhs); }
/* 8  : D  */ template<>
inline bool PrimitiveCmpLt(int8_t lhs, double rhs)
{ return static_cast<double>(lhs) < (rhs); }

// int16_t
/* 16 : 8  */ template<>
inline bool PrimitiveCmpLt(int16_t lhs, uint8_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint16_t>(lhs) < static_cast<uint16_t>(rhs); }
/* 16 : 16 */ template<>
inline bool PrimitiveCmpLt(int16_t lhs, uint16_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint16_t>(lhs) < static_cast<uint16_t>(rhs); }
/* 16 : 32 */ template<>
inline bool PrimitiveCmpLt(int16_t lhs, uint32_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs); }
/* 16 : 64 */ template<>
inline bool PrimitiveCmpLt(int16_t lhs, uint64_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 16 : 8  */ template<>
inline bool PrimitiveCmpLt(int16_t lhs, int8_t rhs)
{ return (lhs) < static_cast<int16_t>(rhs); }
/* 16 : 16 */
/* 16 : 32 */ template<>
inline bool PrimitiveCmpLt(int16_t lhs, int32_t rhs)
{ return static_cast<int32_t>(lhs) < (rhs); }
/* 16 : 64 */ template<>
inline bool PrimitiveCmpLt(int16_t lhs, int64_t rhs)
{ return static_cast<int64_t>(lhs) < (rhs); }
/* 16 : F  */ template<>
inline bool PrimitiveCmpLt(int16_t lhs, float rhs)
{ return static_cast<float>(lhs) < (rhs); }
/* 16 : D  */ template<>
inline bool PrimitiveCmpLt(int16_t lhs, double rhs)
{ return static_cast<double>(lhs) < (rhs); }

// int32_t
/* 32 : 8  */ template<>
inline bool PrimitiveCmpLt(int32_t lhs, uint8_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs); }
/* 32 : 16 */ template<>
inline bool PrimitiveCmpLt(int32_t lhs, uint16_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs); }
/* 32 : 32 */ template<>
inline bool PrimitiveCmpLt(int32_t lhs, uint32_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs); }
/* 32 : 64 */ template<>
inline bool PrimitiveCmpLt(int32_t lhs, uint64_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 32 : 8  */ template<>
inline bool PrimitiveCmpLt(int32_t lhs, int8_t rhs)
{ return (lhs) < static_cast<int32_t>(rhs); }
/* 32 : 16 */ template<>
inline bool PrimitiveCmpLt(int32_t lhs, int16_t rhs)
{ return (lhs) < static_cast<int32_t>(rhs); }
/* 32 : 32 */
/* 32 : 64 */ template<>
inline bool PrimitiveCmpLt(int32_t lhs, int64_t rhs)
{ return static_cast<int64_t>(lhs) < (rhs); }
/* 32 : F  */ template<>
inline bool PrimitiveCmpLt(int32_t lhs, float rhs)
{ return static_cast<float>(lhs) < (rhs); }
/* 32 : D  */ template<>
inline bool PrimitiveCmpLt(int32_t lhs, double rhs)
{ return static_cast<double>(lhs) < (rhs); }

// int64_t
/* 64 : 8  */ template<>
inline bool PrimitiveCmpLt(int64_t lhs, uint8_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 16 */ template<>
inline bool PrimitiveCmpLt(int64_t lhs, uint16_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 32 */ template<>
inline bool PrimitiveCmpLt(int64_t lhs, uint32_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 64 */ template<>
inline bool PrimitiveCmpLt(int64_t lhs, uint64_t rhs)
{ return lhs < 0 ?
		true : static_cast<uint64_t>(lhs) < static_cast<uint64_t>(rhs); }
/* 64 : 8  */ template<>
inline bool PrimitiveCmpLt(int64_t lhs, int8_t rhs)
{ return (lhs) < static_cast<int64_t>(rhs); }
/* 64 : 16 */ template<>
inline bool PrimitiveCmpLt(int64_t lhs, int16_t rhs)
{ return (lhs) < static_cast<int64_t>(rhs); }
/* 64 : 32 */ template<>
inline bool PrimitiveCmpLt(int64_t lhs, int32_t rhs)
{ return (lhs) < static_cast<int64_t>(rhs); }
/* 64 : 64 */
/* 64 : F  */ template<>
inline bool PrimitiveCmpLt(int64_t lhs, float rhs)
{ return static_cast<float>(lhs) < (rhs); }
/* 64 : D  */ template<>
inline bool PrimitiveCmpLt(int64_t lhs, double rhs)
{ return static_cast<double>(lhs) < (rhs); }

// float
/* F  : 8  */ template<>
inline bool PrimitiveCmpLt(float lhs, uint8_t rhs)
{ return (lhs) < static_cast<float>(rhs); }
/* F  : 16 */ template<>
inline bool PrimitiveCmpLt(float lhs, uint16_t rhs)
{ return (lhs) < static_cast<float>(rhs); }
/* F  : 32 */ template<>
inline bool PrimitiveCmpLt(float lhs, uint32_t rhs)
{ return (lhs) < static_cast<float>(rhs); }
/* F  : 64 */ template<>
inline bool PrimitiveCmpLt(float lhs, uint64_t rhs)
{ return (lhs) < static_cast<float>(rhs); }
/* F  : 8  */ template<>
inline bool PrimitiveCmpLt(float lhs, int8_t rhs)
{ return (lhs) < static_cast<float>(rhs); }
/* F  : 16 */ template<>
inline bool PrimitiveCmpLt(float lhs, int16_t rhs)
{ return (lhs) < static_cast<float>(rhs); }
/* F  : 32 */ template<>
inline bool PrimitiveCmpLt(float lhs, int32_t rhs)
{ return (lhs) < static_cast<float>(rhs); }
/* F  : 64 */ template<>
inline bool PrimitiveCmpLt(float lhs, int64_t rhs)
{ return (lhs) < static_cast<float>(rhs); }
/* F  : D  */ template<>
inline bool PrimitiveCmpLt(float lhs, double rhs)
{ return static_cast<double>(lhs) < (rhs); }

// double
/* D  : 8  */ template<>
inline bool PrimitiveCmpLt(double lhs, uint8_t rhs)
{ return (lhs) < static_cast<double>(rhs); }
/* D  : 16 */ template<>
inline bool PrimitiveCmpLt(double lhs, uint16_t rhs)
{ return (lhs) < static_cast<double>(rhs); }
/* D  : 32 */ template<>
inline bool PrimitiveCmpLt(double lhs, uint32_t rhs)
{ return (lhs) < static_cast<double>(rhs); }
/* D  : 64 */ template<>
inline bool PrimitiveCmpLt(double lhs, uint64_t rhs)
{ return (lhs) < static_cast<double>(rhs); }
/* D  : 8  */ template<>
inline bool PrimitiveCmpLt(double lhs, int8_t rhs)
{ return (lhs) < static_cast<double>(rhs); }
/* D  : 16 */ template<>
inline bool PrimitiveCmpLt(double lhs, int16_t rhs)
{ return (lhs) < static_cast<double>(rhs); }
/* D  : 32 */ template<>
inline bool PrimitiveCmpLt(double lhs, int32_t rhs)
{ return (lhs) < static_cast<double>(rhs); }
/* D  : 64 */ template<>
inline bool PrimitiveCmpLt(double lhs, int64_t rhs)
{ return (lhs) < static_cast<double>(rhs); }
/* D  : F  */ template<>
inline bool PrimitiveCmpLt(double lhs, float rhs)
{ return (lhs) < static_cast<double>(rhs); }


//========== PrimitiveCmpGt ==========

// LHS is same as RHS
template<typename _RLhsType>
inline bool PrimitiveCmpGt(_RLhsType lhs, _RLhsType rhs)
{
	return lhs > rhs;
}

// uint8_t
/* 8  : 8  */
/* 8  : 16 */ template<>
inline bool PrimitiveCmpGt(uint8_t lhs, uint16_t rhs)
{ return static_cast<uint16_t>(lhs) > (rhs); }
/* 8  : 32 */ template<>
inline bool PrimitiveCmpGt(uint8_t lhs, uint32_t rhs)
{ return static_cast<uint32_t>(lhs) > (rhs); }
/* 8  : 64 */ template<>
inline bool PrimitiveCmpGt(uint8_t lhs, uint64_t rhs)
{ return static_cast<uint64_t>(lhs) > (rhs); }
/* 8  : 8  */ template<>
inline bool PrimitiveCmpGt(uint8_t lhs, int8_t rhs)
{ return rhs < 0 ?
		true : (lhs) > static_cast<uint8_t>(rhs); }
/* 8  : 16 */ template<>
inline bool PrimitiveCmpGt(uint8_t lhs, int16_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint16_t>(lhs) > static_cast<uint16_t>(rhs); }
/* 8  : 32 */ template<>
inline bool PrimitiveCmpGt(uint8_t lhs, int32_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs); }
/* 8  : 64 */ template<>
inline bool PrimitiveCmpGt(uint8_t lhs, int64_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 8  : F  */ template<>
inline bool PrimitiveCmpGt(uint8_t lhs, float rhs)
{ return static_cast<float>(lhs) > (rhs); }
/* 8  : D  */ template<>
inline bool PrimitiveCmpGt(uint8_t lhs, double rhs)
{ return static_cast<double>(lhs) > (rhs); }

// uint16_t
/* 16 : 8  */ template<>
inline bool PrimitiveCmpGt(uint16_t lhs, uint8_t rhs)
{ return (lhs) > static_cast<uint16_t>(rhs); }
/* 16 : 16 */
/* 16 : 32 */ template<>
inline bool PrimitiveCmpGt(uint16_t lhs, uint32_t rhs)
{ return static_cast<uint32_t>(lhs) > (rhs); }
/* 16 : 64 */ template<>
inline bool PrimitiveCmpGt(uint16_t lhs, uint64_t rhs)
{ return static_cast<uint64_t>(lhs) > (rhs); }
/* 16 : 8  */ template<>
inline bool PrimitiveCmpGt(uint16_t lhs, int8_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint16_t>(lhs) > static_cast<uint16_t>(rhs); }
/* 16 : 16 */ template<>
inline bool PrimitiveCmpGt(uint16_t lhs, int16_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint16_t>(lhs) > static_cast<uint16_t>(rhs); }
/* 16 : 32 */ template<>
inline bool PrimitiveCmpGt(uint16_t lhs, int32_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs); }
/* 16 : 64 */ template<>
inline bool PrimitiveCmpGt(uint16_t lhs, int64_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 16 : F  */ template<>
inline bool PrimitiveCmpGt(uint16_t lhs, float rhs)
{ return static_cast<float>(lhs) > (rhs); }
/* 16 : D  */ template<>
inline bool PrimitiveCmpGt(uint16_t lhs, double rhs)
{ return static_cast<double>(lhs) > (rhs); }

// uint32_t
/* 32 : 8  */ template<>
inline bool PrimitiveCmpGt(uint32_t lhs, uint8_t rhs)
{ return (lhs) > static_cast<uint32_t>(rhs); }
/* 32 : 16 */ template<>
inline bool PrimitiveCmpGt(uint32_t lhs, uint16_t rhs)
{ return (lhs) > static_cast<uint32_t>(rhs); }
/* 32 : 32 */
/* 32 : 64 */ template<>
inline bool PrimitiveCmpGt(uint32_t lhs, uint64_t rhs)
{ return static_cast<uint64_t>(lhs) > (rhs); }
/* 32 : 8  */ template<>
inline bool PrimitiveCmpGt(uint32_t lhs, int8_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs); }
/* 32 : 16 */ template<>
inline bool PrimitiveCmpGt(uint32_t lhs, int16_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs); }
/* 32 : 32 */ template<>
inline bool PrimitiveCmpGt(uint32_t lhs, int32_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs); }
/* 32 : 64 */ template<>
inline bool PrimitiveCmpGt(uint32_t lhs, int64_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 32 : F  */ template<>
inline bool PrimitiveCmpGt(uint32_t lhs, float rhs)
{ return static_cast<float>(lhs) > (rhs); }
/* 32 : D  */ template<>
inline bool PrimitiveCmpGt(uint32_t lhs, double rhs)
{ return static_cast<double>(lhs) > (rhs); }

// uint64_t
/* 64 : 8  */ template<>
inline bool PrimitiveCmpGt(uint64_t lhs, uint8_t rhs)
{ return (lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 16 */ template<>
inline bool PrimitiveCmpGt(uint64_t lhs, uint16_t rhs)
{ return (lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 32 */ template<>
inline bool PrimitiveCmpGt(uint64_t lhs, uint32_t rhs)
{ return (lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 64 */
/* 64 : 8  */ template<>
inline bool PrimitiveCmpGt(uint64_t lhs, int8_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 16 */ template<>
inline bool PrimitiveCmpGt(uint64_t lhs, int16_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 32 */ template<>
inline bool PrimitiveCmpGt(uint64_t lhs, int32_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 64 */ template<>
inline bool PrimitiveCmpGt(uint64_t lhs, int64_t rhs)
{ return rhs < 0 ?
		true : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 64 : F  */ template<>
inline bool PrimitiveCmpGt(uint64_t lhs, float rhs)
{ return static_cast<float>(lhs) > (rhs); }
/* 64 : D  */ template<>
inline bool PrimitiveCmpGt(uint64_t lhs, double rhs)
{ return static_cast<double>(lhs) > (rhs); }

// int8_t
/* 8  : 8  */ template<>
inline bool PrimitiveCmpGt(int8_t lhs, uint8_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint8_t>(lhs) > (rhs); }
/* 8  : 16 */ template<>
inline bool PrimitiveCmpGt(int8_t lhs, uint16_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint16_t>(lhs) > (rhs); }
/* 8  : 32 */ template<>
inline bool PrimitiveCmpGt(int8_t lhs, uint32_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint32_t>(lhs) > (rhs); }
/* 8  : 64 */ template<>
inline bool PrimitiveCmpGt(int8_t lhs, uint64_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint64_t>(lhs) > (rhs); }
/* 8  : 8  */
/* 8  : 16 */ template<>
inline bool PrimitiveCmpGt(int8_t lhs, int16_t rhs)
{ return static_cast<int16_t>(lhs) > (rhs); }
/* 8  : 32 */ template<>
inline bool PrimitiveCmpGt(int8_t lhs, int32_t rhs)
{ return static_cast<int32_t>(lhs) > (rhs); }
/* 8  : 64 */ template<>
inline bool PrimitiveCmpGt(int8_t lhs, int64_t rhs)
{ return static_cast<int64_t>(lhs) > (rhs); }
/* 8  : F  */ template<>
inline bool PrimitiveCmpGt(int8_t lhs, float rhs)
{ return static_cast<float>(lhs) > (rhs); }
/* 8  : D  */ template<>
inline bool PrimitiveCmpGt(int8_t lhs, double rhs)
{ return static_cast<double>(lhs) > (rhs); }

// int16_t
/* 16 : 8  */ template<>
inline bool PrimitiveCmpGt(int16_t lhs, uint8_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint16_t>(lhs) > static_cast<uint16_t>(rhs); }
/* 16 : 16 */ template<>
inline bool PrimitiveCmpGt(int16_t lhs, uint16_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint16_t>(lhs) > static_cast<uint16_t>(rhs); }
/* 16 : 32 */ template<>
inline bool PrimitiveCmpGt(int16_t lhs, uint32_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs); }
/* 16 : 64 */ template<>
inline bool PrimitiveCmpGt(int16_t lhs, uint64_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 16 : 8  */ template<>
inline bool PrimitiveCmpGt(int16_t lhs, int8_t rhs)
{ return (lhs) > static_cast<int16_t>(rhs); }
/* 16 : 16 */
/* 16 : 32 */ template<>
inline bool PrimitiveCmpGt(int16_t lhs, int32_t rhs)
{ return static_cast<int32_t>(lhs) > (rhs); }
/* 16 : 64 */ template<>
inline bool PrimitiveCmpGt(int16_t lhs, int64_t rhs)
{ return static_cast<int64_t>(lhs) > (rhs); }
/* 16 : F  */ template<>
inline bool PrimitiveCmpGt(int16_t lhs, float rhs)
{ return static_cast<float>(lhs) > (rhs); }
/* 16 : D  */ template<>
inline bool PrimitiveCmpGt(int16_t lhs, double rhs)
{ return static_cast<double>(lhs) > (rhs); }

// int32_t
/* 32 : 8  */ template<>
inline bool PrimitiveCmpGt(int32_t lhs, uint8_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs); }
/* 32 : 16 */ template<>
inline bool PrimitiveCmpGt(int32_t lhs, uint16_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs); }
/* 32 : 32 */ template<>
inline bool PrimitiveCmpGt(int32_t lhs, uint32_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint32_t>(lhs) > static_cast<uint32_t>(rhs); }
/* 32 : 64 */ template<>
inline bool PrimitiveCmpGt(int32_t lhs, uint64_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 32 : 8  */ template<>
inline bool PrimitiveCmpGt(int32_t lhs, int8_t rhs)
{ return (lhs) > static_cast<int32_t>(rhs); }
/* 32 : 16 */ template<>
inline bool PrimitiveCmpGt(int32_t lhs, int16_t rhs)
{ return (lhs) > static_cast<int32_t>(rhs); }
/* 32 : 32 */
/* 32 : 64 */ template<>
inline bool PrimitiveCmpGt(int32_t lhs, int64_t rhs)
{ return static_cast<int64_t>(lhs) > (rhs); }
/* 32 : F  */ template<>
inline bool PrimitiveCmpGt(int32_t lhs, float rhs)
{ return static_cast<float>(lhs) > (rhs); }
/* 32 : D  */ template<>
inline bool PrimitiveCmpGt(int32_t lhs, double rhs)
{ return static_cast<double>(lhs) > (rhs); }

// int64_t
/* 64 : 8  */ template<>
inline bool PrimitiveCmpGt(int64_t lhs, uint8_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 16 */ template<>
inline bool PrimitiveCmpGt(int64_t lhs, uint16_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 32 */ template<>
inline bool PrimitiveCmpGt(int64_t lhs, uint32_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 64 */ template<>
inline bool PrimitiveCmpGt(int64_t lhs, uint64_t rhs)
{ return lhs < 0 ?
		false : static_cast<uint64_t>(lhs) > static_cast<uint64_t>(rhs); }
/* 64 : 8  */ template<>
inline bool PrimitiveCmpGt(int64_t lhs, int8_t rhs)
{ return (lhs) > static_cast<int64_t>(rhs); }
/* 64 : 16 */ template<>
inline bool PrimitiveCmpGt(int64_t lhs, int16_t rhs)
{ return (lhs) > static_cast<int64_t>(rhs); }
/* 64 : 32 */ template<>
inline bool PrimitiveCmpGt(int64_t lhs, int32_t rhs)
{ return (lhs) > static_cast<int64_t>(rhs); }
/* 64 : 64 */
/* 64 : F  */ template<>
inline bool PrimitiveCmpGt(int64_t lhs, float rhs)
{ return static_cast<float>(lhs) > (rhs); }
/* 64 : D  */ template<>
inline bool PrimitiveCmpGt(int64_t lhs, double rhs)
{ return static_cast<double>(lhs) > (rhs); }

// float
/* F  : 8  */ template<>
inline bool PrimitiveCmpGt(float lhs, uint8_t rhs)
{ return (lhs) > static_cast<float>(rhs); }
/* F  : 16 */ template<>
inline bool PrimitiveCmpGt(float lhs, uint16_t rhs)
{ return (lhs) > static_cast<float>(rhs); }
/* F  : 32 */ template<>
inline bool PrimitiveCmpGt(float lhs, uint32_t rhs)
{ return (lhs) > static_cast<float>(rhs); }
/* F  : 64 */ template<>
inline bool PrimitiveCmpGt(float lhs, uint64_t rhs)
{ return (lhs) > static_cast<float>(rhs); }
/* F  : 8  */ template<>
inline bool PrimitiveCmpGt(float lhs, int8_t rhs)
{ return (lhs) > static_cast<float>(rhs); }
/* F  : 16 */ template<>
inline bool PrimitiveCmpGt(float lhs, int16_t rhs)
{ return (lhs) > static_cast<float>(rhs); }
/* F  : 32 */ template<>
inline bool PrimitiveCmpGt(float lhs, int32_t rhs)
{ return (lhs) > static_cast<float>(rhs); }
/* F  : 64 */ template<>
inline bool PrimitiveCmpGt(float lhs, int64_t rhs)
{ return (lhs) > static_cast<float>(rhs); }
/* F  : D  */ template<>
inline bool PrimitiveCmpGt(float lhs, double rhs)
{ return static_cast<double>(lhs) > (rhs); }

// double
/* D  : 8  */ template<>
inline bool PrimitiveCmpGt(double lhs, uint8_t rhs)
{ return (lhs) > static_cast<double>(rhs); }
/* D  : 16 */ template<>
inline bool PrimitiveCmpGt(double lhs, uint16_t rhs)
{ return (lhs) > static_cast<double>(rhs); }
/* D  : 32 */ template<>
inline bool PrimitiveCmpGt(double lhs, uint32_t rhs)
{ return (lhs) > static_cast<double>(rhs); }
/* D  : 64 */ template<>
inline bool PrimitiveCmpGt(double lhs, uint64_t rhs)
{ return (lhs) > static_cast<double>(rhs); }
/* D  : 8  */ template<>
inline bool PrimitiveCmpGt(double lhs, int8_t rhs)
{ return (lhs) > static_cast<double>(rhs); }
/* D  : 16 */ template<>
inline bool PrimitiveCmpGt(double lhs, int16_t rhs)
{ return (lhs) > static_cast<double>(rhs); }
/* D  : 32 */ template<>
inline bool PrimitiveCmpGt(double lhs, int32_t rhs)
{ return (lhs) > static_cast<double>(rhs); }
/* D  : 64 */ template<>
inline bool PrimitiveCmpGt(double lhs, int64_t rhs)
{ return (lhs) > static_cast<double>(rhs); }
/* D  : F  */ template<>
inline bool PrimitiveCmpGt(double lhs, float rhs)
{ return (lhs) > static_cast<double>(rhs); }

} // namespace Internal
} // namespace SimpleObjects
