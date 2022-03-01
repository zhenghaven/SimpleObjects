#pragma once

#include <string>

#include "ToString.hpp"

#include "Internal/rj_dtoa.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

//==================== Implementations ====================

template<>
inline std::string Internal::ToString(const bool& val)
{
	return val ? "true" : "false";
}

template<>
inline std::string Internal::ToString(const int8_t& val)
{
	return std::to_string(val);
}

template<>
inline std::string Internal::ToString(const int16_t& val)
{
	return std::to_string(val);
}

template<>
inline std::string Internal::ToString(const int32_t& val)
{
	return std::to_string(val);
}

template<>
inline std::string Internal::ToString(const int64_t& val)
{
	return std::to_string(val);
}

template<>
inline std::string Internal::ToString(const uint8_t& val)
{
	return std::to_string(val);
}

template<>
inline std::string Internal::ToString(const uint16_t& val)
{
	return std::to_string(val);
}

template<>
inline std::string Internal::ToString(const uint32_t& val)
{
	return std::to_string(val);
}

template<>
inline std::string Internal::ToString(const uint64_t& val)
{
	return std::to_string(val);
}

template<>
inline std::string Internal::ToString(const float& val)
{
	return Internal::dtoa<std::string>(val);
}

template<>
inline std::string Internal::ToString(const double& val)
{
	return Internal::dtoa<std::string>(val);
}

} // namespace SimpleObjects
