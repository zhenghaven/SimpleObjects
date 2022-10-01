// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once


#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

enum class ObjCategory
{
	Null,
	Bool,
	Integer,
	Real,
	String,
	List,
	Dict,
	StaticDict,
	Bytes,
};

enum class RealNumType
{
	Bool,
	Int8,
	Int16,
	Int32,
	Int64,
	UInt8,
	UInt16,
	UInt32,
	UInt64,
	Float,
	Double,
	// All enum type above are RESERVED for RealNumImpl<> class ONLY

	Other,  // for future extensions, use this
};

} // namespace SimpleObjects
