// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once


#include <cstdint>

#include "BasicDefs.hpp"


#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{


template<typename _ValType>
struct RealNumTraits
{
	static constexpr ObjCategory sk_cat();
	static constexpr const char* sk_catName();

	static constexpr RealNumType sk_numType();
	static constexpr const char* sk_numTypeName();

}; // struct RealNumTraits


template<>
inline constexpr ObjCategory RealNumTraits<bool    >::sk_cat() { return ObjCategory::Bool; }
template<>
inline constexpr ObjCategory RealNumTraits<int8_t  >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<int16_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<int32_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<int64_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<uint8_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<uint16_t>::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<uint32_t>::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<uint64_t>::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<float   >::sk_cat() { return ObjCategory::Real; }
template<>
inline constexpr ObjCategory RealNumTraits<double  >::sk_cat() { return ObjCategory::Real; }

template<>
inline constexpr const char* RealNumTraits<bool    >::sk_catName() { return "Bool";  }
template<>
inline constexpr const char* RealNumTraits<int8_t  >::sk_catName() { return "Integer";  }
template<>
inline constexpr const char* RealNumTraits<int16_t >::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<int32_t >::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<int64_t >::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<uint8_t >::sk_catName() { return "Integer";  }
template<>
inline constexpr const char* RealNumTraits<uint16_t>::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<uint32_t>::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<uint64_t>::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<float   >::sk_catName() { return "Real";  }
template<>
inline constexpr const char* RealNumTraits<double  >::sk_catName() { return "Real"; }

template<>
inline constexpr RealNumType RealNumTraits<bool    >::sk_numType() { return RealNumType::Bool;  }
template<>
inline constexpr RealNumType RealNumTraits<int8_t  >::sk_numType() { return RealNumType::Int8;  }
template<>
inline constexpr RealNumType RealNumTraits<int16_t >::sk_numType() { return RealNumType::Int16; }
template<>
inline constexpr RealNumType RealNumTraits<int32_t >::sk_numType() { return RealNumType::Int32; }
template<>
inline constexpr RealNumType RealNumTraits<int64_t >::sk_numType() { return RealNumType::Int64; }
template<>
inline constexpr RealNumType RealNumTraits<uint8_t >::sk_numType() { return RealNumType::UInt8;  }
template<>
inline constexpr RealNumType RealNumTraits<uint16_t>::sk_numType() { return RealNumType::UInt16; }
template<>
inline constexpr RealNumType RealNumTraits<uint32_t>::sk_numType() { return RealNumType::UInt32; }
template<>
inline constexpr RealNumType RealNumTraits<uint64_t>::sk_numType() { return RealNumType::UInt64; }
template<>
inline constexpr RealNumType RealNumTraits<float   >::sk_numType() { return RealNumType::Float;  }
template<>
inline constexpr RealNumType RealNumTraits<double  >::sk_numType() { return RealNumType::Double; }

template<>
inline constexpr const char* RealNumTraits<bool    >::sk_numTypeName() { return "Bool";  }
template<>
inline constexpr const char* RealNumTraits<int8_t  >::sk_numTypeName() { return "Int8";  }
template<>
inline constexpr const char* RealNumTraits<int16_t >::sk_numTypeName() { return "Int16"; }
template<>
inline constexpr const char* RealNumTraits<int32_t >::sk_numTypeName() { return "Int32"; }
template<>
inline constexpr const char* RealNumTraits<int64_t >::sk_numTypeName() { return "Int64"; }
template<>
inline constexpr const char* RealNumTraits<uint8_t >::sk_numTypeName() { return "UInt8";  }
template<>
inline constexpr const char* RealNumTraits<uint16_t>::sk_numTypeName() { return "UInt16"; }
template<>
inline constexpr const char* RealNumTraits<uint32_t>::sk_numTypeName() { return "UInt32"; }
template<>
inline constexpr const char* RealNumTraits<uint64_t>::sk_numTypeName() { return "UInt64"; }
template<>
inline constexpr const char* RealNumTraits<float   >::sk_numTypeName() { return "Float";  }
template<>
inline constexpr const char* RealNumTraits<double  >::sk_numTypeName() { return "Double"; }

} // namespace SimpleObjects
