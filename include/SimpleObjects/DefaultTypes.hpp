// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Null.hpp"
#include "Numeric.hpp"
#include "String.hpp"
#include "List.hpp"
#include "Dict.hpp"

#include "Object.hpp"
#include "HashableObject.hpp"

#include "ConstSequence.hpp"
#include "StaticDict.hpp"

#include "ToStringImpl.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

// ========== Basic Type Controll ==========

template<typename _KeyType, typename _ValType>
using MapType = std::unordered_map<_KeyType, _ValType>;

template<typename _ValType>
using VecType = std::vector<_ValType>;

// ========== Convenient types of Null ==========

using Null = NullImpl<std::string>;

inline const Null& None()
{
	static Null n;
	return n;
}

// ========== Convenient types of Numeric ==========

using Bool   = Numeric<bool    , std::string>;

using Int8   = Numeric<int8_t  , std::string>;
using Int16  = Numeric<int16_t , std::string>;
using Int32  = Numeric<int32_t , std::string>;
using Int64  = Numeric<int64_t , std::string>;

using UInt8  = Numeric<uint8_t , std::string>;
using UInt16 = Numeric<uint16_t, std::string>;
using UInt32 = Numeric<uint32_t, std::string>;
using UInt64 = Numeric<uint64_t, std::string>;

using Float  = Numeric<float   , std::string>;
using Double = Numeric<double  , std::string>;

// ========== Convenient types of String ==========

using String = StringCat<std::string, std::string>;

// ========== Convenient types of Object ==========

using Object = ObjectImpl<std::string>;

// ========== Convenient types of HashableObject ==========

using HashableObject = HashableObjectImpl<std::string>;

// ========== Convenient types of List ==========

using List = ListCat<VecType<Object>, std::string>;

// ========== Convenient types of Dict ==========

using Dict = DictCat<MapType<HashableObject, Object>, std::string>;

// ========== Convenient types of base classes ==========

using BaseObj = BaseObject<std::string>;
using HashableBaseObj = HashableBaseObject<std::string>;

using NumericBaseObj = NumericBaseObject<std::string>;
using StringBaseObj = StringBaseObject<char, std::string>;
using ListBaseObj = ListBaseObject<Object, std::string>;
using DictBaseObj = DictBaseObject<HashableObject, Object, std::string>;

// ========== Convenient types of static Dict ==========

using BaseRef = std::reference_wrapper<BaseObj>;
using HashableBaseKRef = HashableBaseReferenceWrapper<std::string, true>;

template<typename _ValType, _ValType ..._data>
using FromStrSeq = Internal::FromDataSeqImpl<String, _ValType, _data...>;
template<typename _StrSeq>
using StrKey = typename _StrSeq::template ToOther<FromStrSeq>::type;
template<int64_t _Val>
using Int64Key = StaticPrimitiveValue<Int64, _Val>;

template<typename _Tp>
using StaticDict = StaticDictImpl<_Tp, HashableBaseKRef, BaseRef, MapType>;

}//namespace SimpleObjects
