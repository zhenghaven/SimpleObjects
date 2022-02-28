#pragma once

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{
namespace Internal
{

/**
 * @brief A generic template function to convert a value into a string
 *        representation
 *
 * @tparam _OutputType  The output string type
 * @tparam _InputType   The input value type
 * @param val           The input value
 * @return The output string
 */
template<typename _OutputType, typename _InputType>
_OutputType ToString(const _InputType& val);

template<typename _OutputType>
_OutputType ToString(const char* val);

template<typename _OutputType, typename _ItType>
_OutputType ToString(_ItType begin, _ItType end)
{
	return _OutputType(begin, end);
}

} // Internal
} // namespace SimpleObjects
