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

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

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

using List = ListCat<std::vector<Object>, std::string>;

// ========== Convenient types of Dict ==========

using Dict = DictCat<std::unordered_map<HashableObject, Object>, std::string>;

// ========== Convenient types of base classes ==========

using BaseObj = BaseObject<std::string>;
using HashableBaseObj = HashableBaseObject<std::string>;

using NumericBaseObj = NumericBaseObject<std::string>;
using StringBaseObj = StringBaseObject<char, std::string>;
using ListBaseObj = ListBaseObject<Object, std::string>;
using DictBaseObj = DictBaseObject<HashableObject, Object, std::string>;

}//namespace SimpleObjects
