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

//using Null = NullImpl;

inline const Null& None()
{
	static Null n;
	return n;
}

// ========== Convenient types of Numeric ==========

using Bool   = Numeric<bool    >;

using Int8   = Numeric<int8_t  >;
using Int16  = Numeric<int16_t >;
using Int32  = Numeric<int32_t >;
using Int64  = Numeric<int64_t >;

using UInt8  = Numeric<uint8_t >;
using UInt16 = Numeric<uint16_t>;
using UInt32 = Numeric<uint32_t>;
using UInt64 = Numeric<uint64_t>;

using Float  = Numeric<float   >;
using Double = Numeric<double  >;

// ========== Convenient types of String ==========

using String = StringCat<std::string>;

// ========== Convenient types of List ==========

using List = ListCat<std::vector<Object> >;

// ========== Convenient types of Dict ==========

using Dict = DictCat<std::unordered_map<HashableObject, Object> >;

}//namespace SimpleObjects
